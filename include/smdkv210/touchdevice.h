#ifndef TOUCHDEVICE_H
#define TOUCHDEVICE_H


#include <linux/input.h>


class touchdevice
{
private:
    int fd;
    struct input_event event;

public:

    touchdevice();
    virtual ~touchdevice();


    void open_device();
    void close_device();

    void input();

};










#endif
















