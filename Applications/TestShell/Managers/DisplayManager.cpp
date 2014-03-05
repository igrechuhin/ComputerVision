#include "DisplayManager.h"

#include "TestShell.h"

DisplayManager::DisplayManager( TestShell* Parent )
  : QObject(Parent)
{
}

DisplayManager::~DisplayManager()
{
}

void DisplayManager::clearTest()
{
  TestShell* parent(reinterpret_cast<TestShell*>(parent()));
  parent->ui.testFrames->clearFrame();
  parent->ui.testText->clear();
}

void DisplayManager::newFrame( const Frame& FrameRef, const qint64& Pos )
{
  TestShell* parent(reinterpret_cast<TestShell*>(parent()));
  parent->ui.mainFrame->clearFrame();
  parent->ui.mainFrame->setFrame(FrameRef);
  if (Pos > 0)
  {
    setPosition(Pos);
  }
}

void DisplayManager::newRect( const QRect& Rect, const QString& Description )
{
  TestShell* parent(reinterpret_cast<TestShell*>(parent()));
  parent->ui.mainFrame->addRect(Rect, Description);
}

void DisplayManager::newTestFrame( const Frame& FrameRef, const QString& Description )
{
  TestShell* parent(reinterpret_cast<TestShell*>(parent()));
  parent->ui.testFrames->addFrame(FrameRef, Description);
}

void DisplayManager::newTestText( const QString& TestMessage )
{
  TestShell* parent(reinterpret_cast<TestShell*>(parent()));
  parent->ui.testText->addItem(TestMessage);
}

void DisplayManager::newLogText( int Severity, const QString& LogMessage )
{
  TestShell* parent(reinterpret_cast<TestShell*>(parent()));
  QIcon icon;
  switch (Severity)
  {
  case 0: icon = QIcon(QPixmap::fromImage(QImage(":/TestShell/Resources/info50x50.png"))); break;
  case 1: icon = QIcon(QPixmap::fromImage(QImage(":/TestShell/Resources/warning50x50.png"))); break;
  default: icon = QIcon(QPixmap::fromImage(QImage(":/TestShell/Resources/error50x50.png"))); break;
  }
  parent->ui.logText->addItem(new QListWidgetItem(icon, LogMessage, parent->ui.logText));
  parent->ui.logText->scrollToBottom();
}

void DisplayManager::setVideoSource( const qint64& TotalFrames )
{
  TestShell* parent(reinterpret_cast<TestShell*>(parent()));
  parent->ui.statusLabel->setVisible(true);
  parent->ui.seekSlider->setVisible(true);
  parent->ui.seekSlider->setMinimum(0);
  parent->ui.seekSlider->setMaximum(TotalFrames);
  parent->ui.seekSlider->setSingleStep(1);
}

void DisplayManager::setPosition( const qint64& Pos )
{
  TestShell* parent(reinterpret_cast<TestShell*>(parent()));
  qint64 totalFrames(parent->ui.seekSlider->maximum());
  qreal percent((100 * static_cast<qreal>(Pos)) / static_cast<qreal>(totalFrames));
  QString statusText = QString("Percent position: %1 %     Frame %2 of %3").arg(QString::number(percent, 'f', 3)).arg(Pos).arg(totalFrames);
  parent->ui.statusLabel->setText(statusText);
  parent->ui.seekSlider->setValue(Pos);
}
