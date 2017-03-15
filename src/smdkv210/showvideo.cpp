#include <smdkv210/showvideo.h>

#include <unistd.h>

showvideo::showvideo()
    :screen(NULL), vd(NULL), img(NULL), pp(NULL), p(NULL), len(0)
{
    screen = new LinuxFbScreen(1024, 600);

    screen->initDevice();           //初始化播放设备

    vd = new videodevice;

    int iRet = -1;
    iRet = vd->open_device();       //打开摄像头
    if(-1 == iRet){
        vd->close_device();
    }

    iRet = vd->init_v4l2();         //初始化v4l2
    if(-1 == iRet){
        vd->close_device();
    }

    iRet = vd->start_capturing();   //开始视频采集
    if(-1 == iRet){
        vd->stop_capturing();
        vd->close_device();
    }

    pp  = (unsigned char *)malloc(VIDEO_WIDTH * VIDEO_HEIGHT * 3 * sizeof(char));
    img = new C1Image(pp, VIDEO_WIDTH, VIDEO_HEIGHT, C1Image::Format_RGB888);

}


void showvideo::show()
{
    int iRet = -1;
    iRet = vd->get_frame((void * *)&p, &len);  //获取视频采集的初始数据
    if(-1 == iRet){
        printf("get frame failed.\n");
    }

    sleep(1);

    convert_yuv_rgb_buffer(p, pp, VIDEO_WIDTH, VIDEO_HEIGHT);   //数据转换

    sleep(1);

    screen->setPixmap(192, 60, img);

    sleep(1);

    vd->unget_frame();
}

showvideo::~showvideo()
{
    vd->stop_capturing();
    vd->close_device();

    screen->shutdownDevice();
}


//yuv格式转换为rgb格式的算法处理函数
int showvideo::convert_yuv_to_rgb_pixel(int y, int u, int v)
{
    unsigned int pixel32 = 0;
    unsigned char * pixel = (unsigned char *)&pixel32;
    int r, g, b;
    r = (int)(y + (1.370705 * (v - 128)));
    g = (int)(y - (0.698001 * (v - 128)) - (0.337633 * (u - 128)));
    b = (int)(y + (1.732446 * (u - 128)));
    if(r > 255) r = 255;
    if(g > 255) g = 255;
    if(b > 255) b = 255;
    if(r < 0) r = 0;
    if(r < 0) g = 0;
    if(r < 0) b = 0;
    pixel[0] = r * 220/256;
    pixel[1] = g * 220/256;
    pixel[2] = b * 220/256;

    return pixel32;
}

int showvideo::convert_yuv_rgb_buffer(unsigned char *yuv, unsigned char *rgb,\
                   unsigned int width, unsigned int height)
{
    unsigned in,  out = 0;
    unsigned int  pixel_16;
    unsigned char pixel_24[3];
    unsigned int  pixel32;

    int y0, u, y1, v;
    for(in = 0; in < width * height * 2; in +=4)
    {
        pixel_16 = yuv[in+3]<<24 | yuv[in+2]<<16 | yuv[in+1]<<8 | yuv[in+0];
        y0 = (pixel_16 & 0x000000ff);
        u  = (pixel_16 & 0x0000ff00) >> 8;
        y1 = (pixel_16 & 0x00ff0000) >> 16;
        v  = (pixel_16 & 0xff000000) >> 24;

        pixel32 = convert_yuv_to_rgb_pixel(y0,u,v);
        pixel_24[0] = (pixel32 & 0x000000ff);
        pixel_24[1] = (pixel32 & 0x0000ff00) >> 8;
        pixel_24[2] = (pixel32 & 0x00ff0000) >> 16;
        rgb[out++] = pixel_24[0];
        rgb[out++] = pixel_24[1];
        rgb[out++] = pixel_24[2];

        pixel32 = convert_yuv_to_rgb_pixel(y1,u,v);
        pixel_24[0] = (pixel32 & 0x000000ff);
        pixel_24[1] = (pixel32 & 0x0000ff00) >> 8;
        pixel_24[2] = (pixel32 & 0x00ff0000) >> 16;
        rgb[out++] = pixel_24[0];
        rgb[out++] = pixel_24[1];
        rgb[out++] = pixel_24[2];
    }
    return 0;
}






















