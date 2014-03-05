#ifndef PLUGINS_DATABASES_CACHE_INFO_H
#define PLUGINS_DATABASES_CACHE_INFO_H

#include "Object.h"

#include "../Types/Info.h"

#include "Adapters/Storage_Info.h"

class QString;

namespace plugins
{
  namespace databases
  {
    namespace cache
    {
      class Info : public Object<Storage_Info>, public DBInfo
      {
      public:
        Info( Database* Connection, const QString& ID = QString(), bool SaveOnDestroy = false );
        Info( Database* Connection, d_ref<Storage_Info> Other );
        virtual ~Info();

        virtual qint64 getFischerIndex( const AlgType& Algorithm );
        virtual bool getNeedModelUpdate( const AlgType& Algorithm );
        virtual bool getNeedFischerUpdate( const AlgType& Algorithm );

        virtual void setFischerIndex( const AlgType& Algorithm, const qint64& Value );
        virtual void setNeedModelUpdate( const AlgType& Algorithm, const bool& Value );
        virtual void setNeedFischerUpdate( const AlgType& Algorithm, const bool& Value );
      };
    }
  }
}

#endif // PLUGINS_DATABASES_CACHE_INFO_H
