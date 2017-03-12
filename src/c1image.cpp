

#include <c1image.h>


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

C1Image::~C1Image()
{

}

void C1Image::loadFromData(int w, int h,const unsigned char *data)
{
    if(!d)
        return;

    d->width = w;
    d->height= h;
    d->data  = (unsigned char *)data;
}

//C1Image& C1Image::loadFromData(const char * data)


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














