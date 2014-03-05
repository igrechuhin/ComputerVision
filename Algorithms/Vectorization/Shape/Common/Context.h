#ifndef ALGORITHMS_VECTORIZATION_SHAPE_COMMON_CONTEXT_H
#define ALGORITHMS_VECTORIZATION_SHAPE_COMMON_CONTEXT_H

#include "../../../Common/Algorithms.h"

#include <QMultiMap>
#include <QVector>
#include <QPoint>

namespace algorithms
{
  namespace vectorization
  {
    namespace shape
    {
      struct Input
      {
        AlgType Detector;
      };

      struct Output
      {
        QVector<QPoint> Value;
      };
    }
    
    struct Shape
    {
      shape::Input In;
      QMultiMap<AlgType, shape::Output> Out;
    };
  }
}

typedef algorithms::vectorization::shape::Input AlgVecShpInput;
typedef algorithms::vectorization::shape::Output AlgVecShpOutput;
typedef QMultiMap<AlgType, AlgVecShpOutput> AlgVecShpOutputMap;
typedef algorithms::vectorization::Shape AlgVecShpInOut;

QDataStream& operator>>( QDataStream& Stream, AlgVecShpInOut& Out );
QDataStream& operator<<( QDataStream& Stream, const AlgVecShpInOut& In );

#endif // ALGORITHMS_VECTORIZATION_SHAPE_COMMON_CONTEXT_H
