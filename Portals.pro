#-------------------------------------------------
#
# Project created by QtCreator 2017-03-21T15:33:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Portals
TEMPLATE = app


SOURCES += $$PWD/src/*.cpp

HEADERS  += $$PWD/include/*.h
INCLUDEPATH += $$PWD/include/
include($(HOME)/NGL/UseNGL.pri)

FORMS += $$PWD/ui/*.ui

OBJECTS_DIR=   $$PWD/obj

MOC_DIR = $$PWD/moc

UI_DIR = $$PWD/include

FORMS    += $$PWD/ui/mainwindow.ui
