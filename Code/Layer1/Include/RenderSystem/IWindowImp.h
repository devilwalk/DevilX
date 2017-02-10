#pragma once
#include "IRenderTargetImp.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
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
			virtual UInt32 getWidth() const override;
			virtual UInt32 getHeight() const override;
			virtual Void resize() override;
		};
	}
}