#include <iostream>
#include <unistd.h>


#include <smdkv210/linuxfbscreen.h>
#include <c1image.h>


#include <smdkv210/showvideo.h>
#include "IM_320_240.hpp"

#include "opencv2/core.hpp"
//#include "opencv2/highgui/highgui.hpp"
//#include "opencv2/imgproc/imgproc.hpp"

using namespace std;
using namespace cv;

//******************灰度转换函数*************************
//第一个参数image输入的彩色RGB图像；
//第二个参数imageGray是转换后输出的灰度图像；
//*************************************************************
void ConvertRGB2GRAY(const Mat &image,Mat &imageGray);

Mat imageSource;
Mat imageGray;
Mat imageGaussian;

int main()
{
    //将位图数据直接转成Mat类型对象
    Mat imageSource(320, 240, CV_8UC3, (char *)IM_320_240);

    //利用opencv相关对Mat类型对象进行图像处理
    //ConvertRGB2GRAY(imageSource,imageGray); //RGB转换为灰度图

    //提取处理后的Mat类型对象的像素数据

    for( size_t nrow = 0; nrow < 1; nrow++)
     {
        for(size_t ncol = 0; ncol < imageSource.cols; ncol++)
        {
            Vec3b bgr = imageSource.at<Vec3b>(nrow,ncol);
            cout   << "("<<bgr.val[0]<<","
                         <<bgr.val[1]<<","
                         <<bgr.val[2]<<")";
        }
        cout << endl;
     }
    //显示
    LinuxFbScreen screen(1024, 600);
    screen.initDevice();


#if 0

    unsigned int *p = screen.get_displayspace_point();

    for( unsigned int nrow = 0; nrow < (unsigned int)imageSource.rows; nrow++)
    {
        uchar* data = imageSource.ptr<uchar>(nrow);

        for(unsigned int ncol = 0; ncol < (unsigned int)imageSource.cols * imageSource.channels(); ncol++)
        {
            *(p + nrow * 1024 + ncol) = data[ncol];
        }
    }
#endif


#if 0
    unsigned int *p = screen.get_displayspace_point();

    for( unsigned int nrow = 0; nrow < (unsigned int)imageGray.rows; nrow++)
    {
        uchar* data = imageGray.ptr<uchar>(nrow);

        for(unsigned int ncol = 0; ncol < (unsigned int)imageGray.cols * imageGray.channels(); ncol++)
        {
            *(p + nrow * 1024 + ncol) = data[ncol];
        }
    }
#endif



    //C1Image *img = new C1Image;

    //img->data =

    //img->loadFromData(320, 240, pdata);

    //screen.setPixmap(352, 180, img);

    //img->freeData();

    sleep(3);
    screen.shutdownDevice();


#if 0
    //数据流直接转Mat对象测试

    uchar matrix[90] = {

        0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
        0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
        0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
        0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
        0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
        0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff

    };
    //将位图数据直接转成Mat类型对象
    //Mat img(1024, 600, CV_8UC3, (char *)Image_001);
    Mat img(5, 6, CV_8UC3, (char *)matrix);

    cout << img;
#endif


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
//*************************************************************
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
    for(int i=0;i<imageGray.rows;i++)
    {
        for(int j=0;j<imageGray.cols;j++)
        {
            pointImageGray[i*stepImageGray+j]=0.114*pointImage[i*stepImage+3*j]+0.587*pointImage[i*stepImage+3*j+1]+0.299*pointImage[i*stepImage+3*j+2];
        }
    }
}
