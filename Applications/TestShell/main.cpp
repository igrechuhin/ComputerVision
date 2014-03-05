#include "testshell.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QCoreApplication::setOrganizationName("PFPI");
    QCoreApplication::setApplicationName("TestShell");

    TestShell w;
    QApplication::connect(&w, SIGNAL(quit()), &a, SLOT(quit()));
    w.showMaximized();
    return a.exec();
}
