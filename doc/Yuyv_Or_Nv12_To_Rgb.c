
//NV12(yuv420)转RGB
int nv12torgb(unsigned char *rgb, unsigned int width,unsigned int height)
{

     unsigned char *yuv= (unsigned char *)(cap_buffers[v4l2_buf.index].start);

     unsigned int pixel24;
     unsigned char *pixel = (unsigned char *)&pixel24;
     unsigned int i=0,j=0;
     int numOfPixel = width * height;
     int positionOfV = numOfPixel;
     for(i=0; i<height; i++){
         int startY = i*width;
         int step = i/2*width;
         int startV = positionOfV + step;
         for(j = 0; j < width; j++){
             int Y = startY + j;
             int V = startV + j/2;
             int U = V + 1;
             int index = Y*3;
             pixel24 = yuvtorgb(yuv[Y], yuv[U], yuv[V]);
             rgb[index+0] = pixel[0];
             rgb[index+1] = pixel[1];
             rgb[index+2] = pixel[2];
         }
     }

    return 0;
}

int yuvtorgb(int Y, int U, int V)
{
    unsigned int pixel24 = 0;
    unsigned char *pixel = (unsigned char *)&pixel24;
    int r, g, b;

    r = (int)((Y&0xff) + 1.4075 * ((V&0xff)-128));
    g = (int)((Y&0xff) - 0.3455 * ((U&0xff)-128) - 0.7169*((V&0xff)-128));
    b = (int)((Y&0xff) + 1.779 * ((U&0xff)-128));
    r =(r<0? 0: r>255? 255 : r);
    g =(g<0? 0: g>255? 255 : g);
    b =(b<0? 0: b>255? 255 : b);

    pixel[0] = r;
    pixel[1] = g;
    pixel[2] = b;

    return pixel24;
}

//YUYV(yuv422)转RGB
void video_yuyv_to_rgb24(const void *yuyv,void *rgb,unsigned int width,unsigned int height)
{  
    int yuvdata[4];  
	unsigned char *yuv_buf;
    unsigned int i, j;  
	
	#define Y0  0  
	#define U   1  
	#define Y1  2  
	#define V   3  

	yuv_buf = (unsigned char *)yuyv;
	if(rgb != NULL)
	{
		for(i = 0; i < height * 2; i++){  
			for(j = 0; j < width; j+= 4){  
				/* get Y0 U Y1 V */  
				yuvdata[Y0] = *(yuv_buf + i * width + j + 0);  
				yuvdata[U]  = *(yuv_buf + i * width + j + 1);  
				yuvdata[Y1] = *(yuv_buf + i * width + j + 2);  
				yuvdata[V]  = *(yuv_buf + i * width + j + 3);  

				video_yuv_to_rgb_pixel((unsigned char **)(&rgb), yuvdata[Y0], yuvdata[U], yuvdata[V], 0);
				video_yuv_to_rgb_pixel((unsigned char **)(&rgb), yuvdata[Y1], yuvdata[U], yuvdata[V], 0);
			}
		}
	}

}


void video_yuv_to_rgb_pixel(unsigned char **pixel, int y, int u, int v)
{
	int rgbdata[3];
	
	#define R   0
	#define G   1
	#define B   2
	
	/*
	* YUV与RGB相互转换的公式如下（RGB取值范围均为0-255）
	* Y = 0.299R + 0.587G + 0.114B
	* U = -0.147R - 0.289G + 0.436B
	* V = 0.615R - 0.515G - 0.100B
	* R = Y + 1.14V
	* G = Y - 0.39U - 0.58V
	* B = Y + 2.03U
	*/
	
	rgbdata[R] = y + (v - 128) + (((v - 128) * 104 ) >> 8);  
	rgbdata[G] = y - (((u - 128) * 89) >> 8) - (((v - 128) * 183) >> 8);  
	rgbdata[B] = y + (u - 128) + (((u - 128) * 199) >> 8);  
	
	if (rgbdata[R] > 255)  rgbdata[R] = 255;        
	if (rgbdata[R] < 0) rgbdata[R] = 0;            
	if (rgbdata[G] > 255)  rgbdata[G] = 255;        
	if (rgbdata[G] < 0) rgbdata[G] = 0;            
	if (rgbdata[B] > 255)  rgbdata[B] = 255;        
	if (rgbdata[B] < 0) rgbdata[B] = 0;
	

	(*pixel)[0] = rgbdata[R];  
	(*pixel)[1] = rgbdata[G];  
	(*pixel)[2] = rgbdata[B];
	
	(*pixel) +=3;
}

