#ifndef COMMON_MODELS_SCALE_H
#define COMMON_MODELS_SCALE_H

#include <QtGlobal>

namespace common
{
  namespace models
  {
    struct Scale
    {
      Scale()
        : Levels(0),
          Factor(0)
      {}
      quint8 Levels;
      qreal Factor;
    };

    Q_DECLARE_TYPEINFO(Scale, Q_MOVABLE_TYPE);
  }
}

QDataStream& operator >> (QDataStream& Stream, common::models::Scale& Value);
QDataStream& operator << (QDataStream& Stream, const common::models::Scale& Value);

#endif // COMMON_MODELS_SCALE_H