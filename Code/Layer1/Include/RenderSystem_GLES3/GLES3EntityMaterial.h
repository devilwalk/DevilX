#pragma once
#include "GLES3BaseObject.h"
#include "GLES3EntityTechnique.h"
#include "GLES3Enum.h"
#include "GLES3ConstantBufferContainer.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		namespace NSGLES3
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