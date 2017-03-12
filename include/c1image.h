#ifndef C1IMAGE_H
#define C1IMAGE_H


#include <stdio.h>
//#include <c1painter.h>              //应该是图片利用painter来显示
                                    //所以Image类应嵌套一个painter
                                    //嵌套的方式有组合和继承

class ImageData;

class C1Image
{
private:
    ImageData *d;

public:

    C1Image();
    virtual ~C1Image();


    void loadFromData(int w, int h, const unsigned char *data);
   //C1Image& loadFromData(const char *data);   //把数据提取成C1Image类型的对象

    //ImageData& formImage(C1Image& i);       //提供访问私有数据接口

    unsigned int width() const;
    unsigned int height() const;
    unsigned char *data() const;
};


#endif
