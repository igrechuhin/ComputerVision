#include "Matrix.h"

#include <ippm.h>

#define MATRIX_INST(T) { \
                          QVector<QPointF> vec; \
                          Matrix<T> m1; \
                          Matrix<T> m2(vec); \
                          m1.resize(1, 1); \
                          m1.data(); \
                          m1.constData(); \
                          m1.type(); \
                          m1.rows(); \
                          m1.cols(); \
                          m1.size(); \
                          m1.bytesPerLine(); \
                          m1.bytesPerElement(); \
                          m1.set(m1.get(0,0),0,0); \
                          m1 -= m2; \
                          m1 += m2; \
                          m1 *= qreal(1.0); \
                          m1 /= qreal(1.0); \
                          m1.invert(); \
                          m1.inversed(); \
                          m1.transposed(); \
                          m1.xxT(); \
                          m1 = m1 * m2; \
                          QDataStream dataStream; \
                          dataStream << m1; \
                          dataStream >> m1; \
                        }

namespace
{
  template <typename T>
  int resolveType()
  {
    if (typeid(T) == typeid(quint8))
      return CV_8U;
    else if (typeid(T) == typeid(qint32))
      return CV_32S;
    else if (typeid(T) == typeid(qreal))
      return CV_64F;
    Q_ASSERT(!"Not implemented");
    return CV_8U;
  }
}

namespace common
{

  template <typename T>
  Matrix<T>::Matrix( const int Rows /*= 0*/, const int Cols /*= 0 */ )
    : cv::Mat(zeros(Rows, Rows ? (Cols ? Cols : 1) : 0, resolveType<T>()))
  {
  }

  template <typename T>
  Matrix<T>::Matrix( const QVector<QPointF>& Other )
    : cv::Mat(typeid(T) == typeid(qreal) ? 2 * Other.size() : Other.size(),
              typeid(T) == typeid(qreal) ? 1 : 2, resolveType<qreal>())
  {
    if (typeid(T) == typeid(qreal))
    {
      int realPartSize(Other.size());
      for (int row(0); row < realPartSize; row++)
      {
        const QPointF& point(Other[row]);
        set(point.x(), row);
        set(point.y(), realPartSize + row);
      }
    }
    else
    {
      Q_ASSERT(!"TODO");
    }
  }

  template <typename T>
  Matrix<T>::Matrix( const cv::Mat& Other )
    : cv::Mat(Other)
  {
  }

  template <typename T>
  Matrix<T>::~Matrix()
  {
  }

  template <class T>
  void Matrix<T>::resize( const int Rows, const int Cols /*= 1 */ )
  {
    cv::Mat::operator=(zeros(Rows, Cols, resolveType<T>()));
  }

  template <typename T>
  T* Matrix<T>::data() const
  {
    return reinterpret_cast<T*>(cv::Mat::data);
  }

  template <typename T>
  const T* Matrix<T>::constData() const
  {
    return reinterpret_cast<T*>(cv::Mat::data);
  }

  template <typename T>
  T* Matrix<T>::row( const int Row ) const
  {
    return reinterpret_cast<T*>(cv::Mat::data + Row*bytesPerLine());
  }

  template <typename T>
  const T* Matrix<T>::constRow( const int Row ) const
  {
    return reinterpret_cast<T*>(cv::Mat::data  + Row*bytesPerLine());
  }

  template <class T>
  int Matrix<T>::type() const
  {
    return cv::Mat::type();
  }

  template <typename T>
  int Matrix<T>::rows() const
  {
    return cv::Mat::rows;
  }

  template <typename T>
  int Matrix<T>::cols() const
  {
    return cv::Mat::cols;
  }

  template <typename T>
  int Matrix<T>::size() const
  {
    return cols() * rows();
  }

  template <class T>
  int Matrix<T>::bytesPerLine() const
  {
    return step.buf[0];
  }

  template <class T>
  int Matrix<T>::bytesPerElement() const
  {
    return step.buf[1];
  }

