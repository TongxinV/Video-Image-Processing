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
    virtual ~LinuxFbScreenPrivate();

    void openTty();
    void closeTty();

    int ttyfd;

};


LinuxFbScreenPrivate::LinuxFbScreenPrivate()
    :ttyfd(-1)
{

}

LinuxFbScreenPrivate::~LinuxFbScreenPrivate()
{
    closeTty();
}

void LinuxFbScreenPrivate::openTty()
{
    const char *const devs[] = {"/dev/fb0", "/dev/fb1", "/dev/fb2", 0};

    for (const char * const *dev = devs; *dev; ++dev) {
        ttyfd = ::open(*dev, O_RDWR);
        if (ttyfd != -1)
            break;
    }

    if (ttyfd == -1)
        return;
}

void LinuxFbScreenPrivate::closeTty()
{
    if (ttyfd == -1)
        return;

    ::close(ttyfd);
    ttyfd = -1;
}


LinuxFbScreen::LinuxFbScreen()
    : d_ptr(new LinuxFbScreenPrivate)
{

}


LinuxFbScreen::~LinuxFbScreen()
{

}

bool LinuxFbScreen::initDevice()
{
    //Step 1 : open fb device
    d_ptr->openTty();

    //Step 2 : get  fb info
    fb_var_screeninfo vinfo;
    fb_fix_screeninfo finfo;

    memset(&vinfo, 0, sizeof(vinfo));
    memset(&finfo, 0, sizeof(finfo));

    if (ioctl(d_ptr->ttyfd, FBIOGET_VSCREENINFO, &vinfo)) {
        perror("QLinuxFbScreen::initDevice");
        return false;
    }

    if (ioctl(d_ptr->ttyfd, FBIOGET_FSCREENINFO, &vinfo)) {
        perror("QLinuxFbScreen::initDevice");
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
    this->fb_ptr = (unsigned char *)mmap(NULL, len, PROT_READ | PROT_WRITE, MAP_SHARED, d_ptr->ttyfd, 0);
    if (NULL == this->fb_ptr){
        perror("mmap");
        return false;
    }
    printf("fb mmap success. pfb = %p.\n", this->fb_ptr);

    return true;

}


