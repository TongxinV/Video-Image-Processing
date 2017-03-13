
#include <codec/e1bitmap.h>



BmpHandler::BmpHandler()
    : C1Image()
{

}

BmpHandler::~BmpHandler()
{

}

bool BmpHandler::Read24BitBmpFile(const char* path)
{

    //unsigned char *pp = (unsigned char *)malloc(1024*600*3*sizeof(char));

    FILE* pfile = NULL;

    pfile = fopen(path,"rb");//打开一个二进制文件，文件必须存在，只允许读

    if(NULL==pfile){
        printf("file %s open fail!\n", path);
        return false;
    }
    //printf("file %s open success..\n", path);

    fclose(pfile);

    //printf("file %s close success..\n", path);

    return true;
}

/*
BmpHandler& BmpHandler::Read24BitBmpFile2Img(const char* path)
{
    FILE* pfile = NULL;

    pfile = fopen(path,"rb");//打开一个二进制文件，文件必须存在，只允许读

    if(NULL==pfile){
        printf("file %s open fail!\n", path);
        return NULL;
    }
    printf("file %s open success..\n", path);

    fclose(pfile);

    printf("file %s close success..\n", path);


    return NULL;
}
*/














