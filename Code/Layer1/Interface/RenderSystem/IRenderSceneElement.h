#pragma once
#include "IRenderEnum.h"
#include "IRenderTransformer.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		class ISceneElement
		{
		protected:
			virtual ~ISceneElement(){ }
		public:
			virtual const String & getName()const=0;
			virtual Void setTransformer(ITransformer * transformer)=0;
			virtual ITransformer * getTransformer()const=0;
		};
	}
}