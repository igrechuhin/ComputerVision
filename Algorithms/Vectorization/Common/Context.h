#ifndef ALGORITHMS_VECTORIZATION_COMMON_CONTEXT_H
#define ALGORITHMS_VECTORIZATION_COMMON_CONTEXT_H

#include "../Shape/Common/Context.h"

#include <QVector>
#include <QPoint>

namespace algorithms
{
  struct Vectorization
  {
    AlgVecShpInOut Shape;
  };
}

typedef algorithms::Vectorization AlgVecInOut;

QDataStream& operator>>( QDataStream& Stream, AlgVecInOut& Value );
QDataStream& operator<<( QDataStream& Stream, const AlgVecInOut& Value );

#endif // ALGORITHMS_VECTORIZATION_COMMON_CONTEXT_H

