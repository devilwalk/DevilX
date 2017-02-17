#pragma once
#include "IRenderSceneElement.h"
#include "IRenderEntityRenderable.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		class IEntity
		{
		protected:
			virtual ~IEntity(){}
		public:
			virtual ISceneElement * queryInterface_ISceneElement()const=0;
			virtual IEntityRenderable * createRenderable(const String & name)=0;
			virtual IEntityRenderable * getRenderable(const String & name)const=0;
			virtual IEntityRenderable * getRenderable(UInt32 index)const=0;
			virtual UInt32 getRenderableCount()const=0;
			virtual Void destroyRenderable(IEntityRenderable * renderable)=0;
		};
	}
}