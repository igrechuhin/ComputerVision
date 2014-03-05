#include "ProcessThread.h"

ProcessThread::ProcessThread( QObject *parent, QThread::Priority PriorityVal )
  : QThread(parent)
{
  start(PriorityVal);
}

ProcessThread::~ProcessThread()
{
  quit();
  wait();
}
