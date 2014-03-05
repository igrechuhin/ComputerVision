#ifndef ALGORITHMS_DETECTION_VIOLAJONES_H
#define ALGORITHMS_DETECTION_VIOLAJONES_H

#include "../../Common/Context.h"
#include "../../Interface.h"

#include <QObject>

struct CvMemStorage;
struct CvHaarClassifierCascade;

namespace algorithms
{
  namespace detection
  {
    class ViolaJones : public QObject, Interface
    {
      Q_OBJECT
      Q_INTERFACES(AlgInterface)

    public:
      ViolaJones();
      virtual ~ViolaJones();

      virtual bool init( ContextType& Context );

      virtual void process( ContextType& Context, const Frame& Image );

      virtual QString getName() const { return "Viola Jones"; }
      virtual Type getType() const { return AlgorithmsDetectorViolaJones; }

    private:
      CvMemStorage* Storage;
      CvHaarClassifierCascade* ClassifierCascade;
    };
  }
}

#endif // ALGORITHMS_DETECTION_VIOLAJONES_H
