#pragma once
#include "D3D11BaseObject.h"
#include "D3D11EntityTechnique.h"
#include "D3D11Enum.h"
#include "D3D11ConstantBufferContainer.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		namespace NSD3D11
		{
			class CSubEntityImp;
			class CEntityMaterial
				:public CConstantBufferContainer
				,public TMessageReceiver<IColourUnitStateImp>
				,public TMessageReceiver<ISubEntityImp>
			{
			protected:
				CSubEntityImp * const mSubEntity;
				std::array<CEntityTechnique*,CEnum::ETechniqueType_Count> mTechniques;
			public:
				CEntityMaterial(CSubEntityImp * subEntity);
				~CEntityMaterial();
				CSubEntityImp * getSubEntity()const
				{
					return mSubEntity;
				}
				CEntityTechnique * getTechnique(CEnum::ETechniqueType type)const
				{
					return mTechniques[type];
				}
			protected:
				Void _refreshTechnique();
				// Í¨¹ý TInterfaceObject ¼Ì³Ð
				virtual Void onMessage(IColourUnitStateImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
				virtual Void onMessage(ISubEntityImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
				// Inherited via CConstantBufferContainer
				virtual Void _updateConstantBuffer(Byte * buffer) override;
			};
		}
	}
}