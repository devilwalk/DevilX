#pragma once
#include "GL4RenderTarget.h"
#include "GL4DepthStencil.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		namespace NSGL4
		{
			class CRenderTargetImp
				:public TInternalObject<CRenderTarget>
			{
			protected:
				GLuint mRenderTargetResource;
				CDepthStencil * mDepthStencil;
				//TResourcePtrContainer<IViewportImp*const,CViewportImp> mViewports;
			public:
				CRenderTargetImp(GLuint rt);
				virtual ~CRenderTargetImp();
				decltype(mRenderTargetResource) getRenderTargetResource()const
				{
					return mRenderTargetResource;
				}
				GLuint getDepthStencil()const
				{
					return mDepthStencil->getInternal();
				}
				Void prepare();
				virtual Void render();
			};
			class CWindowImp
				:public TBaseObject<CWindowImp>
				,public TInterfaceObject<IWindowImp>
				,public CMessageNotifier
				,public CRenderTargetImp
			{
			public:
				enum EMessage
				{
					EMessage_BeginResize,
					EMessage_EndResize
				};
			protected:
				VoidPtr mDC;
			public:
				CWindowImp(IWindowImp * interfaceImp);
				~CWindowImp();
				decltype(mDC) getDC()const
				{
					return mDC;
				}
				virtual Void render() override;
			protected:
				virtual Void onMessage(IWindowImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
			};
		}
	}
}