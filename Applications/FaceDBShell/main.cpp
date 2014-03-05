#include "FaceDBShell.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QCoreApplication::setOrganizationName("PFPI");
    QCoreApplication::setApplicationName("FaceDBShell");

    FaceDBShell w;
    w.show();
    return a.exec();
}
