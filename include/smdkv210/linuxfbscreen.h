#ifndef LINUXFBSCREEN_H
#define LINUXFBSCREEN_H

#include <c1screen.h>

class LinuxFbScreenPrivate;


/* 我的想法：把需要交互的数据做成父类 私有封装成一个类 */
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
