#include "mainwindow.h"
#include <QApplication>
#include <QSurfaceFormat>

int main(int argc, char *argv[])
{
    QSurfaceFormat format ;
    //format . setVersion (4 , 0) ;
    format . setDepthBufferSize (24) ;
    format . setSamples (4) ;
    format . setProfile ( QSurfaceFormat :: CompatibilityProfile ) ;
    QSurfaceFormat :: setDefaultFormat ( format ) ;

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
