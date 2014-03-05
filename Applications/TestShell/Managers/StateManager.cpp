#include "StateManager.h"

#include "../../Common/Settings/Settings.h"
#include "../../Common/ModuleLoader/ModuleLoader.h"

#include <QMetaType>
#include <QDir>
#include <QFileDialog>
#include <QPluginLoader>
#include <QApplication>

const QThread::Priority SOURCE_PRIORITY(QThread::IdlePriority);
const QThread::Priority PROCESSOR_PRIORITY(QThread::HighestPriority);

StateManager::StateManager( QWidget* Parent )
  : QObject(Parent),
    CurrentState(NoOpState),
    WorkThread(new ProcessThread(this, PROCESSOR_PRIORITY))
{
  loadSourcesPlugins();

  qRegisterMetaType<Frame>("Frame");
  Display.reset(new DisplayManager(reinterpret_cast<TestShell*>(Parent)));
  connect(this, SIGNAL(log(int, const QString&)), Display.data(), SLOT(newLogText(int, const QString&)));
}

StateManager::~StateManager()
{
  Worker.reset();
  Display.reset();
}

void StateManager::openFile()
{
  closeSource();
  common::Settings settings;
  QString srcFilePath(settings.get(common::Settings::SettingsSourcePath, QDir::currentPath()).toString());
  QString srcFileName(QFileDialog::getOpenFileName(reinterpret_cast<QWidget*>(parent()), tr("Open file"), srcFilePath, getFilters()));
  if (srcFileName.isEmpty())
  {
    emit log(0, tr("Open file source was canceled."));
    return;
  }
  settings.set(common::Settings::SettingsSourcePath, srcFileName.left(srcFileName.lastIndexOf('/') + 1));
  openSource(srcFileName);
}

void StateManager::openCapture()
{
  closeSource();
  openSource();
}

void StateManager::openSource( const QString& srcFileName /*= QString()*/ )
{
  foreach(Interface* source, AvailableSources)
  {
    if (source->canProcess(srcFileName) && source->open(srcFileName))
    {
      Source.reset(new SourceManager(this, source));
      connect(Source.data(), SIGNAL(newFrame(const Frame&, const qint64&)), Display.data(), SLOT(newFrame(const Frame&, const qint64&)));
      connect(Source.data(), SIGNAL(sourceFinished()), this, SLOT(sourceFinished()));
      if (Source->isSeekable())
      {
        Display->setVideoSource(Source->getTotalFrames());
      }
      Source->play();
      CurrentState = PlayState;
      emit updateToState(CurrentState);
      emit log(0, tr("Opened ") + source->getName().toLower() + tr(" source."));
      return;
    }
  }
  emit log(1, tr("Can not open ") + srcFileName + tr(" source. No suitable handler found."));
}

void StateManager::closeSource()
{
  if (CurrentState == NoOpState)
    return;
  Worker.reset();
  Source.reset();
  CurrentState = NoOpState;
  emit updateToState(CurrentState);
  log(0, tr("Closed source."));
}

void StateManager::play( bool DoPlay, bool DoLog )
{
  Q_ASSERT((CurrentState == PlayState) || (CurrentState == PauseState));
  Q_ASSERT((CurrentState == PlayState) != DoPlay );
  Source->play(DoPlay);
  if (DoPlay)
  {
    CurrentState = PlayState;
    if (DoLog)
    {
      log(0, tr("Playback started."));
    }
  }
  else
  {
    CurrentState = PauseState;
    if (DoLog)
    {
      log(0, tr("Playback paused."));
    }
  }
  emit updateToState(CurrentState);
}

void StateManager::run( bool DoRun )
{
  Q_ASSERT((CurrentState == PlayState) || (CurrentState == PauseState));
  if (DoRun)
  {
    Worker.reset(new Processor);
    Worker->moveToThread(WorkThread.data());
    connect(Source.data(), SIGNAL(newFrame(const Frame&, const qint64&)), Worker.data(), SLOT(processNewFrame(const Frame&)), Qt::BlockingQueuedConnection);
    connect(Worker.data(), SIGNAL(clearTest()), Display.data(), SLOT(clearTest()));
    connect(Worker.data(), SIGNAL(testFrame(const Frame&, const QString&)), Display.data(), SLOT(newTestFrame(const Frame&, const QString&)));
    connect(Worker.data(), SIGNAL(testText(const QString&)), Display.data(), SLOT(newTestText(const QString&)));
    connect(Worker.data(), SIGNAL(log(int, const QString&)), Display.data(), SLOT(newLogText(int, const QString&)));
    connect(Worker.data(), SIGNAL(testRect(const QRect&, const QString&)), Display.data(), SLOT(newRect(const QRect&, const QString&)));
    WorkThread->setPriority(PROCESSOR_PRIORITY);
    Source->getCurrentFrame();
    emit log(0, tr("Processing started."));
  }
  else
  {
    Worker.reset();
    emit log(0, tr("Processing paused."));
  }
}

void StateManager::processCurrent()
{
  Source->getCurrentFrame();
}

void StateManager::processNext()
{
  Source->getNextFrame();
}

void StateManager::closeApplication()
{
  if (CurrentState != NoOpState)
    closeSource();
  CurrentState = ClosedState;
  emit updateToState(CurrentState);
}

QString StateManager::getFilters()
{
  const QString openBracket(" (");
  const QString closeBracket(")");
  const QString extsSeparator(";");
  const QString filtersSeparator(";;");
  QStringList filters(tr("Media files") + openBracket);
  typedef QList<Interface*>::const_iterator listIter;
  for (listIter iter(AvailableSources.constBegin()); iter != AvailableSources.constEnd(); iter++)
  {
    if ((*iter)->getFilters().empty())
      continue;
    filters << (*iter)->getName() + tr(" files") + openBracket;
    foreach(QString ext, (*iter)->getFilters())
    {
      ext += extsSeparator;
      filters.first() += ext;
      filters.last() += ext;
    }
    filters.last().remove(filters.last().lastIndexOf(extsSeparator), extsSeparator.size());
    filters.last() += closeBracket;
  }
  filters.first().remove(filters.first().lastIndexOf(extsSeparator), extsSeparator.size());
  filters.first() += closeBracket;

  return filters.join(filtersSeparator);
}

void StateManager::loadSourcesPlugins()
{
  QDir pluginsDir(qApp->applicationDirPath());
  if (!pluginsDir.cd(common::Settings().get(common::Settings::SettingsPluginsPath, "Plugins").toString()))
    return;
  AvailableSources = loadModules<Interface, SrcList >(pluginsDir);
}

void StateManager::sliderPressed()
{
  StateBeforeSlider = CurrentState;
  if (StateBeforeSlider == PlayState)
  {
    play(false, false);
  }
}

void StateManager::sliderReleased()
{
  if (StateBeforeSlider == PlayState)
  {
    play(true, false);
  }
}

void StateManager::sliderMoved( int Value )
{
  Source->setPosition(Value);
  processNext();
}

void StateManager::sourceFinished()
{
  play(false, false);
  Display->setPosition(0);
}
