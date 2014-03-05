#include "Photos.h"

#include "Faces.h"

#include "Common.h"

#include "Adapters/Storage_Faces.h"

#include <QString>

namespace plugins
{
  namespace databases
  {
    namespace cache
    {
      Photos::Photos( Database* Connection, const QString& ID /*= QString()*/, bool SaveOnDestroy/* = false*/ )
        : Object<Storage_Photos>(Connection, ID, SaveOnDestroy)
      {
      }

      Photos::Photos( Database* Connection, d_ref<Storage_Photos> Other )
        : Object<Storage_Photos>(Connection, Other)
      {
      }

      Photos::~Photos()
      {
      }

      qint32 Photos::getWidth()
      {
        return DBObj->getWidth();
      }

      qint32 Photos::getHeight()
      {
        return DBObj->getHeight();
      }

      quint8 Photos::getColorDepth()
      {
        return DBObj->getColorDepth();
      }

      quint8 Photos::getMiddleBrightness()
      {
        return DBObj->getMiddleBrightness();
      }

      qint16 Photos::getFacesCount()
      {
        return DBObj->getFacesCount();
      }

      common::Frame Photos::getImage()
      {
        common::Frame image;
        QByteArray imageBuffer;
        fileBinStreamToQByteArray(imageBuffer, DBObj->getImage());
        bool loadOK(image.loadFromData(imageBuffer));
        Q_ASSERT(loadOK);
        return image;
      }

      qint64 Photos::getCRC()
      {
        return DBObj->getCRC().get_int64();
      }

      QList<QSharedPointer<DBFaces> > Photos::getFaces()
      {
        QList<QSharedPointer<DBFaces> > facesPtrs;
        d_ref< d_relationship<Storage_Faces> > dbFaces(DBObj->getFaces());
        for (d_relationship<Storage_Faces>::iterator dbFace(dbFaces->begin()); dbFace != dbFaces->end(); ++dbFace)
        {
          facesPtrs.append(QSharedPointer<DBFaces>(new Faces(DBConnection, *dbFace)));
        }
        return facesPtrs;
      }

      void Photos::setWidth( const qint32& Value )
      {
        DBObj->setWidth(Value);
      }

      void Photos::setHeight( const qint32& Value )
      {
        DBObj->setHeight(Value);
      }

      void Photos::setColorDepth( const quint8& Value )
      {
        DBObj->setColorDepth(Value);
      }

      void Photos::setMiddleBrightness( const quint8& Value )
      {
        DBObj->setMiddleBrightness(Value);
      }

      void Photos::setFacesCount( const qint16& Value )
      {
        DBObj->setFacesCount(Value);
      }

      void Photos::setImage( const common::Frame& Value )
      {
        d_ref<d_file_bin_stream> imageStream(d_file_bin_stream::create_new(DBConnection));
        qByteArrayToFileBinStream(imageStream, Value);
        DBObj->setImage(imageStream);
      }

      void Photos::setCRC( const qint64& Value )
      {
        DBObj->setCRC(Value);
      }

      void Photos::addFace( const QSharedPointer<DBFaces>& Value )
      {
        Q_ASSERT(!"TODO");
      }
    }
  }
}
