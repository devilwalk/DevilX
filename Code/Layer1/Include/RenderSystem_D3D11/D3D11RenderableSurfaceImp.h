#pragma once
#include "D3D11RenderTargetImp.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		namespace NSD3D11
		{
			class CRenderableSurfaceImp
				:public TBaseObject<CRenderableSurfaceImp>
				,public TInterfaceObject<IRenderableSurfaceImp>
				,public CRenderTargetImp
				,public CDirtyFlagContainer
			{
			public:
				enum EDirtyFlag
				{
					EDirtyFlag_Texture
				};
			protected:
				ID3D11Texture2D * mRenderTargetResource;
			public:
				CRenderableSurfaceImp(IRenderableSurfaceImp * interfaceImp);
				~CRenderableSurfaceImp();
				virtual ID3D11Texture2D * getRenderTargetResource() override
				{
					process(EDirtyFlag_Texture);
					return mRenderTargetResource;
				}
				// Í¨¹ý TInterfaceObject ¼Ì³Ð
				virtual Void onMessage(IRenderableSurfaceImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
				virtual Boolean _process(UInt32 flagIndex,OUT Bool & needNextProcess) override;
			};
		}
	}
}