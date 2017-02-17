#pragma once
#include "IRenderTextureUnitState.h"
#include "IRenderColourUnitState.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		class IOverlayElement
		{
		protected:
			virtual ~IOverlayElement(){}
		public:
			virtual const String & getName()const=0;
			virtual Void setPosition(const CFloat2 & position)=0;
			virtual const CFloat2 & getPosition()const=0;
			virtual Void setSize(const CFloat2 & size)=0;
			virtual const CFloat2 & getSize()const=0;
			virtual Void setOrder(Int32 order)=0;
			virtual Int32 getOrder()const=0;
			virtual IColourUnitState * getColourUnitState()=0;
			virtual ITextureUnitState * getTextureUnitState()=0;
			virtual Void setUVTransform(const CFloat2 & offset,const CFloat2 & scale)=0;
			virtual const CFloat2 & getUVOffset()const=0;
			virtual const CFloat2 & getUVScale()const=0;
		};
	}
}