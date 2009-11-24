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
#LIBS += -L"C:\Native\OpenCV20\lib" -lcxcore200 -lcv200 -lcvaux200 -lhighgui200 -lml200
#INCLUDEPATH += C:\Native\OpenCV20\include


# Linux:
LIBS += -lcxcore -lcv -lcvaux -lhighgui -lml

