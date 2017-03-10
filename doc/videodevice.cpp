#include "videodevice.h"

videodevice::videodevice()
{
    this->fd = -1;
    this->iCount=4;
    this->iIndex=-1;
    this->buffers=NULL;
}

videodevice::~videodeice()
{

}


int videodevice::open_device()
{
    //使用阻塞方式打开摄像头设备
    this->fd = open(DEVICE_NAME,O_RDWR);
    if( -1 == this->fd)
    {
        perror("open");
        return -1;
    }

    return 0;
}


int videodevice::close_device()
{
    if( -1 == close(this->fd))
        return -1;
    return 0;
}

int videodevice::init_device()
{
    //查询v4l2设备驱动的功能，例如设备驱动名、总线信息、版本信息等
    struct v4l2_capability cap;

    memset(&cap, 0, sizeof(cap));
    if( -1 == ioctl(this->fd, VIDIOC_QUERYCAP, &cap)) //查询驱动功能
    {
        perror("ioctl VIDIOC_QUERYCAP");
        return -1;
    }
    if (!(cap.capabilities & V4L2_CAP_VIDEO_CAPTURE))
    {
        return -1;
    }
    if (!(cap.capabilities & V4L2_CAP_STREAMING))
    {
        return -1;
    }

#if 1
    printf("Capability infrmations: \n");
    printf("driver: %s\n", cap.driver);
    printf("card: %s\n", cap.card);
    printf("bus_info:%s\n", cap.bus_info);
    printf("version:%08x\n", cap.version);
    printf("capabilities:%08x\n", cap.capabilities);
#endif

    //设置视频捕获格式，设置视频图像数据的长、宽，图像格式（YUYV）
    struct v4l2_format fmt;
    memset(&fmt, 0, sizeof(fmt));

    //视频数据流类型
    fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

    fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_YUYV;//视频源格式为YUYV(其他JPEG、RGB)
    fmt.fmt.pix.width  = 640;
    fmt.fmt.pix.height = 480;
    fmt.fmt.pix.field  = V4L2_FIELD_INTERLACED; //隔行扫描 显示必须也是隔行扫描

    if (-1 == ioctl(fd, VIDIOC_S_FMT, &fmt))     //设置视频捕捉格式
    {
        perror("ioctl VIDIOC_S_FMT error");
        return -1;
    }

    return 0;

}























