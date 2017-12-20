#pragma once
#include "IRenderSceneElement.h"
#include "IRenderEnum.h"
#include "IRenderValueUnitState.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		class IDirectionLightProperty
		{
		protected:
			virtual ~IDirectionLightProperty(){}
		public:
			virtual const CFloat3 & getDirection()const=0;
		};
		class IPointLightProperty
		{
		protected:
			virtual ~IPointLightProperty(){}
		public:
			virtual Float getRange()const=0;
		};
		class ISpotLightProperty
		{
		protected:
			virtual ~ISpotLightProperty(){}
		public:
			virtual const CFloat3 & getDirection()const=0;
			virtual Float getRange()const=0;
			virtual void setAngle(const CDegree & angle)=0;
			virtual const CDegree & getAngle()const=0;
		};
		class ILight
		{
		protected:
			virtual ~ILight(){}
		public:
			virtual ISceneElement * queryInterface_ISceneElement()const=0;
			virtual IDirectionLightProperty * queryInterface_IDirectionLightProperty()const=0;
			virtual IPointLightProperty * queryInterface_IPointLightProperty()const=0;
			virtual ISpotLightProperty * queryInterface_ISpotLightProperty()const=0;
			virtual IEnum::ELightType getType()const=0;
			virtual IColourUnitState * getDiffuseColourUnitState()=0;
			virtual IColourUnitState * getSpecularColourUnitState()=0;
			virtual Void setShadowEnable(Bool enable)=0;
			virtual Bool getShadowEnable()const=0;
		};
	}
}