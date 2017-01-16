#pragma once
#include "GL4RenderTask.h"
#include "GL4Viewport.h"
#include "GL4Camera.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		namespace NSGL4
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