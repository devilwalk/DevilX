#pragma once
#include "IRenderTechnique.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		class IMaterial
		{
		protected:
			virtual ~IMaterial(){ }
		public:
			virtual const String & getName()const=0;
			virtual ITechnique * createTechnique(const String & name)=0;
			virtual ITechnique * getTechnique(const String & name)=0;
			virtual Void destroyTechnique(ITechnique * tech)=0;
		};
	}
}