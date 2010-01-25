# -------------------------------------------------
# Project created by QtCreator 2010-01-19T15:36:15
# -------------------------------------------------
QT += network
QT -= gui
TARGET = ClientLib
TEMPLATE = lib
DEFINES += CLIENTLIB_LIBRARY
SOURCES += clientlib.cpp \
    bconnection.cpp \
    bdatagram.cpp \
    bconnectionexception.cpp
HEADERS += clientlib.h \
    ClientLib_global.h \
    bconnection.h \
    bdatagram.h \
    bconnectionexception.h
