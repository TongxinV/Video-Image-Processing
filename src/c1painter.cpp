#include <c1painter.h>


C1Painter::C1Painter()
    : Width(0), Height(0), x0(0), y0(0),
      pStar(NULL), pData(NULL)
{

}


C1Painter::~C1Painter(){

}

void C1Painter::initPainter(unsigned int * displaySpace, unsigned int w, unsigned int h)
{
    pStar = displaySpace;
    Width = w;
    Height= h;
}

void C1Painter::setPixmap()
{
    unsigned int *p = pStar;

    unsigned int x, y;

    for (y=y0; y<Height; y++)
    {
        for (x=x0; x<Width; x++)
        {
            *(p + y * Width + x) = 0xffffffff;
        }
    }
}
