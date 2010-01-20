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
    faces.cpp \
    quadrangles.cpp \
    points.cpp
HEADERS += configdialog.h \
    videoinput.h \
    frameretreiver.h \
    imagedisplayer.h \
    faces.h \
    quadrangles.h \
    points.h
FORMS += configdialog.ui
RESOURCES += icons.qrc
win32 { 
    LIBS += -L"C:\Native\OpenCV20\lib" \
        -lcxcore200 \
        -lcv200 \
        -lcvaux200 \
        -lhighgui200 \
        -lml200
    INCLUDEPATH += "C:\Native\OpenCV20\include"
}
unix:LIBS += -lcxcore \
    -lcv \
    -lcvaux \
    -lhighgui \
    -lml
