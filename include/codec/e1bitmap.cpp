
#include <codec/e1bitmap.h>



BmpHandler::BmpHandler()
    : C1Image()
{

}

BmpHandler::~BmpHandler()
{

}

bool BmpHandler::read24BitBmpFile2Img(const char* path)
{
    FILE* infile = NULL;

    /* Step 1 ...open bmp file*///打开一个二进制文件，文件必须存在，只允许读
    infile = fopen(path,"rb");

    if(NULL==infile){
        fprintf(stderr, "file %s open fail!\n", path);
        return false;
    }
    fprintf(stdout, "file %s open success..\n", path);

    /* Step 2.1 ...read fileHeader */
    fread(&fileType, sizeof(unsigned short),1, infile);
    if (fileType != 0x4D42){
        printf("It's not bmp file! \n");
    }

    fread(&fileHeader, sizeof(BMP_FILEHDR), 1, infile);
    printf("======================================\n");
    showBmpHead(&fileHeader);

    /* Step 2.2 ...read infoHeader */
    fread(&infoHeader, sizeof(BMP_INFOHDR), 1, infile);
    printf("======================================\n");
    showBmpInfoHead(&infoHeader);


    fseek(infile,fileHeader.bfOffBits,SEEK_SET);

#if 1
    unsigned int w;
    unsigned int h;
    unsigned int c;

    if (infoHeader.biBitCount == 24)
    {
        printf("该位图为24位真彩色\n\n");

        d->width    = w = infoHeader.biWidth;
        d->height   = h = infoHeader.biHeight;
        d->channels = c = infoHeader.biBitCount/8;
        d->data = (unsigned char*)malloc(sizeof(unsigned char)*w*h*c);

        /*没有以下处理，直接读出来的图片是颠倒的*/
        fseek(infile,fileHeader.bfOffBits,SEEK_SET);


        for(unsigned int i=0;i<h;i++)
        {
            if(fread(d->data+(h-1-i)*w*3,sizeof(char),w*3,infile)!=w*3){
                fclose(infile);
                free(d->data);
                return false;
            }
            fseek(infile,(3*w+3)/4*4-3*w,SEEK_CUR);   //不知其作用为何。去掉也能正确执行
        }
    }

#endif

    fclose(infile);

    return true;
}

void BmpHandler::decodeBmpFile()
{

}

/*
void BmpHandler::releaseBmpFile()
{

}
*/

void BmpHandler::showBmpHead(BMP_FILEHDR *pBmpHead)
{
    printf("位图文件头:\n");
    printf("文件类型:%u\n",fileType);
    printf("文件大小:%d\n",pBmpHead->bfSize);
    printf("保留字:%d\n",pBmpHead->bfReserved1);
    printf("保留字:%d\n",pBmpHead->bfReserved2);
    printf("实际位图数据的偏移字节数: %d\n",pBmpHead->bfOffBits);
}


void BmpHandler::showBmpInfoHead(BMP_INFOHDR* pBmpInfoHead)
{
    printf("位图信息头:\n");
    printf("结构体的长度:%d\n",pBmpInfoHead->biSize);
    printf("位图宽:%d\n",pBmpInfoHead->biWidth);
    printf("位图高:%d\n",pBmpInfoHead->biHeight);
    printf("biPlanes平面数:%d\n",pBmpInfoHead->biPlanes);
    printf("biBitCount采用颜色位数:%d\n",pBmpInfoHead->biBitCount);
    printf("压缩方式:%d\n",pBmpInfoHead->biCompression);
    printf("biSizeImage实际位图数据占用的字节数:%d\n",pBmpInfoHead->biSizeImage);
    printf("X方向分辨率:%d\n",pBmpInfoHead->biXPelsPerMeter);
    printf("Y方向分辨率:%d\n",pBmpInfoHead->biYPelsPerMeter);
    printf("使用的颜色数:%d\n",pBmpInfoHead->biClrUsed);
    printf("重要颜色数:%d\n",pBmpInfoHead->biClrImportant);
}










