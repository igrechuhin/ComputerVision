#include "Info.h"

namespace plugins
{
  namespace databases
  {
    namespace cache
    {
      Info::Info( Database* Connection, const QString& ID /*= QString() */, bool SaveOnDestroy/* = false*/ )
        : Object<Storage_Info>(Connection, ID, SaveOnDestroy)
      {
      }

      Info::Info( Database* Connection, d_ref<Storage_Info> Other )
        : Object<Storage_Info>(Connection, Other)
      {
      }

      Info::~Info()
      {
      }

      qint64 Info::getFischerIndex( const AlgType& Algorithm )
      {
        return DBObj->getFischerIndex().get_int64();
      }

      bool Info::getNeedModelUpdate( const AlgType& Algorithm )
      {
        return DBObj->getNeedModelUpdate();
      }

      bool Info::getNeedFischerUpdate( const AlgType& Algorithm )
      {
        return DBObj->getNeedFischerUpdate();
      }

      void Info::setFischerIndex( const AlgType& Algorithm, const qint64& Value )
      {
        DBObj->setFischerIndex(Value);
      }

      void Info::setNeedModelUpdate( const AlgType& Algorithm, const bool& Value )
      {
        DBObj->setNeedModelUpdate(Value);
      }

      void Info::setNeedFischerUpdate( const AlgType& Algorithm, const bool& Value )
      {
        DBObj->setNeedFischerUpdate(Value);
      }
    }
  }
}
