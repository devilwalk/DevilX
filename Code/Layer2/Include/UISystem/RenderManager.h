#pragma once
#include "IGraphicWindowImp.h"
#include "RenderRectangle.h"
namespace NSDevilX
{
	namespace NSUISystem
	{
		class CRenderManager
			:public TBaseObject<CRenderManager>
			,public TMessageReceiver<IGraphicWindowImp>
		{
		protected:
			NSRenderSystem::IViewport * const mViewport;
			NSRenderSystem::IRenderableObject * mRenderableObject;
			NSRenderSystem::IVisibleArea * mVisibleArea;
		public:
			CRenderManager(NSRenderSystem::IViewport * vp);
			~CRenderManager();
			NSRenderSystem::IViewport * getViewport()const
			{
				return mViewport;
			}
			NSRenderSystem::IRenderableObject * getRenderableObject()const
			{
				return mRenderableObject;
			}
			Void addImageWindow(IGraphicWindowImp * window);
			Void removeImageWindow(IGraphicWindowImp * window);

			// Í¨¹ý TMessageReceiver ¼Ì³Ð
			virtual Void onMessage(IGraphicWindowImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
		};
	}
}