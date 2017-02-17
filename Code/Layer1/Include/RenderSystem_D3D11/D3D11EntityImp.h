#pragma once
#include "D3D11BaseObject.h"
#include "D3D11EntityRenderableImp.h"
#include "D3D11Transformer.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		namespace NSD3D11
		{
			class CScene;
			class CEntityImp
				:public TBaseObject<CEntityImp>
				,public TInterfaceObject<IEntityImp>
				,public TMessageReceiver<ISceneElementImp>
			{
			protected:
				CScene * const mScene;
				CTransformer * mTransformer;
				TResourcePtrMap<IEntityRenderableImp*const,CEntityRenderableImp> mRenderables;
			public:
				CEntityImp(IEntityImp * interfaceImp);
				virtual ~CEntityImp();
				CScene * getScene()const
				{
					return mScene;
				}
				CTransformer * getTransformer()const
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