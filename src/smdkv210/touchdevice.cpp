


#include "smdkv210/touchdevice.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#define DEVICE_TOUCH  	"/dev/input/event2"

int touchdevice::fd = -1;
struct input_event touchdevice::event;

touchdevice::touchdevice()
{
    open_device();
}

touchdevice::~touchdevice()
{
    close_device();
}


void touchdevice::open_device()
{
    fd = open(DEVICE_TOUCH, O_RDONLY);
    if(fd < 0){
        perror("open");
        return ;
    }
}

void touchdevice::close_device()
{
    if(-1 == fd)
        return;

    ::close(fd);
    fd = -1;
}


void touchdevice::input()
{
    if(fd == -1){
        fprintf(stderr, "touch input device is not open.\n");
        return ;
    }

    // 第2步：读取一个event事件包
    memset(&event, 0, sizeof(struct input_event));

    if (read(fd, &event, sizeof(struct input_event)) != sizeof(struct input_event)){
        perror("read");
        return ;
    }
#if 0
    printf("-------------------------\n");
    printf("type: %hd\n", event.type);
    printf("code: %hd\n", event.code);
    printf("value: %d\n", event.value);
    printf("\n");
#endif
}

int touchdevice::index()
{
    //#define  EV_UNKNOWN 0
    //#define  EV_IMGPROC 1
    //#define  EV_VDOSHOW 2

    if ((event.type == EV_ABS) && (event.code == ABS_X))
    {
        if ((event.value > 200) && (event.value < 824))
        {
            return EV_IMGPROC;
        }

        if ((event.value > 824) && (event.value <1024))
        {
            return EV_VDOSHOW;
        }
    }

    return EV_UNKNOWN;
}



