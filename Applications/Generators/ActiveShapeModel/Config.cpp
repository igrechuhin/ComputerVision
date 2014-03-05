#include "Config.h"

#include <QFile>

namespace
{
  const QDataStream::ByteOrder BYTE_ORDER = QDataStream::LittleEndian;

  const quint8 DEFAULT_MAX_AGE(127);

  const quint8 DEFAULT_PYRAMID_LEVELS(4);
  const qreal DEFAULT_SCALE_FACTOR(2);

  const quint32 DEFAULT_NEIGS(20);
  const quint32 DEFAULT_NEIGS2D(26);
  const quint32 DEFAULT_NEIGS_FINAL(22);
  const qreal DEFAULT_BMAX(1.8f);
  const qreal DEFAULT_BMAX_FINAL(3.0f);

  using namespace common::models;
  const Profile::TypeOption DEFAULT_PROFILE_TYPE(Profile::Profile1D);
  const quint32 DEFAULT_MAX_SEARCH_ITERS(10);
  const quint8 DEFAULT_QUALIFYING_DISP(75);
  const qint32 DEFAULT_PIX_SEARCH_1D(3);
  const qint32 DEFAULT_PIX_SEARCH_2D(3);
  const qint32 DEFAULT_PROFILE1D_SIZE(13);
  const qint32 DEFAULT_PROFILE2D_SIZE(5);

  const quint32 DEFAULT_MEAN_SHAPE_SEARCH_ITERATIONS(3);

  const QString CLOSED_FOREHEAD_STR[] = {"None", "Not closed", "Closed", "Any"};
  const QString GLASSES_STR[] = {"None", "Not present", "Present", "Any"};
  const QString GENDER_STR[] = {"None", "Female", "Male", "Any"};
}

Config::Config()
{
  setDefault();
}

Config::~Config()
{
}

void Config::read( const QString& FilePath )
{
  QFile configFile(FilePath);
  if (!configFile.exists())
  {
    emit log(tr("Config file does not exist: %1 ").arg(FilePath));
    return;
  }

  if (!configFile.open(QIODevice::ReadOnly))
  {
    emit log(tr("Can not open config file: %1").arg(FilePath));
    return;
  }

  QDataStream configFileStream(&configFile);
  configFileStream.setByteOrder(BYTE_ORDER);

  configFileStream >> Photos;
  configFileStream >> Faces;
  configFileStream >> Persons;

  configFileStream >> Extensions;
  configFileStream >> Scale;
  configFileStream >> PrincComp;
  configFileStream >> PyrLevels;
  using namespace common::models;
  configFileStream >> ProfileSize[Profile::Profile1D];
  configFileStream >> ProfileSize[Profile::Profile2D];
  configFileStream >> MeanShapeSearchIterations;
}

void Config::logConfiguration()
{
  emit log(tr("Model configuration:"));
  emit log(tr("\t\t\t\tMin\tMax\t\t\tValue"));

  logPhotoConfiguration();
  logFaceConfiguration();
  logPersonConfiguration();

  emit log(tr("Mirror                      \t\t\t\t\t%1").arg(Extensions.testFlag(MirrorExtend) ? "TRUE" : "FALSE"));
  emit log(tr("Number of pyramid levels    \t\t\t\t\t%1").arg(Scale.Levels));
  emit log(tr("Scale factor                \t\t\t\t\t%1").arg(Scale.Factor));
  emit log(tr("Mean shape search iterations\t\t\t\t\t%1").arg(MeanShapeSearchIterations));
  emit log(tr("Number of eigen values to leave:"));
  emit log(tr("\t\t\t\t1D:\t\t\t\t%1").arg(PrincComp.NEigs));
  emit log(tr("\t\t\t\t2D:\t\t\t\t%1").arg(PrincComp.NEigs2D));
  emit log(tr("\t\t\t\tFinal:\t\t\t\t%1").arg(PrincComp.NEigsFinal));
  emit log(tr("Cut factor:"));
  emit log(tr("\t\t\t\tbMax:\t\t\t\t%1").arg(PrincComp.BMax));
  emit log(tr("\t\t\t\tbMaxFinal:\t\t\t%1").arg(PrincComp.BMaxFinal));
  emit log(tr("Profiles:"));
  for (int index(0); index < PyrLevels.size(); index++)
  {
    emit log(tr("\t\tLevel %1 / %2:").arg(index+1).arg(PyrLevels.size()));
    emit log(tr("\t\t\t\tMax search iters:\t\t%1").arg(PyrLevels[index].MaxSearchIters));
    emit log(tr("\t\t\t\tQualifying disp: \t\t%1").arg(PyrLevels[index].QuialifyingDisp));
    emit log(tr("\t\t\t\t1D size:         \t\t%1").arg(ProfileSize[Profile::Profile1D]));
    emit log(tr("\t\t\t\tPix search 1D:   \t\t%1").arg(PyrLevels[index].PixSearch[Profile::Profile1D]));
    emit log(tr("\t\t\t\t2D size:         \t\t%1").arg(ProfileSize[Profile::Profile2D]));
    emit log(tr("\t\t\t\tPix search 2D:   \t\t%1").arg(PyrLevels[index].PixSearch[Profile::Profile2D]));
  }
}

