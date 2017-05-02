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
			virtual Void setUVs(const CFloat2 & uv0,const CFloat2 & uv1,const CFloat2 & uv2,const CFloat2 & uv3)=0;
			virtual const CFloat2 * getUVs()const=0;
			virtual Void setOrder(Int32 order)=0;
			virtual Int32 getOrder()const=0;
			virtual Void SetScissorRect(const CFloat2 & position,const CFloat2 & size)=0;
			virtual const CFloat2 & getScissorRectPosition()const=0;
			virtual const CFloat2 & getScissorRectSize()const=0;
			virtual IColourUnitState * getColourUnitState()=0;
			virtual ITextureUnitState * getTextureUnitState()=0;
		};
	}
}