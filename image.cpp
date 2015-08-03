#include <image.h>

Image::Image(){
	data=NULL;
}

Image::Image(int w,int h,int c){
	data=new unsigned char[w*h*c];
}

Image::~Image() {
	delete [] data;
}

bool Image::readRaw(char* filename){
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

signed char Image::getPixel(int w,int h,int c){
	return data[(h*width+w)*channels+c];
}

int Image::getWidth(){
	return width;
}

int Image::getHeight(){
	return height;
}

int Image::getChannels(){
	return channels;
}

unsigned char* Image::getData(){
	return data;
}

string Image::getColorspace(){
	return colorspace;
}

void Image::setData(unsigned char* d){
	data=d;
}

void Image::setWidth(int w){
	width=w;
}

void Image::setHeight(int h){
	height=h;
}

void Image::setChannels(int c){
	channels=c;
}

void Image::setColorSpace(string color){
	colorspace=color;
}

void Image::setImageInfo(int w,int h,int c){
	width=w;
	height=h;
	channels=c;
}

void Image::setImageInfo(int w,int h,int c,string color){
	width=w;
	height=h;
	channels=c;
	colorspace=color;
}

double PSNR(unsigned char* img1,unsigned char* img2,int w,int h,int c){
	double psnr=0;
	for(int i=0;i<h;i++){
		for(int j=0;j<w;j++){
			for(int k=0;k<c;k++){
				psnr+= 255/(img1[(i*w+j)*c+k]-img2[(i*w+j)*c+k]);
			}
		}
	}
}