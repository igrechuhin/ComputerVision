#ifndef COMMON_MODELS_ACTIVESHAPEMODEL_H
#define COMMON_MODELS_ACTIVESHAPEMODEL_H

#include "PrincipalComponents.h"
#include "MeanShape.h"
#include "Profile.h"
#include "Shape.h"
#include "Scale.h"

class QString;

namespace common
{
  namespace models
  {
    class ActiveShapeModel
    {
    public:
      enum State
      {
        StateOK,
        StateFileNotFound,
        StatePermissionError,
        StateInvalidModel
      };

      enum ComplexityFlag
      {
        RealFlag,
        ComplexFlag
      };

      ActiveShapeModel();
      ~ActiveShapeModel();

      State read( const QString& FilePath );
      State write( const QString& FilePath );

    public:
      ComplexityFlag Complexity;
      PrincipalComponents PrincComp;
      MeanShape Shape;
      QVector<Profile> PyrLevels;
      QVector<LandmarkTriangle> Landmarks;
      Scale ScaleObj;
    };
  }
}

#endif // COMMON_MODELS_ACTIVESHAPEMODEL_H