  template <typename T>
  void Matrix<T>::set( const T Value, const int Row, const int Col /*= 0 */ )
  {
    Q_ASSERT(constData() && 0 <= Row && Row < rows() && 0 <= Col && Col < cols());
    *(row(Row) + Col) = Value;
  }

  template <typename T>
  T Matrix<T>::get( const int Row, const int Col /*= 0 */ ) const
  {
    Q_ASSERT(constData() && 0 <= Row && Row < rows() && 0 <= Col && Col < cols());
    return *(constRow(Row) + Col);
  }

  template <typename T>
  Matrix<T>& Matrix<T>::operator-=( const Matrix<T>& Other )
  {
    Q_ASSERT(size() > 0 && Other.size() > 0 && rows() == Other.rows());
    Q_ASSERT(Other.cols() == cols() || Other.cols() == 1);
    bool genericProcessing(true);
    if (Other.cols() == cols())
    {
      const int src1Stride1(bytesPerLine());
      const int src1Stride2(bytesPerElement());
      const int src2Stride1(Other.bytesPerLine());
      const int src2Stride2(Other.bytesPerElement());
      const int dstStride1(src1Stride1);
      const int dstStride2(src1Stride2);
      const int width(Other.cols());
      const int height(Other.rows());
      if (type() == CV_64F)
      {
        const Ipp64f* pSrc1(reinterpret_cast<const Ipp64f*>(constData()));
        const Ipp64f* pSrc2(reinterpret_cast<const Ipp64f*>(Other.constData()));
        Ipp64f* pDst(reinterpret_cast<Ipp64f*>(data()));
        IppStatus status(ippmSub_mm_64f(pSrc1, src1Stride1, src1Stride2, 
                                        pSrc2, src2Stride1, src2Stride2,
                                        pDst, dstStride1, dstStride2, width, height));
        Q_ASSERT(status == ippStsNoErr);
        genericProcessing = false;
      }
    }
    else if (Other.cols() == 1)
    {
      Q_ASSERT(!"CHECK");
      const int dataSize(Other.size());
      const int src1Stride(cols() * sizeof(T));
      const int src2Stride(Other.cols() * sizeof(T));
      const int dstStride(src1Stride);
      if (type() == CV_64F)
      {
        const Ipp64f* pSrc1(reinterpret_cast<const Ipp64f*>(constData()));
        const Ipp64f* pSrc2(reinterpret_cast<const Ipp64f*>(Other.constData()));
        Ipp64f* pDst(reinterpret_cast<Ipp64f*>(data()));
        for (int col(0); col < cols(); col++, pSrc1++, pDst++)
        {
          IppStatus status(ippmSub_vv_64f(pSrc1, src1Stride, pSrc2, src2Stride, pDst, dstStride, dataSize));
          Q_ASSERT(status == ippStsNoErr);
        }
        genericProcessing = false;
      }
    }
    if (genericProcessing)
    {
      Q_ASSERT(!"CHECK");
      const int thisCols(cols());
      const int otherCols(Other.cols());
      for (int row(0); row < rows(); row++)
      {
        T* thisData(data() + row*thisCols);
        const T* otherData0(Other.constData() + row*otherCols);
        const T* otherData(otherData0);
        for (int thisCol(0), otherCol(0); thisCol < thisCols; thisCol++, otherCol++, thisData++, otherData++)
        {
          if (otherCol == otherCols)
          {
            otherData = otherData0;
            otherCol = 0;
          }
          *thisData -= *otherData;
        }
      }
    }
    return *this;
  }

