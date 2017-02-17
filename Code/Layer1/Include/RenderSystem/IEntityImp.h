#pragma once
#include "IEntityRenderableImp.h"
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
				EMessage_BeginRenderableCreate,
				EMessage_EndRenderableCreate,
				EMessage_BeginRenderableDestroy,
				EMessage_EndRenderableDestroy
			};
		protected:
			ISceneElementImp * mSceneElement;
			TNamedIndexResourcePtrContainer<IEntityRenderableImp> mRenderables;
		public:
			IEntityImp(const String & name,ISceneImp * scene);
			virtual ~IEntityImp();
			// Inherited via IRenderableObject
			virtual ISceneElement * queryInterface_ISceneElement() const override;
			virtual IEntityRenderable * createRenderable(const String & name) override;
			virtual IEntityRenderable * getRenderable(const String & name) const override;
			virtual IEntityRenderable * getRenderable(UInt32 index) const override;
			virtual UInt32 getRenderableCount() const override;
			virtual Void destroyRenderable(IEntityRenderable * renderable) override;
		};
	}
}