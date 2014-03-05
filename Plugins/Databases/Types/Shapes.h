#ifndef PLUGINS_DATABASES_TYPES_SHAPES_H
#define PLUGINS_DATABASES_TYPES_SHAPES_H

#include "QueryValues.h"
#include "Object.h"

#include <QPoint>
#include <QVector>
#include <QMap>
#include <QSharedPointer>

namespace plugins
{
  namespace databases
  {
    class Faces;

    class Shapes : virtual public Object
    {
    public:
      enum QueryKey
      {
      };

      Shapes() {}
      virtual ~Shapes() {}

      virtual QVector<QPoint> getShape() = 0;

      virtual QSharedPointer<Faces> getFace() = 0;

      virtual void setShape( const QVector<QPoint>& Value ) = 0;

      virtual void setFace( const QSharedPointer<Faces>& Value ) = 0;
    };
  }
}

typedef plugins::databases::Shapes DBShapes;
typedef QMap<DBShapes::QueryKey, plugins::databases::QueryValue> ShapesQueryMap;

#endif // PLUGINS_DATABASES_TYPES_SHAPES_H