#pragma once
#include "D3D11BaseObject.h"
#include "D3D11SubEntityImp.h"
#include "D3D11TransformerImp.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		namespace NSD3D11
		{
			class CSceneImp;
			class CEntityImp
				:public TBaseObject<CEntityImp>
				,public TInterfaceObject<IEntityImp>
				,public TMessageReceiver<ISceneElementImp>
			{
			protected:
				CSceneImp * const mScene;
				CTransformerImp * mTransformer;
				TResourcePtrMap<ISubEntityImp*const,CSubEntityImp> mSubEntities;
			public:
				CEntityImp(IEntityImp * interfaceImp);
				virtual ~CEntityImp();
				CSceneImp * getScene()const
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