#ifndef PLUGINS_DATABASES_INTERFACE_H
#define PLUGINS_DATABASES_INTERFACE_H

#include "Types/Photos.h"
#include "Types/Faces.h"
#include "Types/Persons.h"
#include "Types/Detectors.h"
#include "Types/Shapes.h"
#include "Types/Info.h"

#include <QtPlugin>
#include <QSharedPointer>
#include <QStringList>
#include <QMap>

namespace plugins
{
  namespace databases
  {
    class Interface
    {
    public:
      virtual ~Interface() {}

      virtual void openConnection( const QString& Host, const QString& Port, const QString& Namespace, const QString& User, const QString& Password ) = 0;

      virtual QSharedPointer<Photos> getPhoto( const QString& ID = QString(), bool SaveOnDestroy = false ) = 0;
      virtual QSharedPointer<Faces> getFace( const QString& ID = QString(), bool SaveOnDestroy = false ) = 0;
      virtual QSharedPointer<Persons> getPerson( const QString& ID = QString(), bool SaveOnDestroy = false ) = 0;
      virtual QSharedPointer<Detectors> getDetector( const QString& ID = QString(), bool SaveOnDestroy = false ) = 0;
      virtual QSharedPointer<Shapes> getShape( const QString& ID = QString(), bool SaveOnDestroy = false ) = 0;
      virtual QSharedPointer<Info> getInfo() = 0;

      virtual QStringList getIDs( const PhotosQueryMap& Query ) = 0;
      virtual QStringList getIDs( const FacesQueryMap& Query ) = 0;
      virtual QStringList getIDs( const PersonsQueryMap& Query ) = 0;
      virtual QStringList getIDs( const DetectorsQueryMap& Query ) = 0;
      virtual QStringList getIDs( const ShapesQueryMap& Query ) = 0;
    };
  }
}

typedef plugins::databases::Interface DBInterface;
typedef QList<DBInterface*> DBList;

Q_DECLARE_INTERFACE(DBInterface, "com.pfpi.Plugins.Databases.Interface/1.0");

#endif // PLUGINS_DATABASES_INTERFACE_H
