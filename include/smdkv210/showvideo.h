#ifndef SHOWVIDEO_H
#define SHOWVIDEO_H


#include <smdkv210/linuxfbscreen.h>
#include <smdkv210/videodevice.h>
#include <c1image.h>

class showvideo
{
private:
    LinuxFbScreen *screen;          //用于显示视频图片
    videodevice *vd;                //videodevice对象
    C1Image *img;                   //图片
    unsigned char *pp;              //转换之后的视频数据
    unsigned char *p;               //存放获取的原始视频数据 buffers->start
    int len;                        //存放原始视频数据的长度 buffers->length
/*
public:
    typedef enum tagstatus{
        Not_available,              //不可用
        Accessable                  //允许访问
    }status_e;
    status_e STAT;
*/
public:
    showvideo();
    virtual ~showvideo();

    void show();
    int convert_yuv_to_rgb_pixel(int y, int u, int v);
    int convert_yuv_rgb_buffer(unsigned char *yuv, unsigned char *rgb,\
                       unsigned int width, unsigned int height);

    void video_yuv_to_rgb_pixel(unsigned char **pixel, int y, int u, int v);
    void video_yuyv_to_rgb24(const void *yuyv,void *rgb,\
                             unsigned int width,unsigned int height);

};


#endif
