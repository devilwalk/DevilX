#pragma once
#include "D3D11VertexBufferImp.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		namespace NSD3D11
		{
			class CShader
			{
			protected:
				ID3DBlob * const mCode;
				TMap(const String,UInt32) mResourceSlots;
			public:
				CShader(ID3DBlob * code);
				virtual ~CShader();
				ID3DBlob * getBlob()const
				{
					return mCode;
				}
				UInt32 getSlot(const String & name)const;
			};
			class CVertexShader
				:public CShader
				,public TBaseObject<CVertexShader>
				,public TCOMInternalObject<ID3D11VertexShader>
			{
			protected:
				ID3D11InputLayout * mInputLayout;
				TVector(D3D11_INPUT_ELEMENT_DESC) mInputElementDescs;
				UInt8 mInputSlots[CEnum::EVertexBufferType_Count];
			public:
				CVertexShader(ID3DBlob * code);
				~CVertexShader();
				ID3D11InputLayout * getInputLayout()const
				{
					return mInputLayout;
				}
				decltype(mInputElementDescs) const & getInputElementDescs()const
				{
					return mInputElementDescs;
				}
				decltype(mInputSlots) const & getInputSlots()const
				{
					return mInputSlots;
				}
			};
			class CPixelShader
				:public CShader
				,public TBaseObject<CPixelShader>
				,public TCOMInternalObject<ID3D11PixelShader>
			{
			public:
				CPixelShader(ID3DBlob * code);
				~CPixelShader();
			};
		}
	}
}