#include <iostream>
#include <unistd.h>
#include <smdkv210/linuxfbscreen.h>

#include <c1image.h>
//#include <Image_001.h>
#include <Image_002.h>
using namespace std;

int main()
{
    C1Image img;

    img.loadFromData(1024, 600, Image_002);

    LinuxFbScreen screen(1024, 600);
    screen.initDevice();
    screen.setPixmap(0, 0, img);
    sleep(3);
    screen.shutdownDevice();

    cout << "Hello World!" << endl;
    return 0;
}
