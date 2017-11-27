#pragma once
#include "IRenderEnum.h"
#include "IRenderColourUnitState.h"
#include "IRenderTextureUnitState.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		class ICommonMaterial
		{
		protected:
			virtual ~ICommonMaterial(){}
		public:
			virtual IColourUnitState * getColourUnitState(IEnum::ECommonMaterialColourStateType type)=0;
			virtual ITextureUnitState * getTextureUnitState()=0;
		};
		class ILightMaterial
		{
		protected:
			virtual ~ILightMaterial(){}
		public:
			virtual IColourUnitState * getColourUnitState(IEnum::ELightMaterialColourStateType type)=0;
			virtual ITextureUnitState * getTextureUnitState(IEnum::ELightMaterialTextureUnitStateType type)=0;
		};
		class IPhysicalBasedLightMaterial
		{
		protected:
			virtual ~IPhysicalBasedLightMaterial(){}
		public:
			virtual Void setMetallic(Float value)=0;
			virtual Float getMetallic()const=0;
			virtual Void setRoughness(Float Value)=0;
			virtual Float getRoughness()const=0;
			virtual ITextureUnitState * getTextureUnitState(IEnum::EPhysicalBasedLightMaterialTextureUnitStateType type)=0;
		};
	}
}