#pragma once
#include "CommonType.h"
namespace NSDevilX
{
	using DirectX::operator+;
	using DirectX::operator-;
	using DirectX::operator*;
	using DirectX::operator/;
	using DirectX::operator+=;
	using DirectX::operator-=;
	using DirectX::operator*=;
	using DirectX::operator/=;
	inline DirectX::XMVECTOR XM_CALLCONV operator %(DirectX::FXMVECTOR leftValue,DirectX::FXMVECTOR rightValue)
	{
		return DirectX::XMVectorMod(leftValue,rightValue);
	}
	//scalar operator
#define VECTOR_OPERATOR_FUNC(type0,type1,type2,type3) \
	inline DirectX::XMVECTOR XM_CALLCONV operator +(DirectX::FXMVECTOR leftValue,type1 rightValue) \
	{ \
		return leftValue+DirectX::XMLoad##type0##4(reinterpret_cast<type3*>(&DirectX::XM##type2##4(rightValue,rightValue,rightValue,rightValue))); \
	} \
	inline DirectX::XMVECTOR XM_CALLCONV operator +(type1 leftValue,DirectX::FXMVECTOR rightValue) \
	{ \
		return rightValue+leftValue; \
	} \
	inline DirectX::XMVECTOR XM_CALLCONV operator -(DirectX::FXMVECTOR leftValue,type1 rightValue) \
	{ \
		return leftValue-DirectX::XMLoad##type0##4(reinterpret_cast<type3*>(&DirectX::XM##type2##4(rightValue,rightValue,rightValue,rightValue))); \
	} \
	inline DirectX::XMVECTOR XM_CALLCONV operator -(type1 leftValue,DirectX::FXMVECTOR rightValue) \
	{ \
		return DirectX::XMLoad##type0##4(reinterpret_cast<type3*>(&DirectX::XM##type2##4(leftValue,leftValue,leftValue,leftValue)))-rightValue; \
	} \
	inline DirectX::XMVECTOR XM_CALLCONV operator /(type1 leftValue,DirectX::FXMVECTOR rightValue) \
	{ \
		return DirectX::XMLoad##type0##4(reinterpret_cast<type3*>(&DirectX::XM##type2##4(leftValue,leftValue,leftValue,leftValue)))/rightValue; \
	} \
	inline DirectX::XMVECTOR XM_CALLCONV operator %(DirectX::FXMVECTOR leftValue,type1 rightValue) \
	{ \
		return leftValue%DirectX::XMLoad##type0##4(reinterpret_cast<type3*>(&DirectX::XM##type2##4(rightValue,rightValue,rightValue,rightValue))); \
	} \
	inline DirectX::XMVECTOR XM_CALLCONV operator %(type1 leftValue,DirectX::FXMVECTOR rightValue) \
	{ \
		return DirectX::XMLoad##type0##4(reinterpret_cast<type3*>(&DirectX::XM##type2##4(leftValue,leftValue,leftValue,leftValue)))%rightValue; \
	}
	VECTOR_OPERATOR_FUNC(Float,Float,FLOAT,DirectX::XMFLOAT4)
	VECTOR_OPERATOR_FUNC(Int,Int32,INT,UInt32)
	VECTOR_OPERATOR_FUNC(Int,UInt32,UINT,UInt32)
#undef VECTOR_OPERATOR_FUNC
#define VECTOR_OPERATOR_FUNC(type0,type1,type2,type3) \
	inline DirectX::XMVECTOR XM_CALLCONV operator *(DirectX::FXMVECTOR leftValue,type1 rightValue) \
	{ \
		return leftValue*DirectX::XMLoad##type0##4(reinterpret_cast<type3*>(&DirectX::XM##type2##4(rightValue,rightValue,rightValue,rightValue))); \
	} \
	inline DirectX::XMVECTOR XM_CALLCONV operator *(type1 leftValue,DirectX::FXMVECTOR rightValue) \
	{ \
		return rightValue*leftValue; \
	}
	VECTOR_OPERATOR_FUNC(Int,Int32,INT,UInt32)
	VECTOR_OPERATOR_FUNC(Int,UInt32,UINT,UInt32)
#undef VECTOR_OPERATOR_FUNC
}