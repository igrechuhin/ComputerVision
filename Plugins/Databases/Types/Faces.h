#ifndef PLUGINS_DATABASES_TYPES_FACES_H
#define PLUGINS_DATABASES_TYPES_FACES_H

#include "QueryValues.h"
#include "Object.h"

#include <QMap>
#include <QSharedPointer>

namespace plugins
{
  namespace databases
  {
    class Photos;
    class Persons;
    class Detectors;
    class Shapes;

    class Faces : virtual public Object
    {
    public:
      enum QueryKey
      {
        QueryAgeMin,
        QueryAgeMax,
        QueryClosedForeheadSet,
        QueryClosedEyebrowSet,
        QueryGlassesSet,
        QueryMoustacheSet,
        QueryBeardSet,
        QueryBetweenEyesDistanceMin,
        QueryBetweenEyesDistanceMax,
        QueryOrientationList
      };

      Faces() {}
      virtual ~Faces() {}

      virtual quint8 getAge() = 0;
      virtual BoolQueries getClosedForehead() = 0;
      virtual BoolQueries getClosedEyebrow() = 0;
      virtual BoolQueries getGlasses() = 0;
      virtual BoolQueries getMoustache() = 0;
      virtual BoolQueries getBeard() = 0;
      virtual qint32 getBetweenEyesDistance() = 0;
      virtual OrientationQueries getOrientation() = 0;

      virtual QSharedPointer<Photos> getPhoto() = 0;
      virtual QSharedPointer<Persons> getPerson() = 0;
      virtual QList<QSharedPointer<Detectors> > getDetectors() = 0;
      virtual QList<QSharedPointer<Shapes> > getShapes() = 0;

      virtual void setAge( const quint8& Value ) = 0;
      virtual void setClosedForehead( const BoolQueries& Value ) = 0;
      virtual void setClosedEyebrow( const BoolQueries& Value ) = 0;
      virtual void setGlasses( const BoolQueries& Value ) = 0;
      virtual void setMoustache( const BoolQueries& Value ) = 0;
      virtual void setBeard( const BoolQueries& Value ) = 0;
      virtual void setBetweenEyesDistance( const qint32& Value ) = 0;
      virtual void setOrientation( const OrientationQueries& Value ) = 0;

      virtual void setPhoto( const QSharedPointer<Photos>& Value ) = 0;
      virtual void setPerson( const QSharedPointer<Persons>& Value ) = 0;
      virtual void addDetector( const QSharedPointer<Detectors>& Value ) = 0;
      virtual void addShape( const QSharedPointer<Shapes>& Value ) = 0;
    };
  }
}

typedef plugins::databases::Faces DBFaces;
typedef QMap<DBFaces::QueryKey, plugins::databases::QueryValue> FacesQueryMap;

QDataStream& operator >> (QDataStream& Stream, DBFaces::QueryKey& Value);
QDataStream& operator << (QDataStream& Stream, const DBFaces::QueryKey& Value);

#endif // PLUGINS_DATABASES_TYPES_FACES_H