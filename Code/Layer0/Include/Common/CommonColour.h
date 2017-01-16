#pragma once
#include "CommonVectorF.h"
namespace NSDevilX
{
	class CColour
		:public CFloat4
	{
	public:
		static const CColour sBlack;
		static const CColour sWhite;
		static const CColour sRed;
		static const CColour sGreen;
		static const CColour sBlue;
	public:
		using CFloat4::CFloat4;
		CColour(UInt8 r=0,UInt8 g=0,UInt8 b=0,UInt8 a=0);
		RGBA rgba8()const
		{
			CFloat4 rgba=DirectX::XMVectorClamp(*this,CFloat4::sZero,CFloat4::sOne);
			return (static_cast<RGBA>(rgba.x*255)<<24)|(static_cast<RGBA>(rgba.y*255)<<16)|(static_cast<RGBA>(rgba.z*255)<<8)|(static_cast<RGBA>(rgba.w*255)<<0);
		}
	};
}