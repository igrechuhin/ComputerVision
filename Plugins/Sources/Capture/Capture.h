#ifndef PLUGINS_SOURCES_CAPTURESOURCE_H
#define PLUGINS_SOURCES_CAPTURESOURCE_H

#include "../Interface.h"

#include <QObject>

#include <highgui_c.h>

namespace plugins
{
  namespace sources
  {
    class Capture : public QObject, Interface
    {
      Q_OBJECT
      Q_INTERFACES(SrcInterface)

    public:
      Capture();
      virtual ~Capture();

      virtual bool canProcess( const QString& SourceURI = QString() ) const;

      virtual bool open( const QString& SourceURI = QString() );
      virtual void close();

      virtual bool haveMoreFrames() const;
      virtual bool isSeekable() const { return false; }

      virtual qint64 getPosition() const { return 0; }
      virtual void setPosition( const qint64& /*Pos*/ ) {}
      virtual qint64 getTotalFrames() const { return 0; }

      virtual void getCurrentFrame( Frame& FrameRef );
      virtual void getNextFrame( Frame& FrameRef );

      virtual double getFPS() const;

      virtual QString getName() const  { return tr("Camera"); }
      virtual QStringList getFilters() const;

    private:
      CvCapture* Camera;
    };
  }
}

#endif // PLUGINS_SOURCES_CAPTURESOURCE_H
