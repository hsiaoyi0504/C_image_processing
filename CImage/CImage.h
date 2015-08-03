#define BYTE   unsigned char  // 1 byte
#define WORD   unsigned short // 2 byte
#define DWORD  unsigned long  // 4 byte
#define COLORREF DWORD        // 用來存RGB的色彩值，格式為 0x00bbggrr

#define RGB(R,G,B) ( (COLORREF)R + ((COLORREF)G<<8) + ((COLORREF)B<<16) )
#define GetRValue(color) ((BYTE)((color & 0x000000FF)    ))
#define GetGValue(color) ((BYTE)((color & 0x0000FF00)>>8 ))
#define GetBValue(color) ((BYTE)((color & 0x00FF0000)>>16))

#pragma pack(1) //設定以1Byte為單位做結構成員對齊

struct BITMAPFILEHEADER { 
  WORD    Type;     //file type, must be BM(0x4d42)
  DWORD   Size;     //total file size, in bytes
  WORD    Reserved1;//must be zero.  
  WORD    Reserved2;//must be zero.  
  DWORD   OffBits;  //the offset, in bytes, from BITMAPFILEHEADER to Pixel Data
};

struct BITMAPINFOHEADER {
  DWORD Size;    //the number of bytes required by BITMAPINFOHEADER
  long  Width;   //the width of the bitmap, in pixels
  long  Height;  //the height of the bitmap, in pixels
  WORD  Planes;  //the number of planes for the target device. This value must be set to 1
  WORD  BitCount;//the number of bits-per-pixel. must be 0,1,4,8,16,24,or 32 
  DWORD Compression;//the type of compression for a compressed bottom-up bitmap. An uncompressed format is BI_RGB
  DWORD SizeImage;//the size, in bytes, of the image. This may be set to zero for BI_RGB bitmaps
  long  XPelsPerMeter; //the horizontal resolution, in pixels-per-meter
  long  YPelsPerMeter; //the vertical resolution, in pixels-per-meter
  DWORD ClrUsed; //the number of color indexes in the color table that are actually used by the bitmap
  DWORD ClrImportant; //the number of color indexes that are required for displaying the bitmap.
}; 

struct RGBQUAD {
  BYTE Blue; 
  BYTE Green; 
  BYTE Red; 
  BYTE Reserved; 
};

#pragma pack() //還原結構成員對齊的單位為預設值

class CImage  
{
//建構子、解構子
public:
	CImage();
	~CImage();

// Attributes 成員變數
private:
	BITMAPFILEHEADER m_BmpFileHeader;
	BITMAPINFOHEADER m_BmpInfoHeader;
	RGBQUAD *m_pPalette;   // allocate memory
	BYTE   *m_pPixelData; // allocate memory
	BYTE   **m_pPixelMatrix; // allocate memory

	int m_Width;
	int m_Height;
	int m_MemWidth;
	int m_Bpp;

// Operations 成員函式
public:
	bool Create(int width,int height,int bpp);
	bool LoadBmpFile(const char *filename);
	bool SaveBmpFile(const char *filename);
	int	GetWidth() { return m_Width; };
	int GetHeight(){ return m_Height;};
	BYTE **GetPixelMatrix(){ return m_pPixelMatrix; };
	DWORD GetPixel(int x,int y);
	BYTE  GetGrayPixel(int x,int y);
	BYTE  GetR(int x,int y);
	BYTE  GetG(int x,int y);
	BYTE  GetB(int x,int y);
	void  SetPixel(int x,int y,DWORD color);
	void  SetGrayPixel(int x,int y,BYTE value);
	void  SetR(int x,int y,BYTE value);
	void  SetG(int x,int y,BYTE value);
	void  SetB(int x,int y,BYTE value);
};

