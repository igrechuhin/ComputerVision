#include "Algorithms.h"

#include "../Interface.h"

QDataStream& operator>>( QDataStream& Stream, AlgType& Value )
{
  qint32 tmp;
  Stream >> tmp;
  Value = static_cast<AlgType>(tmp);
  return Stream;
}

QDataStream& operator<<( QDataStream& Stream, const AlgType& Value )
{
  qint32 tmp(Value);
  Stream << tmp;
  return Stream;
}
