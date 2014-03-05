#include "FaceDBShell.h"

#include "../../Algorithms/Common/Processor.h"

#include "../../Common/Settings/Settings.h"
#include "../../Common/CRC/CRC64.h"
#include "../../Common/ModuleLoader/ModuleLoader.h"
#include "../../Common/Models/ActiveShapeModel/Shape.h"

#include <QDir>
#include <QPluginLoader>
#include <QFileDialog>

namespace
{
  const QString DEFAULT_HOST("SRVRAZRAB1");
  const QString DEFAULT_PORT("1972");
  const QString DEFAULT_NAMESPACE("FACES");
  const QString DEFAULT_USER("facedbuser");
  const QString DEFAULT_PASSWORD("facedbuser_password");
}

FaceDBShell::FaceDBShell(QWidget *parent, Qt::WFlags flags)
    : QMainWindow(parent, flags),
      Context(new AlgContext),
      photoMiddleBrightness(0),
      IsNewImage(false)
{
  ui.setupUi(this);

  initContext();
  loadPlugins();
  loadAlgorithms();
  openDBConnection();
  initUI();
}

FaceDBShell::~FaceDBShell()
{
}

void FaceDBShell::initContext()
{
  using namespace common;
  Settings settings;
  Context->Detection.In.HaarCascadeClassifierFileName =
    settings.get(Settings::SettingsDetectionViolaJonesClassifier, "haarcascade_frontalface_default.xml").toString();
  Context->Detection.In.ScaleFactor = settings.get(Settings::SettingsDetectionScaleFactor, 1.1f).toReal();
}


void FaceDBShell::loadPlugins()
{
  QDir pluginsDir(qApp->applicationDirPath());
  bool pluginsDirExist(pluginsDir.cd(Settings().get(Settings::SettingsPluginsPath, "Plugins").toString()));
  Q_ASSERT(pluginsDirExist);
  SrcList sources(loadModules<SrcInterface, SrcList>(pluginsDir));
  DBList databases(loadModules<DBInterface, DBList>(pluginsDir));
  Q_ASSERT(!sources.isEmpty() && !databases.isEmpty());
  Database = databases.first();
  foreach(SrcInterface* src, sources)
  {
    if (src->getName() == tr("Image"))
    {
      Source = src;
      break;
    }
  }
  Q_ASSERT(Source && Database);
}

void FaceDBShell::loadAlgorithms()
{
  QDir algorithmsDir(qApp->applicationDirPath());
  using namespace common;
  bool algorithmsDirExist(algorithmsDir.cd(Settings().get(Settings::SettingsAlgorithmsPath, "Algorithms").toString()));
  Q_ASSERT(algorithmsDirExist);
  Algorithms = loadModules<AlgInterface, AlgMap>(algorithmsDir);
  foreach(AlgInterface* algorithm, Algorithms.values())
  {
    bool initOK(algorithm->init(*Context));
    Q_ASSERT(initOK);
  }
}

void FaceDBShell::openDBConnection()
{
  Q_ASSERT(Database);
  using namespace common;
  Settings settings;
  QString vHost(settings.get(Settings::SettingsDatabaseHost, DEFAULT_HOST).toString());
  QString vPort(settings.get(Settings::SettingsDatabasePort, DEFAULT_PORT).toString());
  QString vNamespace(settings.get(Settings::SettingsDatabaseNamespace, DEFAULT_NAMESPACE).toString());
  QString vUser(settings.get(Settings::SettingsDatabaseUser, DEFAULT_USER).toString());
  QString vPassword(settings.get(Settings::SettingsDatabasePassword, DEFAULT_PASSWORD).toString());
  Database->openConnection(vHost, vPort, vNamespace, vUser, vPassword);
}

void FaceDBShell::initUI()
{
  using namespace algorithms;
  AlgMap::ConstIterator detAlg(Algorithms.lowerBound(AlgorithmsDetectorsBegin));
  AlgMap::ConstIterator detEnd(Algorithms.upperBound(AlgorithmsDetectorsEnd));
  for (; detAlg != detEnd; detAlg++)
  {
    ui.selectDetector->addItem((*detAlg)->getName(), int(detAlg.key()));
  }
}

