#include "Matrix.h"

#include "../../Common/Math/Matrix.h"
#include <mclcppclass.h>

namespace adapters
{
  void Convert( mwArray& Output, const Matrix<qreal>& Input )
  {
    mwArray tmp(Input.rows(), Input.cols(), mxDOUBLE_CLASS, mxREAL);
    for (int row(0); row < Input.rows(); row++)
    {
      for (int col(0); col < Input.cols(); col++)
      {
        tmp.Get(2, row+1, col+1).Set(mwArray(Input.get(row, col)));
      }
    }
    Output.Set(tmp);
  }
}
