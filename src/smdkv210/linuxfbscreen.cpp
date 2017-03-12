#include <smdkv210/linuxfbscreen.h>

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/fb.h>
#include <sys/ioctl.h>
#include <string.h>
#include <sys/mman.h>

class LinuxFbScreenPrivate
{
public:
    LinuxFbScreenPrivate();
    /*
     * LinuxFbScreen 有拷贝构造函数 所以LinuxFbScreenPrivate可以没有
     * 把私有变量封装成一个类的指针的好处 而且简化了LinuxFbScreen拷贝构造函数的处理
     */
    virtual ~LinuxFbScreenPrivate();

    void openTty();
    void closeTty();

    int ttyfd;

};


LinuxFbScreenPrivate::LinuxFbScreenPrivate():ttyfd(-1)
{

}

LinuxFbScreenPrivate::~LinuxFbScreenPrivate()
{
    closeTty();
}

void LinuxFbScreenPrivate::openTty()
{
    printf("1.\n");
    printf("1.\n");
    const char *const devs[] = {"/dev/fb0", "/dev/fb1", "/dev/fb2", 0};

    for (const char * const *dev = devs; *dev; ++dev) {
        ttyfd = ::open(*dev, O_RDWR);
        printf("%s.\n", *dev);
        if (ttyfd != -1)
            break;
    }

    if (ttyfd == -1)
        printf("2.\n");
        return;
}

void LinuxFbScreenPrivate::closeTty()
{
    if (ttyfd == -1)
        return;

    ::close(ttyfd);
    ttyfd = -1;
}


LinuxFbScreen::LinuxFbScreen(unsigned int w, unsigned int h)
    : C1Screen(w, h), painter(new C1Painter), d_ptr(new LinuxFbScreenPrivate)
{

}
LinuxFbScreen::LinuxFbScreen(const LinuxFbScreen &)
    : C1Screen(0, 0), painter(new C1Painter), d_ptr(new LinuxFbScreenPrivate)
{

}

LinuxFbScreen::~LinuxFbScreen()
{

}

bool LinuxFbScreen::initDevice()
{
    //Step 1 : open fb device
    d_ptr->openTty();

    //Step 2 : get fb info
    fb_var_screeninfo vinfo;
    fb_fix_screeninfo finfo;

    memset(&vinfo, 0, sizeof(vinfo));
    memset(&finfo, 0, sizeof(finfo));

    if (ioctl(d_ptr->ttyfd, FBIOGET_VSCREENINFO, &vinfo)) {
        perror("LinuxFbScreen::initDevice");
        return false;
    }

    if (ioctl(d_ptr->ttyfd, FBIOGET_FSCREENINFO, &finfo)) {
        perror("LinuxFbScreen::initDevice");
        return false;
    }
#if 1
    printf("smem_start = 0x%lx, smem_len = %u.\n", finfo.smem_start, finfo.smem_len);

    printf("xres = %u, yres = %u.\n", vinfo.xres, vinfo.yres);
    printf("xres_virtual = %u, yres_virtual = %u.\n", vinfo.xres_virtual, vinfo.yres_virtual);
    printf("bpp = %u.\n", vinfo.bits_per_pixel);
#endif

    // Step 3 : mmap
    unsigned long len = vinfo.xres_virtual * vinfo.yres_virtual * vinfo.bits_per_pixel / 8;
    displaySpace = (unsigned int *)mmap(NULL, len, PROT_READ | PROT_WRITE, MAP_SHARED, d_ptr->ttyfd, 0);
    if (NULL == displaySpace){
        perror("mmap");
        return false;
    }
    printf("fb mmap success. pfb = %p.\n", displaySpace);


    // init painter
    painter->_initPainter(displaySpace, physWidth, physHeight);


    return true;

}

void LinuxFbScreen::shutdownDevice()
{
    d_ptr->closeTty();
}

void LinuxFbScreen::setPixmap(int x, int y, C1Image &i)
{

    painter->_setPixmap(x, y, i);
}
