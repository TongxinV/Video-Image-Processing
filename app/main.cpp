#include <iostream>
#include <unistd.h>


#include <smdkv210/linuxfbscreen.h>
#include <c1image.h>
#include <smdkv210/videodevice.h>


using namespace std;

int main()
{
    videodevice vd;

    vd.open_device();

    vd.init_device();

    vd.init_mmap();

    //vd.init_v4l2();

    vd.start_capturing();

    sleep(1);

    vd.stop_capturing();

    vd.close_device();


#if 0
    LinuxFbScreen screen(1024, 600);
    screen.initDevice();

    C1Image *img = new C1Image;

    img->loadFromData("tu001.bmp");

    screen.setPixmap(0, 0, img);

    img->freeData();


    sleep(3);
    screen.shutdownDevice();
#endif
    cout << "Hello World!" << endl;
    return 0;
}
