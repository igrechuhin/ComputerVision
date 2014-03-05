#include "Generator.h"

#include <QtCore/QCoreApplication>
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QTimer>

namespace
{
  void showHelp()
  {
    QFile stdOut;
    stdOut.open(stdout, QIODevice::WriteOnly);
    QTextStream console(&stdOut);

    console << "Usage:"                                                           << endl;
    console << "   ASMModelGenerator.exe [/?]"                                    << endl;
    console << "                         [/c configuration_file]"                 << endl;
    console                                                                       << endl;
    console << "Description:"                                                     << endl;
    console << "   /?   Display this message."                                    << endl;
    console << "   /c   Path to the config file."                                 << endl;
    console << "        If not specified, default settings are considered."       << endl;
    console << "        Default settings - builds the model on all the database." << endl;
  }
}

int main(int argc, char *argv[])
{
  QCoreApplication app(argc, argv);

  QCoreApplication::setOrganizationName("PFPI");
  QCoreApplication::setApplicationName("ActiveShapeModelGenerator");

  QStringList cmdArgs(app.arguments());

  if (cmdArgs.contains("/?"))
  {
    showHelp();
    return 0;
  }

  Generator generator(cmdArgs);
  generator.run();

  QTimer::singleShot(0, &app, SLOT(quit()));
  return app.exec();
}
