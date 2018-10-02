#pragma once
#include "IRenderable.h"
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
			virtual IRenderable * queryInterface_IRenderable()const=0;
			virtual const String & getName()const=0;
			virtual IEntity * getEntity()const=0;
		};
	}
}