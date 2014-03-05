#include "Generator.h"

#include "../../../Common/Settings/Settings.h"
#include "../../../Common/ModuleLoader/ModuleLoader.h"
#include "../../../Common/Math/EigenProblems.h"

#include <QDir>
#include <QApplication>
#include <QTextStream>
#include <QtCore/qmath.h>

namespace
{
  const QString DEFAULT_HOST("SRVRAZRAB1");
  const QString DEFAULT_PORT("1972");
  const QString DEFAULT_NAMESPACE("FACES");
  const QString DEFAULT_USER("facedbuser");
  const QString DEFAULT_PASSWORD("facedbuser_password");

  const QString MODEL_NAME("Active Shape Model");
  const QString MODEL_FILE_NAME("Model.asm");
  
  void getLandmarks( QVector<common::models::LandmarkTriangle>& Landmarks, qint16 PointsCount )
  {
    using namespace common::models;
    Q_ASSERT(PointsCount == sizeof(TRIANGLE_INDEX)/sizeof(LandmarkTriangle));
    for (int index(0); index < PointsCount; index++)
    {
      Landmarks << TRIANGLE_INDEX[index];
    }
  }

  QVector<QVector2D> getWhiskers( const QVector<QPoint>& Shape ) 
  {
    QVector<QVector2D> shapeWhiskers;
    for (qint32 index(0); index < Shape.size(); index++)
    {
      using namespace common::models;
      QPoint prevPoint(Shape[TRIANGLE_INDEX[index].iPrev]);
      QPoint nextPoint(Shape[TRIANGLE_INDEX[index].iNext]);
      QPoint thisPoint(Shape[index]);
      QVector2D ntVector(nextPoint - thisPoint);
      QVector2D tpVector(thisPoint - prevPoint);

      QVector2D whisker(ntVector.normalized() - tpVector.normalized());
      Q_ASSERT(!qFuzzyCompare(whisker.x(), 0) || !qFuzzyCompare(whisker.y(), 0));
      whisker /= qMax(qAbs(whisker.x()), qAbs(whisker.y()));
      shapeWhiskers << whisker;
    }
    return shapeWhiskers;
  }
}

Generator::Generator( const QStringList& Parameters )
{
  getDatabase();
  Info = Database->getInfo();

  QObject::connect(&ConfigObj, SIGNAL(log(QString)), this, SLOT(log(QString)));
  STDOut.open(stdout, QIODevice::WriteOnly);

  parseParameters(Parameters);
}

Generator::~Generator(void)
{
}

void Generator::run()
{
  //////////////////////////////////////////////////////////////////////////
  Info->setNeedModelUpdate(algorithms::AlgorithmsVectorizationActiveShapeModel, true);
  //////////////////////////////////////////////////////////////////////////

  if (!Info->getNeedModelUpdate(algorithms::AlgorithmsVectorizationActiveShapeModel))
    return;

  getFacesIDs();
  if (FacesIDs.isEmpty())
    return;

  generate();

  Info->setNeedModelUpdate(algorithms::AlgorithmsVectorizationActiveShapeModel, false);
}

void Generator::getDatabase()
{
  QDir pluginsDir(qApp->applicationDirPath());
  using namespace common;
  bool pluginsDirExist(pluginsDir.cd(Settings().get(Settings::SettingsPluginsPath, "Plugins").toString()));
  Q_ASSERT(pluginsDirExist);
  DBList databases(loadModules<DBInterface, DBList>(pluginsDir));
  Q_ASSERT(!databases.isEmpty());
  Database = databases.first();
  openDBConnection();
}

void Generator::openDBConnection()
{
  Q_ASSERT(Database);
  common::Settings settings;
  QString vHost(settings.get(common::Settings::SettingsDatabaseHost, DEFAULT_HOST).toString());
  QString vPort(settings.get(common::Settings::SettingsDatabasePort, DEFAULT_PORT).toString());
  QString vNamespace(settings.get(common::Settings::SettingsDatabaseNamespace, DEFAULT_NAMESPACE).toString());
  QString vUser(settings.get(common::Settings::SettingsDatabaseUser, DEFAULT_USER).toString());
  QString vPassword(settings.get(common::Settings::SettingsDatabasePassword, DEFAULT_PASSWORD).toString());
  Database->openConnection(vHost, vPort, vNamespace, vUser, vPassword);
}

