#pragma once
#include "IRenderEnum.h"
#include "IRenderTexture.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		class ITextureUnitState
		{
		protected:
			virtual ~ITextureUnitState(){}
		public:
			virtual IEnum::ETextureUnitStateType getType()const=0;
			virtual Void setTexture(ITexture * texture)=0;
			virtual ITexture * getTexture()const=0;
		};
	}
}