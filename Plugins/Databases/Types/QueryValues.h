#ifndef PLUGINS_DATABASES_TYPES_QUERY_VALUES_H
#define PLUGINS_DATABASES_TYPES_QUERY_VALUES_H

#include <QFlags>

namespace plugins
{
  namespace databases
  {
    enum BoolQuery
    {
      BoolEmpty = 0x0,
      BoolFalse = 0x1,
      BoolTrue = 0x2,
    };
    
    enum OrientationQuery
    {
      OrientationEmpty = 0x0,
      Orientation12 = 0x1,
      Orientation13 = 0x2,
      Orientation14 = 0x4,
      Orientation21 = 0x8,
      Orientation22 = 0x10,
      Orientation23 = 0x20,
      Orientation24 = 0x40,
      Orientation25 = 0x80,
      Orientation32 = 0x100,
      Orientation33 = 0x200,
      Orientation34 = 0x400 
    };
    
    union QueryValue
    {
      QueryValue() : vint64(Q_INT64_C(0x0000000000000000)) {}
      QueryValue( quint8 Value ) : vuint8(Value) {}
      QueryValue( qint16 Value ) : vint16(Value) {}
      QueryValue( qint32 Value ) : vint32(Value) {}
      QueryValue( qint64 Value ) : vint64(Value) {}
      QueryValue( BoolQuery Value ) : vbool(Value) {}
      QueryValue( OrientationQuery Value ) : vorientation(Value) {}

      quint8 vuint8;
      qint16 vint16;
      qint32 vint32;
      qint64 vint64;
      BoolQuery vbool;
      OrientationQuery vorientation;
    };
  }
}

Q_DECLARE_FLAGS(BoolQueries, plugins::databases::BoolQuery)
Q_DECLARE_FLAGS(OrientationQueries, plugins::databases::OrientationQuery)

Q_DECLARE_OPERATORS_FOR_FLAGS(BoolQueries)
Q_DECLARE_OPERATORS_FOR_FLAGS(OrientationQueries)

typedef plugins::databases::QueryValue DBQueryValue;

QDataStream& operator >> (QDataStream& Stream, DBQueryValue& Value);
QDataStream& operator << (QDataStream& Stream, const DBQueryValue& Value);

#endif // PLUGINS_DATABASES_TYPES_QUERY_VALUES_H