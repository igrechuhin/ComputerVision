#ifndef COMMON_MODELS_PROFILE_H
#define COMMON_MODELS_PROFILE_H

#include "../../Math/Matrix.h"

#include <QVector>

namespace common
{
  namespace models
  {
    struct Profile
    {
      enum TypeOption
      {
        Profile1D,
        Profile2D,
        ProfilesCount
      };
      struct PointStatistic
      {
        struct  
        {
          Matrix<qreal> Mean;
          Matrix<qreal> InvCovar;
        } ProfileType[ProfilesCount];
      };

      TypeOption PointType;
      QVector<PointStatistic> Points;
      qint32 PixSearch[ProfilesCount];
      quint32 MaxSearchIters;
      quint8 QuialifyingDisp;
    };
  }
}

QDataStream& operator >> (QDataStream& Stream, common::models::Profile& Value);
QDataStream& operator << (QDataStream& Stream, const common::models::Profile& Value);

#endif // COMMON_MODELS_PROFILE_H