void Generator::parseParameters( const QStringList& Parameters )
{
  log(tr("Parsing input parameters..."));
  int configParameterIndex(Parameters.indexOf("/c"));
  if (configParameterIndex != -1 && configParameterIndex < Parameters.size() - 1)
  {
    ConfigObj.read(Parameters[configParameterIndex + 1]);
  }
  ConfigObj.logConfiguration();
}

void Generator::getFacesIDs()
{
  FacesIDs.clear();
  QStringList photosIDList(Database->getIDs(ConfigObj.Photos));
  QStringList facesIDList(Database->getIDs(ConfigObj.Faces));
  QStringList personsIDList(Database->getIDs(ConfigObj.Persons));
  foreach(const QString& faceID, facesIDList)
  {
    QSharedPointer<DBFaces> dbFace(Database->getFace(faceID));
    QSharedPointer<DBPhotos> dbPhoto(dbFace->getPhoto());
    QSharedPointer<DBPersons> dbPersons(dbFace->getPerson());
    if (photosIDList.contains(dbPhoto->getID()) && personsIDList.contains(dbPersons->getID()))
      FacesIDs << faceID;
  }
}

void Generator::generate()
{
  log(tr("Generating model..."));
  
  using namespace common::models;
  ActiveShapeModel model;
  model << ConfigObj;

  getMeanShape(model.Shape);
  getPrincipalComponents(model.PrincComp, model.Shape);
  qint16 pointsCount(model.Shape.Value.size());
  getLandmarks(model.Landmarks, pointsCount);
  getProfiles(model.PyrLevels, pointsCount);

  saveModel(model);
}

void Generator::getMeanShape( common::models::MeanShape& Shape )
{
  log(tr("\tCalculating mean shape..."));
  log(tr("\t\tAligning shapes in max %1 iterations:").arg(ConfigObj.MeanShapeSearchIterations));
  QList<QSharedPointer<DBShapes> > dbShapesList(Database->getFace(FacesIDs.first())->getShapes());
  Q_ASSERT(dbShapesList.size() == 1);
  int pointsCount(dbShapesList.first()->getShape().size());
  Shape.Value.resize(pointsCount);
  QVector<qreal> weights(pointsCount, 1.0f);
  bool firstIteration(true);
  qreal prevDistance(FLT_MAX);
  qint64 shapeWidth(0);
  qint64 extFacesCount(0);
  QVector<qint64> detectorsWidth(algorithms::AlgorithmsDetectorsEnd);
  QVector<qint64> detectorsCount(algorithms::AlgorithmsDetectorsEnd);
  using namespace common::models;
  for(quint32 searchIteration(0); searchIteration < ConfigObj.MeanShapeSearchIterations; searchIteration++)
  {
    QVector<QPointF> prevMeanShape(Shape.Value);
    Shape.Value = QVector<QPointF>(pointsCount);
    foreach(const QString& faceID, FacesIDs)
    {
      ExtendedFace extFace(getExtendedFace(faceID, ExtractShape | ExtractDetectors));
      foreach(const Config::Extend type, extFace.Shapes.keys())
      {
        const QVector<QPoint>& shape(extFace.Shapes[type]);
        QVector<QPointF> centeredShape(getCenteredShape(shape));
        if (firstIteration)
        {
          shapeWidth += getShapeWidth(shape);
          QPointF shapeCenter(getShapeCenter(shape));
          const AlgDetOutputMap detectors(extFace.Detectors[type]);
          foreach(const AlgType& detType, detectors.keys())
          {
            const QRect& detRect(detectors.value(detType).Rectangle);
            detectorsWidth[detType] += detRect.width();
            detectorsCount[detType]++;
            Shape.Detectors[detType].Shift += shapeCenter - detRect.center();
          }
          extFacesCount++;
        }
        else
        {
          alignShape(centeredShape, prevMeanShape, weights);
        }

        for (int pointIndex(0); pointIndex < pointsCount; pointIndex++)
        {
          Shape.Value[pointIndex] += centeredShape[pointIndex];
        }
      }
    }
    qreal distance(0);
    for (int pointIndex(0); pointIndex < pointsCount; pointIndex++)
    {
      Shape.Value[pointIndex] /= extFacesCount;
      distance += (Shape.Value[pointIndex] - prevMeanShape[pointIndex]).manhattanLength();
    }
    if (distance > prevDistance)
    {
      Shape.Value = prevMeanShape;
      break;
    }
    log(tr("\t\t\tIteration %1 distance: %2").arg(searchIteration+1).arg(distance));
    prevDistance = distance;
    firstIteration = false;
  }

  Shape.FaceWidth = static_cast<qreal>(shapeWidth) / static_cast<qreal>(extFacesCount);
  using namespace algorithms;
  Shape.Detectors[AlgorithmsDetectorsBegin].Scale = 1.0; // scale for mean shape
  Shape.Detectors[AlgorithmsDetectorsBegin].Shift = QPointF(); // shift for mean shape
  for (int index(AlgorithmsDetectorsBegin + 1); index < AlgorithmsDetectorsEnd; index++)
  {
    const qint64& detCount(detectorsCount[index]);
    const qreal detWidth(static_cast<qreal>(detectorsWidth[index]) / static_cast<qreal>(detCount));
    Shape.Detectors[index].Scale = Shape.FaceWidth / detWidth;
    Shape.Detectors[index].Shift /= detCount;
  }
}

