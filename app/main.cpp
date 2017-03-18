#include <iostream>
#include <unistd.h>


//#include <smdkv210/linuxfbscreen.h>
//#include <c1image.h>
//#include <smdkv210/videodevice.h>

#include <smdkv210/showvideo.h>
#include "Image_001.h"

#include "opencv2/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace std;
using namespace cv;

int main()
{
    //将位图文件转成Mat类型对象
    Mat img(1024, 600, CV_8UC3, (char *)Image_001);

    //利用opencv相关对Mat类型对象进行图像处理
    sleep(1);

    //提取处理后的Mat类型对象的像素数据


    //显示


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
