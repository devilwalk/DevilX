#pragma once
#include "IRenderableImp.h"
#include "ISceneElementImp.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		class IRenderableObjectImp
			:public IRenderableObject
			,public TBaseObject<IRenderableObjectImp>
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
			TNamedIndexResourcePtrContainer<IRenderableImp> mRenderables;
		public:
			IRenderableObjectImp(const String & name,ISceneImp * scene);
			virtual ~IRenderableObjectImp();
			// Inherited via IRenderableObject
			virtual ISceneElement * queryInterface_ISceneElement() const override;
			virtual IRenderable * createRenderable(const String & name) override;
			virtual IRenderable * getRenderable(const String & name) const override;
			virtual IRenderable * getRenderable(UInt32 index) const override;
			virtual UInt32 getRenderableCount() const override;
			virtual Void destroyRenderable(IRenderable * renderable) override;
		};
	}
}