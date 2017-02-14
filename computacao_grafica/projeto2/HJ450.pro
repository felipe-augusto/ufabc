#-------------------------------------------------
#
# Project created by QtCreator 2016-06-21T08:28:47
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HJ450
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    openglwidget.cpp \
    scene.cpp \
    sceneobject.cpp \
    light.cpp \
    material.cpp \
    camera.cpp \
    trackball.cpp

HEADERS  += mainwindow.h \
    openglwidget.h \
    scene.h \
    sceneobject.h \
    light.h \
    material.h \
    camera.h \
    trackball.h

FORMS    += mainwindow.ui

RESOURCES += \
    resources.qrc

DISTFILES += \
    vgouraud.glsl \
    fgouraud.glsl \
    fphong.glsl \
    vflat.glsl \
    ../../../shaders/fgouraud.glsl \
    ../../../shaders/fphong.glsl \
    ../../../shaders/fshader1.glsl \
    ../../../shaders/vflat.glsl \
    ../../../shaders/vgouraud.glsl \
    ../../../shaders/vphong.glsl \
    ../../../shaders/vshader1.glsl
