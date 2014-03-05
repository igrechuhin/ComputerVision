#ifndef ADAPTERS_MATLAB_ACTIVESHAPEMODEL_H
#define ADAPTERS_MATLAB_ACTIVESHAPEMODEL_H

class mwArray;

namespace common
{
  namespace models
  {
    class ActiveShapeModel;
  }
}

namespace adapters
{
  using namespace common::models;

  void Convert( mwArray& Output, ActiveShapeModel& Input );
}

#endif // ADAPTERS_MATLAB_ACTIVESHAPEMODEL_H
