


#include "smdkv210/touchdevice.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#define DEVICE_TOUCH  	"/dev/input/event2"


touchdevice::touchdevice()
    :fd(-1)
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

    printf("-------------------------\n");
    printf("type: %hd\n", event.type);
    printf("code: %hd\n", event.code);
    printf("value: %d\n", event.value);
    printf("\n");
}





