#pragma once
#include "D3D11BaseObject.h"
#include "D3D11EntityImp.h"
#include "D3D11Camera.h"
#include "D3D11Light.h"
#include "D3D11ConstantBufferContainer.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		namespace NSD3D11
		{
			class CSceneImp
				:public TInterfaceObject<ISceneImp>
				,public CConstantBufferContainer
			{
			protected:
				TResourcePtrMap<IEntityImp*const,CEntityImp> mEntities;
				TResourcePtrMap<ICameraImp*const,CCamera> mCameras;
				TResourcePtrMap<ILightImp*const,CLight> mLights;
			public:
				CSceneImp(ISceneImp * interfaceImp);
				~CSceneImp();
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