#include <stdio.h>
#include <math.h>
#include <string>
class Image
{
	private:
		int width,height,channels;
		unsigned char* data;
		string colorspace;
	public:
		Image()
		Image(int w,int h,int c)
		~Image()
		bool readRaw(char* filename);
		unsigned char getPixel(int w,int h,int c);
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