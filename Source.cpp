#include<iostream>
#include<stdio.h>
#include<math.h>
using namespace std;

int main()
{
	const int Width=512;
	const int Height=512;
	unsigned char *P=new unsigned char [Width*Height*3];
	
	FILE *ReadPtr=fopen ("lena.raw","rb"); 
	FILE *WritePtrR=fopen("lena_R.raw","wb");   
	FILE *WritePtrG=fopen("lena_G.raw","wb");
	FILE *WritePtrB=fopen("lena_B.raw","wb");
	FILE *WritePtrY=fopen("lena_Y.raw","wb");
	FILE *WritePtrU=fopen("lena_U.raw","wb");
	FILE *WritePtrV=fopen("lena_V.raw","wb");
	FILE *WritePtrAC1=fopen("lena_AC1.raw","wb");
	FILE *WritePtrAC2=fopen("lena_AC2.raw","wb");

	for(int i=0; i<Height; i++)
	{
     for(int j=0; j<Width; j++)
	 {
		 P[(i*Width+j)*3]=fgetc(ReadPtr);
		 P[(i*Width+j)*3+1]=fgetc(ReadPtr);
		 P[(i*Width+j)*3+2]=fgetc(ReadPtr);
	 }			
	}
	
	double PSNR1=0;
	double PSNR2=0;
	double *B=new double[Width*Height*3];


	for(int i=0; i<Height; i++)
	{
     for(int j=0; j<Width; j++)
	 {
		 fputc(P[(i*Width+j)*3],WritePtrR);
		 fputc(P[(i*Width+j)*3+1],WritePtrG);
		 fputc(P[(i*Width+j)*3+2],WritePtrB);
		 fputc(P[(i*Width+j)*3]*0.299+P[(i*Width+j)*3+1]*0.587+P[(i*Width+j)*3+2]*0.114,WritePtrY);
		 fputc(((P[(i*Width+j)*3]*-0.14713+P[(i*Width+j)*3+1]*-0.28886+P[(i*Width+j)*3+2]*0.436)+111.17745)*(255/(111.18+111.17745)),WritePtrU);
		 fputc(((P[(i*Width+j)*3]*0.615+P[(i*Width+j)*3+1]*-0.51499+P[(i*Width+j)*3+2]*-0.100011)+156.825)*(255/(156.825+156.825)),WritePtrV);
		 fputc(P[(i*Width+j)*3]*0.299+P[(i*Width+j)*3+1]*0.587+P[(i*Width+j)*3+2]*0.114+(P[(i*Width+j)*3]*0.615+P[(i*Width+j)*3+1]*-0.51499+P[(i*Width+j)*3+2]*-0.100011)*1.13983,WritePtrAC1);
		 fputc(P[(i*Width+j)*3]*0.299+P[(i*Width+j)*3+1]*0.587+P[(i*Width+j)*3+2]*0.114+(P[(i*Width+j)*3]*-0.14713+P[(i*Width+j)*3+1]*-0.28886+P[(i*Width+j)*3+2]*0.436)*-0.39465+(P[(i*Width+j)*3]*0.615+P[(i*Width+j)*3+1]*-0.51499+P[(i*Width+j)*3+2]*-0.100011)*-0.58060,WritePtrAC1);
		 fputc(P[(i*Width+j)*3]*0.299+P[(i*Width+j)*3+1]*0.587+P[(i*Width+j)*3+2]*0.114+(P[(i*Width+j)*3]*-0.14713+P[(i*Width+j)*3+1]*-0.28886+P[(i*Width+j)*3+2]*0.436)*2.03211,WritePtrAC1);
		 
		 PSNR1+=pow(P[(i*Width+j)*3]-(P[(i*Width+j)*3]*0.299+P[(i*Width+j)*3+1]*0.587+P[(i*Width+j)*3+2]*0.114+(P[(i*Width+j)*3]*0.651+P[(i*Width+j)*3+1]*-0.51499+P[(i*Width+j)*3+2]*-0.100011)*1.13983),2)+pow(P[(i*Width+j)*3+1]-(P[(i*Width+j)*3]*0.299+P[(i*Width+j)*3+1]*0.587+P[(i*Width+j)*3+2]*0.114+(P[(i*Width+j)*3]*-0.14713+P[(i*Width+j)*3+1]*-0.28886+P[(i*Width+j)*3+2]*0.436)*-0.39465+(P[(i*Width+j)*3]*0.651+P[(i*Width+j)*3+1]*-0.51499+P[(i*Width+j)*3+2]*-0.100011)*-0.58060),2)+pow(P[(i*Width+j)*3+2]-(P[(i*Width+j)*3]*0.299+P[(i*Width+j)*3+1]*0.587+P[(i*Width+j)*3+2]*0.114+(P[(i*Width+j)*3]*-0.14713+P[(i*Width+j)*3+1]*-0.28886+P[(i*Width+j)*3+2]*0.436)*2.03211),2);
		 PSNR1/=Width*Height*3;

		 B[(i*Width+j)*3]=P[(i*Width+j)*3]*0.299+P[(i*Width+j)*3+1]*0.587+P[(i*Width+j)*3+2]*0.114+(P[(i*Width+j)*3]*0.615+P[(i*Width+j)*3+1]*-0.51499+P[(i*Width+j)*3+2]*-0.100011)*1.13983;
		 B[(i*Width+j)*3+1]=P[(i*Width+j)*3]*0.299+P[(i*Width+j)*3+1]*0.587+P[(i*Width+j)*3+2]*0.114+(P[(i*Width+j)*3]*-0.14713+P[(i*Width+j)*3+1]*-0.28886+P[(i*Width+j)*3+2]*0.436)*-0.39465+(P[(i*Width+j)*3]*0.615+P[(i*Width+j)*3+1]*-0.51499+P[(i*Width+j)*3+2]*-0.100011)*-0.58060;
		 B[(i*Width+j)*3+2]=P[(i*Width+j)*3]*0.299+P[(i*Width+j)*3+1]*0.587+P[(i*Width+j)*3+2]*0.114+(P[(i*Width+j)*3]*-0.14713+P[(i*Width+j)*3+1]*-0.28886+P[(i*Width+j)*3+2]*0.436)*2.03211;

		 fputc(B[(i*Width+j)*3],WritePtrAC2);
		 fputc(B[(i*Width+j)*3+1],WritePtrAC2);
		 fputc(B[(i*Width+j)*3+2],WritePtrAC2);

		 PSNR2+=pow(B[(i*Width+j)*3]-P[(i*Width+j)*3],2)+pow(B[(i*Width+j)*3+1]-P[(i*Width+j)*3+1],2)+pow(B[(i*Width+j)*3+2]-P[(i*Width+j)*3+2],2);
	     PSNR2/=Width*Height*3;

	 }	
	}
		
	PSNR1=10*log10(255*255/PSNR1);
	PSNR2=10*log10(255*255/PSNR2);
	cout<<"PSNR1="<<PSNR1<<"dB"<<endl<<"PSNR2="<<PSNR2<<"dB";

	fclose(ReadPtr);
	fclose(WritePtrR);
	fclose(WritePtrG);
	fclose(WritePtrB);
	fclose(WritePtrY);
	fclose(WritePtrU);
	fclose(WritePtrV);
	fclose(WritePtrAC1);
	fclose(WritePtrAC2);
	delete []P;
	return 0;
}