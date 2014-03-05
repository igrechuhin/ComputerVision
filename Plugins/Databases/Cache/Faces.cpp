#include "Faces.h"

#include "Photos.h"
#include "Persons.h"
#include "Detectors.h"
#include "Shapes.h"

namespace plugins
{
  namespace databases
  {
    namespace cache
    {
      Faces::Faces( Database* Connection, const QString& ID /*= QString()*/, bool SaveOnDestroy/* = false*/ )
        : Object<Storage_Faces>(Connection, ID, SaveOnDestroy)
      {
      }

      Faces::Faces( Database* Connection, d_ref<Storage_Faces> Other )
        : Object<Storage_Faces>(Connection, Other)
      {
      }

      Faces::~Faces()
      {
      }

      quint8 Faces::getAge()
      {
        return DBObj->getAge();
      }

      BoolQueries Faces::getClosedForehead()
      {
        return DBObj->getClosedForehead() ? BoolTrue : BoolFalse;
      }

      BoolQueries Faces::getClosedEyebrow()
      {
        return DBObj->getClosedEyebrow() ? BoolTrue : BoolFalse;
      }

      BoolQueries Faces::getGlasses()
      {
        return DBObj->getGlasses() ? BoolTrue : BoolFalse;
      }

      BoolQueries Faces::getMoustache()
      {
        return DBObj->getMoustache() ? BoolTrue : BoolFalse;
      }

      BoolQueries Faces::getBeard()
      {
        return DBObj->getBeard() ? BoolTrue : BoolFalse;
      }

      qint32 Faces::getBetweenEyesDistance()
      {
        return DBObj->getBetweenEyesDistance();
      }

      OrientationQueries Faces::getOrientation()
      {
        switch (DBObj->getOrientation())
        {
        case 12: return Orientation12;
        case 13: return Orientation13;
        case 14: return Orientation14;
        case 21: return Orientation21;
        case 22: return Orientation22;
        case 23: return Orientation23;
        case 24: return Orientation24;
        case 25: return Orientation25;
        case 32: return Orientation32;
        case 33: return Orientation33;
        case 34: return Orientation34;
        default: return OrientationEmpty;
        }
      }

      QSharedPointer<DBPhotos> Faces::getPhoto()
      {
        d_ref<Storage_Photos> dbPhoto(DBObj->getPhoto());
        if (dbPhoto.is_null())
        {
          QSharedPointer<DBPhotos> photo(new Photos(DBConnection));
          setPhoto(photo);
          return photo;
        }
        else
          return QSharedPointer<DBPhotos>(new Photos(DBConnection, dbPhoto));
      }

      QSharedPointer<DBPersons> Faces::getPerson()
      {
        d_ref<Storage_Persons> dbPerson(DBObj->getPerson());
        if (dbPerson.is_null())
        {
          QSharedPointer<DBPersons> person(new Persons(DBConnection));
          setPerson(person);
          return person;
        }
        else
          return QSharedPointer<DBPersons>(new Persons(DBConnection, dbPerson));
      }

      QList<QSharedPointer<DBDetectors> > Faces::getDetectors()
      {
        QList<QSharedPointer<DBDetectors> > detectorsPtrs;
        d_ref< d_relationship<Storage_Detectors> > dbDetectors(DBObj->getDetectors());
        for (d_relationship<Storage_Detectors>::iterator dbDetector(dbDetectors->begin()); dbDetector != dbDetectors->end(); ++dbDetector)
        {
          detectorsPtrs.append(QSharedPointer<DBDetectors>(new Detectors(DBConnection, *dbDetector)));
        }
        return detectorsPtrs;
      }

      QList<QSharedPointer<DBShapes> > Faces::getShapes()
      {
        QList<QSharedPointer<DBShapes> > shapesPtrs;
        d_ref< d_relationship<Storage_Shapes> > dbShapes(DBObj->getShapes());
        for (d_relationship<Storage_Shapes>::iterator dbShape(dbShapes->begin()); dbShape != dbShapes->end(); ++dbShape)
        {
          shapesPtrs.append(QSharedPointer<DBShapes>(new Shapes(DBConnection, *dbShape)));
        }
        return shapesPtrs;
      }

      void Faces::setAge( const quint8& Value )
      {
        DBObj->setAge(Value);
      }

      void Faces::setClosedForehead( const BoolQueries& Value )
      {
        Q_ASSERT(Value.testFlag(BoolTrue) || Value.testFlag(BoolFalse));
        DBObj->setClosedForehead(Value.testFlag(BoolTrue));
      }

      void Faces::setClosedEyebrow( const BoolQueries& Value )
      {
        Q_ASSERT(Value.testFlag(BoolTrue) || Value.testFlag(BoolFalse));
        DBObj->setClosedEyebrow(Value.testFlag(BoolTrue));
      }

      void Faces::setGlasses( const BoolQueries& Value )
      {
        Q_ASSERT(Value.testFlag(BoolTrue) || Value.testFlag(BoolFalse));
        DBObj->setGlasses(Value.testFlag(BoolTrue));
      }

      void Faces::setMoustache( const BoolQueries& Value )
      {
        Q_ASSERT(Value.testFlag(BoolTrue) || Value.testFlag(BoolFalse));
        DBObj->setMoustache(Value.testFlag(BoolTrue));
      }

      void Faces::setBeard( const BoolQueries& Value )
      {
        Q_ASSERT(Value.testFlag(BoolTrue) || Value.testFlag(BoolFalse));
        DBObj->setBeard(Value.testFlag(BoolTrue));
      }

      void Faces::setBetweenEyesDistance( const qint32& Value )
      {
        DBObj->setBetweenEyesDistance(Value);
      }

      void Faces::setOrientation( const OrientationQueries& Value )
      {
        bool haveOrientation(false);
        for (int orient(Orientation12); orient <= Orientation34; orient *= 2)
        {
          if (Value.testFlag(static_cast<OrientationQuery>(orient)))
          {
            Q_ASSERT(!haveOrientation);
            int dbOrient(0);
            switch (orient)
            {
            case Orientation12: dbOrient = 12; break;
            case Orientation13: dbOrient = 13; break;
            case Orientation14: dbOrient = 14; break;
            case Orientation21: dbOrient = 21; break;
            case Orientation22: dbOrient = 22; break;
            case Orientation23: dbOrient = 23; break;
            case Orientation24: dbOrient = 24; break;
            case Orientation25: dbOrient = 25; break;
            case Orientation32: dbOrient = 32; break;
            case Orientation33: dbOrient = 33; break;
            case Orientation34: dbOrient = 34; break;
            default: Q_ASSERT(false);
            }
            haveOrientation = true;
            DBObj->setOrientation(dbOrient);
          }
        }
        Q_ASSERT(haveOrientation);
      }

      void Faces::setPhoto( const QSharedPointer<DBPhotos>& Value )
      {
        DBObj->setPhoto(*qSharedPointerCast<Photos>(Value));
      }

      void Faces::setPerson( const QSharedPointer<DBPersons>& Value )
      {
        DBObj->setPerson(*qSharedPointerCast<Persons>(Value));
      }

      void Faces::addDetector( const QSharedPointer<DBDetectors>& Value )
      {
        Q_ASSERT(!"TODO");
      }

      void Faces::addShape( const QSharedPointer<DBShapes>& Value )
      {
        Q_ASSERT(!"TODO");
      }
    }
  }
}
