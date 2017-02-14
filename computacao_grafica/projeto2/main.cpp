#include "mainwindow.h"
#include <QApplication>
# include <QSurface>
int main(int argc, char *argv[])
{
    QSurfaceFormat format ;
    //format.setVersion(4,1);
    format.setProfile(QSurfaceFormat::CompatibilityProfile);
    // depth of the buffer size : to better depth test
    format.setDepthBufferSize (32) ;
    // antialiasing sampling
    format.setSamples(4);
    QSurfaceFormat::setDefaultFormat(format);
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
