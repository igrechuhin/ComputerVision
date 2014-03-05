#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "../../Algorithms/Interface.h"

#include <QRect>
#include <QString>
#include <QMap>
#include <QScopedPointer>
#include <QObject>

namespace common
{
  class Frame;
}

namespace algorithms
{
  struct ContextType;
  enum Type;
}

using namespace common;

class Processor : public QObject
{
  Q_OBJECT

public:
    Processor();
    ~Processor();

private:
  void initContext();
  void loadAlgorithms();

public slots:
  void processNewFrame( const Frame& Image );

signals:
  void clearTest();
  void testRect( const QRect& Rect, const QString& Description );
  void testFrame( const Frame& TestImage, const QString& Description );
  void testText( const QString& TestMessage );

  void log( int Severity, const QString& Message );

private:
  AlgMap Algorithms;
  QScopedPointer<AlgContext> Context;
};

#endif // PROCESSOR_H