  template <typename T>
  Matrix<T>& Matrix<T>::operator+=( const Matrix<T>& Other )
  {
    Q_ASSERT(size() > 0 && Other.size() > 0 && rows() == Other.rows());
    Q_ASSERT(Other.cols() == cols() || Other.cols() == 1);
    bool genericProcessing(true);
    if (Other.cols() == cols())
    {
      const int src1Stride1(bytesPerLine());
      const int src1Stride2(bytesPerElement());
      const int src2Stride1(Other.bytesPerLine());
      const int src2Stride2(Other.bytesPerElement());
      const int dstStride1(src1Stride1);
      const int dstStride2(src1Stride2);
      const int width(Other.cols());
      const int height(Other.rows());
      if (type() == CV_64F)
      {
        const Ipp64f* pSrc1(reinterpret_cast<const Ipp64f*>(constData()));
        const Ipp64f* pSrc2(reinterpret_cast<const Ipp64f*>(Other.constData()));
        Ipp64f* pDst(reinterpret_cast<Ipp64f*>(data()));
        IppStatus status(ippmAdd_mm_64f(pSrc1, src1Stride1, src1Stride2, 
                                        pSrc2, src2Stride1, src2Stride2,
                                        pDst, dstStride1, dstStride2, width, height));
        Q_ASSERT(status == ippStsNoErr);
        genericProcessing = false;
      }
    }
    else if (Other.cols() == 1)
    {
      Q_ASSERT(!"CHECK");
      const int dataSize(Other.size());
      const int src1Stride(cols() * sizeof(T));
      const int src2Stride(Other.cols() * sizeof(T));
      const int dstStride(src1Stride);
      if (type() == CV_64F)
      {
        const Ipp64f* pSrc1(reinterpret_cast<const Ipp64f*>(constData()));
        const Ipp64f* pSrc2(reinterpret_cast<const Ipp64f*>(Other.constData()));
        Ipp64f* pDst(reinterpret_cast<Ipp64f*>(data()));
        for (int col(0); col < cols(); col++, pSrc1++, pDst++)
        {
          IppStatus status(ippmAdd_vv_64f(pSrc1, src1Stride, pSrc2, src2Stride, pDst, dstStride, dataSize));
          Q_ASSERT(status == ippStsNoErr);
        }
        genericProcessing = false;
      }
    }
    if (genericProcessing)
    {
      Q_ASSERT(!"CHECK");
      const int thisCols(cols());
      const int otherCols(Other.cols());
      for (int row(0); row < rows(); row++)
      {
        T* thisData(data() + row*thisCols);
        const T* otherData0(Other.constData() + row*otherCols);
        const T* otherData(otherData0);
        for (int thisCol(0), otherCol(0); thisCol < thisCols; thisCol++, otherCol++, thisData++, otherData++)
        {
          if (otherCol == otherCols)
          {
            otherData = otherData0;
            otherCol = 0;
          }
          *thisData += *otherData;
        }
      }
    }
    return *this;
  }

  template <typename T>
  Matrix<T>& Matrix<T>::operator*=( const qreal& Value )
  {
    Q_ASSERT(constData() && size());
    int srcStride1(bytesPerLine());
    int srcStride2(bytesPerElement());
    if (type() == CV_64F)
    {
      Ipp64f* pSrc(reinterpret_cast<Ipp64f*>(data()));
      const Ipp64f val(static_cast<const Ipp64f>(Value));
      IppStatus status(ippmMul_mc_64f(pSrc, srcStride1, srcStride2,
                                      val,
                                      pSrc, srcStride1, srcStride2, cols(), rows()));
      Q_ASSERT(status == ippStsNoErr);
    }
    else
    {
      Q_ASSERT(!"CHECK");
      const T mulValue(static_cast<const T>(Value));
      for (int rowIndex(0); rowIndex < rows(); rowIndex++)
      {
        T* rowPtr(row(rowIndex));
        for (int colIndex(0); colIndex < cols(); colIndex++, rowPtr++)
        {
          *rowPtr *= mulValue;
        }
      }
    }
    return *this;
  }

  template <typename T>
  Matrix<T>& Matrix<T>::operator/=( const qreal& Value )
  {
    return operator*=(1.0 / Value);
  }

  template <class T>
  void Matrix<T>::invert()
  {
    *this = inversed();
  }

  template <class T>
  Matrix<T> Matrix<T>::inversed() const
  {
    return inv();
  }

  template <typename T>
  Matrix<T> Matrix<T>::transposed() const
  {
    return t();
  }

