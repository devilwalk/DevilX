#pragma once
#include "CommonDataStream.h"
namespace NSDevilX
{
	class CImage
		:public TBaseObject<CImage>
	{
	public:
		enum EPixelType
		{
			EPixelType_Unknown,
			EPixelType_RGB8,
			EPixelType_RGBA8
		};
	protected:
		EPixelType mPixelType;
		UInt32 mBPP;
		UInt32 mWidth;
		UInt32 mHeight;
		TVector<Byte> mPixels;
	public:
		static Void convertRGB8ToRGBA8(const Byte * src,Byte * dst,UInt32 pixelCount);
		static Void convertRGBA8ToRGB8(const Byte * src,Byte * dst,UInt32 pixelCount);
		CImage();
		CImage(const CDataStream & dataStream);
		~CImage();
		Void load(const CDataStream & dataStream);
		EPixelType getPixelType()const
		{
			return mPixelType;
		}
		UInt32 getWidth()const
		{
			return mWidth;
		}
		UInt32 getHeight()const
		{
			return mHeight;
		}
		UInt32 getBPP()const
		{
			return mBPP;
		}
		const Byte * getPixels()const
		{
			return &mPixels[0];
		}
		CImage * convert(EPixelType type)const;
	};
}