QString FaceDBShell::getFilters()
{
  Q_ASSERT(Source);
  const QString extsSeparator(";");
  QString filters(Source->getName() + tr(" files ("));
  QStringList filtersExts(Source->getFilters());
  Q_ASSERT(!filtersExts.empty());
  foreach(QString ext, filtersExts)
  {
    ext += extsSeparator;
    filters += ext;
  }
  filters.remove(filters.lastIndexOf(extsSeparator), extsSeparator.size());
  filters += ")";
  return filters;
}

QString FaceDBShell::getImageIDinDB()
{
  Frame photo;
  Source->getCurrentFrame(photo);
  PhotosQueryMap query;
  using namespace plugins::databases;
  query.insert(Photos::QueryWidth, photo.width());
  query.insert(Photos::QueryHeight, photo.height());
  query.insert(Photos::QueryCRC, photo.crc());
  QStringList ids(Database->getIDs(query));
  Q_ASSERT(ids.size() <= 1);
  return ids.isEmpty() ? QString() : ids[0];
}

void FaceDBShell::processImage()
{
  QString imageID/*(getImageIDinDB())*/;
  Image = Database->getPhoto(imageID);
  IsNewImage = imageID.isNull();
  if (IsNewImage)
  {
    findFaces();
    setNewImageInfo();
  }
  else
  {
    log(1, tr("This photo is already in database."));
  }
  uiUpdateImageInfo();
  
  processFaces();
}

void FaceDBShell::processFaces()
{
  if (IsNewImage)
  {
    qint16 facesCount(getFacesCount());
    for (int faceIndex(0); faceIndex < facesCount; faceIndex++)
    {
      QSharedPointer<DBFaces> dbFace(Database->getFace());
      dbFace->setPhoto(Image);
    }
  }
  uiUpdatePersonsInfo();
  uiUpdateFacesInfo();

  processDetectors();
} 


void FaceDBShell::processDetectors()
{
  if (IsNewImage)
  {
    setDefaultLocations();
    setRestLocations();
  }
  uiUpdateDetectorsInfo();

  processShapes();
}

void FaceDBShell::processShapes()
{
  if (IsNewImage)
  {
    log(0, tr("Searching shapes..."));
    Frame photo;
    Source->getCurrentFrame(photo);
    using namespace algorithms;
    AlgType detToUse(ui.selectDetector->itemData(ui.selectDetector->currentIndex()).toInt());
    Context->Vectorization.Shape.In.Detector = detToUse;
    process(*Context, photo, Algorithms, AlgorithmsVectorizationsBegin, AlgorithmsVectorizationsEnd);
    setShapes();
  }
  uiUpdateShapesInfo();
}

void FaceDBShell::setNewImageInfo()
{
  Frame photo;
  Source->getCurrentFrame(photo);
  Image->setWidth(photo.width());
  Image->setHeight(photo.height());
  Image->setColorDepth(photo.getColorDepth());
  if (photoMiddleBrightness == 0)
  {
    photoMiddleBrightness = photo.getMiddleBrightness();
  }
  Image->setMiddleBrightness(photoMiddleBrightness);
  Image->setImage(photo);
  Image->setCRC(photo.crc());
}

void FaceDBShell::setDefaultLocations()
{
  AlgType defaultDetector(getMaxFacesCountDetector());
  QList<AlgDetOutput> defaultLocations(Context->Detection.Out.values(defaultDetector));
  QList<QSharedPointer<DBFaces> > dbFaces(Image->getFaces());
  Q_ASSERT(dbFaces.size() == defaultLocations.size());
  QList<AlgDetOutput>::ConstIterator location(defaultLocations.constBegin());
  QList<QSharedPointer<DBFaces> >::ConstIterator dbFace(dbFaces.constBegin());
  for (; dbFace != dbFaces.constEnd() && location != defaultLocations.constEnd(); dbFace++, location++)
  {
    QSharedPointer<DBDetectors> dbDetector(Database->getDetector());
    dbDetector->setType(defaultDetector);
    dbDetector->setLocation(*location);
    dbDetector->setFace(*dbFace);
  }
}

