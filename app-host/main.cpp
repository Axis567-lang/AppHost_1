#include "MainWindow.h"
#include <QtPlugin>
#include <QApplication>

Q_IMPORT_PLUGIN(CubePlugin)
Q_IMPORT_PLUGIN(SpherePlugin)

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
