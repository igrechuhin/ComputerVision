#include "Context.h"

QDataStream& operator>>( QDataStream& Stream, AlgVecInOut& Value )
{
  Stream >> Value.Shape;
  return Stream;
}

QDataStream& operator<<( QDataStream& Stream, const AlgVecInOut& Value )
{
  Stream << Value.Shape;
  return Stream;
}
