#ifndef ALGORITHMS_COMMON_PROCESSOR_H
#define ALGORITHMS_COMMON_PROCESSOR_H

#include "../../Common/Frame/Frame.h"

#include "../Interface.h"

#include "Context.h"
#include "Algorithms.h"

#include <QMap>

typedef QMap<AlgType, qint32> AlgTimeMap;

namespace algorithms
{
  AlgTimeMap process( ContextType& Context, const common::Frame& Image, AlgMap& Algorithms, const Type& Begin, const Type& End );
}

#endif // ALGORITHMS_COMMON_PROCESSOR_H