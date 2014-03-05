#ifndef ADAPTERS_MATLAB_QPOINTF_H
#define ADAPTERS_MATLAB_QPOINTF_H

#include <QPointF>
#include <QVector>

class mwArray;

namespace adapters
{
  void Convert( mwArray& Output, const QPointF& Input );
  void Convert( mwArray& Output, const QVector<QPointF>& Input );
}

#endif // ADAPTERS_MATLAB_QPOINTF_H