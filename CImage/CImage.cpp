#include <stdio.h>
#include "CImage.h"

CImage::CImage()
{
	m_pPalette=NULL;
	m_pPixelData=NULL;
	m_pPixelMatrix=NULL;
}
CImage::~CImage()
{
	if(m_pPalette)     delete [] m_pPalette;
	if(m_pPixelData)   delete [] m_pPixelData;
	if(m_pPixelMatrix) delete [] m_pPixelMatrix;
}

bool CImage::Create(int width, int height, int bpp)
{
	m_Bpp=bpp;		//bit per pixel
	m_Width=width;		//寬
	m_Height=height;	//高
	m_MemWidth = m_Width * (m_Bpp >> 3);
	m_MemWidth = (m_MemWidth + 3) >> 2 << 2;
	int PaletteSize = 0;
	switch ( m_Bpp ){
		case 1: PaletteSize = 2;  break;
		case 4:	PaletteSize = 16; break;
		case 8:	PaletteSize = 256;break;
	}

	m_BmpFileHeader.Type=0x4d42;
	m_BmpFileHeader.Size= sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER)
		+ sizeof(RGBQUAD)*PaletteSize + m_MemWidth*m_Height;
	m_BmpFileHeader.Reserved1=0;
	m_BmpFileHeader.Reserved2=0;
	m_BmpFileHeader.OffBits=sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER)
		+ sizeof(RGBQUAD)*PaletteSize;

	m_BmpInfoHeader.Size = sizeof(BITMAPINFOHEADER);  
	m_BmpInfoHeader.Width = m_Width;   
	m_BmpInfoHeader.Height = m_Height; 
	m_BmpInfoHeader.Planes = 1; 
	m_BmpInfoHeader.BitCount = short(m_Bpp);
	m_BmpInfoHeader.Compression = 0L;
	m_BmpInfoHeader.SizeImage = 0;
	m_BmpInfoHeader.XPelsPerMeter = 100;
	m_BmpInfoHeader.YPelsPerMeter = 100;
	m_BmpInfoHeader.ClrUsed = PaletteSize; 
	m_BmpInfoHeader.ClrImportant = PaletteSize; 

	int i,y;
	m_pPalette = new RGBQUAD [PaletteSize];
	if(PaletteSize){
		for(i=0;i<PaletteSize;i++){
			m_pPalette[i].Red  =i;
			m_pPalette[i].Green=i;
			m_pPalette[i].Blue =i;
			m_pPalette[i].Reserved=0;
		}
	}
	long size = m_MemWidth*m_Height;
	m_pPixelData = new BYTE [size];
	for(i=0;i<size;i++) 
			m_pPixelData[i] = 0;
	m_pPixelMatrix = new BYTE* [m_Height];
	for(y=0;y<m_Height;y++) 
		m_pPixelMatrix[y] = &m_pPixelData[(m_Height-y-1)*m_MemWidth];
	
	return true;
}

bool CImage::LoadBmpFile(const char *filename)
{
	FILE *fp=fopen(filename,"rb");
	if(fp==NULL){printf("read file error!");return false;};
	size_t numread;
	//讀取FileHeader
	numread=fread(&m_BmpFileHeader,1,14,fp);
	if(numread!=14) return false;
	if(m_BmpFileHeader.Type!=0x4d42) return false;
	//讀取InfoHeader	
	numread=fread(&m_BmpInfoHeader,1,sizeof(BITMAPINFOHEADER),fp);
	if(numread!= sizeof(BITMAPINFOHEADER)) return false;
	//設定ColorTable的大小
	//InfoHeader的BitCount屬性代表bpp(bit per pixel)
	int PaletteSize = 0; //調色盤的大小
	switch ( m_BmpInfoHeader.BitCount ){
		case 1:	PaletteSize = 2;  break; //1個bit可以存兩種顏色
		case 4:	PaletteSize = 16; break; //4個bit可以存16種顏色
		case 8:	PaletteSize = 256;break; //8個bit可以存256種顏色
	}	//24、32個bit已有完整色彩，所以不需要調色盤，預設值PaletteSize = 0
	//開始將各項檔案資訊存到CImage的物件屬性
	m_Bpp=m_BmpInfoHeader.BitCount;		//bit per pixel
	m_Width=m_BmpInfoHeader.Width;		//寬
	m_Height=m_BmpInfoHeader.Height;	//高
	m_MemWidth = m_Width * (m_Bpp >> 3);
	m_MemWidth = (m_MemWidth + 3) >> 2 << 2;
	//讀取ColorTable
	if(PaletteSize){
		m_pPalette = new RGBQUAD [PaletteSize];
		numread=fread(m_pPalette,sizeof(RGBQUAD),PaletteSize,fp);
		if(numread!=PaletteSize)	return false;
	}
	//讀取ImageData
	int size = m_MemWidth*m_Height;
	m_pPixelData = new BYTE [size];
	numread = fread(m_pPixelData,1,size,fp);
	if(numread!=size) return false;
	int y;
	m_pPixelMatrix = new BYTE* [m_Height];
	for(y=0;y<m_Height;y++) 
			m_pPixelMatrix[y] = &m_pPixelData[(m_Height-y-1)*m_MemWidth];
	
	fclose(fp);
	return true;
}

