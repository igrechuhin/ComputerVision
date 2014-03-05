#include "Detectors.h"

#include "Faces.h"

#include "Adapters/Storage_FaceRect.h"

namespace plugins
{
  namespace databases
  {
    namespace cache
    {
      Detectors::Detectors( Database* Connection, const QString& ID /*= QString()*/, bool SaveOnDestroy/* = false*/ )
        : Object<Storage_Detectors>(Connection, ID, SaveOnDestroy)
      {
      }

      Detectors::Detectors( Database* Connection, d_ref<Storage_Detectors> Other )
        : Object<Storage_Detectors>(Connection, Other)
      {
      }

      Detectors::~Detectors()
      {
      }

      AlgType Detectors::getType()
      {
        return static_cast<AlgType>(DBObj->getType().value());
      }

      AlgDetOutput Detectors::getLocation()
      {
        AlgDetOutput location;
        d_ref<Storage_FaceRect> dbRect(DBObj->getRect());
        location.Rectangle.setX(dbRect->getX());
        location.Rectangle.setY(dbRect->getY());
        location.Rectangle.setWidth(dbRect->getWidth());
        location.Rectangle.setHeight(dbRect->getHeight());
        using namespace algorithms::detection;
        if (dbRect->getLeft() == 1)
        {
          location.Points.insert(LeftEyePoint, QPoint(dbRect->getLeftX(), dbRect->getLeftY()));
        }
        if (dbRect->getRight() == 1)
        {
          location.Points.insert(RightEyePoint, QPoint(dbRect->getRightX(), dbRect->getRightY()));
        }
        return location;
      }

      QSharedPointer<DBFaces> Detectors::getFace()
      {
        d_ref<Storage_Faces> dbFace(DBObj->getFace());
        if (dbFace.is_null())
        {
          QSharedPointer<DBFaces> face(new Faces(DBConnection));
          setFace(face);
          return face;
        }
        else
          return QSharedPointer<DBFaces>(new Faces(DBConnection, dbFace));
      }

      void Detectors::setType( const AlgType& Value )
      {
        DBObj->setType(Value.operator int());
      }

      void Detectors::setLocation( const AlgDetOutput& Value )
      {
        d_ref<Storage_FaceRect> dbRect(DBObj->getRect());
        dbRect->setX(Value.Rectangle.x());
        dbRect->setY(Value.Rectangle.y());
        dbRect->setWidth(Value.Rectangle.width());
        dbRect->setHeight(Value.Rectangle.height());
        using namespace algorithms::detection;
        if (Value.Points.contains(LeftEyePoint))
        {
          dbRect->setLeft(1);
          dbRect->setLeftX(Value.Points[LeftEyePoint].x());
          dbRect->setLeftY(Value.Points[LeftEyePoint].y());
        }
        else
        {
          dbRect->setLeft(0);
          dbRect->setLeftX(0);
          dbRect->setLeftY(0);
        }
        if (Value.Points.contains(RightEyePoint))
        {
          dbRect->setRight(1);
          dbRect->setRightX(Value.Points[RightEyePoint].x());
          dbRect->setRightY(Value.Points[RightEyePoint].y());
        }
        else
        {
          dbRect->setRight(0);
          dbRect->setRightX(0);
          dbRect->setRightY(0);
        }
      }

      void Detectors::setFace( const QSharedPointer<DBFaces>& Value )
      {
        DBObj->setFace(*qSharedPointerCast<Faces>(Value));
      }
    }
  }
}
