TEMPLATE = app
TARGET   = app
DESTDIR  = ../bin

INCLUDEPATH += . ../include
DEPENDPATH += .



LIBS += -lpthread -lrt
LIBS += -L ../lib -lbase

# lib-opencv
# 头文件路径
INCLUDEPATH += /opt/lib-opencv/include
DEPENDPATH  += /opt/lib-opencv/include
# 动态库路径
# 要么导出环境变量 export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/opt/lib-opencv/lib 然后只要
# LIBS += -lopencv_core
# 要么添加相应链接库路径
LIBS += -L/opt/lib-opencv/lib -lopencv_core -lopencv_imgproc






SOURCES += main.cpp \

HEADERS += \
    IM_320_240.hpp