void Generator::getPrincipalComponents( common::models::PrincipalComponents& PrincComp, const common::models::MeanShape& Shape )
{
  log(tr("\tCalculating principal components..."));
  log(tr("\t\tCalculating covariation matrix..."));
  using namespace common;
  using namespace common::models;
  const Matrix<modelT> meanContour(Shape.Value);
  Matrix<modelT> covMatrix(meanContour.rows(), meanContour.rows());
  QVector<qreal> weights(Shape.Value.size(), 1.0f);
  qint64 extFacesCount(0);
  foreach(const QString& faceID, FacesIDs)
  {
    ExtendedFace extFace(getExtendedFace(faceID, ExtractShape));
    foreach(const QVector<QPoint>& faceShape, extFace.Shapes)
    {
      QVector<QPointF> centeredShape(getCenteredShape(faceShape));
      alignShape(centeredShape, Shape.Value, weights);
      Matrix<modelT> contour(centeredShape);
      contour -= meanContour;
      covMatrix += contour.xxT();
      extFacesCount++;
    }
  }
  covMatrix /= extFacesCount - 1;

  log(tr("\t\tCalculating eigen values and vectors..."));
  Matrix<qreal>& eigenValues(PrincComp.EigenValues);
  Matrix<modelT>& eigenVectors(PrincComp.EigenVectors);
  int pcaResult(EigenValuesVectorsSym(covMatrix, eigenValues, eigenVectors));
  Q_ASSERT(pcaResult == ippStsNoErr);
}

void Generator::getProfiles( QVector<common::models::Profile>& PyrLevels, qint16 PointsCount )
{
  using namespace common::models;
  log(tr("\tCalculating points profiles..."));
  clearProfiles(PyrLevels, PointsCount);
  getProfilesMean(PyrLevels);
  getProfilesCovar(PyrLevels);
}

void Generator::clearProfiles( QVector<common::models::Profile>& PyrLevels, qint16 PointsCount )
{
  log(tr("\t\tAllocating space for level profiles data..."));
  using namespace common::models;
  for (quint8 level(0); level < ConfigObj.Scale.Levels; level++)
  {
    QVector<Profile::PointStatistic>& points(PyrLevels[level].Points);
    points.resize(PointsCount);
    using namespace common::models;
    qint32 vectorSize1D(ConfigObj.ProfileSize[Profile::Profile1D]);
    qint32 vectorSize2D(ConfigObj.ProfileSize[Profile::Profile2D] * ConfigObj.ProfileSize[Profile::Profile2D]);
    for (qint16 index(0); index < PointsCount; index++)
    {
      points[index].ProfileType[Profile::Profile1D].Mean.resize(vectorSize1D);
      points[index].ProfileType[Profile::Profile1D].InvCovar.resize(vectorSize1D, vectorSize1D);
      points[index].ProfileType[Profile::Profile2D].Mean.resize(vectorSize2D);
      points[index].ProfileType[Profile::Profile2D].InvCovar.resize(vectorSize2D, vectorSize2D);
    }
  }
}

