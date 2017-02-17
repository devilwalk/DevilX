#pragma once
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
			virtual Void setTexture(ITexture * texture)=0;
			virtual ITexture * getTexture()const=0;
		};
	}
}