#ifndef C1PAINTER_H
#define C1PAINTER_H

#include <stdio.h>

class C1Painter
{
private:

    unsigned int Width;
    unsigned int Height;             //画板的宽和高

    unsigned int x0;
    unsigned int y0;                 //显示位置
    unsigned int * pStar;      //画板原点 应被赋值 4byte

    unsigned char *pData;            //图片数据         1byte

public:
    C1Painter();
    ~C1Painter();

    void initPainter(unsigned int *const displaySpace, unsigned int w, unsigned int h);
    void setPixmap();      //显示数据
};






#endif
