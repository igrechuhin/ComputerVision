#ifndef APPLICATIONS_GENERATORS_ACTIVESHAPEMODEL_CONFIG_H
#define APPLICATIONS_GENERATORS_ACTIVESHAPEMODEL_CONFIG_H

#include "../../../Plugins/Databases/Types/Photos.h"
#include "../../../Plugins/Databases/Types/Faces.h"
#include "../../../Plugins/Databases/Types/Persons.h"

#include "../../../Common/Models/ActiveShapeModel/ActiveShapeModel.h"

#include <QFlags>
#include <QObject>

class Config;
common::models::ActiveShapeModel& operator << (common::models::ActiveShapeModel& Model, const Config& Value);

class Config : public QObject
{
  Q_OBJECT

  friend common::models::ActiveShapeModel& operator << (common::models::ActiveShapeModel& Model, const Config& Value);

public:
  Config();
  ~Config();

  void read( const QString& FilePath );
//   void write( const QString& FilePath );

  void logConfiguration();

private:
  void setDefault();
  void setDefaultScale();
  void setDefaultPrincipalComponents();
  void setDefaultProfile();

  void logPhotoConfiguration();
  void logFaceConfiguration();
  void logPersonConfiguration();

signals:
  void log( QString Msg );

public:
  enum Extend
  {
    NoExtend = 0x0,
    MirrorExtend = 0x1
  };
  Q_DECLARE_FLAGS(Extends, Extend)

  PhotosQueryMap Photos;
  FacesQueryMap Faces;
  PersonsQueryMap Persons;

  Extends Extensions;
  common::models::Scale Scale;
  common::models::PrincipalComponents PrincComp;
  QVector<common::models::Profile> PyrLevels;
  qint32 ProfileSize[common::models::Profile::ProfilesCount];
  quint32 MeanShapeSearchIterations;
};

QDataStream& operator >> (QDataStream& Stream, Config::Extends& Value);

Q_DECLARE_OPERATORS_FOR_FLAGS(Config::Extends)

#endif // APPLICATIONS_GENERATORS_ACTIVESHAPEMODEL_CONFIG_H
