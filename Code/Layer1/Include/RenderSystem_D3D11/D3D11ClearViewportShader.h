#pragma once
#include "D3D11Shader.h"
#include "D3D11ConstantBuffer.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		namespace NSD3D11
		{
			class CClearViewportShader
				:public TBaseObject<CClearViewportShader>
			{
			public:
				enum EType
				{
					EType_ColourOnly,
					EType_DepthOnly,
					EType_StencilOnly,
					EType_ColourAndDepth,
					EType_ColourAndStencil,
					EType_DepthAndStencil,
					EType_All
				};
				enum EDepthStencilStateType
				{
					EDepthStencilStateType_WriteDepthOnly,
					EDepthStencilStateType_WriteStencilOnly,
					EDepthStencilStateType_WriteAll,
					EDepthStencilStateType_Null,
					EDepthStencilStateType_Count
				};
				enum EBlendStateType
				{
					EBlendStateType_WriteColour,
					EBlendStateType_Null,
					EBlendStateType_Count
				};
			protected:
				CVertexShader * mVertexShader;
				CPixelShader * mPixelShader;
				ID3D11DepthStencilState * mDepthStencilState[EDepthStencilStateType_Count];
				ID3D11BlendState1 * mBlendState[EBlendStateType_Count];
				ID3D11RasterizerState1 * mRasterizerState;
			public:
				CClearViewportShader();
				~CClearViewportShader();
				CVertexShader * getVertexShader()const
				{
					return mVertexShader;
				}
				CPixelShader * getPixelShader()const
				{
					return mPixelShader;
				}
				ID3D11DepthStencilState * getDepthStencilState(EType type=EType_All)const
				{
					switch(type)
					{
					case EType_ColourOnly:
						return mDepthStencilState[EDepthStencilStateType_Null];
					case EType_ColourAndStencil:
					case EType_StencilOnly:
						return mDepthStencilState[EDepthStencilStateType_WriteStencilOnly];
					case EType_DepthOnly:
					case EType_ColourAndDepth:
						return mDepthStencilState[EDepthStencilStateType_WriteDepthOnly];
					case EType_DepthAndStencil:
					case EType_All:
						return mDepthStencilState[EDepthStencilStateType_WriteAll];
					}
					return mDepthStencilState[0];
				}
				ID3D11BlendState1 * getBlendState(EType type=EType_All)const
				{
					switch(type)
					{
					case NSDevilX::NSRenderSystem::NSD3D11::CClearViewportShader::EType_ColourOnly:
					case NSDevilX::NSRenderSystem::NSD3D11::CClearViewportShader::EType_ColourAndDepth:
					case NSDevilX::NSRenderSystem::NSD3D11::CClearViewportShader::EType_ColourAndStencil:
					case NSDevilX::NSRenderSystem::NSD3D11::CClearViewportShader::EType_All:
						return mBlendState[EBlendStateType_WriteColour];
					case NSDevilX::NSRenderSystem::NSD3D11::CClearViewportShader::EType_DepthOnly:
					case NSDevilX::NSRenderSystem::NSD3D11::CClearViewportShader::EType_StencilOnly:
					case NSDevilX::NSRenderSystem::NSD3D11::CClearViewportShader::EType_DepthAndStencil:
						return mBlendState[EBlendStateType_Null];
					}
					return mBlendState[0];
				}
				ID3D11RasterizerState1 * getRasterizerState()const
				{
					return mRasterizerState;
				}
			protected:
				ID3DBlob * _generateVertexShaderCode()const;
				ID3DBlob * _generatePixelShaderCode()const;
				Void _generateDepthStencilState(EDepthStencilStateType type);
				Void _generateBlendState(EBlendStateType type);
				Void _generateRasterizerState();
			};
		}
	}
}