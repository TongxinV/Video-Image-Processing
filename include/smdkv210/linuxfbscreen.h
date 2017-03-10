#ifndef LINUXFBSCREEN_H
#define LINUXFBSCREEN_H

#include <c1screen.h>

class LinuxFbScreenPrivate;

class LinuxFbScreen : public C1Screen
{
public:
    LinuxFbScreen();
    LinuxFbScreen(LinuxFbScreen&);
    virtual ~LinuxFbScreen();

    virtual bool initDevice();
    virtual void shutdownDevice();

private:
    LinuxFbScreenPrivate *d_ptr;

};


#endif
