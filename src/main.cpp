#include "mainwindow.h"
#include <QApplication>

#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//Config taken from Simple NGL
//https://github.com/NCCA/SimpleNGL/blob/master/src/main.cpp#L13
//Author: Jon Macey Accesed: 31/03

    QSurfaceFormat format;
    // set the number of samples for multisampling
    // will need to enable glEnable(GL_MULTISAMPLE); once we have a context
    format.setSamples(4);
#if defined(__APPLE__)
    // at present mac osx Mountain Lion only supports GL3.2
    // the new mavericks will have GL 4.x so can change
    format.setMajorVersion(4);
    format.setMinorVersion(1);
#else
    // with luck we have the latest GL version so set to that
    format.setMajorVersion(4);
    format.setMinorVersion(5);
#endif
    // now we are going to set to CoreProfile OpenGL so we can't use and old Immediate mode GL
    format.setProfile(QSurfaceFormat::CoreProfile);
    // now set the depth buffer to 24 bits
    format.setDepthBufferSize(24);
    // set that as the default format for all windows
    QSurfaceFormat::setDefaultFormat(format);

//End Citation

    MainWindow w;
    w.show();

    return a.exec();
}
