#ifndef TOUCHDEVICE_H
#define TOUCHDEVICE_H


#include <linux/input.h>

enum INPUTEvent
{
    EV_UNKNOWN,
    EV_IMGPROC,
    EV_VDOSHOW,
    EV_KEEPON
};

class touchdevice
{
private:
    static int fd;
    static struct input_event event;

public:

    touchdevice();
    virtual ~touchdevice();


    void open_device();
    void close_device();

    static void input();
    static int  index();

};










#endif
















