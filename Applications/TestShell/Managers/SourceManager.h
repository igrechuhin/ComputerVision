#ifndef SOURCEMANAGER_H
#define SOURCEMANAGER_H

#include "../../Plugins/Sources/Interface.h"

#include <QTimer>
#include <QString>

using namespace plugins::sources;
class SourceManager : public QTimer
{
  Q_OBJECT

public:
  SourceManager( QObject* Parent, Interface* SourcePtr );
  ~SourceManager();

  void play( bool DoPlay = true );

  void getCurrentFrame();
  void getNextFrame();

  bool isSeekable() const;

  qint64 getPosition();
  void setPosition( const qint64& Pos );
  qint64 getTotalFrames() const;

protected:
  virtual void timerEvent( QTimerEvent* TEvent );

private:
  void openSource( const QMap<QString, Interface*>& AvailableSources );
  bool isThisSource( const QString& FileName, const QStringList& SourceExtensions ) const;

private slots:
  void queryFrame();

signals:
  void newFrame( const Frame&, const qint64& );
  void sourceFinished();

private:
  const bool IsCameraSource;
  Interface* Source;
  Frame CurrentFrame;
};

#endif // SOURCEMANAGER_H
