#pragma once
namespace NSDevilX
{
	inline Boolean XM_CALLCONV operator==(DirectX::FXMMATRIX leftValue,DirectX::FXMMATRIX rightValue)
	{
		return DirectX::XMVector4Equal(leftValue.r[0],rightValue.r[0])
			&&DirectX::XMVector4Equal(leftValue.r[1],rightValue.r[1])
			&&DirectX::XMVector4Equal(leftValue.r[2],rightValue.r[2])
			&&DirectX::XMVector4Equal(leftValue.r[3],rightValue.r[3]);
	}
	inline Boolean XM_CALLCONV operator!=(DirectX::FXMMATRIX leftValue,DirectX::FXMMATRIX rightValue)
	{
		return DirectX::XMVector4NotEqual(leftValue.r[0],rightValue.r[0])
			&&DirectX::XMVector4NotEqual(leftValue.r[1],rightValue.r[1])
			&&DirectX::XMVector4NotEqual(leftValue.r[2],rightValue.r[2])
			&&DirectX::XMVector4NotEqual(leftValue.r[3],rightValue.r[3]);
	}
	// 	inline bool MatrixEqual(const DirectX::XMMATRIX & leftValue,const DirectX::XMMATRIX & rightValue)
	// 	{
	// 		return leftValue==rightValue;
	// 	}
	// 	inline bool MatrixNotEqual(const DirectX::XMMATRIX & leftValue,const DirectX::XMMATRIX & rightValue)
	// 	{
	// 		return leftValue!=rightValue;
	// 	}
#define BEGIN_MATRIX_CLASS(v) \
	class CMatrix##v##F \
		:public DirectX::XMFLOAT##v##X##v \
	{ \
	public: \
		static const CMatrix##v##F sIdentity; \
		CMatrix##v##F() \
		{ \
		} \
		CMatrix##v##F(const DirectX::XMMATRIX & cpy) \
		{ \
			*this=cpy; \
		} \
		operator DirectX::XMMATRIX()const \
		{ \
			return DirectX::XMLoadFloat##v##x##v(this); \
		} \
		const CMatrix##v##F & operator=(const DirectX::XMFLOAT##v##X##v & src) \
		{ \
			DirectX::XMStoreFloat##v##x##v(this,DirectX::XMLoadFloat##v##x##v(&src)); \
			return *this; \
		} \
		const CMatrix##v##F & operator=(const DirectX::XMMATRIX & src) \
		{ \
			DirectX::XMStoreFloat##v##x##v(this,src); \
			return *this; \
		}
#define END_CLASS };
	BEGIN_MATRIX_CLASS(4)
	END_CLASS
#undef BEGIN_VECTOR_CLASS
#undef END_CLASS
}