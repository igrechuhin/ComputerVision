#ifndef COMMON_MODELS_MODELT_H
#define COMMON_MODELS_MODELT_H

#include <QtGlobal>

namespace common
{
  namespace models
  {
#ifdef ComplexType
    typedef ipp::IeppXXYc<Ipp64f> modelT;
#else
    typedef qreal modelT;
#endif // ComplexType
  }
}

#endif // COMMON_MODELS_MODELT_H