#pragma once
#include "IRenderCamera.h"
#include "IRenderOverlay.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		class IViewport
		{
		protected:
			virtual ~IViewport(){}
		public:
			virtual IOverlay * queryInterface_IOverlay()const=0;
			virtual const String & getName()const=0;
			virtual Void setCamera(ICamera * camera)=0;
			virtual ICamera * getCamera()const=0;
			virtual Void setLeft(Float left)=0;
			virtual Float getLeft()const=0;
			virtual Void setTop(Float top)=0;
			virtual Float getTop()const=0;
			virtual Void setWidth(Float width)=0;
			virtual Float getWidth()const=0;
			virtual Void setHeight(Float height)=0;
			virtual Float getHeight()const=0;
			virtual Void setOrder(UInt32 order)=0;
			virtual UInt32 getOrder()const=0;
			virtual Void setTechnique(IEnum::ERenderTechnique technique)=0;
			virtual IEnum::ERenderTechnique getTechnique()const=0;
			virtual Void setClearColour(const CColour & colour)=0;
			virtual const CColour & getClearColour()const=0;
		};
	}
}