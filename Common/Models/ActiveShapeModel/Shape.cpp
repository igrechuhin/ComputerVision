#include "Shape.h"

#include "../../Math/SolveSLE.h"

#include <QVector2D>

namespace
{
  const qint16 LEFT_EYE_INDEX(25);
  const qint16 RIGHT_EYE_INDEX(36);

  QVector<QPointF> transformShape( const common::Matrix<qreal>& Transform, const QVector<QPointF>& InShape )
  {
    QPointF additionPoint;
    for (int colIndex(2); colIndex < Transform.cols(); colIndex++)
    {
      additionPoint += QPointF(Transform.get(0, colIndex), Transform.get(1, colIndex));
    }
    QVector<QPointF> outShape;
    const qreal M00(Transform.get(0, 0));
    const qreal M01(Transform.get(0, 1));
    const qreal M10(Transform.get(1, 0));
    const qreal M11(Transform.get(1, 1));

    for (int pointIndex(0); pointIndex < InShape.size(); pointIndex++)
    {
      const QPointF& inPoint(InShape[pointIndex]);
      const QPointF outPoint( M00*inPoint.x() + M01*inPoint.y(),
                              M10*inPoint.x() + M11*inPoint.y());
      outShape << outPoint + additionPoint;
    }
    return outShape;
  }
}

namespace common
{
  namespace models
  {
    QPointF getShapeCenter( const QVector<QPoint>& Shape )
    {
      Q_ASSERT(!Shape.isEmpty());
      QPointF shapeCenter;
      foreach(const QPoint& point, Shape)
      {
        shapeCenter += point;
      }
      shapeCenter /= Shape.size();
      return shapeCenter;
    }

    QVector<QPointF> getCenteredShape( const QVector<QPoint>& Shape )
    {
      Q_ASSERT(!Shape.isEmpty());
      QVector<QPointF> centeredShape;
      QPointF shapeCenter(getShapeCenter(Shape));
      for (int index(0); index < Shape.size(); index++)
      {
        centeredShape << Shape[index] - shapeCenter;
      }
      return centeredShape;
    }

    QVector<QPointF> getScaledShape( const QVector<QPoint>& Shape, const qreal& ScaleFactor )
    {
      QVector<QPointF> scaledShape;
      for (int index(0); index < Shape.size(); index++)
      {
        scaledShape << QPointF(Shape[index]) * ScaleFactor;
      }
      return scaledShape;
    }

    QVector<QPoint> getMirroredShape( const QVector<QPoint>& Shape, const int& ImageWidth )
    {
      QVector<QPoint> tmpShape;
      for (int index(0); index < Shape.size(); index++)
      {
        tmpShape << QPoint(ImageWidth - Shape[index].x(), Shape[index].y());
      }
      QVector<QPoint> mirroredShape;
      for (int index(0); index < tmpShape.size(); index++)
      {
        mirroredShape << tmpShape[SYMMETRIC_INDEX[index]];
      }
      return mirroredShape;
    }

    qint32 getShapeWidth( const QVector<QPoint>& Shape )
    {
      Q_ASSERT(!Shape.isEmpty());
      qint32 faceWidth(0);
      qint32 mostLeftPointX(LONG_MAX);
      qint32 mostRightPointX(LONG_MIN);
      foreach(const QPoint& point, Shape)
      {
        mostLeftPointX = qMin(mostLeftPointX, point.x());
        mostRightPointX = qMax(mostRightPointX, point.x());
      }
      faceWidth = mostRightPointX - mostLeftPointX;
      return faceWidth;
    }

    qint32 getBetweenEyesDistance( const QVector<QPoint>& Shape )
    {
      Q_ASSERT(Shape.size() > qMax(LEFT_EYE_INDEX, RIGHT_EYE_INDEX));
      return QVector2D(Shape[LEFT_EYE_INDEX] - Shape[RIGHT_EYE_INDEX]).length();
    }

    void alignShape( QVector<QPointF>& Shape, const QVector<QPointF>& AnchorShape, const QVector<qreal>& Weights )
    {
      const int pointsCount(Shape.size());
      Q_ASSERT(pointsCount == AnchorShape.size() && pointsCount == Weights.size());
      qreal X1(0), Y1(0), X2(0), Y2(0), W(0), Z(0), C1(0), C2(0);
      for (int pointIndex(0); pointIndex < pointsCount; pointIndex++)
      {
        const qreal x1(AnchorShape[pointIndex].x());
        const qreal y1(AnchorShape[pointIndex].y());
        const qreal x2(Shape[pointIndex].x());
        const qreal y2(Shape[pointIndex].y());
        const qreal w(Weights[pointIndex]);

        W  += w;
        Z  += w * (x2*x2 + y2*y2);
        X1 += w * x1;
        Y1 += w * y1;
        X2 += w * x2;
        Y2 += w * y2;
        C1 += w * (x1*x2 + y1*y2);
        C2 += w * (y1*x2 - x1*y2);
      }

      Matrix<qreal> A(4, 4);
      A.set(X2, 0, 0); A.set(-Y2, 0, 1); A.set(  W, 0, 2); A.set( 0, 0, 3);
      A.set(Y2, 1, 0); A.set( X2, 1, 1); A.set(  0, 1, 2); A.set( W, 1, 3);
      A.set( Z, 2, 0); A.set(  0, 2, 1); A.set( X2, 2, 2); A.set(Y2, 2, 3);
      A.set( 0, 3, 0); A.set(  Z, 3, 1); A.set(-Y2, 3, 2); A.set(X2, 3, 3);

      Matrix<qreal> B(4);
      B.set(X1, 0);
      B.set(Y1, 1);
      B.set(C1, 2);
      B.set(C2, 3);

      Matrix<qreal> X;
      int solveResult(SolveWithLU(A, B, X));
      Q_ASSERT(solveResult == 0);

      Matrix<qreal> transform(2, 3);
      transform.set(X.get(0), 0, 0); transform.set(-X.get(1), 0, 1); transform.set(X.get(2), 0, 2);
      transform.set(X.get(1), 1, 0); transform.set( X.get(0), 1, 1); transform.set(X.get(3), 1, 2);

      Shape = transformShape(transform, Shape);
    }

  }
}

QDataStream& operator<<( QDataStream& Stream, const common::models::LandmarkTriangle& Value )
{
  Stream << Value.iPrev;
  Stream << Value.iNext;
  return Stream;
}

QDataStream& operator>>( QDataStream& Stream, common::models::LandmarkTriangle& Value )
{
  Stream >> Value.iPrev;
  Stream >> Value.iNext;
  return Stream;
}
