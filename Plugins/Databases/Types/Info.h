#ifndef PLUGINS_DATABASES_TYPES_INFO_H
#define PLUGINS_DATABASES_TYPES_INFO_H

#include "../../../Algorithms/Common/Algorithms.h"

#include "QueryValues.h"
#include "Object.h"

namespace plugins
{
  namespace databases
  {
    class Info : virtual public Object
    {
    public:
      Info() {}
      virtual ~Info() {}

      virtual qint64 getFischerIndex( const AlgType& Algorithm ) = 0;
      virtual bool getNeedModelUpdate( const AlgType& Algorithm ) = 0;
      virtual bool getNeedFischerUpdate( const AlgType& Algorithm ) = 0;

      virtual void setFischerIndex( const AlgType& Algorithm, const qint64& Value ) = 0;
      virtual void setNeedModelUpdate( const AlgType& Algorithm, const bool& Value ) = 0;
      virtual void setNeedFischerUpdate( const AlgType& Algorithm, const bool& Value ) = 0;
    };
  }
}

typedef plugins::databases::Info DBInfo;

#endif // PLUGINS_DATABASES_TYPES_INFO_H
