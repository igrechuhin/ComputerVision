#ifndef APPLICATIONS_GENERATORS_ACTIVESHAPEMODEL_GENERATOR_H
#define APPLICATIONS_GENERATORS_ACTIVESHAPEMODEL_GENERATOR_H

#include "Config.h"

#include "../../../Plugins/Databases/Interface.h"
#include "../../../Plugins/Databases/Types/Info.h"

#include "../../../Common/Models/ActiveShapeModel/ActiveShapeModel.h"
#include "../../../Common/Frame/Frame.h"
#include "../../../Common/Math/Matrix.h"

#include <QStringList>
#include <QFile>
#include <QObject>
#include <QPoint>
#include <QVector2D>

class Generator : public QObject
{
  Q_OBJECT

  struct ExtendedFace
  {
    QMap<Config::Extend, common::Frame> Images;
    QMap<Config::Extend, QVector<QPoint> > Shapes;
    QMap<Config::Extend, AlgDetOutputMap> Detectors;
  };

public:
  enum ExtractFlag
  {
    ExtractNothing = 0x0,
    ExtractShape = 0x1,
    ExtractImage = 0x2,
    ExtractDetectors = 0x4
  };
  Q_DECLARE_FLAGS(Extract, ExtractFlag)

  Generator( const QStringList& Parameters );
  ~Generator();

  void run();

private:
  void getDatabase();
  void openDBConnection();

  void parseParameters( const QStringList& Parameters );

  void getFacesIDs();
  void generate();

  void getMeanShape( common::models::MeanShape& Shape );
  void getPrincipalComponents( common::models::PrincipalComponents& PrincComp, const common::models::MeanShape& Shape );
  void getProfiles( QVector<common::models::Profile>& PyrLevels, qint16 PointsCount );
  void clearProfiles( QVector<common::models::Profile>& PyrLevels, qint16 PointsCount );
  void getProfilesMean( QVector<common::models::Profile>& PyrLevels);
  common::Matrix<qreal> get1DProfile( const common::Frame& Image, const QPointF& Point, const QVector2D& Whisker );
  common::Matrix<qreal> get2DProfile( const common::Frame& Image, const QPointF& Point );
  void getProfilesCovar( QVector<common::models::Profile>& PyrLevels);
  ExtendedFace getExtendedFace( const QString& FaceID, Extract DataType );

  void saveModel( common::models::ActiveShapeModel &model );

public slots:
  void log( QString Msg );

private:
  QFile STDOut;

  DBInterface* Database;
  QSharedPointer<DBInfo> Info;
  QStringList FacesIDs;

  Config ConfigObj;

  QStringList Log;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(Generator::Extract)

#endif // APPLICATIONS_GENERATORS_ACTIVESHAPEMODEL_GENERATOR_H
