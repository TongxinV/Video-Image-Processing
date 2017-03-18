TEMPLATE = app
TARGET   = app
DESTDIR  = ../bin

INCLUDEPATH += . ../include
DEPENDPATH += .

LIBS += -L ../lib -lbase

# opencv-arm
INCLUDEPATH += $$PWD/../../../../../../usr/local/opencv-arm/include
DEPENDPATH += $$PWD/../../../../../../usr/local/opencv-arm/include

LIBS += -lpthread -lrt
LIBS += -L$$PWD/../../../../../../usr/local/opencv-arm/lib/ -lopencv_core \
   -lopencv_highgui -lopencv_imgproc -lopencv_ml


SOURCES += main.cpp \

HEADERS += \
    Image_001.h
