#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;
using namespace NSD3D11;
NSDevilX::NSRenderSystem::NSD3D11::CEntityTechnique::CEntityTechnique(CEnum::ETechniqueType type,CEntityMaterial * material)
	:mType(type)
	,mMaterial(material)
{}

NSDevilX::NSRenderSystem::NSD3D11::CEntityTechnique::~CEntityTechnique()
{
	for(auto pass:mPasses)
		DEVILX_DELETE(pass);
}

NSDevilX::NSRenderSystem::NSD3D11::CEntityForwardTechnique::CEntityForwardTechnique(CEntityMaterial * material)
	:CEntityTechnique(CEnum::ETechniqueType_Forward,material)
{
	mPasses.resize(CEnum::EForwardPassType_Count);
	for(int i=0;i<CEnum::EForwardPassType_Count;++i)
	{
		mPasses[i]=DEVILX_NEW CEntityForwardPass((CEnum::EForwardPassType)i,this);
	}
}

NSDevilX::NSRenderSystem::NSD3D11::CEntityForwardTechnique::~CEntityForwardTechnique()
{}

NSDevilX::NSRenderSystem::NSD3D11::CEntityQueryTechnique::CEntityQueryTechnique(CEntityMaterial * material)
	:CEntityTechnique(CEnum::ETechniqueType_Query,material)
{
	mPasses.push_back(DEVILX_NEW CEntityQueryPass(this));
}

NSDevilX::NSRenderSystem::NSD3D11::CEntityQueryTechnique::~CEntityQueryTechnique()
{}
