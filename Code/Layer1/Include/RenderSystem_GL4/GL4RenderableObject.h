#pragma once
#include "GL4Renderable.h"
#include "GL4TransformerImp.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		namespace NSGL4
		{
			class CScene;
			class CRenderableObject
				:public TBaseObject<CRenderableObject>
				,public TInterfaceObject<IRenderableObjectImp>
				,public TMessageReceiver<ISceneElementImp>
			{
			protected:
				CScene * const mScene;
				CTransformerImp * mTransformer;
				TResourcePtrContainer<IRenderableImp*const,CRenderable> mRenderables;
			public:
				CRenderableObject(IRenderableObjectImp * interfaceImp);
				virtual ~CRenderableObject();
				CScene * getScene()const
				{
					return mScene;
				}
				CTransformerImp * getTransformer()const
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