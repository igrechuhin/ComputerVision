#ifndef COMMON_MATH_EIGENPROBLEMS_H
#define COMMON_MATH_EIGENPROBLEMS_H

#include "Matrix.h"

namespace common
{
  template <typename T>
  int EigenValuesVectorsSym( const Matrix<T>& SymMatrix, Matrix<qreal>& EigenValues, Matrix<T>& EigenVectors );
}

#endif // COMMON_MATH_EIGENPROBLEMS_H