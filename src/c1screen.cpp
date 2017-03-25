#include <c1screen.h>



C1Screen::C1Screen(unsigned int w, unsigned int h)
    : displayId(0), physWidth(w), physHeight(h),
      displaylenth(0), displaySpace(NULL)
{

}

C1Screen::~C1Screen()
{

}


unsigned int *C1Screen::get_displayspace_point()
{
    return displaySpace ? displaySpace:NULL;
}
