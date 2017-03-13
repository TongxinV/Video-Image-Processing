
TARGET  = base
TEMPLATE= lib
VERSION = 0.1.0
CONFIG += static

DESTDIR = ../lib

INCLUDEPATH += ../include
DEPENDPATH  += . ../include


SOURCES += \
    smdkv210/linuxfbscreen.cpp \
    c1screen.cpp \
    c1painter.cpp \
    c1image.cpp
HEADERS += \
    smdkv210/linuxfbscreen.h \
    ../include/c1screen.h \
    ../include/c1painter.h \
    ../include/c1image.h
