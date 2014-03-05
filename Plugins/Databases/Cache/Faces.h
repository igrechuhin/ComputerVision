#ifndef PLUGINS_DATABASES_CACHE_FACES_H
#define PLUGINS_DATABASES_CACHE_FACES_H

#include "Object.h"

#include "../Types/Photos.h"
#include "../Types/Faces.h"
#include "../Types/Persons.h"
#include "../Types/Detectors.h"
#include "../Types/Shapes.h"

#include "Adapters/Storage_Faces.h"

class QString;

namespace plugins
{
  namespace databases
  {
    namespace cache
    {
      class Faces : public Object<Storage_Faces>, public DBFaces
      {
      public:
        Faces( Database* Connection, const QString& ID = QString(), bool SaveOnDestroy = false );
        Faces( Database* Connection, d_ref<Storage_Faces> Other );
        virtual ~Faces();

        virtual quint8 getAge();
        virtual BoolQueries getClosedForehead();
        virtual BoolQueries getClosedEyebrow();
        virtual BoolQueries getGlasses();
        virtual BoolQueries getMoustache();
        virtual BoolQueries getBeard();
        virtual qint32 getBetweenEyesDistance();
        virtual OrientationQueries getOrientation();

        virtual QSharedPointer<DBPhotos> getPhoto();
        virtual QSharedPointer<DBPersons> getPerson();
        virtual QList<QSharedPointer<DBDetectors> > getDetectors();
        virtual QList<QSharedPointer<DBShapes> > getShapes();

        virtual void setAge( const quint8& Value );
        virtual void setClosedForehead( const BoolQueries& Value );
        virtual void setClosedEyebrow( const BoolQueries& Value );
        virtual void setGlasses( const BoolQueries& Value );
        virtual void setMoustache( const BoolQueries& Value );
        virtual void setBeard( const BoolQueries& Value );
        virtual void setBetweenEyesDistance( const qint32& Value );
        virtual void setOrientation( const OrientationQueries& Value );

        virtual void setPhoto( const QSharedPointer<DBPhotos>& Value );
        virtual void setPerson( const QSharedPointer<DBPersons>& Value );
        virtual void addDetector( const QSharedPointer<DBDetectors>& Value );
        virtual void addShape( const QSharedPointer<DBShapes>& Value );
      };
    }
  }
}

#endif // PLUGINS_DATABASES_CACHE_FACES_H
