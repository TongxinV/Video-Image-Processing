#include <iostream>
#include <unistd.h>


#include <smdkv210/linuxfbscreen.h>
#include <c1image.h>


#include <smdkv210/showvideo.h>
#include "IM_320_240.hpp"

#include "opencv2/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace std;
using namespace cv;

//******************灰度转换函数**********************
void ConvertRGB2GRAY(const Mat &image,Mat &imageGray);

Mat imageSource;
Mat imageGray;
Mat imageCanny;

int main()
{
    LinuxFbScreen screen(1024, 600);
    screen.initDevice();

    //============================

    Mat imageSource(240, 320, CV_8UC3, (uchar *)IM_320_240);//将位图数据直接转成Mat类型对象

    uchar* data = NULL;

    data = imageSource.data; //提取处理后的Mat类型对象的像素数据
    screen.showImageBGR(320, 240, data);

    ConvertRGB2GRAY(imageSource,imageGray); //RGB转换为灰度图

    data = imageGray.data;   //提取处理后的Mat类型对象的像素数据
    screen.showImageGray(320, 240, data);

    Canny(imageGray, imageCanny, 100, 300, 3);//边缘检测

    data = imageCanny.data;  //提取处理后的Mat类型对象的像素数据
    screen.showImageGray(320, 240, data);

    //=============================

    sleep(3);
    screen.shutdownDevice();

#if 0
    //视频显示测试
    showvideo sv;

    for(int i = 0; i < 1000; ++i){
        sv.show();
        //usleep(100);
    }

#endif

#if 0
    //videodevice 测试
    videodevice vd;

    vd.open_device();

    vd.init_v4l2();     //利用v4l2初始化摄像头

    vd.start_capturing();

    sleep(1);

    vd.stop_capturing();

    vd.close_device();
#endif

#if 0
    //图片显示测试
    LinuxFbScreen screen(1024, 600);
    screen.initDevice();

    C1Image *img = new C1Image;

    img->loadFromData("tu001.bmp");

    screen.setPixmap(200, 200, img);

    img->freeData();


    sleep(3);
    screen.shutdownDevice();
#endif

    cout << "Hello World!" << endl;
    return 0;
}



//******************灰度转换函数*************************
//第一个参数image输入的彩色RGB图像；
//第二个参数imageGray是转换后输出的灰度图像；
//*****************************************************
void ConvertRGB2GRAY(const Mat &image,Mat &imageGray)
{
    if(!image.data||image.channels()!=3)
    {
        return ;
    }
    imageGray=Mat::zeros(image.size(),CV_8UC1);
    uchar *pointImage=image.data;
    uchar *pointImageGray=imageGray.data;
    int stepImage=image.step;
    int stepImageGray=imageGray.step;

    int i,j;
    int cnt;

    for(i=0;i<imageGray.rows;i++)
    {
        for(j=0;j<imageGray.cols;j++)
        {
            //pointImageGray[i*stepImageGray+j]=0.114*pointImage[i*stepImage+3*j]+0.587*pointImage[i*stepImage+3*j+1]+0.299*pointImage[i*stepImage+3*j+2];
            cnt = i*stepImage+3*j;
            pointImageGray[i*stepImageGray+j]=(76*pointImage[cnt+0]+150*pointImage[cnt+1]+30*pointImage[cnt+2]) >> 8;
        }
    }
}
