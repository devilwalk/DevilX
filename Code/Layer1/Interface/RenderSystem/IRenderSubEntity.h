#pragma once
#include "IRenderGeometry.h"
#include "IRenderGeometryUsage.h"
#include "IRenderBuffer.h"
#include "IRenderBufferUsage.h"
#include "IRenderValueUnitState.h"
#include "IRenderTextureUnitState.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		class IEntity;
		class ISubEntity
		{
		protected:
			virtual ~ISubEntity(){}
		public:
			virtual IGeometryUsage * queryInterface_IGeometryUsage()const=0;
			virtual const String & getName()const=0;
			virtual IEntity * getEntity()const=0;
			virtual Void setRenderable(Bool renderable)=0;
			virtual Bool isRenderable()const=0;
			virtual Void setQueriable(Bool queriable)=0;
			virtual Bool isQueriable()const=0;
			virtual Void setGeometry(IGeometry * geometry)=0;
			virtual IGeometry * getGeometry()const=0;
			virtual Void setQueryBuffer(IBuffer * buffer)=0;
			virtual IBuffer * getQueryBuffer()const=0;
			virtual IBufferUsage * getQueryBufferUsage()const=0;
			virtual Void setVisible(Bool visible)=0;
			virtual Bool getVisible()const=0;
			virtual Void setAmbientModel(IEnum::EMaterialAmbientModel model)=0;
			virtual IEnum::EMaterialAmbientModel getAmbientModel()const=0;
			virtual Void setDiffuseModel(IEnum::EMaterialDiffuseModel model)=0;
			virtual IEnum::EMaterialDiffuseModel getDiffuseModel()const=0;
			virtual Void setSpecularModel(IEnum::EMaterialSpecularModel model)=0;
			virtual IEnum::EMaterialSpecularModel getSpecularModel()const=0;
			virtual IColourUnitState * getAlphaColourUnitState()=0;
			virtual IColourUnitState * getEmissiveColourUnitState()=0;
			virtual IColourUnitState * getDiffuseColourUnitState()=0;
			virtual IColourUnitState * getSpecularColourUnitState()=0;
			virtual ITextureUnitState * getDiffuseTextureUnitState()=0;
			virtual ITextureUnitState * getSpecularTextureUnitState()=0;
			virtual ITextureUnitState * getNormalTextureUnitState()=0;
			virtual IFloatUnitState * getMetallicUnitState()=0;
			virtual IFloatUnitState * getRoughnessUnitState()=0;
			virtual IFloatUnitState * getSpecularPowerUnitState()=0;
			virtual Void setAlphaTestValue(Float alpha)=0;
			virtual Float getAlphaTestValue()const=0;
			virtual Void setTransparentEnable(Bool enable)=0;
			virtual Bool getTransparentEnable()const=0;
		};
	}
}