#ifndef PLUGINS_DATABASES_CACHE_PERSONS_H
#define PLUGINS_DATABASES_CACHE_PERSONS_H

#include "Object.h"

#include "../Types/Faces.h"
#include "../Types/Persons.h"

#include "Adapters/Storage_Persons.h"

class QString;

namespace plugins
{
  namespace databases
  {
    namespace cache
    {
      class Persons : public Object<Storage_Persons>, public DBPersons
      {
      public:
        Persons( Database* Connection, const QString& ID = QString(), bool SaveOnDestroy = false );
        Persons( Database* Connection, d_ref<Storage_Persons> Other );
        virtual ~Persons();

        virtual BoolQueries getGender();

        virtual QList<QSharedPointer<DBFaces> > getFaces();

        virtual void setGender( const BoolQueries& Value );

        virtual void addFace( const QSharedPointer<DBFaces>& Value );
      };
    }
  }
}

#endif // PLUGINS_DATABASES_CACHE_PERSONS_H
