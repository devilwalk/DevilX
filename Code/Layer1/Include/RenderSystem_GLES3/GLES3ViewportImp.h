#pragma once
#include "GLES3RenderTask.h"
#include "GLES3Viewport.h"
#include "GLES3Camera.h"
#include "GLES3OverlayManager.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		namespace NSGLES3
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