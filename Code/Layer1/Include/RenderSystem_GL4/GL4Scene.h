#pragma once
#include "GL4RenderableObject.h"
#include "GL4Camera.h"
#include "GL4Light.h"
#include "GL4ConstantBufferContainer.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		namespace NSGL4
		{
			class CScene
				:public TInterfaceObject<ISceneImp>
				,public CConstantBufferContainer
			{
			protected:
				TResourcePtrContainer<IRenderableObjectImp*const,CRenderableObject> mRenderableObjects;
				TResourcePtrContainer<ICameraImp*const,CCamera> mCameras;
				TResourcePtrContainer<ILightImp*const,CLight> mLights;
			public:
				CScene(ISceneImp * interfaceImp);
				~CScene();
				CRenderableObject * getRenderableObject(IRenderableObjectImp * interfaceImp)const
				{
					return mRenderableObjects.get(interfaceImp);
				}
				CCamera * getCamera(ICameraImp * interfaceImp)const
				{
					return mCameras.get(interfaceImp);
				}
				// Í¨¹ý TInterfaceObject ¼Ì³Ð
				virtual Void onMessage(ISceneImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;

				// Inherited via CConstantBufferContainer
				virtual Void _updateConstantBuffer(Byte * buffer) override;
			};
		}
	}
}