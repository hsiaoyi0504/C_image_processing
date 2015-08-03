#include <stdio.h>
#include <math.h>
#include <string>
using namespace std;
class Image
{
	private:
		int width,height,channels;
		unsigned char* data;
		string colorspace;
	public:
		Image();
		Image(int w,int h,int c);
		~Image();
		bool readRaw(char* filename);
		//getter and setter
		unsigned char getPixel(int w,int h,int c);
		unsigned char getR(int w,int h);
		unsigned char getG(int w,int h);
		unsigned char getB(int w,int h);
		int getWidth();
		int getHeight();
		int getChannels();
		unsigned char* getData();
		string getColorspace();
		void setData(unsigned char* d);
		void setWidth(int w);
		void setHeight(int h);
		void setChannels(int c);
		void setColorSpace(string color);
		void setImageInfo(int w,int h,int c);
		void setImageInfo(int w,int h,int c,string color);
};

double MSE(Image img1,Image img2);
double MSE(const unsigned char* img1,const unsigned char* img2,int w,int h,int c);
double PSNR(Image img1,Image img2);
double PSNR(const unsigned char* img1,const unsigned char* img2,int w,int h,int c);
