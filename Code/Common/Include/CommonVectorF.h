#pragma once
#include "CommonVector.h"
namespace NSDevilX
{
#define VECTOR_OPERATOR_FUNC(specialNamespace,type0,type1,x,op,func) \
	inline Boolean operator op(const specialNamespace::XM##type0##x & leftValue,const specialNamespace::XM##type0##x & rightValue) \
	{ \
		return DirectX::XMVector##x##func(specialNamespace::XMLoad##type1##x(&leftValue),specialNamespace::XMLoad##type1##x(&rightValue)); \
	} \
	inline Boolean XM_CALLCONV operator op(const specialNamespace::XM##type0##x & leftValue,DirectX::FXMVECTOR rightValue) \
	{ \
		return DirectX::XMVector##x##func(specialNamespace::XMLoad##type1##x(&leftValue),rightValue); \
	} \
	inline Boolean XM_CALLCONV operator op(DirectX::FXMVECTOR leftValue,const specialNamespace::XM##type0##x & rightValue) \
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
	} \
	inline DirectX::XMVECTOR operator /(const specialNamespace::XM##type0##x & leftValue,const specialNamespace::XM##type0##x & rightValue) \
	{ \
		return specialNamespace::XMLoad##type1##x(&leftValue)/specialNamespace::XMLoad##type1##x(&rightValue); \
	} \
	inline DirectX::XMVECTOR XM_CALLCONV operator /(const specialNamespace::XM##type0##x & leftValue,DirectX::FXMVECTOR rightValue) \
	{ \
		return specialNamespace::XMLoad##type1##x(&leftValue)/rightValue; \
	} \
	inline DirectX::XMVECTOR XM_CALLCONV operator /(DirectX::FXMVECTOR leftValue,const specialNamespace::XM##type0##x & rightValue) \
	{ \
		return leftValue/specialNamespace::XMLoad##type1##x(&rightValue); \
	}
#define BEGIN_VECTOR_CLASS(specialNamespace,type0,type1,x) \
	VECTOR_OPERATOR_FUNC(specialNamespace,type0,type1,x,==,Equal) \
	VECTOR_OPERATOR_FUNC(specialNamespace,type0,type1,x,!=,NotEqual) \
	VECTOR_OPERATOR_FUNC(specialNamespace,type0,type1,x,>,Greater) \
	VECTOR_OPERATOR_FUNC(specialNamespace,type0,type1,x,>=,GreaterOrEqual) \
	VECTOR_OPERATOR_FUNC(specialNamespace,type0,type1,x,<,Less) \
	VECTOR_OPERATOR_FUNC(specialNamespace,type0,type1,x,<=,LessOrEqual) \
	VECTOR_OPERATOR_FUNC2(specialNamespace,type0,type1,x) \
	class C##type1##x \
		:public specialNamespace::XM##type0##x \
	{ \
	public: \
		static const C##type1##x sZero; \
		static const C##type1##x sOne; \
		using specialNamespace::XM##type0##x::XM##type0##x; \
		using specialNamespace::XM##type0##x::operator=; \
		C##type1##x(const specialNamespace::XM##type0##x & cpy) \
			:specialNamespace::XM##type0##x(cpy) \
		{ } \
		C##type1##x(DirectX::FXMVECTOR cpy) \
		{ \
			*this=cpy; \
		} \
		C##type1##x(const DirectX::XMINT##x & value) \
		{ \
			*this=value; \
		} \
		C##type1##x(const DirectX::XMUINT##x & value) \
		{ \
			*this=value; \
		} \
		operator DirectX::XMVECTOR()const \
		{ \
			return specialNamespace::XMLoad##type1##x(this); \
		} \
		const C##type1##x & operator=(DirectX::FXMVECTOR src) \
		{ \
			specialNamespace::XMStore##type1##x(this,src); \
			return *this; \
		} \
		const C##type1##x & operator=(const DirectX::XMINT##x & value) \
		{ \
			*this=DirectX::XMConvertVectorIntToFloat(DirectX::XMLoadSInt##x(&value),0); \
			return *this; \
		} \
		const C##type1##x & operator=(const DirectX::XMUINT##x & value) \
		{ \
			*this=DirectX::XMConvertVectorUIntToFloat(DirectX::XMLoadUInt##x(&value),0); \
			return *this; \
		} \
		const C##type1##x & operator+=(DirectX::FXMVECTOR value) \
		{ \
			*this=*this+value; \
			return *this; \
		} \
		const C##type1##x & operator-=(DirectX::FXMVECTOR value) \
		{\
			*this=*this-value; \
			return *this; \
		}
#define END_CLASS };
	BEGIN_VECTOR_CLASS(DirectX,FLOAT,Float,2)
	static const CFloat2 sUnitX;
	static const CFloat2 sUnitY;
	CFloat2(Float value=0.0f)
		:DirectX::XMFLOAT2(value,value)
	{}
	CFloat2(float x,float y)
		:DirectX::XMFLOAT2(x,y)
	{ }
	Void normalize()
	{
		*this=DirectX::XMVector2Normalize(*this);
	}
	END_CLASS
	BEGIN_VECTOR_CLASS(DirectX,FLOAT,Float,3)
	static const CFloat3 sUnitX;
	static const CFloat3 sUnitY;
	static const CFloat3 sUnitZ;
	CFloat3(Float value=0.0f)
		:DirectX::XMFLOAT3(value,value,value)
	{
	}
	CFloat3(float x,float y,float z)
		:DirectX::XMFLOAT3(x,y,z)
	{
	}
	Void normalize()
	{
		*this=DirectX::XMVector3Normalize(*this);
	}
	END_CLASS
	BEGIN_VECTOR_CLASS(DirectX,FLOAT,Float,4)
	static const CFloat4 sIdentityQuaternion;
	CFloat4(Float value=0.0f)
		:DirectX::XMFLOAT4(value,value,value,value)
	{
	}
	CFloat4(float x,float y,float z,float w)
		:DirectX::XMFLOAT4(x,y,z,w)
	{
	}
	CFloat4(const DirectX::XMFLOAT3 & vec3,Float w)
		:DirectX::XMFLOAT4(vec3.x,vec3.y,vec3.z,w)
	{
	}
	CFloat4(const DirectX::XMFLOAT2 & xy,const DirectX::XMFLOAT2 & zw)
		:DirectX::XMFLOAT4(xy.x,xy.y,zw.x,zw.y)
	{}
	Void normalize()
	{
		*this=DirectX::XMVector4Normalize(*this);
	}
	Float & operator[](SizeT index)
	{
		switch(index)
		{
		case 0:return x;
		case 1:return y;
		case 2:return z;
		case 3:return w;
		default:
			assert(false);
			return x;
		}
	}
	const Float & operator[](SizeT index)const
	{
		switch(index)
		{
		case 0:return x;
		case 1:return y;
		case 2:return z;
		case 3:return w;
		default:
			assert(false);
			return x;
		}
	}
	END_CLASS
	BEGIN_VECTOR_CLASS(DirectX::PackedVector,HALF,Half,2)
	CHalf2(Float value=0.0f)
		:DirectX::PackedVector::XMHALF2(value,value)
	{}
	CHalf2(Float x,Float y)
		:DirectX::PackedVector::XMHALF2(x,y)
	{}
	CHalf2(DirectX::PackedVector::HALF value)
		:DirectX::PackedVector::XMHALF2(value,value)
	{}
	CHalf2(DirectX::PackedVector::HALF x,DirectX::PackedVector::HALF y)
		:DirectX::PackedVector::XMHALF2(x,y)
	{}
	END_CLASS
	BEGIN_VECTOR_CLASS(DirectX::PackedVector,HALF,Half,4)
	CHalf4(Float value=0.0f)
		:DirectX::PackedVector::XMHALF4(value,value,value,value)
	{
	}
	CHalf4(Float x,Float y,Float z,Float w)
		:DirectX::PackedVector::XMHALF4(x,y,z,w)
	{
	}
	CHalf4(DirectX::PackedVector::HALF value)
		:DirectX::PackedVector::XMHALF4(value,value,value,value)
	{}
	CHalf4(DirectX::PackedVector::HALF x,DirectX::PackedVector::HALF y,DirectX::PackedVector::HALF z,DirectX::PackedVector::HALF w)
		:DirectX::PackedVector::XMHALF4(x,y,z,w)
	{}
	CHalf4(const DirectX::XMFLOAT3 & vec3,Float w)
		:DirectX::PackedVector::XMHALF4(vec3.x,vec3.y,vec3.z,w)
	{
	}
	END_CLASS
#undef VECTOR_OPERATOR_FUNC
#undef VECTOR_OPERATOR_FUNC2
#undef BEGIN_VECTOR_CLASS
#undef END_CLASS
}
