#ifndef PLUGINS_SOURCES_VIDEOSOURCE_H
#define PLUGINS_SOURCES_VIDEOSOURCE_H

#include "../Interface.h"

#include <QObject>

#include <highgui_c.h>

namespace plugins
{
  namespace sources
  {
    class Video : public QObject, Interface
    {
      Q_OBJECT
      Q_INTERFACES(SrcInterface)

    public:
      Video();
      virtual ~Video();

      virtual bool canProcess( const QString& SourceURI = QString() ) const;

      virtual bool open( const QString& SourceURI = QString() );
      virtual void close();

      virtual bool haveMoreFrames() const;
      virtual bool isSeekable() const { return true; }

      virtual qint64 getPosition() const;
      virtual void setPosition( const qint64& Pos );
      virtual qint64 getTotalFrames() const { return TotalFrames; }

      virtual void getCurrentFrame( Frame& FrameRef );
      virtual void getNextFrame( Frame& FrameRef );

      virtual double getFPS() const;

      virtual QString getName() const  { return tr("Video"); }
      virtual QStringList getFilters() const;

    private:
      CvCapture* VideoFile;
      qint64 TotalFrames;
      qreal FPS;
      Frame CurrentFrame;
    };
  }
}

#endif // PLUGINS_SOURCES_VIDEOSOURCE_H
