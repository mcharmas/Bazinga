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

#LIBS += -L"C:\Native\OpenCV20\lib"

LIBS += -lcxcore -lcv -lcvaux -lhighgui -lml
#INCLUDEPATH += C:\Native\OpenCV20\include
