#pragma once
#include "CommonVector.h"
namespace NSDevilX
{
#define VECTOR_OPERATOR_FUNC(op,func,x,type0,type1,type2) \
	inline Boolean operator op(const DirectX::XM##type0##x & leftValue,type1 rightValue) \
	{ \
		type1 temp_value[x]={rightValue}; \
		return DirectX::XMVector##x##func(DirectX::XMLoad##type2##x(&leftValue),DirectX::XMLoad##type2##x(&DirectX::XM##type0##x(temp_value))); \
	} \
	inline Boolean operator op(type1 leftValue,const DirectX::XM##type0##x & rightValue) \
	{ \
		return operator op(rightValue,leftValue); \
	}
	VECTOR_OPERATOR_FUNC(==,EqualInt,2,INT,Int32,SInt)
		VECTOR_OPERATOR_FUNC(!=,NotEqualInt,2,INT,Int32,SInt)
		VECTOR_OPERATOR_FUNC(>,Greater,2,INT,Int32,SInt)
		VECTOR_OPERATOR_FUNC(<,Less,2,INT,Int32,SInt)
		VECTOR_OPERATOR_FUNC(>=,GreaterOrEqual,2,INT,Int32,SInt)
		VECTOR_OPERATOR_FUNC(<=,LessOrEqual,2,INT,Int32,SInt)
		VECTOR_OPERATOR_FUNC(==,EqualInt,3,INT,Int32,SInt)
		VECTOR_OPERATOR_FUNC(!=,NotEqualInt,3,INT,Int32,SInt)
		VECTOR_OPERATOR_FUNC(>,Greater,3,INT,Int32,SInt)
		VECTOR_OPERATOR_FUNC(<,Less,3,INT,Int32,SInt)
VECTOR_OPERATOR_FUNC(>=,GreaterOrEqual,3,INT,Int32,SInt)
VECTOR_OPERATOR_FUNC(<=,LessOrEqual,3,INT,Int32,SInt)
VECTOR_OPERATOR_FUNC(==,EqualInt,4,INT,Int32,SInt)
VECTOR_OPERATOR_FUNC(!=,NotEqualInt,4,INT,Int32,SInt)
VECTOR_OPERATOR_FUNC(>,Greater,4,INT,Int32,SInt)
VECTOR_OPERATOR_FUNC(<,Less,4,INT,Int32,SInt)
	VECTOR_OPERATOR_FUNC(>=,GreaterOrEqual,4,INT,Int32,SInt)
	VECTOR_OPERATOR_FUNC(<=,LessOrEqual,4,INT,Int32,SInt)
	VECTOR_OPERATOR_FUNC(==,EqualInt,2,UINT,UInt32,UInt)
	VECTOR_OPERATOR_FUNC(!=,NotEqualInt,2,UINT,UInt32,UInt)
	VECTOR_OPERATOR_FUNC(>,Greater,2,UINT,UInt32,UInt)
	VECTOR_OPERATOR_FUNC(<,Less,2,UINT,UInt32,UInt)
	VECTOR_OPERATOR_FUNC(>=,GreaterOrEqual,2,UINT,UInt32,UInt)
	VECTOR_OPERATOR_FUNC(<=,LessOrEqual,2,UINT,UInt32,UInt)
	VECTOR_OPERATOR_FUNC(==,EqualInt,3,UINT,UInt32,UInt)
	VECTOR_OPERATOR_FUNC(!=,NotEqualInt,3,UINT,UInt32,UInt)
	VECTOR_OPERATOR_FUNC(>,Greater,3,UINT,UInt32,UInt)
	VECTOR_OPERATOR_FUNC(<,Less,3,UINT,UInt32,UInt)
	VECTOR_OPERATOR_FUNC(>=,GreaterOrEqual,3,UINT,UInt32,UInt)
	VECTOR_OPERATOR_FUNC(<=,LessOrEqual,3,UINT,UInt32,UInt)
	VECTOR_OPERATOR_FUNC(==,EqualInt,4,UINT,UInt32,UInt)
	VECTOR_OPERATOR_FUNC(!=,NotEqualInt,4,UINT,UInt32,UInt)
	VECTOR_OPERATOR_FUNC(>,Greater,4,UINT,UInt32,UInt)
	VECTOR_OPERATOR_FUNC(<,Less,4,UINT,UInt32,UInt)
	VECTOR_OPERATOR_FUNC(>=,GreaterOrEqual,4,UINT,UInt32,UInt)
	VECTOR_OPERATOR_FUNC(<=,LessOrEqual,4,UINT,UInt32,UInt)
#undef VECTOR_OPERATOR_FUNC
#define VECTOR_OPERATOR_FUNC(x,op,func,type0,type1) \
	inline Boolean operator op(const DirectX::XM##type0##x & leftValue,const DirectX::XM##type0##x & rightValue) \
	{ \
		return DirectX::XMVector##x##func(DirectX::XMLoad##type1##x(&leftValue),DirectX::XMLoad##type1##x(&rightValue)); \
	}
	VECTOR_OPERATOR_FUNC(2,==,EqualInt,INT,SInt)
	VECTOR_OPERATOR_FUNC(2,!=,NotEqualInt,INT,SInt)
	VECTOR_OPERATOR_FUNC(2,>,Greater,INT,SInt)
	VECTOR_OPERATOR_FUNC(2,<,Less,INT,SInt)
	VECTOR_OPERATOR_FUNC(2,>=,GreaterOrEqual,INT,SInt)
	VECTOR_OPERATOR_FUNC(2,<=,LessOrEqual,INT,SInt)
	VECTOR_OPERATOR_FUNC(3,==,EqualInt,INT,SInt)
	VECTOR_OPERATOR_FUNC(3,!=,NotEqualInt,INT,SInt)
	VECTOR_OPERATOR_FUNC(3,>,Greater,INT,SInt)
	VECTOR_OPERATOR_FUNC(3,<,Less,INT,SInt)
	VECTOR_OPERATOR_FUNC(3,>=,GreaterOrEqual,INT,SInt)
	VECTOR_OPERATOR_FUNC(3,<=,LessOrEqual,INT,SInt)
	VECTOR_OPERATOR_FUNC(4,==,EqualInt,INT,SInt)
	VECTOR_OPERATOR_FUNC(4,!=,NotEqualInt,INT,SInt)
	VECTOR_OPERATOR_FUNC(4,>,Greater,INT,SInt)
	VECTOR_OPERATOR_FUNC(4,<,Less,INT,SInt)
	VECTOR_OPERATOR_FUNC(4,>=,GreaterOrEqual,INT,SInt)
	VECTOR_OPERATOR_FUNC(4,<=,LessOrEqual,INT,SInt)
	VECTOR_OPERATOR_FUNC(2,==,EqualInt,UINT,UInt)
	VECTOR_OPERATOR_FUNC(2,!=,NotEqualInt,UINT,UInt)
	VECTOR_OPERATOR_FUNC(2,>,Greater,UINT,UInt)
	VECTOR_OPERATOR_FUNC(2,<,Less,UINT,UInt)
	VECTOR_OPERATOR_FUNC(2,>=,GreaterOrEqual,UINT,UInt)
	VECTOR_OPERATOR_FUNC(2,<=,LessOrEqual,UINT,UInt)
	VECTOR_OPERATOR_FUNC(3,==,EqualInt,UINT,UInt)
	VECTOR_OPERATOR_FUNC(3,!=,NotEqualInt,UINT,UInt)
	VECTOR_OPERATOR_FUNC(3,>,Greater,UINT,UInt)
	VECTOR_OPERATOR_FUNC(3,<,Less,UINT,UInt)
	VECTOR_OPERATOR_FUNC(3,>=,GreaterOrEqual,UINT,UInt)
	VECTOR_OPERATOR_FUNC(3,<=,LessOrEqual,UINT,UInt)
	VECTOR_OPERATOR_FUNC(4,==,EqualInt,UINT,UInt)
	VECTOR_OPERATOR_FUNC(4,!=,NotEqualInt,UINT,UInt)
	VECTOR_OPERATOR_FUNC(4,>,Greater,UINT,UInt)
	VECTOR_OPERATOR_FUNC(4,<,Less,UINT,UInt)
	VECTOR_OPERATOR_FUNC(4,>=,GreaterOrEqual,UINT,UInt)
	VECTOR_OPERATOR_FUNC(4,<=,LessOrEqual,UINT,UInt)
#undef VECTOR_OPERATOR_FUNC
#define BEGIN_VECTOR_CLASS(x,type0,type1,type2) \
	class C##type0##x \
		:public DirectX::XM##type1##x \
	{ \
	public: \
		static const C##type0##x sZero; \
		static const C##type0##x sOne; \
		using DirectX::XM##type1##x::XM##type1##x; \
		using DirectX::XM##type1##x::operator=; \
		C##type0##x(type0##32 value=0) \
		{\
			*this=value; \
		} \
		C##type0##x(const DirectX::XM##type1##x & value) \
			:DirectX::XM##type1##x(value) \
		{} \
		C##type0##x(DirectX::FXMVECTOR value) \
		{ \
			*this=value; \
		} \
		C##type0##x(const DirectX::XMFLOAT##x & value) \
		{ \
			*this=value; \
		} \
		operator DirectX::XMVECTOR()const \
		{ \
			return DirectX::XMLoad##type2##x(this); \
		} \
		const C##type0##x & operator=(type0##32 value) \
		{ \
			type0##32 temp_value[x]; \
			for(auto & v:temp_value)v=value; \
			*this=DirectX::XM##type1##x(temp_value); \
			return *this; \
		} \
		type0##32 operator[](SizeT index)const \
		{ \
			return *(reinterpret_cast<const type0##32*>(this)+index); \
		} \
		type0##32 & operator[](SizeT index) \
		{ \
			return *(reinterpret_cast<type0##32*>(this)+index); \
		} \
		const C##type0##x & operator=(DirectX::FXMVECTOR value) \
		{ \
			DirectX::XMStore##type2##x(this,value); \
			return *this; \
		} \
		const C##type0##x & operator=(const DirectX::XMFLOAT##x & value) \
		{ \
			*this=DirectX::XMConvertVectorFloatTo##type0(DirectX::XMLoadFloat##x(&value),0); \
			return *this; \
		} \
		const C##type0##x & operator+=(DirectX::FXMVECTOR value) \
		{ \
			*this=*this+value; \
			return *this; \
		} \
		const C##type0##x & operator-=(DirectX::FXMVECTOR value) \
		{ \
			*this=*this-value; \
			return *this; \
		} \
		const C##type0##x & operator*=(DirectX::FXMVECTOR value) \
		{ \
			*this=*this*value; \
			return *this; \
		} \
		const C##type0##x & operator/=(DirectX::FXMVECTOR value) \
		{ \
			*this=*this/value; \
			return *this; \
		} \
		const C##type0##x & operator%=(DirectX::FXMVECTOR value) \
		{ \
			*this=*this%value; \
			return *this; \
		}
#define END_CLASS };
	BEGIN_VECTOR_CLASS(2,Int,INT,SInt)
	END_CLASS
	BEGIN_VECTOR_CLASS(3,Int,INT,SInt)
	static const CInt3 sUnitX;
	static const CInt3 sUnitY;
	static const CInt3 sUnitZ;
	const CInt2 & xy()const
	{
		return *reinterpret_cast<const CInt2*>(this);
	}
	const CInt2 & yz()const
	{
		return *reinterpret_cast<const CInt2*>(&y);
	}
	END_CLASS
	BEGIN_VECTOR_CLASS(4,Int,INT,SInt)
	CInt4(const DirectX::XMINT3 & vec3,Int32 w)
		:DirectX::XMINT4(vec3.x,vec3.y,vec3.z,w)
	{}
	const CInt2 & xy()const
	{
		return *reinterpret_cast<const CInt2*>(this);
	}
	const CInt2 & yz()const
	{
		return *reinterpret_cast<const CInt2*>(&y);
	}
	const CInt2 & zw()const
	{
		return *reinterpret_cast<const CInt2*>(&z);
	}
	const CInt3 & xyz()const
	{
		return *reinterpret_cast<const CInt3*>(this);
	}
	const CInt3 & yzw()const
	{
		return *reinterpret_cast<const CInt3*>(&y);
	}
	END_CLASS
	BEGIN_VECTOR_CLASS(2,UInt,UINT,UInt)
	END_CLASS
	BEGIN_VECTOR_CLASS(3,UInt,UINT,UInt)
	static const CUInt3 sUnitX;
	static const CUInt3 sUnitY;
	static const CUInt3 sUnitZ;
	const CUInt2 & xy()const
	{
		return *reinterpret_cast<const CUInt2*>(this);
	}
	const CUInt2 & yz()const
	{
		return *reinterpret_cast<const CUInt2*>(&y);
	}
	END_CLASS
	BEGIN_VECTOR_CLASS(4,UInt,UINT,UInt)
	CUInt4(const DirectX::XMUINT3 & vec3,Int32 w)
		:DirectX::XMUINT4(vec3.x,vec3.y,vec3.z,w)
	{}
	const CUInt2 & xy()const
	{
		return *reinterpret_cast<const CUInt2*>(this);
	}
	const CUInt2 & yz()const
	{
		return *reinterpret_cast<const CUInt2*>(&y);
	}
	const CUInt2 & zw()const
	{
		return *reinterpret_cast<const CUInt2*>(&z);
	}
	const CUInt3 & xyz()const
	{
		return *reinterpret_cast<const CUInt3*>(this);
	}
	const CUInt3 & yzw()const
	{
		return *reinterpret_cast<const CUInt3*>(&y);
	}
	END_CLASS
#undef VECTOR_OPERATOR_FUNC
#undef VECTOR_OPERATOR_FUNC2
#undef BEGIN_VECTOR_CLASS
#undef END_CLASS
}
