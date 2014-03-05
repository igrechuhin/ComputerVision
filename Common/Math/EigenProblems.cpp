#include "EigenProblems.h"

#include <ippm.h>

#define EIGENVALUESVECTORSSYMINST(type) { \
                                          Matrix<type> A; \
                                          Matrix<qreal> B; \
                                          Matrix<type> X; \
                                          EigenValuesVectorsSym(A, B, X); \
                                        }

namespace common
{
  template <typename T>
  int EigenValuesVectorsSym( const Matrix<T>& SymMatrix, Matrix<qreal>& EigenValues, Matrix<T>& EigenVectors )
  {
    Q_ASSERT(SymMatrix.type() == EigenVectors.type());
    Q_ASSERT(SymMatrix.constData() && SymMatrix.cols() == SymMatrix.rows());
    int status(0);
    int srcStride1(SymMatrix.bytesPerLine());
    int srcStride2(SymMatrix.bytesPerElement()); 
    int widthHeight(SymMatrix.cols());
    EigenValues.resize(widthHeight);
    EigenVectors.resize(widthHeight, widthHeight);
    int dstStride1(EigenVectors.bytesPerLine());
    int dstStride2(EigenVectors.bytesPerElement()); 
    if (SymMatrix.type() == CV_64F)
    {
      Matrix<Ipp64f> buffer(widthHeight, widthHeight);
      const Ipp64f* pSrc(reinterpret_cast<const Ipp64f*>(SymMatrix.constData()));
      Ipp64f* pBuffer(reinterpret_cast<Ipp64f*>(buffer.data()));
      Ipp64f* pDstVectors(reinterpret_cast<Ipp64f*>(EigenVectors.data()));
      Ipp64f* pDstValues(reinterpret_cast<Ipp64f*>(EigenValues.data()));
      status = ippmEigenValuesVectorsSym_m_64f( pSrc, srcStride1, srcStride2,
                                                pBuffer,
                                                pDstVectors, dstStride1, dstStride2,
                                                pDstValues,
                                                widthHeight);
      Q_ASSERT(status == ippStsNoErr);
    }
    else
    {
      Q_ASSERT_X(false, "EigenValuesVectorsSym", "Routine is not implemented for this data type");
    }
    qreal* eigenValuesDataPtr(EigenValues.data());
    const int elementsCount(EigenValues.size());
    for (int index(0); index < elementsCount; index++, eigenValuesDataPtr++)
    {
      if (*eigenValuesDataPtr < 0)
        *eigenValuesDataPtr = 0;
    }
    return status;
  }

  void instEigenProblems()
  {
    EIGENVALUESVECTORSSYMINST(Ipp64f)
  }
}
