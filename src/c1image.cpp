

#include <c1image.h>
#include <codec/e1bitmap.h>


#include <stdlib.h>

class ImageData
{
public:
    ImageData();
    ~ImageData();

    unsigned int width;
    unsigned int height;
    unsigned int depth;
    unsigned int offset;

    unsigned char *data;


};

ImageData::ImageData()
    : width(0),height(0),depth(0),offset(0),data(NULL)
{

}

ImageData::~ImageData()
{

}


C1Image::C1Image()
    : d(new ImageData)
{

}

C1Image::C1Image(unsigned int w, unsigned int h, unsigned char *data)
    : d(new ImageData)
{
    d->width = w;
    d->height= h;
    d->data  = (unsigned char *)data;
}


C1Image::~C1Image()
{
    //freeData();
}


void C1Image::freeData()
{
    if(!d->data)
        free(d->data);
}


void C1Image::loadFromData(unsigned int w, unsigned int h, const unsigned char *data)
{
    d->width = w;
    d->height= h;
    d->data  = (unsigned char *)data;
}


void C1Image::loadFromData(const char *path)
{
    /* 只考虑[打开的是BMP图片]该情况 */
    /* 外部申请内存，然后把内存地址给img */
    //C1Image *bmpImg;

    BmpHandler bmpCodec;

    if(!bmpCodec.Read24BitBmpFile(path)){
        printf("Read24BitBmpFile failed.\n");
        return ;
    }

    d->width = bmpCodec.d->width;
    d->height= bmpCodec.d->height;
    d->data  = bmpCodec.d->data;
}





unsigned int C1Image::width() const
{
    return d ? d->width:0;
}

unsigned int C1Image::height() const
{
    return d ? d->height:0;
}

unsigned char * C1Image::data() const
{
    return d ? d->data:0;
}














