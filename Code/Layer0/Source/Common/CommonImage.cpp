#include "Precompiler.h"
using namespace NSDevilX;

Void NSDevilX::CImage::convertRGB8ToRGBA8(const Byte * src,Byte * dst,UInt32 pixelCount)
{
	for(UInt32 i=0;i<pixelCount;++i)
	{
#if DEVILX_BYTE_ORDER==DEVILX_BYTE_ORDER_BIG_ENDIAN
		dst[i*4+3]=255;
		dst[i*4+2]=src[i*3+2];
		dst[i*4+1]=src[i*3+1];
		dst[i*4]=src[i*3];
#else
		dst[i*4]=255;
		dst[i*4+1]=src[i*3];
		dst[i*4+2]=src[i*3+1];
		dst[i*4+3]=src[i*3+2];
#endif
	}
}

Void NSDevilX::CImage::convertRGBA8ToRGB8(const Byte * src,Byte * dst,UInt32 pixelCount)
{
	for(UInt32 i=0;i<pixelCount;++i)
	{
#if DEVILX_BYTE_ORDER==DEVILX_BYTE_ORDER_BIG_ENDIAN
		dst[i*3]=src[i*4];
		dst[i*3+1]=src[i*4+1];
		dst[i*3+2]=src[i*4+2];
#else
		dst[i*3+2]=src[i*4+3];
		dst[i*3+1]=src[i*4+2];
		dst[i*3]=src[i*4+1];
#endif
	}
}

NSDevilX::CImage::CImage()
	:mPixelType(EPixelType_Unknown)
	,mBPP(0)
	,mWidth(0)
	,mHeight(0)
{}

