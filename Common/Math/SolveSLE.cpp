#include "SolveSLE.h"

#include <ippm.h>

#define SOLVEWITHLUINST(type) { \
                                Matrix<type> A; \
                                Matrix<type> B; \
                                Matrix<type> X; \
                                SolveWithLU(A, B, X); \
                              }

namespace common
{
  template <typename T>
  int SolveWithLU(const Matrix<T>& A, const Matrix<T>& B, Matrix<T>& X)
  {
    int widthHeight(A.rows());
    Q_ASSERT(widthHeight != 0 && widthHeight == B.rows() && widthHeight == A.cols());
    Q_ASSERT(A.constData() && B.constData());

    Matrix<Ipp32s> dstIndex(widthHeight);
    int srcStride1(A.bytesPerLine());
    int srcStride2(A.bytesPerElement());
    Matrix<T> luDecomp(widthHeight, widthHeight);
    int luDecompStride1(luDecomp.bytesPerLine());
    int luDecompStride2(luDecomp.bytesPerElement());

    X.resize(widthHeight);
    int src2Stride2(B.bytesPerLine());
    int dstStride2(X.bytesPerLine());

    IppStatus status(ippStsNoErr);
    if (typeid(T) == typeid(Ipp64f))
    {
      status = ippmLUDecomp_m_64f(reinterpret_cast<const Ipp64f*>(A.constData()), srcStride1, srcStride2,
                                  dstIndex.data(),
                                  reinterpret_cast<Ipp64f*>(luDecomp.data()), luDecompStride1, luDecompStride2,
                                  widthHeight);
      Q_ASSERT(status == ippStsNoErr);
      status = ippmLUBackSubst_mv_64f(reinterpret_cast<const Ipp64f*>(luDecomp.data()), luDecompStride1, luDecompStride2,
                                      dstIndex.data(),
                                      reinterpret_cast<const Ipp64f*>(B.constData()), src2Stride2,
                                      reinterpret_cast<Ipp64f*>(X.data()), dstStride2,
                                      widthHeight);
      Q_ASSERT(status == ippStsNoErr);
    }
    else
    {
      Q_ASSERT_X(false, "SolveWithLU", "Routine is not implemented for this data type");
    }
    return status;
  }

  void instSolveWithLU()
  {
    SOLVEWITHLUINST(Ipp64f)
  }
}