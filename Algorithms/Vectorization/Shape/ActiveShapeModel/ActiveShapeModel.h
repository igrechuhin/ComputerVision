#ifndef ALGORITHMS_VECTORIZATION_SHAPE_ACTIVESHAPEMODEL_H
#define ALGORITHMS_VECTORIZATION_SHAPE_ACTIVESHAPEMODEL_H

#include "../../../../Common/Models/ActiveShapeModel/ActiveShapeModel.h"

//#include "../../Common/Context.h"
#include "../../../Interface.h"

#ifdef MATLAB
#include <mclcppclass.h>

#include <QLibrary>

typedef bool (*MatlabInitPtr)(void);
typedef void (*MatlabDeInitPtr)(void);
typedef void (*MatlabRunPtr)(int nargout, mwArray& shapes, const mwArray& grayImage, const mwArray& model, const mwArray& faces, const mwArray& detectorToUse);
#endif // MATLAB

#include <QObject>

namespace algorithms
{
  namespace vectorization
  {
    namespace shape
    {
      class ActiveShapeModel : public QObject, Interface
      {
        Q_OBJECT
        Q_INTERFACES(AlgInterface)

      public:
        ActiveShapeModel();
        virtual ~ActiveShapeModel();

        virtual bool init( ContextType& Context );

        virtual void process( ContextType& Context, const Frame& Image );

        virtual QString getName() const { return "Active Shape Model"; }
        virtual Type getType() const { return AlgorithmsVectorizationActiveShapeModel; }

      private:
#ifdef MATLAB
        bool initMATLAB( const QString& DllPath );
        void deinitMATLAB();
        void runMATLAB( ContextType& Context, const Frame& Image );
#endif // MATLAB

      private:
        common::models::ActiveShapeModel Model;

#ifdef MATLAB
        QLibrary MatlabDll;
        MatlabInitPtr MatlabInitFunc;
        MatlabDeInitPtr MatlabDeInitFunc;
        MatlabRunPtr MatlabRunFunc;
        mwArray MatlabModel;
#endif // MATLAB
      };
    }
  }
}

#endif // ALGORITHMS_VECTORIZATION_SHAPE_ACTIVESHAPEMODEL_H
