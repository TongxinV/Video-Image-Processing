#ifndef VIDEODEVICE_H
#define VIDEODEVICE_H


#define DEVICE_NAME "/dev/video3"

class videodevice
{
private:
    typedef struct VideoBuffer{
        unsigned char * start;
        size_t length;
    }VideoBuffer;
    VideoBuffer * buffers;

    int fd;                             //视频设备文件描述符
    unsigned int iCount;                //表示申请多少帧
    int iIndex;                         //表示第几帧


public:
    videodevice();
    virtual ~videodevice();
    int open_device();                  //打开视频设备
    int close_device();                 //关闭视频设备
    int init_device();                  //初始化设备
    int init_mmap();                    //初始化内存（申请内核内存，并映射到用户空间）
    int init_v4l2();                    //初始化v4l2
    int start_capturing();              //开始视频采集
    int stop_capturing();               //停止视频采集
    int get_frame(void * * , int *);    //获取数据
    int unget_frame();                  //帧缓存回收

};

#endif // VIDEODEVICE_H