void Config::setDefault()
{
  using namespace plugins::databases;

  Photos.insert(Photos::QueryWidthMin,            0); Photos.insert(Photos::QueryWidthMax,            LONG_MAX);
  Photos.insert(Photos::QueryHeightMin,           0); Photos.insert(Photos::QueryHeightMax,           LONG_MAX);
  Photos.insert(Photos::QueryColorDepthMin,       0); Photos.insert(Photos::QueryColorDepthMax,       UCHAR_MAX);
  Photos.insert(Photos::QueryMiddleBrightnessMin, 0); Photos.insert(Photos::QueryMiddleBrightnessMax, UCHAR_MAX);
  Photos.insert(Photos::QueryFacesCountMin,       1); Photos.insert(Photos::QueryFacesCountMax,       SHRT_MAX);

  Faces.insert(Faces::QueryAgeMin, 0);  Faces.insert(Faces::QueryAgeMax, DEFAULT_MAX_AGE);
  Faces.insert(Faces::QueryClosedForeheadSet, int(BoolTrue | BoolFalse));
  Faces.insert(Faces::QueryClosedEyebrowSet,  int(BoolTrue | BoolFalse));
  Faces.insert(Faces::QueryGlassesSet,        int(BoolTrue | BoolFalse));
  Faces.insert(Faces::QueryMoustacheSet,      int(BoolTrue | BoolFalse));
  Faces.insert(Faces::QueryBeardSet,          int(BoolTrue | BoolFalse));
  Faces.insert(Faces::QueryBetweenEyesDistanceMin, 10); Faces.insert(Faces::QueryBetweenEyesDistanceMax, LONG_MAX);
  Faces.insert(Faces::QueryOrientationList, int(
                    Orientation12 | Orientation13 | Orientation14 | 
    Orientation21 | Orientation22 | Orientation23 | Orientation24 | Orientation25 | 
                    Orientation32 | Orientation33 | Orientation34));
  
  Persons.insert(Persons::QueryGenderSet, int(BoolTrue | BoolFalse));

  setDefaultScale();
  setDefaultPrincipalComponents();
  setDefaultProfile();

  Extensions |= MirrorExtend;
  MeanShapeSearchIterations = DEFAULT_MEAN_SHAPE_SEARCH_ITERATIONS;
}

void Config::setDefaultScale()
{
  Scale.Levels = DEFAULT_PYRAMID_LEVELS;
  Scale.Factor = DEFAULT_SCALE_FACTOR;
}

void Config::setDefaultPrincipalComponents()
{
  PrincComp.NEigs = DEFAULT_NEIGS;
  PrincComp.NEigs2D = DEFAULT_NEIGS2D;
  PrincComp.NEigsFinal = DEFAULT_NEIGS_FINAL;
  PrincComp.BMax = DEFAULT_BMAX;
  PrincComp.BMaxFinal = DEFAULT_BMAX_FINAL;
}

void Config::setDefaultProfile()
{
  using namespace common::models;
  for (quint8 index(0); index < DEFAULT_PYRAMID_LEVELS; index++)
  {
    Profile level;
    level.PointType = DEFAULT_PROFILE_TYPE;
    level.MaxSearchIters = DEFAULT_MAX_SEARCH_ITERS;
    level.QuialifyingDisp = DEFAULT_QUALIFYING_DISP;
    level.PixSearch[Profile::Profile1D] = DEFAULT_PIX_SEARCH_1D;
    level.PixSearch[Profile::Profile2D] = DEFAULT_PIX_SEARCH_2D;
    PyrLevels << level;
  }
  ProfileSize[Profile::Profile1D] = DEFAULT_PROFILE1D_SIZE;
  ProfileSize[Profile::Profile2D] = DEFAULT_PROFILE2D_SIZE;
}

