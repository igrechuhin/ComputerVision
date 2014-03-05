#include "Scale.h"

#include <QDataStream>

namespace
{
  const qreal DEFAULT_SCALE_FACTOR(2.0f);
}

QDataStream& operator>>( QDataStream& Stream, common::models::Scale& Value )
{
  Stream >> Value.Levels;
  Stream >> Value.Factor;
  Value.Factor = (Value.Factor < 1 ? DEFAULT_SCALE_FACTOR : Value.Factor);
  return Stream;
}

QDataStream& operator<<( QDataStream& Stream, const common::models::Scale& Value )
{
  Stream << Value.Levels;
  Stream << (Value.Factor < 1 ? DEFAULT_SCALE_FACTOR : Value.Factor);
  return Stream;
}
