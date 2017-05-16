#ifndef C1PAINTER_H
#define C1PAINTER_H

#include <stdio.h>

#include <c1image.h>


class C1Painter
{
private:

    unsigned int Width;
    unsigned int Height;             //画板的宽和高

    //int x0;
    //int y0;                        //显示位置
    unsigned int *pStar;             //画板原点 应被赋值

    //unsigned char *data;             //数据point
    //unsigned int  color;             //背景色

public:
    C1Painter();
    virtual ~C1Painter();

    void _initPainter(unsigned int *const displaySpace, unsigned int w, unsigned int h);
    void _setPixmap(unsigned int x, unsigned int y, const C1Image *img);      //在(x,y)显示数据
    void _draw_img_rgb(unsigned int iw, unsigned int ih, unsigned char *data);
    void _draw_img_gray(unsigned int iw, unsigned int ih, unsigned char *data);
};






#endif
