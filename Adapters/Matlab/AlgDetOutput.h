#ifndef ADAPTERS_MATLAB_ALGDETOUTPUT_H
#define ADAPTERS_MATLAB_ALGDETOUTPUT_H

#include "../../Algorithms/Detection/Common/Context.h"

class mwArray;

namespace adapters
{
  void Convert( mwArray& Output, const AlgDetOutput& Input );
}

#endif // ADAPTERS_MATLAB_ALGDETOUTPUT_H