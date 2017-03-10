#include <iostream>
#include <unistd.h>
#include <smdkv210/linuxfbscreen.h>


using namespace std;

int main()
{
    LinuxFbScreen screen;
    screen.initDevice();
    sleep(3);
    screen.shutdownDevice();

    cout << "Hello World!" << endl;
    return 0;
}
