#ifndef COMMON_MATH_SOLVESLE_H
#define COMMON_MATH_SOLVESLE_H

#include "Matrix.h"

namespace common
{
  template <typename T>
  int SolveWithLU( const Matrix<T>& A, const Matrix<T>& B, Matrix<T>& X );
}

#endif // COMMON_MATH_SOLVESLE_H