#pragma once
#include "GLES3EntityImp.h"
#include "GLES3Camera.h"
#include "GLES3Light.h"
#include "GLES3ConstantBufferContainer.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		namespace NSGLES3
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