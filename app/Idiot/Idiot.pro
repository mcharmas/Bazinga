# -------------------------------------------------
# Project created by QtCreator 2010-03-02T17:54:53
# -------------------------------------------------
QT += network
TARGET = Idiot
TEMPLATE = app
SOURCES += main.cpp \
    idiotwindow.cpp \
    imagewidget.cpp
HEADERS += idiotwindow.h \
    imagewidget.h
FORMS += idiotwindow.ui
INCLUDEPATH += "../ClientLib"
win32:LIBS += -L"../ClientLib/release" \
    -lClientLib
unix:LIBS += -L"../ClientLib" \
    -lClientLib
