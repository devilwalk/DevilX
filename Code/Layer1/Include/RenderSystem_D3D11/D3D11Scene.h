#pragma once
#include "D3D11BaseObject.h"
#include "D3D11RenderableObject.h"
#include "D3D11Camera.h"
#include "D3D11Light.h"
#include "D3D11ConstantBufferContainer.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		namespace NSD3D11
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