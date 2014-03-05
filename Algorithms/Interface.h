#ifndef ALGORITHMS_INTERFACE_H
#define ALGORITHMS_INTERFACE_H

#include "Common/Context.h"
#include "Common/Algorithms.h"
#include "../Common/Frame/Frame.h"

#include <QString>
#include <QtPlugin>

namespace algorithms
{
  using namespace common;

  class Interface
  {
  public:
    virtual ~Interface() {}

    virtual bool init( ContextType& Context ) = 0;

    virtual void process( ContextType& Context, const Frame& Image ) = 0;

    virtual QString getName() const = 0;
    virtual Type getType() const = 0;
  };
}

typedef algorithms::Interface AlgInterface;
typedef QMap<AlgType, AlgInterface*> AlgMap;

Q_DECLARE_INTERFACE(AlgInterface, "com.pfpi.Algorithms.Interface/1.0");

#endif // ALGORITHMS_INTERFACE_H
