#ifndef PLUGINS_DATABASES_CACHE_PHOTOS_H
#define PLUGINS_DATABASES_CACHE_PHOTOS_H

#include "Object.h"

#include "../Types/Photos.h"
#include "../Types/Faces.h"

#include "Adapters/Storage_Photos.h"

class QString;

namespace plugins
{
  namespace databases
  {
    namespace cache
    {
      class Photos : public Object<Storage_Photos>, public DBPhotos
      {
      public:
        Photos( Database* Connection, const QString& ID = QString(), bool SaveOnDestroy = false );
        Photos( Database* Connection, d_ref<Storage_Photos> Other );
        virtual ~Photos();

        virtual qint32 getWidth();
        virtual qint32 getHeight();
        virtual quint8 getColorDepth();
        virtual quint8 getMiddleBrightness();
        virtual qint16 getFacesCount();
        virtual common::Frame getImage();
        virtual qint64 getCRC();

        virtual QList<QSharedPointer<DBFaces> > getFaces();

        virtual void setWidth( const qint32& Value );
        virtual void setHeight( const qint32& Value );
        virtual void setColorDepth( const quint8& Value );
        virtual void setMiddleBrightness( const quint8& Value );
        virtual void setFacesCount( const qint16& Value );
        virtual void setImage( const common::Frame& Value );
        virtual void setCRC( const qint64& Value );

        virtual void addFace( const QSharedPointer<DBFaces>& Value );
      };
    }
  }
}

#endif // PLUGINS_DATABASES_CACHE_PHOTOS_H
