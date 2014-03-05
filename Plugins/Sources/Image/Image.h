#ifndef PLUGINS_SOURCES_IMAGESOURCE_H
#define PLUGINS_SOURCES_IMAGESOURCE_H

#include "../Interface.h"

#include <QObject>

namespace plugins
{
  namespace sources
  {
    class Image : public QObject, Interface
    {
      Q_OBJECT
      Q_INTERFACES(SrcInterface)

    public:
      Image();
      virtual ~Image();

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

      virtual QString getName() const  { return tr("Image"); }
      virtual QStringList getFilters() const;

    private:
      bool QueriedFrame;
      Frame CurrentFrame;
    };
  }
}

#endif // PLUGINS_SOURCES_IMAGESOURCE_H
