#ifndef PROCESSTHREAD_H
#define PROCESSTHREAD_H

#include <QThread>

class ProcessThread : public QThread
{
  Q_OBJECT

public:
    ProcessThread( QObject *parent, QThread::Priority PriorityVal );
    ~ProcessThread();

private:
    
};

#endif // PROCESSTHREAD_H
