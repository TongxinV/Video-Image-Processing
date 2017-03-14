#ifndef E1BITMAP_H
#define E1BITMAP_H

#include <c1image.h>

typedef signed char int8;               /* 8 bit signed */
typedef unsigned char uint8;            /* 8 bit unsigned */
typedef short int16;                    /* 16 bit signed */
typedef unsigned short uint16;          /* 16 bit unsigned */
typedef int int32;                      /* 32 bit signed */
typedef unsigned int uint32;            /* 32 bit unsigned */


typedef struct tagBMP_FILEHDR {         /* BMP file header */
    //char   bfType[2];                   // "BM"(0x4D42)
    int32  bfSize;                      // size of file
    int16  bfReserved1;
    int16  bfReserved2;
    int32  bfOffBits;                   // pointer to the pixmap bits
}BMP_FILEHDR;

typedef struct tagBMP_INFOHDR {         /* BMP information header */
    int32  biSize;                      // size of this struct 指定此结构体的长度，为40
    int32  biWidth;                     // pixmap width 位图宽
    int32  biHeight;                    // pixmap height 位图高
    int16  biPlanes;                    // should be 1 平面数，为1
    int16  biBitCount;                  // number of bits per pixel 采用颜色位数，可以是1，2，4，8，16，24，新的可以是32
    int32  biCompression;               // compression method 压缩方式，可以是0，1，2，其中0表示不压缩
    int32  biSizeImage;                 // size of image 实际位图数据占用的字节数
    int32  biXPelsPerMeter;             // horizontal resolution X方向分辨率
    int32  biYPelsPerMeter;             // vertical resolution Y方向分辨率
    int32  biClrUsed;                   // number of colors used 使用的颜色数，如果为0，则表示默认值(2^颜色位数)
    int32  biClrImportant;              // number of important colors 重要颜色数，如果为0，则表示所有颜色都是重要的
}BMP_INFOHDR;

//调色板Palette，当然，这里是对那些需要调色板的位图文件而言的。24位和32位是不需要调色板的。
//（似乎是调色板结构体个数等于使用的颜色数。）

typedef struct tagRGBQUAD {
    int8   rgbBlue;                     //该颜色的蓝色分量
    int8   rgbGreen;                    //该颜色的绿色分量
    int8   rgbRed;                      //该颜色的红色分量
    int8   rgbReserved;                 //保留值
}RGBQUAD;



class BmpHandler : public C1Image
{
private:
    unsigned short fileType;
    BMP_FILEHDR  fileHeader;
    BMP_INFOHDR  infoHeader;

public:

    BmpHandler();
    virtual ~BmpHandler();
    void showBmpHead(BMP_FILEHDR* pBmpHead);
    void showBmpInfoHead(BMP_INFOHDR* pBmpInfoHead);
    //void showRgbQuan();

    bool read24BitBmpFile2Img(const char* path);
    //bool writeImgData2BmpFile();
    void decodeBmpFile();
};









#endif
