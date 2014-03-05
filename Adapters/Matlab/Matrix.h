#ifndef ADAPTERS_MATLAB_MATRIX_H
#define ADAPTERS_MATLAB_MATRIX_H

#include <QtGlobal>

class mwArray;

namespace common
{
  template<class T>
  class Matrix;
}

namespace adapters
{
  using namespace common;

  void Convert( mwArray& Output, const Matrix<qreal>& Input );
}

#endif // ADAPTERS_MATLAB_MATRIX_H