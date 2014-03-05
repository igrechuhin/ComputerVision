#ifndef STATEMANAGER_H
#define STATEMANAGER_H

#include "DisplayManager.h"
#include "SourceManager.h"
#include "Processor/ProcessThread.h"
#include "Processor/Processor.h"

#include <QScopedPointer>
#include <QList>
#include <QString>
#include <QObject>

class StateManager : public QObject
{
  Q_OBJECT

public:
  enum State
  {
    NoOpState,
    PlayState,
    PauseState,
    ClosedState // application exit
  };

public:
  StateManager( QWidget* Parent );

  ~StateManager();

public:
  void emitState() { emit updateToState(CurrentState); }

  QString getFilters();

public slots:
  void openFile();
  void openCapture();
  void closeSource();
  void play( bool DoPlay = false, bool DoLog = true );
  void run( bool DoRun = false );
  void processCurrent();
  void processNext();
  void closeApplication();

  void sliderPressed();
  void sliderReleased();
  void sliderMoved( int Value );

  void sourceFinished();

private:
  void openSource( const QString& srcFileName = QString() );
  void loadSourcesPlugins();

signals:
  void updateToState( StateManager::State NewState );

  void setVideoSource( const qint64& TotalFrames );
  void setVideoPosition( const qint64& Pos );

  void log(int Severity, const QString& LogMessage );

private:
  State CurrentState;
  State StateBeforeSlider;
  QScopedPointer<DisplayManager> Display;
  QScopedPointer<SourceManager> Source;
  QList<Interface*> AvailableSources;

  QScopedPointer<ProcessThread> WorkThread;
  QScopedPointer<Processor> Worker;
};

#endif // STATEMANAGER_H
