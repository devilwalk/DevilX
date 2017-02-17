#pragma once
#include "IRenderTarget.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		class IRenderableSurface
		{
		protected:
			virtual ~IRenderableSurface(){}
		public:
			virtual IRenderTarget * queryInterface_IRenderTarget()const=0;
			virtual const String & getName()const=0;
			virtual Void setSize(UInt32 width,UInt32 height)=0;
			virtual UInt32 getWidth()const=0;
			virtual UInt32 getHeight()const=0;
			virtual Void setFormat(IEnum::ERenderableSurfaceFormat format)=0;
			virtual IEnum::ERenderableSurfaceFormat getFormat()const=0;
		};
	}
}