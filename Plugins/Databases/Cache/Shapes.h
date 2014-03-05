#ifndef PLUGINS_DATABASES_CACHE_SHAPES_H
#define PLUGINS_DATABASES_CACHE_SHAPES_H

#include "Object.h"

#include "../Types/Faces.h"
#include "../Types/Shapes.h"

#include "Adapters/Storage_Shapes.h"

class QString;

namespace plugins
{
  namespace databases
  {
    namespace cache
    {
      class Shapes : public Object<Storage_Shapes>, public DBShapes
      {
      public:
        Shapes( Database* Connection, const QString& ID = QString(), bool SaveOnDestroy = false );
        Shapes( Database* Connection, d_ref<Storage_Shapes> Other );
        virtual ~Shapes();

        virtual QVector<QPoint> getShape();

        virtual QSharedPointer<DBFaces> getFace();

        virtual void setShape( const QVector<QPoint>& Value );

        virtual void setFace( const QSharedPointer<DBFaces>& Value );
      };
    }
  }
}

#endif // PLUGINS_DATABASES_CACHE_SHAPES_H