void Config::logPhotoConfiguration()
{
  emit log(tr("Photo"));
  using namespace plugins::databases;
  emit log(tr("\tWidth\t\t\t%1\t%2").arg(Photos[Photos::QueryWidthMin].vint32).arg(Photos[Photos::QueryWidthMax].vint32));
  emit log(tr("\tHeight\t\t\t%1\t%2").arg(Photos[Photos::QueryHeightMin].vint32).arg(Photos[Photos::QueryHeightMax].vint32));
  emit log(tr("\tColorDepth\t\t%1\t%2").arg(Photos[Photos::QueryColorDepthMin].vuint8).arg(Photos[Photos::QueryColorDepthMax].vuint8));
  emit log(tr("\tMiddleBrightness\t%1\t%2").arg(Photos[Photos::QueryMiddleBrightnessMin].vuint8).arg(Photos[Photos::QueryMiddleBrightnessMax].vuint8));
  emit log(tr("\tFacesCount\t\t%1\t%2").arg(Photos[Photos::QueryFacesCountMin].vint16).arg(Photos[Photos::QueryFacesCountMax].vint16));
}

void Config::logFaceConfiguration()
{
  emit log(tr("Face"));
  using namespace plugins::databases;
  emit log(tr("\tAge\t\t\t%1\t%2").arg(Faces[Faces::QueryAgeMin].vuint8).arg(Faces[Faces::QueryAgeMax].vuint8));
  emit log(tr("\tClosedForehead\t\t\t\t\t\t%1").arg(CLOSED_FOREHEAD_STR[Faces[Faces::QueryClosedForeheadSet].vbool]));
  emit log(tr("\tClosedEyebrow \t\t\t\t\t\t%1").arg(CLOSED_FOREHEAD_STR[Faces[Faces::QueryClosedEyebrowSet].vbool]));
  emit log(tr("\tGlasses       \t\t\t\t\t\t%1").arg(GLASSES_STR[Faces[Faces::QueryGlassesSet].vbool]));
  emit log(tr("\tMoustache     \t\t\t\t\t\t%1").arg(GLASSES_STR[Faces[Faces::QueryMoustacheSet].vbool]));
  emit log(tr("\tBeard         \t\t\t\t\t\t%1").arg(GLASSES_STR[Faces[Faces::QueryBeardSet].vbool]));
  emit log(tr("\tBetweenEyesDistance\t%1\t%2").arg(Faces[Faces::QueryBetweenEyesDistanceMin].vint32).arg(Faces[Faces::QueryBetweenEyesDistanceMax].vint32));

  QString orientStr;
  OrientationQueries orientations(Faces[Faces::QueryOrientationList].vorientation);
  QStringList orientsList;
  if (orientations.testFlag(Orientation12)) orientsList.append("12");
  if (orientations.testFlag(Orientation13)) orientsList.append("13");
  if (orientations.testFlag(Orientation14)) orientsList.append("14");
  if (orientations.testFlag(Orientation21)) orientsList.append("21");
  if (orientations.testFlag(Orientation22)) orientsList.append("22");
  if (orientations.testFlag(Orientation23)) orientsList.append("23");
  if (orientations.testFlag(Orientation24)) orientsList.append("24");
  if (orientations.testFlag(Orientation25)) orientsList.append("25");
  if (orientations.testFlag(Orientation32)) orientsList.append("32");
  if (orientations.testFlag(Orientation33)) orientsList.append("33");
  if (orientations.testFlag(Orientation34)) orientsList.append("34");
  orientStr = orientsList.join(", ");

  emit log(tr("\tOrientation\t\t\t\t\t\t%1").arg(orientStr));
}

void Config::logPersonConfiguration()
{
  emit log(tr("Person"));
  using namespace plugins::databases;
  emit log(tr("\tGender\t\t\t\t\t\t\t%1").arg(GENDER_STR[Persons[Persons::QueryGenderSet].vbool]));
}

ActiveShapeModel& operator<<( ActiveShapeModel& Model, const Config& Value )
{
  Model.PrincComp = Value.PrincComp;
  Model.PyrLevels = Value.PyrLevels;
  Model.ScaleObj = Value.Scale;
  return Model;
}

QDataStream& operator>>( QDataStream& Stream, Config::Extends& Value )
{
  int tmp;
  Stream >> tmp;
  Value = static_cast<Config::Extend>(tmp);
  return Stream;
}
