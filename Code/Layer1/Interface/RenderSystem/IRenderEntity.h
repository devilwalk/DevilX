#pragma once
#include "IRenderSceneElement.h"
#include "IRenderSubEntity.h"
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
			virtual ISubEntity * createSubEntity(const String & name)=0;
			virtual ISubEntity * getSubEntity(const String & name)const=0;
			virtual ISubEntity * getSubEntity(UInt32 index)const=0;
			virtual UInt32 getSubEntityCount()const=0;
			virtual Void destroySubEntity(ISubEntity * subEntity)=0;
		};
	}
}