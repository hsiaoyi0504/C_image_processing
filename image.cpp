#include "image.hpp"

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
				for(int k=0;k<channels;k++){
					data[(i*width+j)*channels+k]=fgetc(readPtr);
				}
			}
		}
		fclose(readPtr);
		colorspace="RGB";
		return true;
	}
	else{
		return false;
	}
}

unsigned char Image::getPixel(int w,int h,int c){
	return data[(h*width+w)*channels+c];
}

unsigned char Image::getR(int w,int h){
	if(colorspace=="RGB")
		return data[(h*width+w)*channels+0];
	else
		printf("Error: the colorspace is not RGB\n");
	return 0;
}

unsigned char Image::getG(int w,int h){
	if(colorspace=="RGB")
		return data[(h*width+w)*channels+1];
	else
		printf("Error: the colorspace is not RGB\n");
	return 0;	
}

unsigned char Image::getB(int w,int h){
	if(colorspace=="RGB")
		return data[(h*width+w)*channels+2];
	else
		printf("Error: the colorspace is not RGB\n");
	return 0;
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

double MSE(const unsigned char* img1,const unsigned char* img2,int w,int h,int c){
	double mse=0;
	for(int i=0;i<h;i++){
		for(int j=0;j<w;j++){
			for(int k=0;k<c;k++){
				mse+= pow(img1[(i*w+j)*c+k]-img2[(i*w+j)*c+k],2);
			}
		}
	}
	mse/=w*h*c;
	return mse;
}

double MSE(Image img1,Image img2){
	int w=img1.getWidth();
	int h=img1.getHeight();
	int c=img1.getChannels();
	return MSE(img1.getData(),img2.getData(),w,h,c);
}

double PSNR(const unsigned char* img1,const unsigned char* img2,int w,int h,int c){
	double mse=MSE(img1,img2,w,h,c);
	return 10*log10(255*255/mse);
}

double PSNR(Image img1,Image img2){
	//check two images are of same format
	double mse=MSE(img1,img2);
	return 10*log10(255*255/mse);
}