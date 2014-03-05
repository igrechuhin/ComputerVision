#ifndef ALGORITHMS_COMMON_ALGORITHMS_H
#define ALGORITHMS_COMMON_ALGORITHMS_H

#include <QDataStream>

namespace algorithms
{
  enum Type
  {
    AlgorithmsBegin,

    AlgorithmsDetectorsBegin = AlgorithmsBegin,
    AlgorithmsDetectorViolaJones,
    AlgorithmsDetectorRowley,
    AlgorithmsDetectorsEnd,
    
    AlgorithmsVectorizationsBegin = AlgorithmsDetectorsEnd,
    AlgorithmsVectorizationActiveShapeModel,
    AlgorithmsVectorizationsEnd,

    AlgorithmsEnd
  };
}

Q_DECLARE_FLAGS(AlgType, algorithms::Type)

QDataStream& operator>>( QDataStream& Stream, AlgType& Value );
QDataStream& operator<<( QDataStream& Stream, const AlgType& Value );

#endif // ALGORITHMS_COMMON_ALGORITHMS_H
