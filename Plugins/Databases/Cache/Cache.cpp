#include "Cache.h"

#include "Photos.h"
#include "Faces.h"
#include "Persons.h"
#include "Detectors.h"
#include "Shapes.h"
#include "Info.h"

namespace
{
  d_list BoolQueriesToList( BoolQueries Value )
  {
    d_list cacheList;
    using namespace plugins::databases;
    if (Value.testFlag(BoolTrue))
    {
      cacheList.append_elem(d_int(1));
    }
    if (Value.testFlag(BoolFalse))
    {
      cacheList.append_elem(d_int(0));
    }
    return cacheList;
  }

  d_list OrientationQueriesToList( const FacesQueryMap& Query )
  {
    using namespace plugins::databases;
    OrientationQueries orientations(Query[Faces::QueryOrientationList].vorientation);
    d_list cacheList;
    if (orientations.testFlag(Orientation12)) cacheList.append_elem(d_int(12));
    if (orientations.testFlag(Orientation13)) cacheList.append_elem(d_int(13));
    if (orientations.testFlag(Orientation14)) cacheList.append_elem(d_int(14));
    if (orientations.testFlag(Orientation21)) cacheList.append_elem(d_int(21));
    if (orientations.testFlag(Orientation22)) cacheList.append_elem(d_int(22));
    if (orientations.testFlag(Orientation23)) cacheList.append_elem(d_int(23));
    if (orientations.testFlag(Orientation24)) cacheList.append_elem(d_int(24));
    if (orientations.testFlag(Orientation25)) cacheList.append_elem(d_int(25));
    if (orientations.testFlag(Orientation32)) cacheList.append_elem(d_int(32));
    if (orientations.testFlag(Orientation33)) cacheList.append_elem(d_int(33));
    if (orientations.testFlag(Orientation34)) cacheList.append_elem(d_int(34));
    return cacheList;
  }

  QStringList getIDsFromQuery( d_query& Query )
  {
    QStringList idList;
    std::string id;
    while (Query.fetch())
    {
      Query.get_data(&id);
      idList << QString::fromStdString(id);
    }
    return idList;
  }
}

namespace plugins
{
  namespace databases
  {
    Cache::Cache()
    {
    }

    Cache::~Cache()
    {
    }

    void Cache::openConnection( const QString& Host /*= cache::DEFAULT_HOST*/, const QString& Port /*= cache::DEFAULT_PORT*/, const QString& Namespace /*= cache::DEFAULT_NAMESPACE*/, const QString& User /*= cache::DEFAULT_USER*/, const QString& Password /*= cache::DEFAULT_PASSWORD */ )
    {
      Db_err connectionError;
      TCPConnection = tcp_conn::connect(std::string(Host.toStdString() + '[' + Port.toStdString() + "]:" + Namespace.toStdString()),
                                        User.toStdString(), Password.toStdString(), 0, &connectionError);
      Q_ASSERT(!connectionError);
    }

    QSharedPointer<Photos> Cache::getPhoto( const QString& ID/* = QString()*/, bool SaveOnDestroy/* = false*/ )
    {
      return QSharedPointer<Photos>(new cache::Photos(getDB(), ID, SaveOnDestroy));
    }

    QSharedPointer<Faces> Cache::getFace( const QString& ID /*= QString()*/, bool SaveOnDestroy/* = false*/ )
    {
      return QSharedPointer<Faces>(new cache::Faces(getDB(), ID, SaveOnDestroy));
    }

    QSharedPointer<Persons> Cache::getPerson( const QString& ID /*= QString()*/, bool SaveOnDestroy/* = false*/ )
    {
      return QSharedPointer<Persons>(new cache::Persons(getDB(), ID, SaveOnDestroy));
    }

    QSharedPointer<Detectors> Cache::getDetector( const QString& ID /*= QString()*/, bool SaveOnDestroy/* = false*/ )
    {
      return QSharedPointer<Detectors>(new cache::Detectors(getDB(), ID, SaveOnDestroy));
    }

    QSharedPointer<Shapes> Cache::getShape( const QString& ID /*= QString()*/, bool SaveOnDestroy/* = false*/ )
    {
      return QSharedPointer<Shapes>(new cache::Shapes(getDB(), ID, SaveOnDestroy));
    }

