#pragma once
#include "IRenderSceneElement.h"
#include "IRenderable.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		class IRenderableObject
		{
		protected:
			virtual ~IRenderableObject(){}
		public:
			virtual ISceneElement * queryInterface_ISceneElement()const=0;
			virtual IRenderable * createRenderable(const String & name)=0;
			virtual IRenderable * getRenderable(const String & name)const=0;
			virtual IRenderable * getRenderable(UInt32 index)const=0;
			virtual UInt32 getRenderableCount()const=0;
			virtual Void destroyRenderable(IRenderable * renderable)=0;
		};
	}
}