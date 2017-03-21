#ifndef C1SCREEN_H
#define C1SCREEN_H

#include <stdio.h>

class C1Screen
{
protected:

    int displayId;

    unsigned int physWidth;
    unsigned int physHeight;

    unsigned int * displaySpace;
public:
    C1Screen(unsigned int w, unsigned int h);
    virtual ~C1Screen();

    virtual bool initDevice() = 0;
    virtual void shutdownDevice() { }

    unsigned int *get_displayspace_point();


};



#endif
