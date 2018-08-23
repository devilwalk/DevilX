#pragma once
#include "D3D11OverlayRenderable.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		namespace NSD3D11
		{
			class CViewportImp;
			class COverlayManager
				:public TBaseObject<COverlayManager>
				,public TMessageReceiver<IViewportImp>
				,public TMessageReceiver<IOverlayElementImp>
				,public TMessageReceiver<ITextureUnitStateImp>
			{
			protected:
				CViewportImp * const mViewport;
				TMap(Int32,TResourcePtrList(COverlayRenderable)) mRenderables;
			public:
				COverlayManager(CViewportImp * viewport);
				~COverlayManager();
				CViewportImp * getViewport()const
				{
					return mViewport;
				}
				Void render();
				// Í¨¹ý TMessageReceiver ¼Ì³Ð
				virtual Void onMessage(IViewportImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
				virtual Void onMessage(IOverlayElementImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
				virtual Void onMessage(ITextureUnitStateImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
			protected:
				COverlayRenderable * _getRenderable(IOverlayElementImp * element);
			};
		}
	}
}