void FaceDBShell::setRestLocations()
{
  typedef QList<QSharedPointer<DBDetectors> >::const_iterator cDetIterator;
  AlgDetOutputMap& locsMap(Context->Detection.Out);
  typedef AlgDetOutputMap::const_iterator cLocIterator;
  using namespace algorithms;
  cLocIterator lastLoc(locsMap.upperBound(AlgorithmsDetectorsEnd));
  AlgType defaultDetector(getMaxFacesCountDetector());
  QList<QSharedPointer<DBFaces> > dbFaces(Image->getFaces());
  for (cLocIterator loc(locsMap.lowerBound(AlgorithmsDetectorsBegin)); loc != lastLoc; loc++)
  {
    if (loc.key() == defaultDetector)
      continue;
    QPointF locCenter(loc->Rectangle.center());
    qreal minDistance(FLT_MAX);
    QSharedPointer<DBFaces> closestDBFace;
    foreach(QSharedPointer<DBFaces> dbFace, dbFaces)
    {
      QPointF detCenter(dbFace->getDetectors().first()->getLocation().Rectangle.center());
      qreal distance((locCenter - detCenter).manhattanLength());
      if (distance < minDistance)
      {
        minDistance = distance;
        closestDBFace = dbFace;
      }
    }
    Q_ASSERT(!closestDBFace.isNull());
    if (!closestDBFace.isNull())
    {
      QSharedPointer<DBDetectors> dbDetector(Database->getDetector());
      dbDetector->setType(loc.key());
      dbDetector->setLocation(*loc);
      dbDetector->setFace(closestDBFace);
    }
  }
}

void FaceDBShell::setShapes()
{
  using namespace algorithms;
  using namespace common::models;
  QList<QSharedPointer<DBFaces> > dbFaces(Image->getFaces());
  foreach(const AlgVecShpOutput& shape, Context->Vectorization.Shape.Out.values(AlgorithmsVectorizationActiveShapeModel))
  {
    qreal minDistance(FLT_MAX);
    QPointF shapeCenter(getShapeCenter(shape.Value));
    QSharedPointer<DBFaces> closestDBFace;
    foreach(QSharedPointer<DBFaces> dbFace, dbFaces)
    {
      QPointF detCenter(dbFace->getDetectors().first()->getLocation().Rectangle.center());
      qreal distance((shapeCenter - detCenter).manhattanLength());
      if (distance < minDistance)
      {
        minDistance = distance;
        closestDBFace = dbFace;
      }
    }
    Q_ASSERT(!closestDBFace.isNull());
    if (!closestDBFace.isNull())
    {
      closestDBFace->setBetweenEyesDistance(getBetweenEyesDistance(shape.Value));
      QList<QSharedPointer<DBShapes> > dbFaceShapes(closestDBFace->getShapes());
      Q_ASSERT(dbFaceShapes.size() <= 1);
      QSharedPointer<DBShapes> dbShape(dbFaceShapes.isEmpty() ? Database->getShape() : dbFaceShapes.first());
      dbShape->setShape(shape.Value);
      dbShape->setFace(closestDBFace);
    }
  }
}

void FaceDBShell::findFaces()
{
  log(0, tr("Searching faces..."));
  Frame photo;
  Source->getCurrentFrame(photo);
  qreal minObjectSize = qreal(ui.minFaceSizeSlider->value()) / 100.0f;
  Context->Detection.In.MinObjectSize = QSize(photo.width(), photo.height()) * minObjectSize;
  using namespace algorithms;
  process(*Context, photo, Algorithms, AlgorithmsDetectorsBegin, AlgorithmsDetectorsEnd);
  Image->setFacesCount(getFacesCount());
  uiEnableControls();
}

qint16 FaceDBShell::getFacesCount()
{
  return Context->Detection.Out.count(getMaxFacesCountDetector());
}

AlgType FaceDBShell::getMaxFacesCountDetector()
{
  using namespace algorithms;
  Type res(AlgorithmsDetectorsBegin);
  int facesCount(0);
  for (int algType(AlgorithmsDetectorsBegin); algType != AlgorithmsDetectorsEnd; algType++)
  {
    int algFacesCount(Context->Detection.Out.count(static_cast<Type>(algType)));
    if (algFacesCount > facesCount)
    {
      facesCount = algFacesCount;
      res = static_cast<Type>(algType);
    }
  }
  return res;
}

qint16 FaceDBShell::getFaceIndex()
{
  return ui.faceIndex->value();
}

void FaceDBShell::uiUpdateImageInfo()
{
  ui.imageWidth->setText(QString::number(Image->getWidth()));
  ui.imageHeight->setText(QString::number(Image->getHeight()));
  ui.imageColorDepth->setText(QString::number(Image->getColorDepth()));
  ui.imageBrightness->setText(QString::number(Image->getMiddleBrightness()));
  ui.mainFrame->setFrame(Image->getImage());
  ui.imageCRC->setText(QString::number(Image->getCRC(), 16));
}

