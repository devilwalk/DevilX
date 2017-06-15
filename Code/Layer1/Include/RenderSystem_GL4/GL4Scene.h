#pragma once
#include "GL4EntityImp.h"
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
				TResourcePtrMap<IEntityImp*const,CEntityImp> mEntities;
				TResourcePtrMap<ICameraImp*const,CCamera> mCameras;
				TResourcePtrMap<ILightImp*const,CLight> mLights;
			public:
				CScene(ISceneImp * interfaceImp);
				~CScene();
				CEntityImp * getRenderableObject(IEntityImp * interfaceImp)const
				{
					return mEntities.get(interfaceImp);
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