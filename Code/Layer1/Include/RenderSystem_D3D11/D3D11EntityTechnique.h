#pragma once
#include "D3D11EntityForwardPass.h"
#include "D3D11Enum.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		namespace NSD3D11
		{
			class CEntityMaterial;
			class CEntityTechnique
			{
			protected:
				CEnum::ETechniqueType const mType;
				CEntityMaterial * const mMaterial;
				TVector<CEntityPass*> mPasses;
			public:
				CEntityTechnique(CEnum::ETechniqueType type,CEntityMaterial * material);
				virtual ~CEntityTechnique();
				CEnum::ETechniqueType getType()const
				{
					return mType;
				}
				CEntityMaterial * getMaterial()const
				{
					return mMaterial;
				}
				decltype(mPasses) const & getPasses()const
				{
					return mPasses;
				}
			};
			class CEntityForwardTechnique
				:public CEntityTechnique
				,public TBaseObject<CEntityForwardTechnique>
			{
			protected:
			public:
				CEntityForwardTechnique(CEntityMaterial * material);
				~CEntityForwardTechnique();
			};
			class CEntityQueryTechnique
				:public CEntityTechnique
				,public TBaseObject<CEntityQueryTechnique>
			{
			protected:
			public:
				CEntityQueryTechnique(CEntityMaterial * material);
				~CEntityQueryTechnique();
			};
		}
	}
}