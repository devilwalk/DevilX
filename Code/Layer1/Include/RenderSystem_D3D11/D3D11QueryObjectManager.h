#pragma once
#include "D3D11QueryObjectRenderable.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		namespace NSD3D11
		{
			class CSceneImp;
			class CQueryObjectManager
				:public TBaseObject<CQueryObjectManager>
				,public TMessageReceiver<ISceneImp>
				,public TMessageReceiver<IQueryObjectImp>
			{
			protected:
				CSceneImp * const mScene;
				TList<CQueryObjectRenderable*> mRenderables;
			public:
				CQueryObjectManager(CSceneImp * scene);
				~CQueryObjectManager();

				// ͨ�� TMessageReceiver �̳�
				virtual Void onMessage(ISceneImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;

				// ͨ�� TMessageReceiver �̳�
				virtual Void onMessage(IQueryObjectImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
			protected:
				Void _addObject(IQueryObjectImp * obj);
				Void _removeObject(IQueryObjectImp * obj);
			};
		}
	}
}