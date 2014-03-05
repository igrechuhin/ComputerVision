#include "Capture.h"

namespace
{
  const double DEFAULT_CAMERA_FPS(30);
}

namespace plugins
{
  namespace sources
  {
    Capture::Capture()
      : Camera(NULL)
    {
    }

    Capture::~Capture()
    {
      close();
    }

    bool Capture::canProcess( const QString& SourceURI /*= QString() */ ) const
    {
      return SourceURI.isEmpty();
    }

    bool Capture::open( const QString& SourceURI /*= QString()*/ )
    {
      Q_ASSERT(canProcess(SourceURI));
      Camera = cvCreateCameraCapture(0);
      return Camera != NULL;
    }

    void Capture::close()
    {
      if (Camera)
        cvReleaseCapture(&Camera);
    }

    bool Capture::haveMoreFrames() const
    {
      return true;
    }

    void Capture::getCurrentFrame( Frame& FrameRef )
    {
      const IplImage* image(cvQueryFrame(Camera));
      Q_ASSERT(image);
      FrameRef = image;
    }

    void Capture::getNextFrame( Frame& FrameRef )
    {
      getCurrentFrame(FrameRef);
    }

    double Capture::getFPS() const
    {
      return DEFAULT_CAMERA_FPS;
    }

    QStringList Capture::getFilters() const
    {
      return QStringList();
    }
  }
}

Q_EXPORT_PLUGIN2(Capture, plugins::sources::Capture);
