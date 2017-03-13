#ifndef C1IMAGE_H
#define C1IMAGE_H


#include <stdio.h>


class ImageData;
//class ImageFile;      //打开文件和关闭文件的处理

class C1Image
{
protected:
    ImageData *d;

public:

    C1Image();
    C1Image(unsigned int w, unsigned int h, unsigned char *data);
    virtual ~C1Image();

    void loadFromData(unsigned int w, unsigned int h, const unsigned char *data);
    void loadFromData(const char *path);

    void freeData();   //d->data将来指向某一块内存，所以需要free，经验不足暂时只能考虑到这种处理方法

    unsigned int width() const;
    unsigned int height() const;
    unsigned char *data() const;
};


#endif
