#ifndef COMMON_MODELS_MEANSHAPE_H
#define COMMON_MODELS_MEANSHAPE_H

#include "ModelT.h"

#include "../../../Algorithms/Common/Algorithms.h"

#include "../../Math/Matrix.h"

#include <QVector>

namespace common
{
  namespace models
  {
    struct MeanShape
    {
      MeanShape()
        : Value(),
          FaceWidth(0)
      {
        for (int index(algorithms::AlgorithmsDetectorsBegin); index < algorithms::AlgorithmsDetectorsEnd; index++)
        {
          Detectors[index].Scale = 0;
          Detectors[index].Shift = QPointF();
        }
      }

      QVector<QPointF> Value;
      qreal FaceWidth;
      struct
      {
        qreal Scale;
        QPointF Shift;
      } Detectors[algorithms::AlgorithmsDetectorsEnd];
    };
  }
}

QDataStream& operator >> (QDataStream& Stream, common::models::MeanShape& Value);
QDataStream& operator << (QDataStream& Stream, const common::models::MeanShape& Value);

#endif // COMMON_MODELS_MEANSHAPE_H