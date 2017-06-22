#pragma once
#include "GLES3BaseObject.h"
#include "GLES3EntityRenderableImp.h"
#include "GLES3TransformerImp.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		namespace NSGLES3
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