void FaceDBShell::uiUpdateFacesInfo()
{
  qint16 facesCount(Image->getFacesCount());
  if (facesCount <= 0)
    return;
  ui.facesCount->setText(QString::number(facesCount));
  ui.faceIndex->setValue(0);
  ui.faceIndex->setMaximum(qMax(facesCount - 1, 0));

  QList<QSharedPointer<DBFaces> > dbFaces(Image->getFaces());
  Q_ASSERT(dbFaces.size() == Image->getFacesCount());
  QSharedPointer<DBFaces> dbFace(dbFaces[getFaceIndex()]);
  ui.age->setValue(dbFace->getAge());
  using namespace plugins::databases;
  ui.closedForehead->setChecked(dbFace->getClosedForehead() == BoolTrue);
  ui.closedEyebrow->setChecked(dbFace->getClosedEyebrow() == BoolTrue);
  ui.glasses->setChecked(dbFace->getGlasses() == BoolTrue);
  ui.moustache->setChecked(dbFace->getMoustache() == BoolTrue);
  ui.beard->setChecked(dbFace->getBeard() == BoolTrue);
  switch (dbFace->getOrientation())
  {
  case Orientation12: ui.orientation12->setChecked(true); break;
  case Orientation13: ui.orientation13->setChecked(true); break;
  case Orientation14: ui.orientation14->setChecked(true); break;
  case Orientation21: ui.orientation21->setChecked(true); break;
  case Orientation22: ui.orientation22->setChecked(true); break;
  case Orientation23: ui.orientation23->setChecked(true); break;
  case Orientation24: ui.orientation24->setChecked(true); break;
  case Orientation25: ui.orientation25->setChecked(true); break;
  case Orientation32: ui.orientation32->setChecked(true); break;
  case Orientation33: ui.orientation33->setChecked(true); break;
  case Orientation34: ui.orientation34->setChecked(true); break;
  default: ui.orientation23->setChecked(true); break;
  }
}

void FaceDBShell::uiUpdatePersonsInfo()
{
  QList<QSharedPointer<DBFaces> > dbFaces(Image->getFaces());
  using namespace plugins::databases;
  foreach(QSharedPointer<DBFaces> dbFace, dbFaces)
  {
    ui.gender->setChecked(dbFace->getPerson()->getGender() == BoolTrue);
  }
}

void FaceDBShell::uiUpdateDetectorsInfo()
{
  QList<QSharedPointer<DBFaces> > dbFaces(Image->getFaces());
  foreach(QSharedPointer<DBFaces> dbFace, dbFaces)
  {
    foreach(QSharedPointer<DBDetectors> detector, dbFace->getDetectors())
    {
      ui.mainFrame->addRect(detector->getLocation().Rectangle, Algorithms[detector->getType()]->getName());
    }
  }
}

void FaceDBShell::uiUpdateShapesInfo()
{
  qint16 facesCount(Image->getFacesCount());
  if (facesCount <= 0)
    return;
  QList<QSharedPointer<DBFaces> > dbFaces(Image->getFaces());
  QSharedPointer<DBFaces> dbFace(dbFaces[getFaceIndex()]);
  ui.betweenEyesDistance->setText(QString::number(dbFace->getBetweenEyesDistance()));
  foreach(QSharedPointer<DBFaces> dbFace, dbFaces)
  {
    foreach(QSharedPointer<DBShapes> shape, dbFace->getShapes())
    {
      ui.mainFrame->addShape(shape->getShape());
    }
  }
}

void FaceDBShell::uiEnableControls()
{
  ui.selectDetector->setEnabled(true);
  ui.minFaceSizeSlider->setEnabled(true);
  bool enablePersonConfig(Image->getFacesCount() > 0);
  ui.faceIndex->setEnabled(enablePersonConfig);
  ui.gender->setEnabled(enablePersonConfig);
  ui.glasses->setEnabled(enablePersonConfig);
  ui.closedForehead->setEnabled(enablePersonConfig);
  ui.moustache->setEnabled(enablePersonConfig);
  ui.closedEyebrow->setEnabled(enablePersonConfig);
  ui.beard->setEnabled(enablePersonConfig);
  ui.orientation12->setEnabled(enablePersonConfig);
  ui.orientation13->setEnabled(enablePersonConfig);
  ui.orientation14->setEnabled(enablePersonConfig);
  ui.orientation21->setEnabled(enablePersonConfig);
  ui.orientation22->setEnabled(enablePersonConfig);
  ui.orientation23->setEnabled(enablePersonConfig);
  ui.orientation24->setEnabled(enablePersonConfig);
  ui.orientation25->setEnabled(enablePersonConfig);
  ui.orientation32->setEnabled(enablePersonConfig);
  ui.orientation33->setEnabled(enablePersonConfig);
  ui.orientation34->setEnabled(enablePersonConfig);
  ui.age->setEnabled(enablePersonConfig);
  ui.saveData->setEnabled(enablePersonConfig);
}

