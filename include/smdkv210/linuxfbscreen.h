#ifndef LINUXFBSCREEN_H
#define LINUXFBSCREEN_H


#include <c1screen.h>
#include <c1painter.h>
#include <c1image.h>



class LinuxFbScreenPrivate;


/* 我的想法：把需要交互的数据做成父类 私有封装成一个类 */
class LinuxFbScreen : public C1Screen
{
public:
    LinuxFbScreen(unsigned int w, unsigned int h);
    LinuxFbScreen(const LinuxFbScreen&);
    virtual ~LinuxFbScreen();

    virtual bool initDevice();
    virtual void shutdownDevice();

    void showImageRGB(unsigned int iw, unsigned int ih, unsigned char *data);   //显示数据
    void showImageGray(unsigned int iw, unsigned int ih, unsigned char *data);  //显示数据
    void setPixmap(unsigned int x, unsigned int y, C1Image *i);         //显示数据

private:

    C1Painter *painter;
    LinuxFbScreenPrivate *d_ptr;

};


#endif