void Generator::getProfilesMean( QVector<common::models::Profile>& PyrLevels )
{
  log(tr("\t\t\tCalculating profiles mean..."));
  using namespace common::models;
  qint64 extFacesCount(0);
  foreach(const QString& faceID, FacesIDs)
  {
    ExtendedFace extFace(getExtendedFace(faceID, ExtractShape | ExtractImage));
    foreach(const Config::Extend& type, extFace.Shapes.keys())
    {
      const QVector<QPoint>& shape(extFace.Shapes[type]);
      const common::Frame& image(extFace.Images[type]);
      const QVector<QVector2D> whiskers(getWhiskers(shape));
      for (quint8 level(0); level < ConfigObj.Scale.Levels; level++)
      {
        QVector<Profile::PointStatistic>& points(PyrLevels[level].Points);
        qreal scaleFactor(1.0 / qPow(ConfigObj.Scale.Factor, level));
        common::Frame scaledImage(image.scaled(scaleFactor));
        const QVector<QPointF> scaledShape(getScaledShape(shape, scaleFactor));
        for (qint32 index(0); index < points.size(); index++)
        {
          points[index].ProfileType[Profile::Profile1D].Mean += get1DProfile(scaledImage, scaledShape[index], whiskers[index]);
          points[index].ProfileType[Profile::Profile2D].Mean += get2DProfile(scaledImage, scaledShape[index]);
        }
      }
      extFacesCount++;
    }
  }
  for (quint8 level(0); level < ConfigObj.Scale.Levels; level++)
  {
    QVector<Profile::PointStatistic>& points(PyrLevels[level].Points);
    for (qint32 index(0); index < points.size(); index++)
    {
      points[index].ProfileType[Profile::Profile1D].Mean /= extFacesCount;
      points[index].ProfileType[Profile::Profile2D].Mean /= extFacesCount;
    }
  }
}

common::Matrix<qreal> Generator::get1DProfile( const common::Frame& Image, const QPointF& Point, const QVector2D& Whisker )
{
  using namespace common::models;
  const int profileLength(ConfigObj.ProfileSize[Profile::Profile1D]);
  const int profileLength_2(profileLength / 2);
  common::Matrix<qreal> profile(profileLength);
  QPoint pixelCoord((Point + ((-profileLength_2-1) * Whisker).toPointF()).toPoint());
  int prevIntensity(Image.valid(pixelCoord) ? qGray(Image.pixel(pixelCoord)) : 0);
  qreal intensityAbsSum(0);
  for (int profileIndex(-profileLength_2), matrixIndex(0); matrixIndex < profileLength; profileIndex++, matrixIndex++)
  {
    pixelCoord = (Point + (profileIndex * Whisker).toPointF()).toPoint();
    int intensity(Image.valid(pixelCoord) ? qGray(Image.pixel(pixelCoord)) : 0);
    int intensityDelta(intensity - prevIntensity);
    profile.set(static_cast<qreal>(intensityDelta), matrixIndex);
    intensityAbsSum += qAbs(intensityDelta);
    prevIntensity = intensity;
  }
  intensityAbsSum /= profileLength;
  profile /= intensityAbsSum;
  return profile;
}

common::Matrix<qreal> Generator::get2DProfile( const common::Frame& Image, const QPointF& Point )
{
  using namespace common::models;
  const int profileLength(ConfigObj.ProfileSize[Profile::Profile2D]);
  const int profileLength_2(profileLength / 2);
  common::Matrix<qreal> profile(profileLength * profileLength);
  const qreal shapeConstant(100);
  for (int y(-profileLength_2), matrixY(0), matrixIndex(0); matrixY < profileLength; y++, matrixY++)
  {
    for (int x(-profileLength_2), matrixX(0); matrixX < profileLength; x++, matrixX++, matrixIndex++)
    {
      const QPoint pixelCoord(Point.toPoint() + QPoint(x, y));
      const int intensity(Image.valid(pixelCoord) ? qGray(Image.pixel(pixelCoord)) : 0);
      const qreal profileValue(static_cast<qreal>(intensity) / (static_cast<qreal>(qAbs(intensity)) + shapeConstant));
      profile.set(profileValue, matrixIndex);
    }
  }
  return profile;
}

