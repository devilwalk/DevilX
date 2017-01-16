#pragma once
#include "D3D11Pass.h"
#include "D3D11Enum.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		namespace NSD3D11
		{
			class CMaterial;
			class CTechnique
			{
			protected:
				CEnum::ETechniqueType const mType;
				CMaterial * const mMaterial;
				TVector<CPass*> mPasses;
			public:
				CTechnique(CEnum::ETechniqueType type,CMaterial * material);
				virtual ~CTechnique();
				CEnum::ETechniqueType getType()const
				{
					return mType;
				}
				CMaterial * getMaterial()const
				{
					return mMaterial;
				}
				decltype(mPasses) const & getPasses()const
				{
					return mPasses;
				}
			};
			class CForwardTechnique
				:public CTechnique
				,public TBaseObject<CForwardTechnique>
			{
			protected:
			public:
				CForwardTechnique(CMaterial * material);
				~CForwardTechnique();
			};
		}
	}
}