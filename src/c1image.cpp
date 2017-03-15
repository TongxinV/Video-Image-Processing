

#include <c1image.h>
#include <codec/e1bitmap.h>


#include <stdlib.h>


ImageData::ImageData()
    : width(0),height(0),depth(24),channels(3), /*offset(0)*/data(NULL)
{

}

ImageData::~ImageData()
{

}


C1Image::C1Image()
    : format(Format_RGB888), fileType(IMG_TYPE_UNKN),
      d(new ImageData)/*, f(new ImageFile)*/
{

}

C1Image::C1Image(unsigned char *data, unsigned int w, unsigned int h, Format Ft)
    : format(Ft), fileType(IMG_TYPE_UNKN),
      d(new ImageData)/*, f(new ImageFile)*/
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
    if(!d->data){
        free(d->data);
        d = NULL;
    }
}


void C1Image::loadFromData(unsigned int w, unsigned int h, const unsigned char *data)
{
    d->width = w;
    d->height= h;
    d->data  = (unsigned char *)data;
}

/* readFile_mallocData */
bool C1Image::loadFromData(const char *path)
{
    /* 只考虑[打开的是BMP图片]该情况 */

    FILE *infile = fopen(path, "rb");
    if (!infile){
        fprintf(stderr, "file %s open fail!\n", path);
        return false;
    }
    fprintf(stdout, "file %s open success..\n", path);

    fclose(infile);

    BmpHandler bmpCodec;

    if(!bmpCodec.read24BitBmpFile2Img(path)){
        printf("Read24BitBmpFile2Img failed.\n");
        return false;
    }

    d->width = bmpCodec.d->width;
    d->height= bmpCodec.d->height;
    d->data  = bmpCodec.d->data;

    return true;
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














