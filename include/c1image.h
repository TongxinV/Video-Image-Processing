#ifndef C1IMAGE_H
#define C1IMAGE_H


#include <stdio.h>
#include <stdlib.h>

//class ImageData;      //本来想使用前置声明，但有继承情况时不行，详情网上查找
//class ImageFile;      //打开文件和关闭文件的处理

class ImageData
{
public:
    ImageData();
    ~ImageData();

    //unsigned short fileType;
    typedef enum tagfileType
    {
        IMG_TYPE_BMP,
        IMG_TYPE_JPEG,
        IMG_TYPE_PNG,
        IMG_TYPE_UNKN
    }fileType_e;

    fileType_e fileType;

    unsigned int width;
    unsigned int height;
    unsigned int depth;
    unsigned int channels;
    //unsigned int offset;

    unsigned char *data;
};


class C1Image
{
protected:
    ImageData *d;
    //ImageFile *f;

public:

    C1Image();
    C1Image(unsigned int w, unsigned int h, unsigned char *data);
    virtual ~C1Image();


    //void readImageFile(const char *path);
    void loadFromData(unsigned int w, unsigned int h, const unsigned char *data);
    bool loadFromData(const char *path);

    void freeData();   //d->data将来指向某一块内存，所以需要free，经验不足暂时只能考虑到这种处理方法

    unsigned int width() const;
    unsigned int height() const;
    unsigned char *data() const;
};


#endif
