#ifndef COMMON_MODELS_PRINCIPALCOMPONENTS_H
#define COMMON_MODELS_PRINCIPALCOMPONENTS_H

#include "ModelT.h"

#include "../../Math/Matrix.h"

namespace common
{
  namespace models
  {
    struct PrincipalComponents
    {
      PrincipalComponents()
        : EigenValues(),
          EigenVectors(),
          NEigs(0),
          NEigs2D(0),
          NEigsFinal(0),
          BMax(0),
          BMaxFinal(0)
      {}

      Matrix<qreal> EigenValues;
      Matrix<modelT> EigenVectors;

      quint32 NEigs;
      quint32 NEigs2D;
      quint32 NEigsFinal;
      qreal BMax;
      qreal BMaxFinal;

//      Matrix<modelT> eigenVectorsInverse();
    };
  }
}

QDataStream& operator >> (QDataStream& Stream, common::models::PrincipalComponents& Value);
QDataStream& operator << (QDataStream& Stream, const common::models::PrincipalComponents& Value);

#endif // COMMON_MODELS_PRINCIPALCOMPONENTS_H