#pragma once
#include "IEntityImp.h"
namespace NSDevilX
{
	namespace NSPhysicalSystem
	{
		class ISceneImp
			:public IScene
			,public TBaseObject<ISceneImp>
			,public CMessageNotifier
		{
		public:
			enum EMessage
			{
				EMessage_BeginDestruction,
				EMessage_EndDestruction,
				EMessage_BeginEntityCreate,
				EMessage_EndEntityCreate,
				EMessage_BeginEntityDestroy,
				EMessage_EndEntityDestroy,
				EMessage_BeginQueryCreate,
				EMessage_EndQueryCreate,
				EMessage_BeginQueryDestroy,
				EMessage_EndQueryDestroy
			};
		protected:
			const String mName;
			TNamedResourcePtrMap<IEntityImp> mEntitys;
			TNamedResourcePtrMap<IQueryImp> mQuerys;
		public:
			ISceneImp(const String & name);
			~ISceneImp();

			// Inherited via IScene
			virtual const String & getName() const override;
			virtual IEntity * createEntity(const String & name) override;
			virtual Void destroyEntity(IEntity * entity) override;
			virtual IEntity * getEntity(const String & name) const override;
			virtual IQuery * createQuery(const String & name,IEnum::EQueryType type) override;
			virtual Void destroyQuery(IQuery * query) override;
			virtual IQuery * getQuery(const String & name) const override;
		};
	}
}