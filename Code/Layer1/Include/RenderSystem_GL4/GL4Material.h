#pragma once
#include "GL4Technique.h"
#include "Gl4Enum.h"
#include "Gl4ConstantBufferContainer.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		namespace NSGL4
		{
			class CRenderable;
			class CMaterial
				:public TInterfaceObject<IMaterialImp>
				,public CConstantBufferContainer
				,public TMessageReceiver<IColourUnitStateImp>
				,public TMessageReceiver<IRenderableImp>
			{
			protected:
				CRenderable * const mRenderable;
				CTechnique * mTechniques[CEnum::ETechniqueType_Count];
			public:
				CMaterial(CRenderable * renderable);
				~CMaterial();
				CRenderable * getRenderable()const
				{
					return mRenderable;
				}
				CTechnique * getTechnique(CEnum::ETechniqueType type)const
				{
					return mTechniques[type];
				}

				// Í¨¹ý TInterfaceObject ¼Ì³Ð
				virtual Void onMessage(IMaterialImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
				virtual Void onMessage(IColourUnitStateImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
				virtual Void onMessage(IRenderableImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
				// Inherited via CConstantBufferContainer
				virtual Void _updateConstantBuffer(Byte * buffer) override;
			};
		}
	}
}