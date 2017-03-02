#include <c1screen.h>


#ifndef NULL
#define NULL 0
#endif


C1Screen::C1Screen(int w, int h)
    : displayId(0), physWidth(w), physHeight(h),
      displaySpace(NULL)
{

}

C1Screen::~C1Screen()
{

}


