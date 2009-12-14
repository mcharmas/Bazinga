#-------------------------------------------------
#
# Project created by QtCreator 2009-10-23T14:21:15
#
#-------------------------------------------------

QT       -= gui

TARGET = KamerkaPobieraczWyswietlacz
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp

# Windows:
#LIBS += -L "E:\OpenCV2.0\lib" -lcxcore200 -lcv200 -lcvaux200 -lhighgui200 -lml200
#INCLUDEPATH += E:\OpenCV2.0\include


# Linux:
LIBS += -lcxcore -lcv -lcvaux -lhighgui -lml

