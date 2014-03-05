#include "ViolaJones.h"

#include "../../../Common/Settings/Settings.h"

#include <objdetect.hpp>
#include <core_c.h>

#include <QApplication>
#include <QDir>

namespace algorithms
{
  namespace detection
  {
    ViolaJones::ViolaJones()
      : Storage(NULL),
        ClassifierCascade(NULL)
    {
    }

    ViolaJones::~ViolaJones()
    {
      if (ClassifierCascade)
      {
        cvReleaseHaarClassifierCascade(&ClassifierCascade);
      }
      if (Storage)
      {
        cvReleaseMemStorage(&Storage);
      }
    }

    bool ViolaJones::init( ContextType& Context )
    {
      Storage = cvCreateMemStorage(0);
      Q_ASSERT(Storage);

      QDir dataDir(qApp->applicationDirPath());
      QString vjDataPath(common::Settings().get(common::Settings::SettingsDataDetectionPath).toString());
      vjDataPath += getName().prepend("/");
      bool dirExist(dataDir.cd(vjDataPath));
      Q_ASSERT(dirExist);
      if (dirExist)
      {
        QByteArray classifierFileName(dataDir.absoluteFilePath(Context.Detection.In.HaarCascadeClassifierFileName).toAscii());
        ClassifierCascade = reinterpret_cast<CvHaarClassifierCascade*>(cvLoad(classifierFileName.constData(), 0, 0, 0));
        Q_ASSERT(ClassifierCascade);
      }

      return Storage && ClassifierCascade;
    }

    void ViolaJones::process( ContextType& Context, const Frame& Image )
    {
      Context.Detection.Out.remove(getType());
      if (!Storage || !ClassifierCascade)
        return;

      CvSeq* objects(cvHaarDetectObjects(&(Image.operator IplImage()), ClassifierCascade, Storage,
                                          Context.Detection.In.ScaleFactor,
                                          4, // Min neighbors
                                          CV_HAAR_DO_CANNY_PRUNING,
                                          cvSize(Context.Detection.In.MinObjectSize.width(),
                                                 Context.Detection.In.MinObjectSize.height())));
      if (!objects)
        return;
      for (qint32 objectIndex(1); objectIndex <= objects->total; objectIndex++)
      {
        CvRect* cvFaceRect = (CvRect*)cvGetSeqElem(objects, objectIndex);
        Output objectPos;
        objectPos.Rectangle.setX(cvFaceRect->x);
        objectPos.Rectangle.setY(cvFaceRect->y);
        objectPos.Rectangle.setWidth(cvFaceRect->width);
        objectPos.Rectangle.setHeight(cvFaceRect->height);

        Context.Detection.Out.insert(getType(), objectPos);
      }
    }
  }
}

Q_EXPORT_PLUGIN2(ViolaJones, algorithms::detection::ViolaJones);
