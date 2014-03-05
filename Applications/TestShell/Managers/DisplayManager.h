#ifndef DISPLAYMANAGER_H
#define DISPLAYMANAGER_H

#include <QObject>

class TestShell;
class QRect;

namespace common
{
  class Frame;
}

using namespace common;

class DisplayManager : public QObject
{
  Q_OBJECT

public:
  DisplayManager( TestShell* Parent );
  ~DisplayManager();

public slots:
  void clearTest();
  void newFrame( const Frame& FrameRef, const qint64& Pos );
  void newRect( const QRect& Rect, const QString& Description );

  void newTestFrame( const Frame& FrameRef, const QString& Description );
  void newTestText( const QString& TestMessage );
  void newLogText( int Severity, const QString& LogMessage );

  void setPosition( const qint64& Pos );
  void setVideoSource( const qint64& TotalFrames );
};

#endif // DISPLAYMANAGER_H
