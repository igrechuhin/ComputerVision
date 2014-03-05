#include "Image.h"

namespace
{
  const double DEFAULT_IMAGE_FPS(1000); // image is shot at once
}

namespace plugins
{
  namespace sources
  {
    Image::Image()
      : QueriedFrame(false)
    {
    }

    Image::~Image()
    {
    }

    bool Image::canProcess( const QString& SourceURI /*= QString() */ ) const
    {
      foreach(const QString& ext, getFilters())
      {
        if (SourceURI.right(SourceURI.size() - SourceURI.lastIndexOf('.')) == ext.right(ext.size() - ext.lastIndexOf('.')))
          return true;
      }
      return false;
    }

    bool Image::open( const QString& SourceURI /*= QString() */ )
    {
      Q_ASSERT(canProcess(SourceURI));
      CurrentFrame = Frame(SourceURI);
      return !CurrentFrame.empty();
    }

    void Image::close()
    {
    }

    bool Image::haveMoreFrames() const
    {
      return !QueriedFrame;
    }

    void Image::getCurrentFrame( Frame& FrameRef )
    {
      QueriedFrame = true;
      FrameRef = CurrentFrame;
    }

    void Image::getNextFrame( Frame& FrameRef )
    {
      getCurrentFrame(FrameRef);
    }

    double Image::getFPS() const
    {
      return DEFAULT_IMAGE_FPS;
    }

    QStringList Image::getFilters() const
    {
      QStringList extensions;
      extensions << "*.bmp" << "*.gif" << "*.jpg" << "*.jpeg" << "*.png" << "*.pbm" << "*.pgm" << "*.ppm" << "*.tiff" << "*.xbm" << "*.xpm";
      return extensions;
    }
  }
}

Q_EXPORT_PLUGIN2(Image, plugins::sources::Image);