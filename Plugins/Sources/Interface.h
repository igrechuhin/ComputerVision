#ifndef PLUGINS_SOURCES_INTERFACE_H
#define PLUGINS_SOURCES_INTERFACE_H

#include "../../Common/Frame/Frame.h"

#include <QString>
#include <QStringList>
#include <QtPlugin>

namespace plugins
{
  namespace sources
  {
    using namespace common;
    class Interface
    {
    public:
      virtual ~Interface() {}

      virtual bool canProcess( const QString& SourceURI = QString() ) const = 0;

      virtual bool open( const QString& SourceURI = QString() ) = 0;
      virtual void close() = 0;

      virtual bool haveMoreFrames() const = 0;
      virtual bool isSeekable() const = 0;

      virtual qint64 getPosition() const = 0;
      virtual void setPosition( const qint64& Pos ) = 0;
      virtual qint64 getTotalFrames() const = 0;

      virtual void getCurrentFrame( Frame& FrameRef ) = 0;
      virtual void getNextFrame( Frame& FrameRef ) = 0;

      virtual double getFPS() const = 0;

      virtual QString getName() const = 0;
      virtual QStringList getFilters() const = 0;
    };
  }
}

typedef plugins::sources::Interface SrcInterface;
typedef QList<SrcInterface*> SrcList;

Q_DECLARE_INTERFACE(SrcInterface, "com.pfpi.Plugins.Sources.Interface/1.0");

#endif // PLUGINS_SOURCES_INTERFACE_H
