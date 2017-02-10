#pragma once
#include "IRenderTargetImp.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		class IRenderableSurfaceImp
			:public IRenderableSurface
			,public IRenderTargetImp
			,public TBaseObject<IRenderableSurfaceImp>
		{
		public:
			enum EMessage
			{
				EMessage_BeginSizeChange=EMessage_EndClearColourChange+1,
				EMessage_EndSizeChange,
				EMessage_BeginFormatChange,
				EMessage_EndFormatChange
			};
		protected:
			const String mName;
			UInt32 mWidth,mHeight;
			IEnum::ERenderableSurfaceFormat mFormat;
		public:
			IRenderableSurfaceImp(const String & name);
			~IRenderableSurfaceImp();

			// Í¨¹ý IRenderableSurface ¼Ì³Ð
			virtual IRenderTarget * queryInterface_IRenderTarget() const override;
			virtual const String & getName() const override;
			virtual Void setSize(UInt32 width,UInt32 height) override;
			virtual UInt32 getWidth() const override;
			virtual UInt32 getHeight() const override;
			virtual Void setFormat(IEnum::ERenderableSurfaceFormat format) override;
			virtual IEnum::ERenderableSurfaceFormat getFormat() const override;
		};
	}
}