#ifndef LINUXFBSCREEN_H
#define LINUXFBSCREEN_H

class LinuxFbScreenPrivate;

void func(void);

class LinuxFbScreen
{
public:
    LinuxFbScreen();
    virtual ~LinuxFbScreen();

    virtual bool initDevice();
    virtual void shutdownDevice();

private:
    unsigned char *fb_ptr;
    LinuxFbScreenPrivate *d_ptr;

};


#endif
