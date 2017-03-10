#ifndef VIDEODEVICE_H
#define VIDEODEVICE_H


#include <stdio.h>
#include <sys/types.h>
#include <linux/videodev.h>

#define DEVICE_NAME "/dev/video0"

class videodevice
{
private:
    typedef struct VideoBuffer{
        unsigned char * start;
        size_t length;
    }VideoBuffer;
    VideoBuffer * buffers;

    int fd;                     //打开的设备文件描述符
    unsigned int iCount;        //表示申请多少帧
    int iIndex;                 //表示第几帧


public:
    videodevice();
    ~videodeice();
    int open_device();
    int close_device();
    int init_device();
    int init_mmap();
    int init_v4l2();
    int start_capturing();
    int stop_capturing();

};

#endif // VIDEODEVICE_H
