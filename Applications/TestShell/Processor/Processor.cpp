#include "Processor.h"

#include "../../Algorithms/Common/Processor.h"

#include "../../Common/Settings/Settings.h"
#include "../../Common/ModuleLoader/ModuleLoader.h"

#include <QTime>
#include <QDir>
#include <QPluginLoader>
#include <QApplication>

Processor::Processor()
  : QObject(0),
    Context(new AlgContext)
{
  initContext();
  loadAlgorithms();
}

Processor::~Processor()
{

}

void Processor::initContext()
{
  common::Settings settings;
  Context->Detection.In.HaarCascadeClassifierFileName =
    settings.get(common::Settings::SettingsDetectionViolaJonesClassifier, "haarcascade_frontalface_default.xml").toString();
  Context->Detection.In.ScaleFactor = settings.get(common::Settings::SettingsDetectionScaleFactor, 1.1f).toReal();
}

void Processor::loadAlgorithms()
{
  QDir algorithmsDir(qApp->applicationDirPath());
  if (!algorithmsDir.cd(common::Settings().get(common::Settings::SettingsAlgorithmsPath, "Algorithms").toString()))
    return;
  Algorithms = loadModules<AlgInterface, AlgMap>(algorithmsDir);
  foreach(AlgInterface* algorithm, Algorithms.values())
  {
    bool initOK(algorithm->init(*Context));
    Q_ASSERT(initOK);
  }
}

void Processor::processNewFrame( const Frame& Image )
{
  emit clearTest();

  qreal minObjectSize = 0.15f;
  Context->Detection.In.MinObjectSize = QSize(Image.width(), Image.height()) * minObjectSize;

  using namespace algorithms;
  AlgTimeMap elapsedTime(process(*Context, Image, Algorithms, AlgorithmsBegin, AlgorithmsEnd));

  AlgTimeMap::const_iterator algTime(elapsedTime.constBegin());
  AlgTimeMap::const_iterator algTimeEnd(elapsedTime.constEnd());
  for (; algTime != algTimeEnd; algTime++)
  {
    emit testText(QString("Algorithm %1 runtime: %2 msec.").arg(Algorithms[algTime.key()]->getName()).arg(algTime.value()));
  }

  AlgDetOutputMap::const_iterator objectsEnd(Context->Detection.Out.constEnd());
  for (AlgDetOutputMap::const_iterator objPos(Context->Detection.Out.constBegin()); objPos != objectsEnd; objPos++)
  {
    emit testRect(objPos.value().Rectangle, Algorithms[objPos.key()]->getName());
  }
   
//   emit testFrame( Image, QString("test4") );
//   emit testFrame( Image(QRect(0,0,100,200)), QString("test1") );
//   emit testFrame( Image(QRect(100,0,100,200)), QString("test2") );
//   emit testFrame( Image(QRect(0,100,100,200)), QString("test3") );
// 
//   static qint64 i = 0;
// 
//   emit testText(QString::number(i++));
//   emit testText(QString::number(i++));
//   emit testText(QString::number(i++));

//   emit log(0, QString::number(i++));
//   emit log(1, QString::number(i++));
//   emit log(2, QString::number(i++));
}