void Generator::getProfilesCovar( QVector<common::models::Profile>& PyrLevels )
{
  log(tr("\t\t\tCalculating profiles covariation..."));
  using namespace common::models;
  qint16 pointsCount(PyrLevels[0].Points.size());
  qint64 extFacesCount(0);
  foreach(const QString& faceID, FacesIDs)
  {
    ExtendedFace extFace(getExtendedFace(faceID, ExtractShape | ExtractImage));
    foreach(const Config::Extend type, extFace.Shapes.keys())
    {
      const QVector<QPoint>& shape(extFace.Shapes[type]);
      const common::Frame& image(extFace.Images[type]);
      const QVector<QVector2D> whiskers(getWhiskers(shape));
      for (quint8 level(0); level < ConfigObj.Scale.Levels; level++)
      {
        QVector<Profile::PointStatistic>& points(PyrLevels[level].Points);
        qreal scaleFactor(1.0 / qPow(ConfigObj.Scale.Factor, level));
        common::Frame scaledImage(image.scaled(scaleFactor));
        const QVector<QPointF> scaledShape(getScaledShape(shape, scaleFactor));
        for (qint32 index(0); index < pointsCount; index++)
        {
          common::Matrix<qreal>& mean1D(points[index].ProfileType[Profile::Profile1D].Mean);
          common::Matrix<qreal>& mean2D(points[index].ProfileType[Profile::Profile2D].Mean);
          common::Matrix<qreal> profile1D(get1DProfile(scaledImage, scaledShape[index], whiskers[index]));
          common::Matrix<qreal> profile2D(get2DProfile(scaledImage, scaledShape[index]));
          profile1D -= mean1D;
          profile2D -= mean2D;
          points[index].ProfileType[Profile::Profile1D].InvCovar += profile1D.xxT();
          points[index].ProfileType[Profile::Profile2D].InvCovar += profile2D.xxT();
        }
      }
      extFacesCount++;
    }
  }
  extFacesCount--;
  for (quint8 level(0); level < ConfigObj.Scale.Levels; level++)
  {
    QVector<Profile::PointStatistic>& points(PyrLevels[level].Points);
    int levelShift(level * pointsCount);
    for (qint32 index(0); index < pointsCount; index++)
    {
      points[index].ProfileType[Profile::Profile1D].InvCovar /= extFacesCount;
      points[index].ProfileType[Profile::Profile2D].InvCovar /= extFacesCount;
      points[index].ProfileType[Profile::Profile1D].InvCovar.invert();
      points[index].ProfileType[Profile::Profile2D].InvCovar.invert();
    }
  }
}

Generator::ExtendedFace Generator::getExtendedFace( const QString& FaceID, Extract DataType )
{
  ExtendedFace extFace;
  QSharedPointer<DBFaces> dbFace(Database->getFace(FaceID));
  if (DataType.testFlag(ExtractImage))
  {
    extFace.Images.insert(Config::NoExtend, dbFace->getPhoto()->getImage());
  }
  if (DataType.testFlag(ExtractShape))
  {
    QList<QSharedPointer<DBShapes> > dbShapesList(dbFace->getShapes());
    Q_ASSERT(dbShapesList.size() == 1);
    QSharedPointer<DBShapes> dbShape(dbShapesList.first());
    extFace.Shapes.insert(Config::NoExtend, dbShape->getShape());
  }
  if (DataType.testFlag(ExtractDetectors))
  {
    QList<QSharedPointer<DBDetectors> > dbDetectorsList(dbFace->getDetectors());
    AlgDetOutputMap originalDetectors;
    foreach(QSharedPointer<DBDetectors> detector, dbDetectorsList)
    {
      originalDetectors.insert(detector->getType(), detector->getLocation());
    }
    extFace.Detectors.insert(Config::NoExtend, originalDetectors);
  }

  if (ConfigObj.Extensions.testFlag(Config::MirrorExtend))
  {
    if (!extFace.Images.isEmpty())
    {
      extFace.Images.insert(Config::MirrorExtend, extFace.Images[Config::NoExtend].mirrored());
    }
    const int imageWidth(dbFace->getPhoto()->getWidth());
    using namespace common::models;
    if (!extFace.Shapes.isEmpty())
    {
      extFace.Shapes.insert(Config::MirrorExtend, getMirroredShape(extFace.Shapes[Config::NoExtend], imageWidth));
    }
    if (!extFace.Detectors.isEmpty())
    {
      extFace.Detectors.insert(Config::MirrorExtend, getMirroredDetectors(extFace.Detectors[Config::NoExtend], imageWidth));
    }
  }
  return extFace;
}

void Generator::saveModel( common::models::ActiveShapeModel& model )
{
  QDir modelDir(qApp->applicationDirPath());
  using namespace common;
  Settings settings;
  QString dataPath(settings.get(Settings::SettingsDataVectorizationPath).toString().append("/"));
  dataPath += MODEL_NAME;
  bool dirExist(modelDir.cd(dataPath));
  Q_ASSERT(dirExist);
  QString modelFilePath(settings.get(Settings::SettingsVectorizationActiveShapeModelFileName, MODEL_FILE_NAME).toString());
  model.write(modelDir.absolutePath() + "/" + modelFilePath);
}

void Generator::log( QString Msg )
{
  QTextStream(&STDOut) << Msg << endl;
  Log.append(Msg);
}
