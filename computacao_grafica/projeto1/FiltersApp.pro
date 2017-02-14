#-------------------------------------------------
#
# Project created by QtCreator 2016-06-25T22:35:08
#
#-------------------------------------------------

QT       += core gui opengl multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FiltersApp
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    openglwidget.cpp \
    videosurface.cpp

HEADERS  += mainwindow.h \
    openglwidget.h \
    videosurface.h

FORMS    += mainwindow.ui

RESOURCES += \
    resources.qrc
