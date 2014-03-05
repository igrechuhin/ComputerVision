#ifndef ADAPTERS_MATLAB_ALGVECSHPOUTPUT_H
#define ADAPTERS_MATLAB_ALGVECSHPOUTPUT_H

#include "../../Algorithms/Vectorization/Shape/Common/Context.h"

class mwArray;

namespace adapters
{
  void Convert( QVector<AlgVecShpOutput>& Output, const mwArray& Input );
}

#endif // ADAPTERS_MATLAB_ALGVECSHPOUTPUT_H