  template <typename T>
  Matrix<T> Matrix<T>::xxT() const
  {
    Q_ASSERT(constData() && size());
    int stride1(bytesPerLine());
    int stride2(bytesPerElement());
    if (type() == CV_64F)
    {
      Matrix<T> mulRes(rows(), rows());
      int dstStride1(mulRes.bytesPerLine());
      int dstStride2(mulRes.bytesPerElement());
      const Ipp64f* dataPtr(reinterpret_cast<const Ipp64f*>(constData()));
      Ipp64f* mulResPtr(reinterpret_cast<Ipp64f*>(mulRes.data()));
      IppStatus status(ippmMul_mt_64f(dataPtr, stride1, stride2, cols(), rows(),
                                      dataPtr, stride1, stride2, cols(), rows(),
                                      mulResPtr, dstStride1, dstStride2));
      Q_ASSERT(status == ippStsNoErr);
      return mulRes;
    }
    Q_ASSERT(!"CHECK");
    return *this * transposed();
  }

  template <typename T>
  Matrix<T> operator*( const Matrix<T>& M1, const Matrix<T>& M2 )
  {
    Q_ASSERT(M1.type() == M2.type());
    Q_ASSERT(M1.constData() && M2.constData() && M1.size() && M2.size());
    Q_ASSERT(M1.cols() == M2.rows());
    Matrix<T> dst(M1.rows(), M2.cols());
    int src1Stride1(M1.cols() * sizeof(T));
    int src2Stride1(M2.cols() * sizeof(T));
    int dstStride1(dst.cols() * sizeof(T));
    int stride2(sizeof(T));
    if (M1.type() == CV_64F)
    {
      const Ipp64f* pSrc1(reinterpret_cast<const Ipp64f*>(M1.constData()));
      const Ipp64f* pSrc2(reinterpret_cast<const Ipp64f*>(M2.constData()));
      Ipp64f* pDst(reinterpret_cast<Ipp64f*>(dst.data()));
      IppStatus status(ippmMul_mm_64f(pSrc1, src1Stride1, stride2, M1.cols(), M1.rows(),
        pSrc2, src2Stride1, stride2, M2.cols(), M2.rows(),
        pDst, dstStride1, stride2));
      Q_ASSERT(status == ippStsNoErr);
    }
    else
    {
      for (int rowIndex(0); rowIndex < dst.rows(); rowIndex++)
      {
        for (int colIndex(0); colIndex < dst.cols(); colIndex++)
        {
          T sumValue;
          memset(&sumValue, 0, sizeof(T));
          for (int sumIndex(0); sumIndex < M1.cols(); sumIndex++)
          {
            sumValue += M1.get(rowIndex, sumIndex) * M2.get(sumIndex, colIndex);
          }
          dst.set(sumValue, rowIndex, colIndex);
        }
      }
    }
    return dst;
  }

  void instMatrix()
  {
    MATRIX_INST(quint8)
    MATRIX_INST(qint32)
    MATRIX_INST(qreal)
  }
}

template <typename T>
QDataStream& operator>>( QDataStream& Stream, common::Matrix<T>& Value )
{
  int type;
  int rows;
  int cols;
  Stream >> type;
  Stream >> rows;
  Stream >> cols;
  Q_ASSERT(type == Value.type());
  Value.resize(rows, cols);
  for (int rowInd(0); rowInd < Value.rows(); rowInd++)
  {
    for (int colInd(0); colInd < Value.cols(); colInd++)
    {
      T element;
      Stream >> element;
      Value.set(element, rowInd, colInd);
    }
  }
  return Stream;
}

template <typename T>
QDataStream& operator<<( QDataStream& Stream, const common::Matrix<T>& Value )
{
  Stream << Value.type();
  Stream << Value.rows();
  Stream << Value.cols();
  for (int rowInd(0); rowInd < Value.rows(); rowInd++)
  {
    for (int colInd(0); colInd < Value.cols(); colInd++)
    {
      Stream << Value.get(rowInd, colInd);
    }
  }
  return Stream;
}
