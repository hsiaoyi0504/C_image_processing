#include <stdio.h>
#include <math.h>

class Image
{
	private:
		int width,height,channels;
		unsigned char* data;
	public:
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
}