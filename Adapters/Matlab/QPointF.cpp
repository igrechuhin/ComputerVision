#include "QPointF.h"

#include <mclcppclass.h>

namespace adapters
{
  void Convert( mwArray& Output, const QPointF& Input )
  {
    mwArray tmp(1, 2, mxDOUBLE_CLASS);
    tmp.Get(2, 1, 1).Set(mwArray(Input.x()));
    tmp.Get(2, 1, 2).Set(mwArray(Input.y()));
    Output.Set(tmp);
  }

  void Convert( mwArray& Output, const QVector<QPointF>& Input )
  {
    mwArray tmp(Input.size(), 2, mxDOUBLE_CLASS);
    for (int index(1); index <= Input.size(); index++)
    {
      const QPointF& point(Input[index-1]);
      tmp.Get(2, index, 1).Set(mwArray(point.x()));
      tmp.Get(2, index, 2).Set(mwArray(point.y()));
    }
    Output.Set(tmp);
  }
}
