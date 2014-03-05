#include "testshell.h"

TestShell::TestShell( QWidget *parent, Qt::WFlags flags )
    : QMainWindow(parent, flags),
      OpenFileBtn(new QPushButton(tr("Open File"))),
      OpenCaptureBtn(new QPushButton(tr("Open Capture"))),
      CloseBtn(new QPushButton(tr("Close"))),
      PlayBtn(new QPushButton(tr("Play"))),
      RunBtn(new QPushButton(tr("Run"))),
      ProcessThisBtn(new QPushButton(tr("Process This"))),
      ProcessNextBtn(new QPushButton(tr("Process Next"))),
      ExitBtn(new QPushButton(tr("Exit"))),
      StateMgr(this)
{
  setupUi();
  connect(&StateMgr, SIGNAL(updateToState(StateManager::State)), this, SLOT(updateToState(StateManager::State)));
  StateMgr.emitState();

  connect(OpenFileBtn,    SIGNAL(clicked(bool)),  &StateMgr, SLOT(openFile()));
  connect(OpenCaptureBtn, SIGNAL(clicked(bool)),  &StateMgr, SLOT(openCapture()));
  connect(CloseBtn,       SIGNAL(clicked(bool)),  &StateMgr, SLOT(closeSource()));
  connect(PlayBtn,        SIGNAL(clicked(bool)),  &StateMgr, SLOT(play(bool)));
  connect(RunBtn,         SIGNAL(clicked(bool)),  &StateMgr, SLOT(run(bool)));
  connect(ProcessThisBtn, SIGNAL(clicked()),      &StateMgr, SLOT(processCurrent()));
  connect(ProcessNextBtn, SIGNAL(clicked()),      &StateMgr, SLOT(processNext()));
  connect(ExitBtn,        SIGNAL(clicked(bool)),  &StateMgr, SLOT(closeApplication()));

  connect(ui.seekSlider, SIGNAL(sliderPressed()), &StateMgr, SLOT(sliderPressed()));
  connect(ui.seekSlider, SIGNAL(sliderReleased()), &StateMgr, SLOT(sliderReleased()));
  connect(ui.seekSlider, SIGNAL(sliderMoved(int)), &StateMgr, SLOT(sliderMoved(int)));

//  addLogText(0, tr("Test shell started."));
}

TestShell::~TestShell()
{
}

void TestShell::setupUi()
{
  ui.setupUi(this);
  
  ui.buttonsBar->addWidget(OpenFileBtn);
  ui.buttonsBar->addWidget(OpenCaptureBtn);
  ui.buttonsBar->addWidget(CloseBtn);
  ui.buttonsBar->addWidget(PlayBtn);
  ui.buttonsBar->addWidget(RunBtn);
  ui.buttonsBar->addWidget(ProcessThisBtn);
  ui.buttonsBar->addWidget(ProcessNextBtn);
  ui.buttonsBar->addWidget(ExitBtn);

  PlayBtn->setCheckable(true);
  RunBtn->setCheckable(true);

  ui.seekSlider->setTracking(true);
}

void TestShell::updateToState( StateManager::State NewState )
{
  switch (NewState)
  {
  case StateManager::NoOpState:
    CloseBtn->setEnabled(false);
    PlayBtn->setText(tr("Play"));
    PlayBtn->setEnabled(false);
    PlayBtn->setChecked(false);
    RunBtn->setEnabled(false);
    RunBtn->setChecked(false);
    ProcessThisBtn->setEnabled(false);
    ProcessNextBtn->setEnabled(false);
    ui.statusLabel->setVisible(false);
    ui.seekSlider->setVisible(false);
  	break;
  case StateManager::PlayState:
  case StateManager::PauseState:
    CloseBtn->setEnabled(true);
    PlayBtn->setEnabled(true);
    RunBtn->setEnabled(true);
    ProcessThisBtn->setEnabled(true);
    ProcessNextBtn->setEnabled(true);
    break;
  case StateManager::ClosedState:
    emit quit();
    break;
  default: Q_ASSERT_X(false, "TestShell::updateToState", "Not implemented");
  }

  if (NewState == StateManager::PlayState)
  {
    PlayBtn->setText(tr("Pause"));
    PlayBtn->setChecked(true);
  }
  else
  {
    PlayBtn->setText(tr("Play"));
    PlayBtn->setChecked(false);
  }
}

void TestShell::setVideoSource( const qint64& TotalFrames )
{
}

void TestShell::setVideoPosition( const qint64& Pos )
{
  qint64 totalFrames(ui.seekSlider->maximum());
  qreal percent(static_cast<qreal>(Pos) / static_cast<qreal>(totalFrames));
  QString statusText = QString("Percent position: %1 %     Frame %2 of %3").arg(percent).arg(Pos).arg(totalFrames);
  ui.statusLabel->setText(statusText);
  ui.seekSlider->setValue(Pos);
}
