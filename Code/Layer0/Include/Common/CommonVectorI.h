#pragma once
#include "CommonVector.h"
namespace NSDevilX
{
#define VECTOR_OPERATOR_FUNC(specialNamespace,type0,type1,x,op,func) \
	inline bool operator op(const specialNamespace::XM##type0##x & leftValue,const specialNamespace::XM##type0##x & rightValue) \
	{ \
		return DirectX::XMVector##x##func(specialNamespace::XMLoad##type1##x(&leftValue),specialNamespace::XMLoad##type1##x(&rightValue)); \
	} \
	inline bool XM_CALLCONV operator op(const specialNamespace::XM##type0##x & leftValue,DirectX::FXMVECTOR rightValue) \
	{ \
		return DirectX::XMVector##x##func(specialNamespace::XMLoad##type1##x(&leftValue),rightValue); \
	} \
	inline bool XM_CALLCONV operator op(DirectX::FXMVECTOR leftValue,const specialNamespace::XM##type0##x & rightValue) \
	{ \
		return DirectX::XMVector##x##func(leftValue,specialNamespace::XMLoad##type1##x(&rightValue)); \
	}
#define VECTOR_OPERATOR_FUNC2(specialNamespace,type0,type1,x) \
	inline DirectX::XMVECTOR operator -(const specialNamespace::XM##type0##x & leftValue,const specialNamespace::XM##type0##x & rightValue) \
	{ \
		return specialNamespace::XMLoad##type1##x(&leftValue)-specialNamespace::XMLoad##type1##x(&rightValue); \
	} \
	inline DirectX::XMVECTOR XM_CALLCONV operator -(const specialNamespace::XM##type0##x & leftValue,DirectX::FXMVECTOR rightValue) \
	{ \
		return specialNamespace::XMLoad##type1##x(&leftValue)-rightValue; \
	} \
	inline DirectX::XMVECTOR XM_CALLCONV operator -(DirectX::FXMVECTOR leftValue,const specialNamespace::XM##type0##x & rightValue) \
	{ \
		return leftValue-specialNamespace::XMLoad##type1##x(&rightValue); \
	} \
	inline DirectX::XMVECTOR operator +(const specialNamespace::XM##type0##x & leftValue,const specialNamespace::XM##type0##x & rightValue) \
	{ \
		return specialNamespace::XMLoad##type1##x(&leftValue)+specialNamespace::XMLoad##type1##x(&rightValue); \
	} \
	inline DirectX::XMVECTOR XM_CALLCONV operator +(const specialNamespace::XM##type0##x & leftValue,DirectX::FXMVECTOR rightValue) \
	{ \
		return specialNamespace::XMLoad##type1##x(&leftValue)+rightValue; \
	} \
	inline DirectX::XMVECTOR XM_CALLCONV operator +(DirectX::FXMVECTOR leftValue,const specialNamespace::XM##type0##x & rightValue) \
	{ \
		return leftValue+specialNamespace::XMLoad##type1##x(&rightValue); \
	} \
	inline DirectX::XMVECTOR operator *(const specialNamespace::XM##type0##x & leftValue,const specialNamespace::XM##type0##x & rightValue) \
	{ \
		return specialNamespace::XMLoad##type1##x(&leftValue)*specialNamespace::XMLoad##type1##x(&rightValue); \
	} \
	inline DirectX::XMVECTOR XM_CALLCONV operator *(const specialNamespace::XM##type0##x & leftValue,DirectX::FXMVECTOR rightValue) \
	{ \
		return specialNamespace::XMLoad##type1##x(&leftValue)*rightValue; \
	} \
	inline DirectX::XMVECTOR XM_CALLCONV operator *(DirectX::FXMVECTOR leftValue,const specialNamespace::XM##type0##x & rightValue) \
	{ \
		return leftValue*specialNamespace::XMLoad##type1##x(&rightValue); \
	}
#define BEGIN_VECTOR_CLASS(specialNamespace,type0,type1,x) \
	VECTOR_OPERATOR_FUNC(specialNamespace,type0,type1,x,==,EqualInt) \
	VECTOR_OPERATOR_FUNC(specialNamespace,type0,type1,x,!=,NotEqualInt) \
	VECTOR_OPERATOR_FUNC(specialNamespace,type0,type1,x,>,Greater) \
	VECTOR_OPERATOR_FUNC(specialNamespace,type0,type1,x,>=,GreaterOrEqual) \
	VECTOR_OPERATOR_FUNC(specialNamespace,type0,type1,x,<,Less) \
	VECTOR_OPERATOR_FUNC(specialNamespace,type0,type1,x,<=,LessOrEqual) \
	VECTOR_OPERATOR_FUNC2(specialNamespace,type0,type1,x) \
	class C##type1##x \
		:public specialNamespace::XM##type0##x \
	{ \
	public: \
		using specialNamespace::XM##type0##x::XM##type0##x; \
		using specialNamespace::XM##type0##x::operator=; \
		C##type1##x(DirectX::FXMVECTOR cpy) \
		{ \
			*this=cpy; \
		} \
		operator DirectX::XMVECTOR()const \
		{ \
			return specialNamespace::XMLoad##type1##x(this); \
		} \
		const C##type1##x & operator=(DirectX::FXMVECTOR src) \
		{ \
			specialNamespace::XMStore##type1##x(this,src); \
			return *this; \
		}
#define END_CLASS };
	BEGIN_VECTOR_CLASS(DirectX,INT,SInt,2)
	static const CSInt2 sZero;
	static const CSInt2 sOne;
	CSInt2(Int32 value)
		:DirectX::XMINT2(value,value)
	{}
	CSInt2(Int32 x,Int32 y)
		:DirectX::XMINT2(x,y)
	{}
	END_CLASS
	BEGIN_VECTOR_CLASS(DirectX,INT,SInt,3)
	static const CSInt3 sZero;
	static const CSInt3 sUnitX;
	static const CSInt3 sUnitY;
	static const CSInt3 sUnitZ;
	static const CSInt3 sOne;
	CSInt3(Int32 value)
		:DirectX::XMINT3(value,value,value)
	{}
	CSInt3(Int32 x,Int32 y,Int32 z)
		:DirectX::XMINT3(x,y,z)
	{}
	END_CLASS
	BEGIN_VECTOR_CLASS(DirectX,INT,SInt,4)
	CSInt4(Int32 value)
		:DirectX::XMINT4(value,value,value,value)
	{}
	CSInt4(Int32 x,Int32 y,Int32 z,Int32 w)
		:DirectX::XMINT4(x,y,z,w)
	{}
	CSInt4(const DirectX::XMINT3 & vec3,Int32 w)
		:DirectX::XMINT4(vec3.x,vec3.y,vec3.z,w)
	{}
	END_CLASS
#undef VECTOR_OPERATOR_FUNC
#undef VECTOR_OPERATOR_FUNC2
#undef BEGIN_VECTOR_CLASS
#undef END_CLASS
}
