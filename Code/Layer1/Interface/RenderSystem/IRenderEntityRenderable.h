#pragma once
#include "IRenderGeometry.h"
#include "IRenderGeometryUsage.h"
#include "IRenderColourUnitState.h"
#include "IRenderTextureUnitState.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		class IEntity;
		class IEntityRenderable
		{
		protected:
			virtual ~IEntityRenderable(){}
		public:
			virtual const String & getName()const=0;
			virtual IEntity * getEntity()const=0;
			virtual IGeometryUsage * queryInterface_IGeometryUsage()const=0;
			virtual Void setGeometry(IGeometry * geometry)=0;
			virtual IGeometry * getGeometry()const=0;
			virtual Void setVisible(Bool visible)=0;
			virtual Bool getVisible()const=0;
			virtual IColourUnitState * getColourUnitState(IEnum::EEntityColourUnitStateType type)=0;
			virtual ITextureUnitState * getTextureUnitState(IEnum::EEntityTextureUnitStateType type)=0;
			virtual Void setLightEnable(Bool enable)=0;
			virtual Bool getLightEnable()const=0;
			virtual Void setAlphaTestValue(Float alpha)=0;
			virtual Float getAlphaTestValue()const=0;
			virtual Void setTransparentEnable(Bool enable)=0;
			virtual Bool getTransparentEnable()const=0;
		};
	}
}