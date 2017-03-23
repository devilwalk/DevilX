#pragma once
#include "IUIEnum.h"
#include "IUIElement.h"
namespace NSDevilX
{
	namespace NSUISystem
	{
		class IGraphicScene;
		class IGraphicWindow
		{
		protected:
			virtual ~IGraphicWindow(){}
		public:
			virtual IElement * queryInterface_IElement()const=0;
			virtual IGraphicScene * getScene()const=0;
			virtual Void setTexture(NSRenderSystem::ITexture * texture,const CUInt2 & pixelStart,const CUInt2 & pixelEnd)=0;
			virtual NSRenderSystem::ITexture * getTexture()const=0;
			virtual const CUInt2 & getPixelStart()const=0;
			virtual const CUInt2 & getPixelEnd()const=0;
			virtual Void setColour(const CColour & colour)=0;
			virtual const CColour & getColour()const=0;
		};
	}
}