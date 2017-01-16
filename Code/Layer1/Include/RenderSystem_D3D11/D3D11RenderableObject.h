#pragma once
#include "D3D11BaseObject.h"
#include "D3D11Renderable.h"
#include "D3D11Transformer.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		namespace NSD3D11
		{
			class CScene;
			class CRenderableObject
				:public TBaseObject<CRenderableObject>
				,public TInterfaceObject<IRenderableObjectImp>
				,public TMessageReceiver<ISceneElementImp>
			{
			protected:
				CScene * const mScene;
				CTransformer * mTransformer;
				TResourcePtrContainer<IRenderableImp*const,CRenderable> mRenderables;
			public:
				CRenderableObject(IRenderableObjectImp * interfaceImp);
				virtual ~CRenderableObject();
				CScene * getScene()const
				{
					return mScene;
				}
				CTransformer * getTransformer()const
				{
					return mTransformer;
				}
				// Í¨¹ý TInterfaceObject ¼Ì³Ð
				virtual Void onMessage(IRenderableObjectImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
				virtual Void onMessage(ISceneElementImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
			protected:
				Void _updateTransformer();
			};
		}
	}
}