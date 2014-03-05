#ifndef PLUGINS_DATABASES_TYPES_DETECTORS_H
#define PLUGINS_DATABASES_TYPES_DETECTORS_H

#include "../../../Algorithms/Detection/Common/Context.h"
#include "../../../Algorithms/Common/Algorithms.h"

#include "QueryValues.h"
#include "Object.h"

#include <QMap>
#include <QSharedPointer>

namespace plugins
{
  namespace databases
  {
    class Faces;

    class Detectors : virtual public Object
    {
    public:
      enum QueryKey
      {
        QueryType
      };

      Detectors() {}
      virtual ~Detectors() {}

      virtual AlgType getType() = 0;
      virtual AlgDetOutput getLocation() = 0;

      virtual QSharedPointer<Faces> getFace() = 0;

      virtual void setType( const AlgType& Value ) = 0;
      virtual void setLocation( const AlgDetOutput& Value ) = 0;

      virtual void setFace( const QSharedPointer<Faces>& Value ) = 0;
    };
  }
}

typedef plugins::databases::Detectors DBDetectors;
typedef QMap<DBDetectors::QueryKey, plugins::databases::QueryValue> DetectorsQueryMap;

#endif // PLUGINS_DATABASES_TYPES_DETECTORS_H