#ifndef PLUGINS_DATABASES_CACHE_DETECTORS_H
#define PLUGINS_DATABASES_CACHE_DETECTORS_H

#include "Object.h"

#include "../Types/Faces.h"
#include "../Types/Detectors.h"

#include "Adapters/Storage_Detectors.h"

class QString;

namespace plugins
{
  namespace databases
  {
    namespace cache
    {
      class Detectors : public Object<Storage_Detectors>, public DBDetectors
      {
      public:
        Detectors( Database* Connection, const QString& ID = QString(), bool SaveOnDestroy = false );
        Detectors( Database* Connection, d_ref<Storage_Detectors> Other );
        virtual ~Detectors();

        virtual AlgType getType();
        virtual AlgDetOutput getLocation();

        virtual QSharedPointer<DBFaces> getFace();

        virtual void setType( const AlgType& Value );
        virtual void setLocation( const AlgDetOutput& Value );

        virtual void setFace( const QSharedPointer<DBFaces>& Value );
      };
    }
  }
}

#endif // PLUGINS_DATABASES_CACHE_DETECTORS_H