NSDevilX::CImage::CImage(CDataStream * dataStream)
	:mPixelType(EPixelType_Unknown)
	,mBPP(0)
	,mWidth(0)
	,mHeight(0)
{
	FreeImage_Initialise();
	TVector<Byte> src;
	src.resize(dataStream->getSize());
	CDataStreamReader * reader=dataStream->createReader();
	reader->process(static_cast<UInt32>(src.size()),&src[0]);
	FIMEMORY * mem=FreeImage_OpenMemory(&src[0],static_cast<UInt32>(src.size()));
	FREE_IMAGE_FORMAT fmat=FreeImage_GetFileTypeFromMemory(mem);
	FIBITMAP * bmp=FreeImage_LoadFromMemory(fmat,mem);
	mBPP=FreeImage_GetBPP(bmp);
	UInt32 sibpp=std::max<UInt32>(mBPP/8,1);
	mWidth=FreeImage_GetWidth(bmp);
	mHeight=FreeImage_GetHeight(bmp);
	mPixels.resize(getWidth()*getHeight()*sibpp);
	switch(FreeImage_GetImageType(bmp))
	{
	case FIT_UNKNOWN:mPixelType=EPixelType_Unknown;break;	//! unknown type
	case FIT_BITMAP:
		switch(getBPP())
		{
		case 1:
			break;
		case 4:
			break;
		case 8:
			break;
		case 16:
			break;
		case 24:
			for(UInt32 v=0;v<getHeight();++v)
			{
				//freeimage uv原点在左下角
				auto data=FreeImage_GetScanLine(bmp,getHeight()-v-1);
				for(UInt32 u=0;u<getWidth();++u)
				{
#if DEVILX_BYTE_ORDER==DEVILX_BYTE_ORDER_BIG_ENDIAN
					mPixels[sibpp*(getWidth()*v+u)]=data[FI_RGBA_RED];
					mPixels[sibpp*(getWidth()*v+u)+1]=data[FI_RGBA_GREEN];
					mPixels[sibpp*(getWidth()*v+u)+2]=data[FI_RGBA_BLUE];
#else
					mPixels[sibpp*(getWidth()*v+u)+2]=data[FI_RGBA_RED];
					mPixels[sibpp*(getWidth()*v+u)+1]=data[FI_RGBA_GREEN];
					mPixels[sibpp*(getWidth()*v+u)]=data[FI_RGBA_BLUE];
#endif
					data+=sibpp;
				}
			}
			mPixelType=EPixelType_RGB8;
			break;
		case 32:
			for(UInt32 v=0;v<getHeight();++v)
			{
				//freeimage uv原点在左下角
				auto data=FreeImage_GetScanLine(bmp,getHeight()-v-1);
				for(UInt32 u=0;u<getWidth();++u)
				{
#if DEVILX_BYTE_ORDER==DEVILX_BYTE_ORDER_BIG_ENDIAN
					mPixels[sibpp*(getWidth()*v+u)]=data[FI_RGBA_RED];
					mPixels[sibpp*(getWidth()*v+u)+1]=data[FI_RGBA_GREEN];
					mPixels[sibpp*(getWidth()*v+u)+2]=data[FI_RGBA_BLUE];
					mPixels[sibpp*(getWidth()*v+u)+3]=data[FI_RGBA_ALPHA];
#else
					mPixels[sibpp*(getWidth()*v+u)+3]=data[FI_RGBA_RED];
					mPixels[sibpp*(getWidth()*v+u)+2]=data[FI_RGBA_GREEN];
					mPixels[sibpp*(getWidth()*v+u)+1]=data[FI_RGBA_BLUE];
					mPixels[sibpp*(getWidth()*v+u)]=data[FI_RGBA_ALPHA];
#endif
					data+=sibpp;
				}
			}
			mPixelType=EPixelType_RGBA8;
			break;
		}
		break;	//! standard image			: 1-, 4-, 8-, 16-, 24-, 32-bit
	case FIT_UINT16:break;	//! array of unsigned short	: unsigned 16-bit
	case FIT_INT16:break;	//! array of short			: signed 16-bit
	case FIT_UINT32:break;	//! array of unsigned long	: unsigned 32-bit
	case FIT_INT32:break;	//! array of long			: signed 32-bit
	case FIT_FLOAT:break;	//! array of float			: 32-bit IEEE floating point
	case FIT_DOUBLE:break;	//! array of double			: 64-bit IEEE floating point
	case FIT_COMPLEX:break;	//! array of FICOMPLEX		: 2 x 64-bit IEEE floating point
	case FIT_RGB16:break;	//! 48-bit RGB image			: 3 x 16-bit
	case FIT_RGBA16:break;	//! 64-bit RGBA image		: 4 x 16-bit
	case FIT_RGBF:break;	//! 96-bit RGB float image	: 3 x 32-bit IEEE floating point
	case FIT_RGBAF:break;	//! 128-bit RGBA float image	: 4 x 32-bit IEEE floating point
	}
	FreeImage_Unload(bmp);
	FreeImage_CloseMemory(mem);
	FreeImage_DeInitialise();
}

NSDevilX::CImage::~CImage()
{
}

CImage * NSDevilX::CImage::convert(EPixelType type) const
{
	CImage * ret=nullptr;
	if(getPixelType()==type)
	{
		ret=DEVILX_NEW CImage(*this);
	}
	else
	{
		ret=DEVILX_NEW CImage();
		ret->mHeight=getHeight();
		ret->mWidth=getWidth();
		ret->mPixelType=type;
		switch(getPixelType())
		{
		case EPixelType_RGB8:
			switch(type)
			{
			case EPixelType_RGBA8:
				ret->mBPP=32;
				ret->mPixels.resize(ret->getWidth()*ret->getHeight()*std::max<UInt32>(ret->getBPP()/8,1));
				convertRGB8ToRGBA8(getPixels(),&ret->mPixels[0],getWidth()*getHeight());
				break;
			}
			break;
		case EPixelType_RGBA8:
			switch(type)
			{
			case EPixelType_RGB8:
				ret->mBPP=24;
				convertRGBA8ToRGB8(getPixels(),&ret->mPixels[0],getWidth()*getHeight());
				break;
			}
			break;
		}
	}
	return ret;
}
