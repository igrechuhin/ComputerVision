#include "Persons.h"

#include "Faces.h"

namespace plugins
{
  namespace databases
  {
    namespace cache
    {
      Persons::Persons( Database* Connection, const QString& ID /*= QString()*/, bool SaveOnDestroy/* = false*/ )
        : Object<Storage_Persons>(Connection, ID, SaveOnDestroy)
      {
      }

      Persons::Persons( Database* Connection, d_ref<Storage_Persons> Other )
        : Object<Storage_Persons>(Connection, Other)
      {
      }

      Persons::~Persons()
      {
      }

      BoolQueries Persons::getGender()
      {
        return DBObj->getGender() ? BoolTrue : BoolFalse;
      }

      QList<QSharedPointer<DBFaces> > Persons::getFaces()
      {
        QList<QSharedPointer<DBFaces> > facesPtrs;
        d_ref< d_relationship<Storage_Faces> > dbFaces(DBObj->getFaces());
        for (d_relationship<Storage_Faces>::iterator dbFace(dbFaces->begin()); dbFace != dbFaces->end(); ++dbFace)
        {
          facesPtrs.append(QSharedPointer<DBFaces>(new Faces(DBConnection, *dbFace)));
        }
        return facesPtrs;
      }

      void Persons::setGender( const BoolQueries& Value )
      {
        Q_ASSERT(Value.testFlag(BoolTrue) || Value.testFlag(BoolFalse));
        DBObj->setGender(Value.testFlag(BoolTrue));
      }

      void Persons::addFace( const QSharedPointer<DBFaces>& Value )
      {
        Q_ASSERT(!"TODO");
      }
    }
  }
}
