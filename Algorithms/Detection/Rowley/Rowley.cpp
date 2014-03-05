#include "Rowley.h"

#include "../../../Common/Settings/Settings.h"

#include "detect.h"

#include <QByteArray>
#include <QSize>
#include <QList>
#include <QApplication>
#include <QDir>

namespace algorithms
{
  namespace detection
  {
    Rowley::Rowley()
    {
    }

    Rowley::~Rowley()
    {
    }

    bool Rowley::init( ContextType& Context )
    {
      QDir dataDir(qApp->applicationDirPath());
      QString rowleyDataPath(common::Settings().get(common::Settings::SettingsDataDetectionPath).toString());
      rowleyDataPath += getName().prepend("/");
      bool dirExist(dataDir.cd(rowleyDataPath));
      Q_ASSERT(dirExist);
      if (dirExist)
      {
        SetDataPath(dataDir.absolutePath().toAscii().data());
      }
      return dirExist;
    }

    void Rowley::process( ContextType& Context, const Frame& Image )
    {
      Context.Detection.Out.remove(getType());
      Frame grayImage;
      convertColor(grayImage, Image, CV_RGB2GRAY);
      Q_ASSERT(grayImage.isContinuous());
      QList<Output> foundObjs(Track_FindAllFacesRegion(Context.Detection.In.MinObjectSize,
                                          grayImage.width(), grayImage.height(),
                                          reinterpret_cast<char*>(grayImage.ptr(0))));
      foreach(const Output& objectPos, foundObjs)
      {
        Context.Detection.Out.insert(getType(), objectPos);
      }
    }
  }
}

Q_EXPORT_PLUGIN2(Rowley, algorithms::detection::Rowley);
