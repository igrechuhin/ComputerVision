#include "../Context.h"

namespace algorithms
{
  namespace detection
  {
    Output& Output::operator/=( const qreal& divisor )
    {
      Rectangle.setX(static_cast<int>(Rectangle.x() / divisor));
      Rectangle.setY(static_cast<int>(Rectangle.y() / divisor));
      Rectangle.setWidth(static_cast<int>(Rectangle.width() / divisor));
      Rectangle.setHeight(static_cast<int>(Rectangle.height() / divisor));
      for (PointsMap::iterator pnt(Points.begin()); pnt != Points.end(); pnt++)
      {
        *pnt /= divisor;
      }
      return *this;
    }
  }
}

AlgDetOutputMap getMirroredDetectors( const AlgDetOutputMap& Detectors, const int& ImageWidth )
{
  AlgDetOutputMap mirrDetectors;
  for (AlgDetOutputMap::const_iterator detector(Detectors.constBegin()); detector != Detectors.constEnd(); detector++)
  {
    AlgDetOutput mirrRect;
    const QRect& rect(detector->Rectangle);
    mirrRect.Rectangle = QRect(ImageWidth - (rect.x() + rect.width()), rect.y(), rect.width(), rect.height());

    using namespace algorithms::detection;
    if (detector->Points.contains(LeftEyePoint))
    {
      const QPoint& leftEye(detector->Points[LeftEyePoint]);
      mirrRect.Points.insert(RightEyePoint, QPoint(ImageWidth - leftEye.x(), leftEye.y()));
    }

    if (detector->Points.contains(RightEyePoint))
    {
      const QPoint& leftEye(detector->Points[RightEyePoint]);
      mirrRect.Points.insert(LeftEyePoint, QPoint(ImageWidth - leftEye.x(), leftEye.y()));
    }
    mirrDetectors.insert(detector.key(), mirrRect);
  }
  return mirrDetectors;
}

QDataStream& operator>>( QDataStream& Stream, AlgDetInput& Value )
{
  Stream >> Value.HaarCascadeClassifierFileName;
  Stream >> Value.ScaleFactor;
  Stream >> Value.MinObjectSize;
  return Stream;
}

QDataStream& operator<<( QDataStream& Stream, const AlgDetInput& Value )
{
  Stream << Value.HaarCascadeClassifierFileName;
  Stream << Value.ScaleFactor;
  Stream << Value.MinObjectSize;
  return Stream;
}

QDataStream& operator>>( QDataStream& Stream, algorithms::detection::PointsType& Value )
{
  quint32 tmp;
  Stream >> tmp;
  Value = static_cast<algorithms::detection::PointType>(tmp);
  return Stream;
}

QDataStream& operator<<( QDataStream& Stream, const algorithms::detection::PointsType& Value )
{
  Stream << quint32(Value);
  return Stream;
}

QDataStream& operator>>( QDataStream& Stream, AlgDetOutput& Value )
{
  Stream >> Value.Rectangle;
  Stream >> Value.Points;
  return Stream;
}

QDataStream& operator<<( QDataStream& Stream, const AlgDetOutput& Value )
{
  Stream << Value.Rectangle;
  Stream << Value.Points;
  return Stream;
}

QDataStream& operator>>( QDataStream& Stream, AlgDetInOut& Value )
{
  Stream >> Value.In;
  Stream >> Value.Out;
  return Stream;
}

QDataStream& operator<<( QDataStream& Stream, const AlgDetInOut& Value )
{
  Stream << Value.In;
  Stream << Value.Out;
  return Stream;
}
