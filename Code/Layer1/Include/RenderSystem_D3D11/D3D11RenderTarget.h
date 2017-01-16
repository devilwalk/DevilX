#pragma once
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		namespace NSD3D11
		{
			class CRenderTarget
				:public TBaseObject<CRenderTarget>
				,public CConstantBufferContainer
			{
			protected:
				ID3D11RenderTargetView * mRenderTargets[8];
				ID3D11DepthStencilView * mDepthStencil;
			public:
				CRenderTarget();
				~CRenderTarget();
				Void getSize(UInt32 & width,UInt32 & height);
				Void setRTView(UInt32 index,ID3D11RenderTargetView * view);
				ID3D11RenderTargetView * getRTView(UInt32 index)const
				{
					return mRenderTargets[index];
				}
				Void setDSView(ID3D11DepthStencilView * view);
				ID3D11DepthStencilView * getDSView()const
				{
					return mDepthStencil;
				}
				Void clearMT(UInt32 index,ID3D11DeviceContext1 * context,const CColour & colour);
				Void clearMT(ID3D11DeviceContext1 * context,Float depth,Int32 stencil);
				Void setupMT(ID3D11DeviceContext1 * context);
			protected:
				// Inherited via CConstantBufferContainer
				virtual Void _updateConstantBuffer(Byte * buffer) override;
			};
		}
	}
}