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
	inline DirectX::XMVECTOR XM_CALLCONV operator ==(DirectX::FXMVECTOR leftValue,DirectX::FXMVECTOR rightValue)
	{
		return DirectX::XMVectorEqual(leftValue,rightValue);
	}
	inline DirectX::XMVECTOR XM_CALLCONV operator !=(DirectX::FXMVECTOR leftValue,DirectX::FXMVECTOR rightValue)
	{
		return DirectX::XMVectorNotEqual(leftValue,rightValue);
	}
	inline DirectX::XMVECTOR XM_CALLCONV operator >(DirectX::FXMVECTOR leftValue,DirectX::FXMVECTOR rightValue)
	{
		return DirectX::XMVectorGreater(leftValue,rightValue);
	}
	inline DirectX::XMVECTOR XM_CALLCONV operator <(DirectX::FXMVECTOR leftValue,DirectX::FXMVECTOR rightValue)
	{
		return DirectX::XMVectorLess(leftValue,rightValue);
	}
	inline DirectX::XMVECTOR XM_CALLCONV operator >=(DirectX::FXMVECTOR leftValue,DirectX::FXMVECTOR rightValue)
	{
		return DirectX::XMVectorGreaterOrEqual(leftValue,rightValue);
	}
	inline DirectX::XMVECTOR XM_CALLCONV operator <=(DirectX::FXMVECTOR leftValue,DirectX::FXMVECTOR rightValue)
	{
		return DirectX::XMVectorLessOrEqual(leftValue,rightValue);
	}
	inline DirectX::XMVECTOR XM_CALLCONV operator %(DirectX::FXMVECTOR leftValue,DirectX::FXMVECTOR rightValue)
	{
		return DirectX::XMVectorMod(leftValue,rightValue);
	}
}