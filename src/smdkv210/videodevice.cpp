#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <stdlib.h>

#include <linux/videodev.h>
#include <smdkv210/videodevice.h>



videodevice::videodevice()
    : buffers(NULL), fd(-1), iCount(4), iIndex(-1)
{

}

videodevice::~videodevice()
{

}


int videodevice::open_device()
{

    this->fd = open(DEVICE_NAME, O_RDWR);
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
    //查询v4l2设备驱动的能力，设备驱动名、总线信息、版本信息等
    struct v4l2_capability cap;

    memset(&cap, 0, sizeof(cap));
    if( -1 == ioctl(this->fd, VIDIOC_QUERYCAP, &cap))
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

    //设置视频的捕获格式，设置视频图像数据的长、宽，图像格式（如JPEG、YUYV）
    struct v4l2_format fmt;
    memset(&fmt, 0, sizeof(fmt));


    fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

    fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_YUYV;    //视频源格式 测试只能设置成YUYV
    fmt.fmt.pix.width  = 640;                       //视频宽度   测试发现改变不了
    fmt.fmt.pix.height = 480;                       //视频高度   测试发现改变不了
    fmt.fmt.pix.field  = V4L2_FIELD_INTERLACED;     //隔行扫描   显示也必须是隔行扫描

    if (-1 == ioctl(fd, VIDIOC_S_FMT, &fmt))
    {
        perror("ioctl VIDIOC_S_FMT error");
        return -1;
    }
#if 1
    if(-1 == ioctl(fd, VIDIOC_G_FMT, &fmt)){        //得到图片格式
        perror("set format failed!");
        return -1;
    }

    printf("fmt.type:\t\t%d\n",fmt.type);
    printf("pix.pixelformat:\t%c%c%c%c\n",\
            fmt.fmt.pix.pixelformat & 0xFF,\
            (fmt.fmt.pix.pixelformat >> 8) & 0xFF,\
            (fmt.fmt.pix.pixelformat >> 16) & 0xFF,\
            (fmt.fmt.pix.pixelformat >> 24) & 0xFF);
    printf("pix.width:\t\t%d\n",fmt.fmt.pix.width);
    printf("pix.height:\t\t%d\n",fmt.fmt.pix.height);
    printf("pix.field:\t\t%d\n",fmt.fmt.pix.field);
#endif

    return 0;
}


int videodevice::init_mmap()
{
    //申请帧缓冲（在内核）\获取相应地址和长度并映射到用户空间\申请到的缓冲放入缓存队列(这一步在init_v4l2)
    struct v4l2_requestbuffers req;
    memset(&req, 0, sizeof(req));
    req.count  = this->iCount;                  //申请缓冲数量
    req.type   = V4L2_BUF_TYPE_VIDEO_CAPTURE;   //数据流类型
    req.memory = V4L2_MEMORY_MMAP;              //存储类型 采用内存映射的方式

    if (-1 == ioctl(fd, VIDIOC_REQBUFS, &req)){ //申请缓冲（在内核）
        perror("ioctl VIDIOC_REQBUFS error!\n");
        return -1;
    }
    printf("request buffer success.\n");

    if (req.count < 2) {
        printf("req.count < 2 \n");
        return -1;
    }

    //VideoBuffer 结构体保存映射后的信息
    this->buffers = (VideoBuffer *)calloc(req.count, sizeof(VideoBuffer));//在用户空间中建立对应内存

    unsigned int n_buffers;
    for (n_buffers = 0; n_buffers < req.count; ++n_buffers)
    {
        struct v4l2_buffer buf;             //驱动中的一帧
        memset(&buf, 0, sizeof(buf));

        buf.type   = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        buf.memory = V4L2_MEMORY_MMAP;
        buf.index  = n_buffers;             //帧号

        //获得内核相对应帧号的缓冲帧的信息，读取到struct v4l2_buffer buf
        if (-1 == ioctl(fd, VIDIOC_QUERYBUF, &buf)){
            perror("ioctl VIDIOC_QUERYBUF error");
            return -1;
        }

        //根据上面获取到的内核缓冲帧的信息，映射到用户空间，保存到之前申请的VideoBuffer结构体类型变量中
        buffers[n_buffers].length = buf.length;
        buffers[n_buffers].start  =(unsigned char*) mmap(NULL, buf.length,\
                           PROT_READ | PROT_WRITE,MAP_SHARED, fd, buf.m.offset);

        if (MAP_FAILED == buffers[n_buffers].start){
            perror("mmap faild! \n");
            return -1;
        }
    }

    printf("Frame buffer %d: address = 0x%x, length = %d \n",\
           req.count, (unsigned int)buffers[n_buffers].start,\
           buffers[n_buffers].length);

    return 0;
}

int videodevice::init_v4l2()
{
    if( -1 == init_device())
        return -1;

    if( -1 == init_mmap())
        return -1;

    return 0;
}

int videodevice::start_capturing()
{
    //造传送带：定义一个管理内核帧缓冲的队列 驱动采集好一帧数据后把这一帧缓冲对应的struct v4l2_buffer变量挂接到队列上
    unsigned int i = 0;
    for (i=0; i<iCount; ++i)
    {
        struct v4l2_buffer buf;
        memset(&buf, 0, sizeof(buf));

        buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        buf.memory = V4L2_MEMORY_MMAP;
        buf.index = i;
        if ( -1 == ioctl(fd, VIDIOC_QBUF, &buf)){
            perror("ioctl VIDIOC_QBUF error");
            return -1;
        }
    }

    //开始采集视频
    enum v4l2_buf_type type;
    type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    if (-1 == ioctl(fd, VIDIOC_STREAMON, &type)){ //捕捉图像数据
        perror("ioctl VIDIOC_STREAMON error!  ");
        return -1;
    }
    printf(" start video capture success.\n");

    return 0;
}

int videodevice::stop_capturing()
{
    //停止视频采集
    enum v4l2_buf_type type;
    type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    if (-1 == ioctl(fd, VIDIOC_STREAMOFF, &type)){ //捕捉图像数据
        perror("ioctl VIDIOC_STREAMON error!  ");
        return -1;
    }
    printf(" stop video capture success.\n");


    return 0;
}

int videodevice::get_frame(void * * frame_buf, int * len)
{
    //从缓冲队列取出一个缓冲帧
    struct v4l2_buffer buf;
    memset(&buf, 0, sizeof(buf));
    buf.type =V4L2_BUF_TYPE_VIDEO_CAPTURE;
    buf.memory =V4L2_MEMORY_MMAP;

    if(ioctl (fd, VIDIOC_DQBUF, &buf) < 0){
        perror("ioctl VIDIOC_DQBUF error!  ");
        return -1;
    }

    *frame_buf = buffers[buf.index].start;
    *len = buffers[buf.index].length;
    iIndex = buf.index;

    return 0;
}

int videodevice::unget_frame()
{
    //帧缓存回队列

    if(iIndex != -1)
    {
        struct v4l2_buffer buf;
        memset(&buf, 0, sizeof(buf));
        buf.type =V4L2_BUF_TYPE_VIDEO_CAPTURE;
        buf.memory =V4L2_MEMORY_MMAP;

        buf.index = iIndex;
        if(ioctl (fd, VIDIOC_QBUF, &buf) < 0){
            perror("ioctl VIDIOC_QBUF error!  ");
            return -1;
        }
        return 0;
    }
    return -1;
}











