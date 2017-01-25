#pragma once
#include "IUIEnum.h"
#include "IUIElement.h"
namespace NSDevilX
{
	namespace NSUISystem
	{
		class IGraphicWindow
		{
		protected:
			virtual ~IGraphicWindow(){}
		public:
			virtual IElement * queryInterface_IElement()const=0;
			virtual Void setImage(const CImage * img,DirectX::FXMVECTOR pixelStartVec=CSInt2::sZero,DirectX::FXMVECTOR pixelEndVec=CSInt2::sOne)=0;
			virtual Void setColour(const CColour & colour)=0;
			virtual const CColour & getColour()const=0;
		};
	}
}