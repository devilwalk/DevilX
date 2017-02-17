#pragma once
#include "CommonVectorF.h"
#include "CommonMemoryAllocatorObjectTemplate.h"
namespace NSDevilX
{
	class CColour
	{
	public:
		enum EType
		{
			EType_Alpha,
			EType_RGB,
			EType_RGBA
		};
		CColour(){}
		virtual ~CColour(){}
		virtual const CColour & operator=(const CColour & cpy)=0;
		virtual Boolean operator==(const CColour & test)const=0;
		virtual Boolean operator!=(const CColour & test)const=0;
		virtual EType type()const=0;
		RGBA rgba8()const
		{
			return (r8())|(g8()<<8)|(b8()<<16)|(a8()<<24);
		}
		UInt8 r8()const
		{
			return static_cast<UInt8>(r()*255);
		}
		UInt8 g8()const
		{
			return static_cast<UInt8>(g()*255);
		}
		UInt8 b8()const
		{
			return static_cast<UInt8>(b()*255);
		}
		UInt8 a8()const
		{
			return static_cast<UInt8>(a()*255);
		}
		virtual Float r()const=0;
		virtual Float g()const=0;
		virtual Float b()const=0;
		virtual Float a()const=0;
	};
	class CFloatAlpha
		:public CColour
		,public TBaseObject<CFloatAlpha>
	{
	protected:
		Float mValue;
	public:
		CFloatAlpha(UInt8 a=0);
		CFloatAlpha(Float a=0.0f);
		CFloatAlpha(const CColour & cpy);
		virtual const CColour & operator=(const CColour & cpy) override;
		virtual Boolean operator==(const CColour & test) const override;
		virtual Boolean operator!=(const CColour & test) const override;
		virtual EType type() const override;
		virtual Float r() const override;
		virtual Float g() const override;
		virtual Float b() const override;
		virtual Float a() const override;
	};
	class CFloatRGB
		:public CFloat3
		,public CColour
		,public TBaseObject<CFloatRGB>
	{
	public:
		static const CFloatRGB sBlack;
		static const CFloatRGB sWhite;
		static const CFloatRGB sRed;
		static const CFloatRGB sGreen;
		static const CFloatRGB sBlue;
	public:
		using CFloat3::CFloat3;
		using CFloat3::operator=;
		CFloatRGB(UInt8 r=0,UInt8 g=0,UInt8 b=0);
		CFloatRGB(const CColour & cpy);
		virtual const CColour & operator=(const CColour & cpy) override;
		virtual Boolean operator==(const CColour & test) const override;
		virtual Boolean operator!=(const CColour & test) const override;
		virtual EType type() const override;
		virtual Float r() const override;
		virtual Float g() const override;
		virtual Float b() const override;
		virtual Float a() const override;
	};
	class CFloatRGBA
		:public CFloat4
		,public CColour
		,public TBaseObject<CFloatRGBA>
	{
	public:
		static const CFloatRGBA sBlack;
		static const CFloatRGBA sWhite;
		static const CFloatRGBA sRed;
		static const CFloatRGBA sGreen;
		static const CFloatRGBA sBlue;
	public:
		using CFloat4::CFloat4;
		using CFloat4::operator=;
		CFloatRGBA(UInt8 r=0,UInt8 g=0,UInt8 b=0,UInt8 a=0);
		CFloatRGBA(const CColour & cpy);
		virtual const CColour & operator=(const CColour & cpy) override;
		virtual Boolean operator==(const CColour & test) const override;
		virtual Boolean operator!=(const CColour & test) const override;
		virtual EType type() const override;
		virtual Float r() const override;
		virtual Float g() const override;
		virtual Float b() const override;
		virtual Float a() const override;
	};
}