bool CImage::SaveBmpFile(const char *filename)
{
	FILE *fp=fopen(filename,"wb");

	int PaletteSize = 0;
    switch ( m_Bpp ){
		case 1: PaletteSize = 2;  break;
		case 4:	PaletteSize = 16; break;
		case 8:	PaletteSize = 256;break;
	}

	fwrite(&m_BmpFileHeader,1,sizeof(BITMAPFILEHEADER),fp);
	fwrite(&m_BmpInfoHeader,1,sizeof(BITMAPINFOHEADER),fp);
	fwrite(m_pPalette,sizeof(RGBQUAD),PaletteSize,fp);
	fwrite(m_pPixelData,1,m_MemWidth*m_Height,fp);

	fclose(fp);
	return true;
} 

DWORD CImage::GetPixel(int x,int y)
{
	if( x<0 || x >= m_Width || y<0 || y >= m_Height ){
		printf("index exceed! x=%d,y=%d\n",x,y);
		return 0;		
	}
	BYTE **mat = m_pPixelMatrix;
	if(m_Bpp==8)
		return RGB(mat[y][x],mat[y][x],mat[y][x]);
	else if(m_Bpp==24)
		return RGB(mat[y][x*3+2],mat[y][x*3+1],mat[y][x*3]);
	else return 0;
}

BYTE CImage::GetGrayPixel(int x,int y)
{
	if( x<0 || x >= m_Width || y<0 || y >= m_Height ){
		printf("index exceed! x=%d,y=%d\n",x,y);
		return 0;		
	}
	BYTE **mat = m_pPixelMatrix;
	if(m_Bpp==8)
		return mat[y][x];
	else if(m_Bpp==24)
		return (BYTE)(0.299*mat[y][x*3+2]+0.587*mat[y][x*3+1]+0.114*mat[y][x*3]);
	else return 0;
}

BYTE CImage::GetR(int x,int y)
{
	if(m_Bpp!=24){
		printf("Bpp must be 24!\n");
		return 0;
	}
	if( x<0 || x >= m_Width || y<0 || y >= m_Height ){
		printf("index exceed! x=%d,y=%d\n",x,y);
		return 0;		
	}
	return m_pPixelMatrix[y][x*3+2];
}
BYTE CImage::GetG(int x,int y)
{
	if(m_Bpp!=24){
		printf("Bpp must be 24!\n");
		return 0;
	}
	if( x<0 || x >= m_Width || y<0 || y >= m_Height ){
		printf("index exceed! x=%d,y=%d\n",x,y);
		return 0;		
	}
	return m_pPixelMatrix[y][x*3+1];
}
BYTE CImage::GetB(int x,int y)
{
	if(m_Bpp!=24){
		printf("Bpp must be 24!\n");
		return 0;
	}
	if( x<0 || x >= m_Width || y<0 || y >= m_Height ){
		printf("index exceed! x=%d,y=%d\n",x,y);
		return 0;		
	}
	return m_pPixelMatrix[y][x*3];
}

void CImage::SetPixel(int x,int y,DWORD color)
{
	if( x<0 || x >= m_Width || y<0 || y >= m_Height ){
		printf("index exceed! x=%d,y=%d\n",x,y);
		return;		
	}
	BYTE **mat = m_pPixelMatrix;
	if(m_Bpp==8)
		mat[y][x]=(BYTE)(0.299*GetRValue(color)+0.587*GetGValue(color)+0.114*GetBValue(color));
	else if(m_Bpp==24){
		mat[y][x*3+2]=GetRValue(color);
		mat[y][x*3+1]=GetGValue(color);
		mat[y][x*3+0]=GetBValue(color);
	}
}

void CImage::SetGrayPixel(int x,int y,BYTE value)
{
	if( x<0 || x >= m_Width || y<0 || y >= m_Height ){
		printf("index exceed! x=%d,y=%d\n",x,y);
		return;		
	}
	BYTE **mat = m_pPixelMatrix;
	if(m_Bpp==8)
		mat[y][x]=value;
	else if(m_Bpp==24){
		mat[y][x*3+2]=value;
		mat[y][x*3+1]=value;
		mat[y][x*3+0]=value;
	}
}

void CImage::SetR(int x,int y,BYTE value)
{
	if(m_Bpp!=24){
		printf("Bpp must be 24!\n");
		return;
	}
	if( x<0 || x >= m_Width || y<0 || y >= m_Height ){
		printf("index exceed! x=%d,y=%d\n",x,y);
		return;		
	}
	m_pPixelMatrix[y][x*3+2]=value;
}
void CImage::SetG(int x,int y,BYTE value)
{
	if(m_Bpp!=24){
		printf("Bpp must be 24!\n");
		return;
	}
	if( x<0 || x >= m_Width || y<0 || y >= m_Height ){
		printf("index exceed! x=%d,y=%d\n",x,y);
		return;		
	}
	m_pPixelMatrix[y][x*3+1]=value;
}
void CImage::SetB(int x,int y,BYTE value)
{
	if(m_Bpp!=24){
		printf("Bpp must be 24!\n");
		return;
	}
	if( x<0 || x >= m_Width || y<0 || y >= m_Height ){
		printf("index exceed! x=%d,y=%d\n",x,y);
		return;		
	}
	m_pPixelMatrix[y][x*3]=value;
}