void FaceDBShell::log( int Severity, const QString& LogMessage )
{
  QIcon icon;
  switch (Severity)
  {
  case 0: icon = QIcon(QPixmap::fromImage(QImage(":/FaceDBShell/Resources/info50x50.png"))); break;
  case 1: icon = QIcon(QPixmap::fromImage(QImage(":/FaceDBShell/Resources/warning50x50.png"))); break;
  default: icon = QIcon(QPixmap::fromImage(QImage(":/FaceDBShell/Resources/error50x50.png"))); break;
  }
  ui.logText->addItem(new QListWidgetItem(icon, LogMessage, ui.logText));
  ui.logText->scrollToBottom();
}

void FaceDBShell::on_openImage_clicked()
{
  Q_ASSERT(Source);
  using namespace common;
  Settings settings;
  QString srcFilePath(settings.get(Settings::SettingsSourcePath, QDir::currentPath()).toString());
  QString srcFileName(QFileDialog::getOpenFileName(this, tr("Open file"), srcFilePath, getFilters()));
  if (srcFileName.isEmpty())
  {
    log(0, tr("Open file source was canceled."));
    return;
  }
  settings.set(Settings::SettingsSourcePath, srcFileName.left(srcFileName.lastIndexOf('/') + 1));
  if (Source->canProcess(srcFileName) && Source->open(srcFileName))
  {
    log(0, tr("Opened file: ") + srcFileName);
    photoMiddleBrightness = 0;
    processImage();
    return;
  }
  log(1, tr("Can not open ") + srcFileName + tr(" source. No suitable handler found."));
}

void FaceDBShell::on_selectDetector_currentIndexChanged( int/* Index*/ )
{
  if (Image.isNull() || !IsNewImage)
    return;
  processShapes();
  uiUpdateImageInfo();
  uiUpdateDetectorsInfo();
  uiUpdateShapesInfo();
}

void FaceDBShell::on_minFaceSizeSlider_valueChanged( int Value )
{
  ui.minFaceSizeDisplay->setText(QString::number(Value) + "%");
  processImage();
}

void FaceDBShell::on_gender_stateChanged ( int State )
{
  QList<QSharedPointer<DBFaces> > dbFaces(Image->getFaces());
  QSharedPointer<DBFaces> dbFace(dbFaces[getFaceIndex()]);
  using namespace plugins::databases;
  dbFace->getPerson()->setGender(State == 2 ? BoolTrue : BoolFalse);
}

void FaceDBShell::on_glasses_stateChanged ( int State )
{
  QList<QSharedPointer<DBFaces> > dbFaces(Image->getFaces());
  QSharedPointer<DBFaces> dbFace(dbFaces[getFaceIndex()]);
  using namespace plugins::databases;
  dbFace->setGlasses(State == 2 ? BoolTrue : BoolFalse);
}

void FaceDBShell::on_closedForehead_stateChanged ( int State )
{
  QList<QSharedPointer<DBFaces> > dbFaces(Image->getFaces());
  QSharedPointer<DBFaces> dbFace(dbFaces[getFaceIndex()]);
  using namespace plugins::databases;
  dbFace->setClosedForehead(State == 2 ? BoolTrue : BoolFalse);
}

void FaceDBShell::on_moustache_stateChanged ( int State )
{
  QList<QSharedPointer<DBFaces> > dbFaces(Image->getFaces());
  QSharedPointer<DBFaces> dbFace(dbFaces[getFaceIndex()]);
  using namespace plugins::databases;
  dbFace->setMoustache(State == 2 ? BoolTrue : BoolFalse);
}

void FaceDBShell::on_closedEyebrow_stateChanged ( int State )
{
  QList<QSharedPointer<DBFaces> > dbFaces(Image->getFaces());
  QSharedPointer<DBFaces> dbFace(dbFaces[getFaceIndex()]);
  using namespace plugins::databases;
  dbFace->setClosedEyebrow(State == 2 ? BoolTrue : BoolFalse);
}

