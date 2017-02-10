#pragma once
#include "IViewportImp.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		class IRenderTargetImp
			:public IRenderTarget
			,public CMessageNotifier
			,public TMessageReceiver<IViewportImp>
		{
		public:
			enum EMessage
			{
				EMessage_BeginViewportCreate,
				EMessage_EndViewportCreate,
				EMessage_BeginViewportDestroy,
				EMessage_EndViewportDestroy,
				EMessage_BeginClearColourChange,
				EMessage_EndClearColourChange
			};
			typedef TNamedIndexResourcePtrContainer<IViewportImp> Viewports;
			typedef TMap<UInt32,TSet<SizeT> > Orders;
		protected:
			Viewports mViewports;
			Orders mOrders;
			CColour mClearColour;
		public:
			IRenderTargetImp();
			virtual ~IRenderTargetImp();
			// Inherited via IRenderTarget
			virtual IViewport * createViewport(const String & name) override;
			virtual Void destroyViewport(IViewport * viewport) override;
			virtual IViewport * getViewport(const String & name) const override;
			virtual Void setClearColour(const CColour & colour) override;
			virtual const CColour & getClearColour() const override;

			// Inherited via TMessageReceiver
			virtual Void onMessage(IViewportImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
		};
	}
}