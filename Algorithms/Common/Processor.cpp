#include "Processor.h"

#include <QTime>

namespace algorithms
{
  AlgTimeMap process( ContextType& Context, const common::Frame& Image, AlgMap& Algorithms, const Type& Begin, const Type& End )
  {
    Q_ASSERT(Begin <= End);
    AlgTimeMap elapsedTime;
    AlgMap::const_iterator alg(Algorithms.lowerBound(Begin));
    AlgMap::const_iterator algEnd(Algorithms.upperBound(End));
    QTime timing;
    timing.start();
    for (; alg != algEnd; alg++)
    {
      AlgInterface* algPtr(alg.value());
      timing.restart();
      algPtr->process(Context, Image);
      elapsedTime.insert(alg.key(), timing.elapsed());
    }
    return elapsedTime;
  }
}
