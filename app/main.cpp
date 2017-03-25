#include <iostream>
#include <unistd.h>
#include <pthread.h>

#include <smdkv210/showvideo.h>
#include <smdkv210/touchdevice.h>
//#include "IM_320_240.hpp"

#include "opencv2/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace std;
using namespace cv;

//******************灰度转换函数**********************
void ConvertRGB2GRAY(const Mat &image,Mat &imageGray);


#define C1VDOSHOW 0
#define C1IMGPROC 1
#define C1KEEPON  2

int eventIndex  = 0;
//******************触摸输入线程**********************

pthread_mutex_t tch_mutex;

void cleanup(void *arg)
{
    printf("cleanup: %s\n", (char *)arg);
}

void *thread_touchinput(void *arg)
{
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
    pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED,NULL);

    pthread_cleanup_push(cleanup, (char *)"Touch Input Event");
    printf("%p.\n", arg);

    touchdevice tc;
    while(1){
        tc.input();

        switch(tc.index())
        {
            case EV_UNKNOWN:
                printf("illegal input!\n");break;
            case EV_IMGPROC:
                printf("eventIndex = C1IMGPROC.\n");
                pthread_mutex_lock(&tch_mutex);
                eventIndex = C1IMGPROC;
                pthread_mutex_unlock(&tch_mutex);break;
            case EV_VDOSHOW:
                printf("eventIndex = C1VDOSHOW.\n");
                pthread_mutex_lock(&tch_mutex);
                eventIndex = C1VDOSHOW;
                pthread_mutex_unlock(&tch_mutex);break;
            default:printf("error.\n");
        }
    }

    pthread_cleanup_pop(0);

    pthread_exit(NULL);

    return NULL;
}

Mat imageSource;
Mat imageGray;
//Mat imageCanny;


int main()
{
    pthread_t id = -1;

    pthread_mutex_init(&tch_mutex, NULL);

    if(-1 != pthread_create(&id, NULL, thread_touchinput, NULL)){
        cout << "Create thread success! " << endl;
    }

    showvideo sv;

    for(int i = 0; i < 1000; ++i){
        sv.proc();

        if(C1IMGPROC == eventIndex)
        {
            printf("************** Image Proc ... **************\n");

            uchar* data = sv.data(); //提取摄像头处理后的RGB格式像素数据

            imageSource = Mat(480, 640, CV_8UC3, data).clone();//用数据初始化矩阵(浅拷贝)，即没有另外开辟内存

            //data = imageSource.data; //提取处理后的Mat类型对象的像素数据
            //sv.inscreen()->showImageRGB (640, 480, imageSource.data);

            //Mat imageGray(480, 640, CV_8UC1, 0);    //这种初始化方式另外开辟了内存

            ConvertRGB2GRAY(imageSource,imageGray); //RGB转换为灰度图

            //data = imageGray.data;   //提取处理后的Mat类型对象的像素数据
            //sv.inscreen()->showImageGray(640, 480, data);


            /**
             * 一调用Canny函数执行几次之后就会触发V4L2驱动相关的错误
             */
            cv::Canny(imageGray, imageGray, 100, 300, 3);     //边缘检测

            //data = imageGray.data;   //提取处理后的Mat类型对象的像素数据
            sv.inscreen()->showImageGray(640, 480, imageGray.data);

            eventIndex = C1KEEPON;

        }
        else if(C1KEEPON == eventIndex)
        {
            //不处理，即保持当前状态
        }
        else if(C1VDOSHOW == eventIndex)
        {
            sv.proc();
            sv.showVideostream();
        }
        else
        {

        }
    }

    printf("cancel thread forced.\n");

    pthread_cancel(id);

    if(pthread_join(id, NULL) != 0){
        printf("pthread_join error.  \n");
    }else{
        printf("pthread_join success.\n");
    }

    pthread_mutex_destroy(&tch_mutex);

#if 0
    //opencv测试
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


    touchdevice tc;
    tc.input();
#endif


#if 0
    //视频显示测试
    showvideo sv;

    for(int i = 0; i < 100; ++i){
        sv.proc();
        sv.show();
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
