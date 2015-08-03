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
		Image(){
			data=NULL;
		}
		Image(int w,int h,int c){
			data=new unsigned char[w*h*c];
		}
		~Image() {
			delete [] data;
		}
		bool readRaw(char* filename){
			FILE * readPtr=fopen(filename,"rb");
			if(readPtr!=NULL){
				for(int i=0;i<height;i++){
					for(int j=0;j<width;j++){
						for(int k=0:k<channels;k++){
							data[(i*width+j)*channels+k]=fgetc(readPtr);
						}
					}
				}
				fclose(readPtr);
				colorspace="YUV";
				return true;
			}
			else{
				return false;
			}
		}
		unsigned char getPixel(int w,int h,int c){
			return data[(h*width+w)*channels+c];
		}
		int getWidth(){
			return width;
		}
		int getHeight(){
			return height;
		}
		int getChannels(){
			return channels;
		}
		unsigned char* getData(){
			return data;
		}
		string getColorspace(){
			return colorspace;
		}
		void setData(unsigned char* d){
			data=d;
		}
		void setWidth(int w){
			width=w;
		}
		void setHeight(int h){
			height=h;
		}
		void setChannels(int c){
			channels=c;
		}
		void setColorSpace(string color){
			colorspace=color;
		}
		void setImageInfo(int w,int h,int c){
			width=w;
			height=h;
			channels=c;
		}
		void setImageInfo(int w,int h,int c,string color){
			width=w;
			height=h;
			channels=c;
			colorspace=color;
		}
};