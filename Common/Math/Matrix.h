#ifndef COMMON_MATH_MATRIX_H
#define COMMON_MATH_MATRIX_H

#include <ippdefs.h>

#include <types_c.h>
#include <core.hpp>

#include <QPointF>
#include <QVector>
#include <QDataStream>

namespace common
{
  template <class T>
  class Matrix : private cv::Mat
  {
  public:
    Matrix( const int Rows = 0, const int Cols = 0 );
    Matrix( const QVector<QPointF>& Other );
    Matrix( const cv::Mat& Other );

    ~Matrix();

    void resize( const int Rows, const int Cols = 1 );

    T* data() const;
    const T* constData() const;

    T* row( const int Row ) const;
    const T* constRow( const int Row ) const;

    int type() const;

    int rows() const;
    int cols() const;
    int size() const;
    int bytesPerLine() const;
    int bytesPerElement() const;

    void set( const T Value, const int Row, const int Col = 0 );
    T get( const int Row, const int Col = 0 ) const;

    Matrix<T>& operator-=( const Matrix<T>& Other );
    Matrix<T>& operator+=( const Matrix<T>& Other );

    Matrix<T>& operator*=( const qreal& Value );
    Matrix<T>& operator/=( const qreal& Value );

    void invert();
    Matrix<T> inversed() const;
    Matrix<T> transposed() const;
    Matrix<T> xxT() const;
  };

  template <typename T>
  Matrix<T> operator*( const Matrix<T>& M1, const Matrix<T>& M2 );
}

template <typename T>
QDataStream& operator >> (QDataStream& Stream, common::Matrix<T>& Value);

template <typename T>
QDataStream& operator << (QDataStream& Stream, const common::Matrix<T>& Value);

#endif // COMMON_MATH_MATRIX_H
