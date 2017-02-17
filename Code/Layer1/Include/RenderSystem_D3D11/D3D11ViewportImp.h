#pragma once
#include "D3D11RenderTask.h"
#include "D3D11Viewport.h"
#include "D3D11Camera.h"
#include "D3D11OverlayManager.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		namespace NSD3D11
		{
			class CRenderTargetImp;
			class CWindowImp;
			class CViewportImp
				:public TBaseObject<CViewportImp>
				,public TInterfaceObject<IViewportImp>
				,public TInternalObject<CViewport>
				,public CDirtyFlagContainer
				,public TMessageReceiver<CWindowImp>
			{
			public:
				enum EDirtyFlag
				{
					EDirtyFlag_Size
				};
			protected:
				CRenderTargetImp * const mRenderTarget;
				CCamera * mCamera;
				CRenderTask * mTask;
				COverlayManager * mOverlayManager;
			public:
				CViewportImp(IViewportImp * interfaceImp);
				~CViewportImp();
				CRenderTargetImp * getRenderTarget()const
				{
					return mRenderTarget;
				}
				CCamera * getCamera()const
				{
					return mCamera;
				}
				COverlayManager * getOverlayManager()const
				{
					return mOverlayManager;
				}
				Void prepare();
				Void render();
				// Inherited via TInterfaceObject
				virtual Void onMessage(IViewportImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
				virtual Void onMessage(CWindowImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
				virtual Boolean _process(UInt32 flagIndex,OUT Bool & needNextProcess) override;
			protected:
				Void _updateInternal();
				Void _updateRenderTask();
			};
		}
	}
}