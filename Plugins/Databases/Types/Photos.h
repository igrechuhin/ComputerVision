#ifndef PLUGINS_DATABASES_TYPES_PHOTOS_H
#define PLUGINS_DATABASES_TYPES_PHOTOS_H

#include "../../../Common/Frame/Frame.h"

#include "QueryValues.h"
#include "Object.h"

#include <QMap>

namespace plugins
{
  namespace databases
  {
    class Faces;

    class Photos : virtual public Object
    {
    public:
      enum QueryKey
      {
        QueryWidthMin,
        QueryWidth,
        QueryWidthMax,
        QueryHeightMin,
        QueryHeight,
        QueryHeightMax,
        QueryColorDepthMin,
        QueryColorDepthMax,
        QueryMiddleBrightnessMin,
        QueryMiddleBrightnessMax,
        QueryFacesCountMin,
        QueryFacesCountMax,
        QueryCRC
      };

      Photos() {}
      virtual ~Photos() {}

      virtual qint32 getWidth() = 0;
      virtual qint32 getHeight() = 0;
      virtual quint8 getColorDepth() = 0;
      virtual quint8 getMiddleBrightness() = 0;
      virtual qint16 getFacesCount() = 0;
      virtual common::Frame getImage() = 0;
      virtual qint64 getCRC() = 0;

      virtual QList<QSharedPointer<Faces> > getFaces() = 0;

      virtual void setWidth( const qint32& Value ) = 0;
      virtual void setHeight( const qint32& Value ) = 0;
      virtual void setColorDepth( const quint8& Value ) = 0;
      virtual void setMiddleBrightness( const quint8& Value ) = 0;
      virtual void setFacesCount( const qint16& Value ) = 0;
      virtual void setImage( const common::Frame& Value ) = 0;
      virtual void setCRC( const qint64& Value ) = 0;

      virtual void addFace( const QSharedPointer<Faces>& Value ) = 0;
    };
  }
}

typedef plugins::databases::Photos DBPhotos;
typedef QMap<DBPhotos::QueryKey, plugins::databases::QueryValue> PhotosQueryMap;

QDataStream& operator >> (QDataStream& Stream, DBPhotos::QueryKey& Value);
QDataStream& operator << (QDataStream& Stream, const DBPhotos::QueryKey& Value);

#endif // PLUGINS_DATABASES_TYPES_PHOTOS_H