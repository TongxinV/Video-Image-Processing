#include <c1painter.h>


C1Painter::C1Painter()
    : Width(0), Height(0),pStar(NULL)
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


void C1Painter::_setPixmap(unsigned int x, unsigned int y, const C1Image *img)
{
    if(!img){
        printf("Images isn't exit!.\n");
        return ;
    }

    unsigned int *p = pStar + y * Width + x;        //画笔位置

    const unsigned char * Byte =img->data ();
    unsigned int imageWidth    =img->width();
    unsigned int imageHeight   =img->height();

    unsigned int i,j;
    unsigned int cnt;

    for (i = 0; (i<imageHeight)&&(i<Height-y); ++i)
    {
        for (j = 0; (j<imageWidth)&&(j<Width-x); ++j)
        {
            cnt = imageWidth*i+j;
            cnt*=3;
            *(p + i * Width + j) = ((Byte[cnt+0] << 16) | (Byte[cnt+1] << 8) | (Byte[cnt+2] << 0));//byte[0-2]:R G B
        }
    }

}

void C1Painter::_draw_img_bgr(unsigned int iw, unsigned int ih, unsigned char *data)
{
    unsigned int *p = pStar;

    const unsigned char * Byte =data;

    printf("========= draw start ==========.\n");
    printf("const unsigned char * Byte = %p.\n", Byte);
    printf("unsigned int iw = %d.\n", iw);
    printf("unsigned int ih = %d.\n", ih);

    unsigned int i,j;
    unsigned int cnt;

    for (i=0; i<ih; i++)
    {
        for (j=0; j<iw; j++)
        {
            cnt = iw*3*i+3*j;
            *(p + i * Width + j) = ((Byte[cnt+2] << 16) | (Byte[cnt+1] << 8) | (Byte[cnt+0] << 0));//byte[0-2]:R G B
        }
    }

    printf("========= draw end  ==========.\n");
}


void C1Painter::_draw_img_gray(unsigned int iw, unsigned int ih, unsigned char *data)
{
    unsigned int *p = pStar;

    const unsigned char * Byte =data;

    printf("========= draw start ==========.\n");
    printf("const unsigned char * Byte = %p.\n", Byte);
    printf("unsigned int iw = %d.\n", iw);
    printf("unsigned int ih = %d.\n", ih);

    unsigned int i,j;
    unsigned int cnt;

    for (i=0; i<ih; i++)
    {
        for (j=0; j<iw; j++)
        {
            cnt = iw*i+j;
            *(p + i * Width + j) = ((Byte[cnt] << 16) | (Byte[cnt] << 8) | (Byte[cnt] << 0));//Gray: R = G = B
        }
    }

    printf("========= draw end  ==========.\n");
}

