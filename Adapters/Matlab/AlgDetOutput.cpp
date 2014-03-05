#include "AlgDetOutput.h"

#include <mclcppclass.h>

#include <QtGlobal>

namespace adapters
{
  void Convert( mwArray& Output, const AlgDetOutput& Input )
  {
    const char* fields[] = {"x", "y", "width", "height", "leftx", "lefty", "rightx", "righty", "left", "right"};
    mwArray modelShape(1, 1, 10, fields);
    const QRect& rect(Input.Rectangle);
    modelShape.Get(fields[0], 1, 1).Set(mwArray(static_cast<qreal>(rect.x())));
    modelShape.Get(fields[1], 1, 1).Set(mwArray(static_cast<qreal>(rect.y())));
    modelShape.Get(fields[2], 1, 1).Set(mwArray(static_cast<qreal>(rect.width())));
    modelShape.Get(fields[3], 1, 1).Set(mwArray(static_cast<qreal>(rect.height())));
    using namespace algorithms::detection;
    if (Input.Points.contains(LeftEyePoint))
    {
      const QPoint& leftEye(Input.Points[LeftEyePoint]);
      modelShape.Get(fields[4], 1, 1).Set(mwArray(static_cast<qreal>(leftEye.x())));
      modelShape.Get(fields[5], 1, 1).Set(mwArray(static_cast<qreal>(leftEye.y())));
      modelShape.Get(fields[8], 1, 1).Set(mwArray(1.0f));
    }
    else
    {
      modelShape.Get(fields[4], 1, 1).Set(mwArray(0.0f));
      modelShape.Get(fields[5], 1, 1).Set(mwArray(0.0f));
      modelShape.Get(fields[8], 1, 1).Set(mwArray(0.0f));
    }

    if (Input.Points.contains(RightEyePoint))
    {
      const QPoint& rightEye(Input.Points[RightEyePoint]);
      modelShape.Get(fields[6], 1, 1).Set(mwArray(static_cast<qreal>(rightEye.x())));
      modelShape.Get(fields[7], 1, 1).Set(mwArray(static_cast<qreal>(rightEye.y())));
      modelShape.Get(fields[9], 1, 1).Set(mwArray(1.0f));
    }
    else
    {
      modelShape.Get(fields[6], 1, 1).Set(mwArray(0.0f));
      modelShape.Get(fields[7], 1, 1).Set(mwArray(0.0f));
      modelShape.Get(fields[9], 1, 1).Set(mwArray(0.0f));
    }
    Output.Set(modelShape);
  }
}
