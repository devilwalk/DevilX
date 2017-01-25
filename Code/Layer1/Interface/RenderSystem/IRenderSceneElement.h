#pragma once
#include "IRenderEnum.h"
#include "IRenderTransformer.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		class IScene;
		class ISceneElement
		{
		protected:
			virtual ~ISceneElement(){ }
		public:
			virtual const String & getName()const=0;
			virtual IScene * getScene()const=0;
			virtual Void setTransformer(ITransformer * transformer)=0;
			virtual ITransformer * getTransformer()const=0;
		};
	}
}