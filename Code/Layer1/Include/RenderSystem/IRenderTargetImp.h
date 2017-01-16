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
			UInt32 mWidth,mHeight;
			Viewports mViewports;
			Orders mOrders;
			CColour mClearColour;
		public:
			IRenderTargetImp();
			virtual ~IRenderTargetImp();
			Void setSize(UInt32 width,UInt32 height)
			{
				mWidth=width;
				mHeight=height;
			}
			// Inherited via IRenderTarget
			virtual UInt32 getWidth() const override;
			virtual UInt32 getHeight() const override;
			virtual IViewport * createViewport(const String & name) override;
			virtual Void destroyViewport(IViewport * viewport) override;
			virtual IViewport * getViewport(const String & name) const override;
			virtual Void setClearColour(const CColour & colour) override;
			virtual const CColour & getClearColour() const override;

			// Inherited via TMessageReceiver
			virtual Void onMessage(IViewportImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
		};
		class IWindowImp
			:public IWindow
			,public IRenderTargetImp
			,public TBaseObject<IWindowImp>
		{
		public:
			enum EMessage
			{
				EMessage_Resize=EMessage_EndClearColourChange+1,
			};
		protected:
			const VoidPtr mHandle;
		public:
			IWindowImp(VoidPtr handle);
			~IWindowImp();
			VoidPtr getHandle()const
			{
				return mHandle;
			}
			// Inherited via IWindow
			virtual IRenderTarget * queryInterface_IRenderTarget() const override;
			virtual Void resize() override;
		};
	}
}