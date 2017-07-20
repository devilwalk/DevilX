#pragma once
#include "ISubEntityImp.h"
#include "ISceneElementImp.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		class IEntityImp
			:public IEntity
			,public TBaseObject<IEntityImp>
			,public CMessageNotifier
		{
		public:
			enum EMessage
			{
				EMessage_BeginSubEntityCreate,
				EMessage_EndSubEntityCreate,
				EMessage_BeginSubEntityDestroy,
				EMessage_EndSubEntityDestroy
			};
		protected:
			ISceneElementImp * mSceneElement;
			TNamedIndexResourcePtrContainer<ISubEntityImp> mSubEntities;
		public:
			IEntityImp(const String & name,ISceneImp * scene);
			virtual ~IEntityImp();
			// Inherited via IRenderableObject
			virtual ISceneElement * queryInterface_ISceneElement() const override;
			virtual ISubEntity * createSubEntity(const String & name) override;
			virtual ISubEntity * getSubEntity(const String & name) const override;
			virtual ISubEntity * getSubEntity(UInt32 index) const override;
			virtual UInt32 getSubEntityCount() const override;
			virtual Void destroySubEntity(ISubEntity * subEntity) override;
		};
	}
}