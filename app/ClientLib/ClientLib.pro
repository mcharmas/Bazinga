# -------------------------------------------------
# Project created by QtCreator 2010-01-19T15:36:15
# -------------------------------------------------
QT += network
TARGET = ClientLib
TEMPLATE = lib
DEFINES += CLIENTLIB_LIBRARY
SOURCES += bconnection.cpp \
    bdatagram.cpp \
    bconnectionexception.cpp \
    bconnectionwidget.cpp \
    bconnectionblocker.cpp \
    bob.cpp \
    boblist.cpp
HEADERS += ClientLib_global.h \
    bconnection.h \
    bdatagram.h \
    bconnectionexception.h \
    bconnectionwidget.h \
    bconnectionblocker.h \
    bob.h \
    boblist.h
FORMS += bconnectionwidget.ui
