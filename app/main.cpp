#include <iostream>
#include <unistd.h>
#include <smdkv210/linuxfbscreen.h>

#include <c1image.h>

using namespace std;

int main()
{


#if 1
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
