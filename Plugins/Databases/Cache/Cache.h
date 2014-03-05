#ifndef PLUGINS_DATABASES_CACHE_H
#define PLUGINS_DATABASES_CACHE_H

#include "../Interface.h"

#include <connection.h>
#include <query.h>

#include <QScopedPointer>
#include <QObject>

namespace plugins
{
  namespace databases
  {
    class Cache : public QObject, Interface
    {
      Q_OBJECT
      Q_INTERFACES(DBInterface)

    public:
      Cache();
      virtual ~Cache();

      virtual void openConnection( const QString& Host, const QString& Port, const QString& Namespace, const QString& User, const QString& Password);

      virtual QSharedPointer<Photos> getPhoto( const QString& ID = QString(), bool SaveOnDestroy = false );
      virtual QSharedPointer<Faces> getFace( const QString& ID = QString(), bool SaveOnDestroy = false );
      virtual QSharedPointer<Persons> getPerson( const QString& ID = QString(), bool SaveOnDestroy = false );
      virtual QSharedPointer<Detectors> getDetector( const QString& ID = QString(), bool SaveOnDestroy = false );
      virtual QSharedPointer<Shapes> getShape( const QString& ID = QString(), bool SaveOnDestroy = false );
      virtual QSharedPointer<Info> getInfo();

      virtual QStringList getIDs( const PhotosQueryMap& Query );
      virtual QStringList getIDs( const FacesQueryMap& Query );
      virtual QStringList getIDs( const PersonsQueryMap& Query );
      virtual QStringList getIDs( const DetectorsQueryMap& Query );
      virtual QStringList getIDs( const ShapesQueryMap& Query );

    private:
      Database* getDB();

    private:
      d_connection TCPConnection;
      QScopedPointer<Database> DBConnection;
    };
  }
}

#endif // PLUGINS_DATABASES_CACHE_H
