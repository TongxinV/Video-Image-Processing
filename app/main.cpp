#include <iostream>
#include <unistd.h>


#include <smdkv210/linuxfbscreen.h>
#include <c1image.h>
#include <smdkv210/videodevice.h>

#include <smdkv210/showvideo.h>

using namespace std;

int main()
{

#if 1
    //视频显示测试
    showvideo sv;

    for(int i = 0; i < 10; ++i){
        sv.show();
        usleep(100);
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