    QSharedPointer<Info> Cache::getInfo()
    {
      d_query dbQuery(getDB());
      Storage_Info::get_IDs(dbQuery);
      dbQuery.execute();
      QStringList ids(getIDsFromQuery(dbQuery));
      Q_ASSERT(ids.isEmpty() || ids.size() == 1);
      return QSharedPointer<Info>(new cache::Info(getDB(), ids.isEmpty() ? QString() : ids.first()));
    }

    QStringList Cache::getIDs( const PhotosQueryMap& Query )
    {
      int index(1);
      d_query dbQuery(getDB());
      if (Query.contains(Photos::QueryWidth) && Query.contains(Photos::QueryHeight) && Query.contains(Photos::QueryCRC))
      {
        Storage_Photos::get_ByWidthHeightCRC(dbQuery);
        dbQuery.set_par(index++, Query[Photos::QueryWidth].vint32);
        dbQuery.set_par(index++, Query[Photos::QueryHeight].vint32);
        dbQuery.set_par(index++, d_int(Query[Photos::QueryCRC].vint64));
      }
      else
      {
        Storage_Photos::get_Filtered(dbQuery);
        dbQuery.set_par(index++, Query[Photos::QueryWidthMin].vint32);
        dbQuery.set_par(index++, Query[Photos::QueryWidthMax].vint32);
        dbQuery.set_par(index++, Query[Photos::QueryHeightMin].vint32);
        dbQuery.set_par(index++, Query[Photos::QueryHeightMax].vint32);
        dbQuery.set_par(index++, Query[Photos::QueryColorDepthMin].vuint8);
        dbQuery.set_par(index++, Query[Photos::QueryColorDepthMax].vuint8);
        dbQuery.set_par(index++, Query[Photos::QueryMiddleBrightnessMin].vuint8);
        dbQuery.set_par(index++, Query[Photos::QueryMiddleBrightnessMax].vuint8);
        dbQuery.set_par(index++, Query[Photos::QueryFacesCountMin].vint16);
        dbQuery.set_par(index++, Query[Photos::QueryFacesCountMax].vint16);
      }
      dbQuery.execute();
      return getIDsFromQuery(dbQuery);
    }

    QStringList Cache::getIDs( const FacesQueryMap& Query )
    {
      int index(1);
      d_query dbQuery(getDB());
      Storage_Faces::get_Filtered(dbQuery);
      dbQuery.set_par(index++, Query[Faces::QueryAgeMin].vuint8);
      dbQuery.set_par(index++, Query[Faces::QueryAgeMax].vuint8);
      dbQuery.set_par(index++, BoolQueriesToList(Query[Faces::QueryClosedForeheadSet].vbool));
      dbQuery.set_par(index++, BoolQueriesToList(Query[Faces::QueryClosedEyebrowSet].vbool));
      dbQuery.set_par(index++, BoolQueriesToList(Query[Faces::QueryGlassesSet].vbool));
      dbQuery.set_par(index++, BoolQueriesToList(Query[Faces::QueryMoustacheSet].vbool));
      dbQuery.set_par(index++, BoolQueriesToList(Query[Faces::QueryBeardSet].vbool));
      dbQuery.set_par(index++, Query[Faces::QueryBetweenEyesDistanceMin].vint32);
      dbQuery.set_par(index++, Query[Faces::QueryBetweenEyesDistanceMax].vint32);
      dbQuery.set_par(index++, OrientationQueriesToList(Query));
      dbQuery.execute();
      return getIDsFromQuery(dbQuery);
    }

    QStringList Cache::getIDs( const PersonsQueryMap& Query )
    {
      int index(1);
      d_query dbQuery(getDB());
      Storage_Persons::get_Filtered(dbQuery);
      dbQuery.set_par(index++, BoolQueriesToList(Query[Persons::QueryGenderSet].vbool));
      dbQuery.execute();
      return getIDsFromQuery(dbQuery);
    }

    QStringList Cache::getIDs( const DetectorsQueryMap& Query )
    {
      int index(1);
      d_query dbQuery(getDB());
      Q_ASSERT(!"TODO");
      dbQuery.execute();
      return getIDsFromQuery(dbQuery);
    }

    QStringList Cache::getIDs( const ShapesQueryMap& Query )
    {
      int index(1);
      d_query dbQuery(getDB());
      Q_ASSERT(!"TODO");
      dbQuery.execute();
      return getIDsFromQuery(dbQuery);
    }

    Database* Cache::getDB()
    {
      if (DBConnection.isNull())
        DBConnection.reset(new Database(TCPConnection));
      return DBConnection.data();
    }
  }
}

Q_EXPORT_PLUGIN2(Cache, plugins::databases::Cache);