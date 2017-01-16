#pragma once
#include "IPhysicalEntity.h"
#include "IPhysicalQuery.h"
namespace NSDevilX
{
	namespace NSPhysicalSystem
	{
		class IScene
		{
		protected:
			virtual ~IScene(){}
		public:
			virtual const String & getName()const=0;
			virtual IEntity * createEntity(const String & name)=0;
			virtual Void destroyEntity(IEntity * entity)=0;
			virtual IEntity * getEntity(const String & name)const=0;
			virtual IQuery * createQuery(const String & name,IEnum::EQueryType type)=0;
			virtual Void destroyQuery(IQuery * query)=0;
			virtual IQuery * getQuery(const String & name)const=0;
		};
	}
}