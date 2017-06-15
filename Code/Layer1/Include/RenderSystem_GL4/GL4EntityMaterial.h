#pragma once
#include "GL4BaseObject.h"
#include "GL4EntityTechnique.h"
#include "GL4Enum.h"
#include "GL4ConstantBufferContainer.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		namespace NSGL4
		{
			class CEntityRenderableImp;
			class CEntityMaterial
				:public CConstantBufferContainer
				,public TMessageReceiver<IColourUnitStateImp>
				,public TMessageReceiver<IEntityRenderableImp>
			{
			protected:
				CEntityRenderableImp * const mRenderable;
				CEntityTechnique * mTechniques[CEnum::ETechniqueType_Count];
			public:
				CEntityMaterial(CEntityRenderableImp * renderable);
				~CEntityMaterial();
				CEntityRenderableImp * getRenderable()const
				{
					return mRenderable;
				}
				CEntityTechnique * getTechnique(CEnum::ETechniqueType type)const
				{
					return mTechniques[type];
				}

				// Í¨¹ý TInterfaceObject ¼Ì³Ð
				virtual Void onMessage(IColourUnitStateImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
				virtual Void onMessage(IEntityRenderableImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
				// Inherited via CConstantBufferContainer
				virtual Void _updateConstantBuffer(Byte * buffer) override;
			};
		}
	}
}