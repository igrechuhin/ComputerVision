#include "Shapes.h"

#include "Faces.h"

#include "Adapters/Storage_Point.h"

namespace plugins
{
  namespace databases
  {
    namespace cache
    {
      Shapes::Shapes( Database* Connection, const QString& ID /*= QString()*/, bool SaveOnDestroy/* = false*/ )
        : Object<Storage_Shapes>(Connection, ID, SaveOnDestroy)
      {
      }

      Shapes::Shapes( Database* Connection, d_ref<Storage_Shapes> Other )
        : Object<Storage_Shapes>(Connection, Other)
      {
      }

      Shapes::~Shapes()
      {
      }

      QVector<QPoint> Shapes::getShape()
      {
        QVector<QPoint> shape;
        d_ref< d_obj_vector<Storage_Point> > dbShape(DBObj->getShape());
        for (qint16 pointIndex(0); pointIndex < dbShape->size(); pointIndex++)
        {
          d_ref<Storage_Point> dbPoint((*dbShape)[pointIndex]);
          shape.push_back(QPoint(dbPoint->getX(), dbPoint->getY()));
        }
        return shape;
      }

      QSharedPointer<DBFaces> Shapes::getFace()
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

      void Shapes::setShape( const QVector<QPoint>& Value )
      {
        d_ref< d_obj_vector<Storage_Point> > dbShapeVector(d_obj_vector<Storage_Point>::create_new(DBConnection));
        for (int pointIndex(0); pointIndex < Value.size(); pointIndex++)
        {
          const QPoint& point(Value[pointIndex]);
          d_ref<Storage_Point> dbPoint(Storage_Point::create_new(DBConnection));
          dbPoint->setX(point.x());
          dbPoint->setY(point.y());
          dbShapeVector->push_back(dbPoint);
        }
        DBObj->setShape(dbShapeVector);
      }

      void Shapes::setFace( const QSharedPointer<DBFaces>& Value )
      {
        DBObj->setFace(*qSharedPointerCast<Faces>(Value));
      }
    }
  }
}
