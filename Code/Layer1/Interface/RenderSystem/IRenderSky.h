#pragma once
#include "IRenderSceneElement.h"
#include "IRenderValueUnitState.h"
#include "IRenderTextureUnitState.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		class ISky
		{
		protected:
			virtual ~ISky(){}
		public:
			virtual ISceneElement * queryInterface_ISceneElement()const=0;
			virtual Void setGeometry(IGeometry * geometry)=0;
			virtual IGeometry * getGeometry()const=0;
			virtual Void setVisible(Bool visible)=0;
			virtual Bool getVisible()const=0;
			virtual Void setOrder(Int32 order)=0;
			virtual Int32 getOrder()const=0;
			virtual IColourUnitState * getColourUnitState()=0;
			virtual ITextureUnitState * getTextureUnitState()=0;
		};
	}
}