#include <c1painter.h>


C1Painter::C1Painter()
    : Width(0), Height(0),
      pStar(NULL), data(NULL), color(0xffffffff)
{

}


C1Painter::~C1Painter(){

}

void C1Painter::_initPainter(unsigned int * displaySpace, unsigned int w, unsigned int h)
{
    pStar = displaySpace;
    Width = w;
    Height= h;
}

void C1Painter::_setPixmap(unsigned int x, unsigned int y,const C1Image &img)
{
    unsigned int *p = pStar;

    const unsigned char * Byte = img.data();
    unsigned int imageWidth    =img.width();
    unsigned int imageHeight  =img.height();

    unsigned int i,j;
    unsigned int cnt;

    for (i = y; (i<imageHeight+y)&&(i<Height); i++)
    {
        for (j = x; (j<imageWidth+x)&&(j<Width); j++)
        {
            cnt = imageWidth*i+j;
            cnt*=3;
            *(p + i * Width + j) = ((Byte[cnt+0] << 16) | (Byte[cnt+1] << 8) | (Byte[cnt+2] << 0));//byte[0-2]:R G B
        }
    }

}

void C1Painter::Draw_Test()
{
    unsigned int *p = pStar;

    unsigned int x, y;

    for (y=0; y<Height; y++)
    {
        for (x=0; x<Width; x++)
        {
            *(p + y * Width + x) = color;
        }
    }
}
