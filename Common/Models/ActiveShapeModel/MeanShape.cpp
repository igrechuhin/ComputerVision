#include "MeanShape.h"

#include "../../Math/Matrix.h"

QDataStream& operator>>( QDataStream& Stream, common::models::MeanShape& Value )
{
  Stream >> Value.Value;
  Stream >> Value.FaceWidth;
  quint32 detCount(algorithms::AlgorithmsDetectorsEnd);
  Stream >> detCount;
  for (quint32 index(0); index < detCount; index++)
  {
    Stream >> Value.Detectors[index].Scale;
    Stream >> Value.Detectors[index].Shift;
  }
  return Stream;
}

QDataStream& operator<<( QDataStream& Stream, const common::models::MeanShape& Value )
{
  Stream << Value.Value;
  Stream << Value.FaceWidth;
  quint32 detCount(algorithms::AlgorithmsDetectorsEnd);
  Stream << detCount;
  for (quint32 index(0); index < detCount; index++)
  {
    Stream << Value.Detectors[index].Scale;
    Stream << Value.Detectors[index].Shift;
  }
  return Stream;
}
