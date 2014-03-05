#ifndef TESTSHELL_H
#define TESTSHELL_H


#include "Managers/StateManager.h"
#include "Managers/DisplayManager.h"

#include <QPushButton>

#include <QtGui/QMainWindow>
#include "ui_testshell.h"

class TestShell : public QMainWindow
{
    Q_OBJECT

 friend class DisplayManager;

public:
    TestShell( QWidget *parent = 0, Qt::WFlags flags = 0 );
    ~TestShell();

public slots:
  void updateToState( StateManager::State NewState );

  void setVideoSource( const qint64& TotalFrames );
  void setVideoPosition( const qint64& Pos );

private:
  void setupUi();

signals:
  void quit();

private:
  Ui::TestShellClass ui;
  QPushButton* OpenFileBtn;
  QPushButton* OpenCaptureBtn;
  QPushButton* CloseBtn;
  QPushButton* PlayBtn;
  QPushButton* RunBtn;
  QPushButton* ProcessThisBtn;
  QPushButton* ProcessNextBtn;
  QPushButton* ExitBtn;
  StateManager StateMgr;
};

#endif // TESTSHELL_H
