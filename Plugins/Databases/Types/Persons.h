#ifndef PLUGINS_DATABASES_TYPES_PERSONS_H
#define PLUGINS_DATABASES_TYPES_PERSONS_H

#include "QueryValues.h"
#include "Object.h"

#include <QMap>
#include <QSharedPointer>

namespace plugins
{
  namespace databases
  {
    class Faces;

    class Persons : virtual public Object
    {
    public:
      enum QueryKey
      {
        QueryGenderSet
      };

      Persons() {}
      virtual ~Persons() {}

      virtual BoolQueries getGender() = 0;

      virtual QList<QSharedPointer<Faces> > getFaces() = 0;

      virtual void setGender( const BoolQueries& Value ) = 0;

      virtual void addFace( const QSharedPointer<Faces>& Value ) = 0;
    };
  }
}

typedef plugins::databases::Persons DBPersons;
typedef QMap<DBPersons::QueryKey, plugins::databases::QueryValue> PersonsQueryMap;

QDataStream& operator >> (QDataStream& Stream, DBPersons::QueryKey& Value);
QDataStream& operator << (QDataStream& Stream, const DBPersons::QueryKey& Value);

#endif // PLUGINS_DATABASES_TYPES_PERSONS_H