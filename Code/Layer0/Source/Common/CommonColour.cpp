#include "Precompiler.h"
using namespace NSDevilX;

const NSDevilX::CFloatRGB NSDevilX::CFloatRGB::sBlack(0.0f,0.0f,0.0f);
const NSDevilX::CFloatRGB NSDevilX::CFloatRGB::sWhite(1.0f,1.0f,1.0f);
const NSDevilX::CFloatRGB NSDevilX::CFloatRGB::sRed(1.0f,0.0f,0.0f);
const NSDevilX::CFloatRGB NSDevilX::CFloatRGB::sGreen(0.0f,1.0f,0.0f);
const NSDevilX::CFloatRGB NSDevilX::CFloatRGB::sBlue(0.0f,0.0f,1.0f);
NSDevilX::CFloatRGB::CFloatRGB(UInt8 r,UInt8 g,UInt8 b)
	:CFloat3(r/255.0f,g/255.0f,b/255.0f)
{

}

NSDevilX::CFloatRGB::CFloatRGB(const CColour & cpy)
	:CFloat3(cpy.r(),cpy.g(),cpy.b())
{}

const CColour & NSDevilX::CFloatRGB::operator=(const CColour & cpy)
{
	*this=CFloat3(cpy.r(),cpy.g(),cpy.b());
	return *this;
}
Boolean NSDevilX::CFloatRGB::operator==(const CColour & test) const
{
	return *this==CFloat3(test.r(),test.g(),test.b());
}
Boolean NSDevilX::CFloatRGB::operator!=(const CColour & test) const
{
	return *this!=CFloat3(test.r(),test.g(),test.b());
}

NSDevilX::CColour::EType NSDevilX::CFloatRGB::type() const
{
	return EType_RGB;
}

Float NSDevilX::CFloatRGB::r() const
{
	return x;
}

Float NSDevilX::CFloatRGB::g() const
{
	return y;
}

Float NSDevilX::CFloatRGB::b() const
{
	return z;
}

Float NSDevilX::CFloatRGB::a() const
{
	return 1.0f;
}
const NSDevilX::CFloatRGBA NSDevilX::CFloatRGBA::sZero(CFloat4::sZero);
const NSDevilX::CFloatRGBA NSDevilX::CFloatRGBA::sBlack(0.0f,0.0f,0.0f,1.0f);
const NSDevilX::CFloatRGBA NSDevilX::CFloatRGBA::sWhite(1.0f,1.0f,1.0f,1.0f);
const NSDevilX::CFloatRGBA NSDevilX::CFloatRGBA::sRed(1.0f,0.0f,0.0f,1.0f);
const NSDevilX::CFloatRGBA NSDevilX::CFloatRGBA::sGreen(0.0f,1.0f,0.0f,1.0f);
const NSDevilX::CFloatRGBA NSDevilX::CFloatRGBA::sBlue(0.0f,0.0f,1.0f,1.0f);
NSDevilX::CFloatRGBA::CFloatRGBA(UInt8 r,UInt8 g,UInt8 b,UInt8 a)
	:CFloat4(r/255.0f,g/255.0f,b/255.0f,a/255.0f)
{

}

NSDevilX::CFloatRGBA::CFloatRGBA(const CColour & cpy)
	:CFloat4(cpy.r(),cpy.g(),cpy.b(),cpy.a())
{}

const CFloatRGBA & NSDevilX::CFloatRGBA::operator=(const CFloatRGBA & cpy)
{
	// TODO: 在此处插入 return 语句
	return static_cast<const CFloatRGBA&>(operator=(static_cast<const CColour &>(cpy)));
}

const CColour & NSDevilX::CFloatRGBA::operator=(const CColour & cpy)
{
	*this=CFloat4(cpy.r(),cpy.g(),cpy.b(),cpy.a());
	return *this;
}
Boolean NSDevilX::CFloatRGBA::operator==(const CColour & test) const
{
	return *this==CFloat4(test.r(),test.g(),test.b(),test.a());
}
Boolean NSDevilX::CFloatRGBA::operator!=(const CColour & test) const
{
	return *this!=CFloat4(test.r(),test.g(),test.b(),test.a());
}

NSDevilX::CColour::EType NSDevilX::CFloatRGBA::type() const
{
	return EType_RGBA;
}

Float NSDevilX::CFloatRGBA::r() const
{
	return x;
}

Float NSDevilX::CFloatRGBA::g() const
{
	return y;
}

Float NSDevilX::CFloatRGBA::b() const
{
	return z;
}

Float NSDevilX::CFloatRGBA::a() const
{
	return w;
}

NSDevilX::CFloatAlpha::CFloatAlpha(UInt8 a)
	:mValue(a/255.0f)
{}

NSDevilX::CFloatAlpha::CFloatAlpha(Float a)
	:mValue(a)
{}

NSDevilX::CFloatAlpha::CFloatAlpha(const CColour & cpy)
	:mValue(cpy.a())
{}

const CColour & NSDevilX::CFloatAlpha::operator=(const CColour & cpy)
{
	mValue=cpy.a();
	return *this;
}
Boolean NSDevilX::CFloatAlpha::operator==(const CColour & test) const
{
	return mValue==test.a();
}
Boolean NSDevilX::CFloatAlpha::operator!=(const CColour & test) const
{
	return mValue!=test.a();
}

NSDevilX::CColour::EType NSDevilX::CFloatAlpha::type() const
{
	return EType_Alpha;
}

Float NSDevilX::CFloatAlpha::r() const
{
	return 0.0f;
}

Float NSDevilX::CFloatAlpha::g() const
{
	return 0.0f;
}

Float NSDevilX::CFloatAlpha::b() const
{
	return 0.0f;
}

Float NSDevilX::CFloatAlpha::a() const
{
	return mValue;
}
