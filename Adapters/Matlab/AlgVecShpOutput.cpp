#include "AlgVecShpOutput.h"

#include <mclcppclass.h>

#include <QtGlobal>

namespace adapters
{
  void Convert( QVector<AlgVecShpOutput>& Output, const mwArray& Input )
  {
    int shapesCount(Input.NumberOfElements());
    Output.clear();
    for (int shapeIndex(1); shapeIndex <= shapesCount ; shapeIndex++)
    {
      const mwArray mwShape(Input.Get(2, shapeIndex, 1));
      mwArray dimensions(mwShape.GetDimensions());
      Q_ASSERT(dimensions.NumberOfElements() == 2);
      int pointsCount(dimensions.Get(1,1));
      AlgVecShpOutput shape;
      for (int pointIndex(1); pointIndex <= pointsCount; pointIndex++)
      {
        int pointX(static_cast<int>(mwShape.Get(2, pointIndex, 1)));
        int pointY(static_cast<int>(mwShape.Get(2, pointIndex, 2)));
        shape.Value << QPoint(pointX, pointY);
      }
      Output << shape;
    }
  }
}