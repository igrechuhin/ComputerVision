#include "Video.h"

namespace
{
  const qint64 FRAMES_DROP_AT_END(2);
}

namespace plugins
{
  namespace sources
  {
    Video::Video()
      : VideoFile(NULL),
      TotalFrames(0)
    {
    }

    Video::~Video()
    {
      close();
    }

    bool Video::canProcess( const QString& SourceURI /*= QString() */ ) const
    {
      foreach(const QString& ext, getFilters())
      {
        if (SourceURI.right(SourceURI.size() - SourceURI.lastIndexOf('.')) == ext.right(ext.size() - ext.lastIndexOf('.')))
          return true;
      }
      return false;
    }

    bool Video::open( const QString& SourceURI /*= QString() */ )
    {
      Q_ASSERT(canProcess(SourceURI));
      VideoFile = cvCreateFileCapture(SourceURI.toAscii().constData());
      Q_ASSERT(VideoFile);
      TotalFrames = qMax(Q_INT64_C(0), static_cast<qint64>(cvGetCaptureProperty(VideoFile, CV_CAP_PROP_FRAME_COUNT)) - FRAMES_DROP_AT_END);
      Q_ASSERT(TotalFrames > 0);
      FPS = cvGetCaptureProperty(VideoFile, CV_CAP_PROP_FPS);
      return VideoFile != NULL;
    }

    void Video::close()
    {
      if (VideoFile)
      {
        cvReleaseCapture(&VideoFile);
      }
    }

    bool Video::haveMoreFrames() const
    {
      return getPosition() < TotalFrames;
    }

    qint64 Video::getPosition() const
    {
      return qBound(Q_INT64_C(0), static_cast<qint64>(cvGetCaptureProperty(VideoFile, CV_CAP_PROP_POS_FRAMES)), TotalFrames);
    }

    void Video::setPosition( const qint64& Pos )
    {
      cvSetCaptureProperty(VideoFile, CV_CAP_PROP_POS_FRAMES, qBound(Q_INT64_C(0), Pos, TotalFrames));
    }

    void Video::getCurrentFrame( Frame& FrameRef )
    {
      const IplImage* image(cvQueryFrame(VideoFile));
      Q_ASSERT(image);
      CurrentFrame = image;
      FrameRef = CurrentFrame;
    }

    void Video::getNextFrame( Frame& FrameRef )
    {
      getCurrentFrame(FrameRef);
    }

    double Video::getFPS() const
    {
      return FPS;
    }

    QStringList Video::getFilters() const
    {
      QStringList extensions;
      extensions << "*.avi" << "*.mpg";
      return extensions;
    }
  }
}

Q_EXPORT_PLUGIN2(Video, plugins::sources::Video);
