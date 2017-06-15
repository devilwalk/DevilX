#pragma once
#include "GL4BaseObject.h"
#include "GL4EntityRenderableImp.h"
#include "GL4TransformerImp.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		namespace NSGL4
		{
			class CScene;
			class CEntityImp
				:public TBaseObject<CEntityImp>
				,public TInterfaceObject<IEntityImp>
				,public TMessageReceiver<ISceneElementImp>
			{
			protected:
				CScene * const mScene;
				CTransformerImp * mTransformer;
				TResourcePtrMap<IEntityRenderableImp*const,CEntityRenderableImp> mRenderables;
			public:
				CEntityImp(IEntityImp * interfaceImp);
				virtual ~CEntityImp();
				CScene * getScene()const
				{
					return mScene;
				}
				CTransformerImp * getTransformer()const
				{
					return mTransformer;
				}
				// Í¨¹ý TInterfaceObject ¼Ì³Ð
				virtual Void onMessage(IEntityImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
				virtual Void onMessage(ISceneElementImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
			protected:
				Void _updateTransformer();
			};
		}
	}
}