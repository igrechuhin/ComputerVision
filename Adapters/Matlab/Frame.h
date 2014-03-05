#ifndef ADAPTERS_MATLAB_FRAME_H
#define ADAPTERS_MATLAB_FRAME_H

class mwArray;

namespace common
{
  class Frame;
}

namespace adapters
{
  using namespace common;

  void Convert( mwArray& Output, const Frame& Input, bool ToGray = true );
}

#endif // ADAPTERS_MATLAB_FRAME_H