void FaceDBShell::on_beard_stateChanged ( int State )
{
  QList<QSharedPointer<DBFaces> > dbFaces(Image->getFaces());
  QSharedPointer<DBFaces> dbFace(dbFaces[getFaceIndex()]);
  using namespace plugins::databases;
  dbFace->setBeard(State == 2 ? BoolTrue : BoolFalse);
}

void FaceDBShell::on_orientation12_clicked()
{
  QList<QSharedPointer<DBFaces> > dbFaces(Image->getFaces());
  QSharedPointer<DBFaces> dbFace(dbFaces[getFaceIndex()]);
  using namespace plugins::databases;
  dbFace->setOrientation(Orientation12);
}

void FaceDBShell::on_orientation13_clicked()
{
  QList<QSharedPointer<DBFaces> > dbFaces(Image->getFaces());
  QSharedPointer<DBFaces> dbFace(dbFaces[getFaceIndex()]);
  using namespace plugins::databases;
  dbFace->setOrientation(Orientation13);
}

void FaceDBShell::on_orientation14_clicked()
{
  QList<QSharedPointer<DBFaces> > dbFaces(Image->getFaces());
  QSharedPointer<DBFaces> dbFace(dbFaces[getFaceIndex()]);
  using namespace plugins::databases;
  dbFace->setOrientation(Orientation14);
}

void FaceDBShell::on_orientation21_clicked()
{
  QList<QSharedPointer<DBFaces> > dbFaces(Image->getFaces());
  QSharedPointer<DBFaces> dbFace(dbFaces[getFaceIndex()]);
  using namespace plugins::databases;
  dbFace->setOrientation(Orientation21);
}

void FaceDBShell::on_orientation22_clicked()
{
  QList<QSharedPointer<DBFaces> > dbFaces(Image->getFaces());
  QSharedPointer<DBFaces> dbFace(dbFaces[getFaceIndex()]);
  using namespace plugins::databases;
  dbFace->setOrientation(Orientation22);
}

void FaceDBShell::on_orientation23_clicked()
{
  QList<QSharedPointer<DBFaces> > dbFaces(Image->getFaces());
  QSharedPointer<DBFaces> dbFace(dbFaces[getFaceIndex()]);
  using namespace plugins::databases;
  dbFace->setOrientation(Orientation23);
}

void FaceDBShell::on_orientation24_clicked()
{
  QList<QSharedPointer<DBFaces> > dbFaces(Image->getFaces());
  QSharedPointer<DBFaces> dbFace(dbFaces[getFaceIndex()]);
  using namespace plugins::databases;
  dbFace->setOrientation(Orientation24);
}

void FaceDBShell::on_orientation25_clicked()
{
  QList<QSharedPointer<DBFaces> > dbFaces(Image->getFaces());
  QSharedPointer<DBFaces> dbFace(dbFaces[getFaceIndex()]);
  using namespace plugins::databases;
  dbFace->setOrientation(Orientation25);
}

void FaceDBShell::on_orientation32_clicked()
{
  QList<QSharedPointer<DBFaces> > dbFaces(Image->getFaces());
  QSharedPointer<DBFaces> dbFace(dbFaces[getFaceIndex()]);
  using namespace plugins::databases;
  dbFace->setOrientation(Orientation32);
}

void FaceDBShell::on_orientation33_clicked()
{
  QList<QSharedPointer<DBFaces> > dbFaces(Image->getFaces());
  QSharedPointer<DBFaces> dbFace(dbFaces[getFaceIndex()]);
  using namespace plugins::databases;
  dbFace->setOrientation(Orientation33);
}

void FaceDBShell::on_orientation34_clicked()
{
  QList<QSharedPointer<DBFaces> > dbFaces(Image->getFaces());
  QSharedPointer<DBFaces> dbFace(dbFaces[getFaceIndex()]);
  using namespace plugins::databases;
  dbFace->setOrientation(Orientation34);
}

void FaceDBShell::on_age_valueChanged( int Value )
{
  QList<QSharedPointer<DBFaces> > dbFaces(Image->getFaces());
  QSharedPointer<DBFaces> dbFace(dbFaces[getFaceIndex()]);
  using namespace plugins::databases;
  dbFace->setAge(Value);
}
