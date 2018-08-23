#pragma once
#include "D3D11Shader.h"
#include "D3D11Texture.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		namespace NSD3D11
		{
			class CPass
			{
			protected:
				CVertexShader * mVertexShader;
				CHullShader * mHullShader;
				CDomainShader * mDomainShader;
				CPixelShader * mPixelShader;
				ID3D11RasterizerState1 * mRasterizerState;
				ID3D11BlendState1 * mBlendState;
				ID3D11DepthStencilState * mDepthState;
				TVector(CTexture*) mVSTextures;
				TVector(CTexture*) mHSTextures;
				TVector(CTexture*) mDSTextures;
				TVector(CTexture*) mPSTextures;
				TVector(ID3D11SamplerState*) mVSSamplerStates;
				TVector(ID3D11SamplerState*) mHSSamplerStates;
				TVector(ID3D11SamplerState*) mDSSamplerStates;
				TVector(ID3D11SamplerState*) mPSSamplerStates;
			public:
				CPass();
				virtual ~CPass();
				CVertexShader * getVertexShader()const
				{
					return mVertexShader;
				}
				CPixelShader * getPixelShader()const
				{
					return mPixelShader;
				}
				ID3D11RasterizerState1 * getRasterizerState()const
				{
					return mRasterizerState;
				}
				ID3D11BlendState1 * getBlendState()const
				{
					return mBlendState;
				}
				ID3D11DepthStencilState * getDepthStencilState()const
				{
					return mDepthState;
				}
				decltype(mVSTextures) const & getVSTextures()const
				{
					return mVSTextures;
				}
				decltype(mVSSamplerStates) const & getVSSamplerStates()const
				{
					return mVSSamplerStates;
				}
				decltype(mHSTextures) const & getHSTextures()const
				{
					return mHSTextures;
				}
				decltype(mHSSamplerStates) const & getHSSamplerStates()const
				{
					return mHSSamplerStates;
				}
				decltype(mDSTextures) const & getDSTextures()const
				{
					return mDSTextures;
				}
				decltype(mDSSamplerStates) const & getDSSamplerStates()const
				{
					return mDSSamplerStates;
				}
				decltype(mPSTextures) const & getPSTextures()const
				{
					return mPSTextures;
				}
				decltype(mPSSamplerStates) const & getPSSamplerStates()const
				{
					return mPSSamplerStates;
				}
			};
		}
	}
}