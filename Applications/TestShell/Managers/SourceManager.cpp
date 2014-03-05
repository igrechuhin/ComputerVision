#include "SourceManager.h"

#include <QPluginLoader>

SourceManager::SourceManager( QObject* Parent, Interface* SourcePtr )
  : QTimer(Parent),
    IsCameraSource(SourcePtr->getName() == tr("Camera")),
    Source(SourcePtr)
{
  setSingleShot(SourcePtr->getName() == tr("Image"));
  double fps(SourcePtr->getFPS());
  setInterval(1000 / fps);
}

SourceManager::~SourceManager()
{
  Source->close();
}

void SourceManager::play( bool DoPlay )
{
  DoPlay ? start() : stop();
}

void SourceManager::getCurrentFrame()
{
  emit newFrame(CurrentFrame, Source->getPosition());
}

void SourceManager::getNextFrame()
{
  singleShot(0, this, SLOT(queryFrame()));
}

void SourceManager::timerEvent( QTimerEvent* TEvent )
{
  queryFrame();
}

bool SourceManager::isSeekable() const
{
  return Source->isSeekable();
}

qint64 SourceManager::getPosition()
{
  return Source->getPosition();
}

void SourceManager::setPosition( const qint64& Pos )
{
  Source->setPosition(Pos);
}

qint64 SourceManager::getTotalFrames() const
{
  return Source->getTotalFrames();
}

void SourceManager::queryFrame()
{
  if (!Source->haveMoreFrames())
  {
    setPosition(0);
    emit sourceFinished();
    return;
  }

  Source->getNextFrame(CurrentFrame);

  if (IsCameraSource)
    CurrentFrame.flipLR();

  getCurrentFrame();
}
