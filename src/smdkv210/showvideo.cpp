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

    video_yuyv_to_rgb24(p, pp, VIDEO_WIDTH, VIDEO_HEIGHT);
    //convert_yuv_rgb_buffer(p, pp, VIDEO_WIDTH, VIDEO_HEIGHT);   //数据转换


    screen->setPixmap(192, 60, img);


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


//==================================================================

void showvideo::video_yuv_to_rgb_pixel(unsigned char **pixel, int y, int u, int v)
{
    int rgbdata[3];

    #define R   0
    #define G   1
    #define B   2

    /*
    * YUV与RGB相互转换的公式如下（RGB取值范围均为0-255）
    * Y = 0.299R + 0.587G + 0.114B
    * U = -0.147R - 0.289G + 0.436B
    * V = 0.615R - 0.515G - 0.100B
    * R = Y + 1.14V
    * G = Y - 0.39U - 0.58V
    * B = Y + 2.03U
    */

    rgbdata[R] = y + (v - 128) + (((v - 128) * 104 ) >> 8);
    rgbdata[G] = y - (((u - 128) * 89) >> 8) - (((v - 128) * 183) >> 8);
    rgbdata[B] = y + (u - 128) + (((u - 128) * 199) >> 8);

    if (rgbdata[R] > 255)  rgbdata[R] = 255;
    if (rgbdata[R] < 0)    rgbdata[R] = 0;
    if (rgbdata[G] > 255)  rgbdata[G] = 255;
    if (rgbdata[G] < 0)    rgbdata[G] = 0;
    if (rgbdata[B] > 255)  rgbdata[B] = 255;
    if (rgbdata[B] < 0)    rgbdata[B] = 0;


    (*pixel)[0] = rgbdata[R];
    (*pixel)[1] = rgbdata[G];
    (*pixel)[2] = rgbdata[B];

    (*pixel) +=3;
}



void showvideo::video_yuyv_to_rgb24(const void *yuyv, void *rgb, unsigned int width, unsigned int height)
{
    int yuvdata[4];
    unsigned char *yuv_buf;
    unsigned int i, j;

    #define Y0  0
    #define U   1
    #define Y1  2
    #define V   3

    yuv_buf = (unsigned char *)yuyv;
    if(rgb != NULL)
    {
        for(i = 0; i < height * 2; i++){
            for(j = 0; j < width; j+= 4){
                /* get Y0 U Y1 V */
                yuvdata[Y0] = *(yuv_buf + i * width + j + 0);
                yuvdata[U]  = *(yuv_buf + i * width + j + 1);
                yuvdata[Y1] = *(yuv_buf + i * width + j + 2);
                yuvdata[V]  = *(yuv_buf + i * width + j + 3);

                video_yuv_to_rgb_pixel((unsigned char **)(&rgb), yuvdata[Y0], yuvdata[U], yuvdata[V]);
                video_yuv_to_rgb_pixel((unsigned char **)(&rgb), yuvdata[Y1], yuvdata[U], yuvdata[V]);
            }
        }
    }

}
















