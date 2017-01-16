#pragma once
#include "IRenderColourUnitState.h"
#include "IRenderTextureUnitState.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		class IMaterial
		{
		protected:
			virtual ~IMaterial(){ }
		public:
			virtual IColourUnitState * getColourUnitState(IEnum::EColourUnitStateType type)=0;
			virtual ITextureUnitState * getTextureUnitState(IEnum::ETextureUnitStateType type)=0;
			virtual Void setLightEnable(Bool enable)=0;
			virtual Bool getLightEnable()const=0;
			virtual Void setAlphaTestValue(Float alpha)=0;
			virtual Float getAlphaTestValue()const=0;
			virtual Void setTransparentEnable(Bool enable)=0;
			virtual Bool getTransparentEnable()const=0;
		};
	}
}