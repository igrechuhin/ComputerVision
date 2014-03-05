#ifndef ALGORITHMS_DETECTION_ROWLEY_H
#define ALGORITHMS_DETECTION_ROWLEY_H

#include "../../Common/Context.h"
#include "../../Interface.h"

#include <QObject>

namespace algorithms
{
  namespace detection
  {
    class Rowley : public QObject, Interface
    {
      Q_OBJECT
      Q_INTERFACES(AlgInterface)

    public:
      Rowley();
      virtual ~Rowley();

      virtual bool init( ContextType& Context );

      virtual void process( ContextType& Context, const Frame& Image );

      virtual QString getName() const { return "Rowley"; }
      virtual Type getType() const { return AlgorithmsDetectorRowley; }
    };
  }
}
#endif // ALGORITHMS_DETECTION_ROWLEY_H
