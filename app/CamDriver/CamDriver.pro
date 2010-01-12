# -------------------------------------------------
# Project created by QtCreator 2010-01-03T18:50:14
# -------------------------------------------------
QT += network
TARGET = CamDriver
TEMPLATE = app
SOURCES += main.cpp \
    configdialog.cpp \
    videoinput.cpp \
    frameretreiver.cpp \
    imagedisplayer.cpp \
    faces.cpp
HEADERS += configdialog.h \
    videoinput.h \
    frameretreiver.h \
    imagedisplayer.h \
    faces.h
FORMS += configdialog.ui
RESOURCES += icons.qrc
LIBS += -L"C:\Native\OpenCV20\lib" \
	-lcxcore200 \
	-lcv200 \
	-lcvaux200 \
	-lhighgui200 \
	-lml200
INCLUDEPATH += "C:\Native\OpenCV20\include"
