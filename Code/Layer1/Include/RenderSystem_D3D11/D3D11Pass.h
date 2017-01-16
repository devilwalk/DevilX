#pragma once
#include "D3D11Shader.h"
#include "D3D11Texture.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		namespace NSD3D11
		{
			class CTechnique;
			class CPass
				:public TBaseObject<CPass>
				,public TMessageReceiver<IMaterialImp>
				,public TMessageReceiver<IRenderableImp>
				,public TMessageReceiver<IGeometryImp>
				,public TMessageReceiver<ITextureUnitStateImp>
			{
			protected:
				CEnum::EForwardPassType const mForwardType;
				CTechnique * const mTechnique;
				CVertexShader * mVertexShader;
				CPixelShader * mPixelShader;
				ID3D11RasterizerState1 * mRasterizerState;
				ID3D11BlendState1 * mBlendState;
				ID3D11DepthStencilState * mDepthState;
				TVector<CTexture*> mVSTextures;
				TVector<CTexture*> mPSTextures;
				TVector<ID3D11SamplerState*> mVSSamplerStates;
				TVector<ID3D11SamplerState*> mPSSamplerStates;
			public:
				CPass(CTechnique * technique);
				CPass(CEnum::EForwardPassType type,CTechnique * technique);
				~CPass();
				CEnum::EForwardPassType getForwardType()const
				{
					return mForwardType;
				}
				CTechnique * getTechnique()const
				{
					return mTechnique;
				}
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
				decltype(mPSTextures) const & getPSTextures()const
				{
					return mPSTextures;
				}
				decltype(mPSSamplerStates) const & getPSSamplerStates()const
				{
					return mPSSamplerStates;
				}

				// Í¨¹ý TMessageReceiver ¼Ì³Ð
				virtual Void onMessage(IMaterialImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
				virtual Void onMessage(IRenderableImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
				virtual Void onMessage(IGeometryImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
				virtual Void onMessage(ITextureUnitStateImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
			protected:
				Void _updateShader();
				Void _updateTextures();
				Void _updateRasterizerState();
				Void _updateBlendState();
				Void _updateDepthStencilState();
				Void _registerToIGeometryImp();
				Void _unregisterToIGeometryImp();
			};
		}
	}
}