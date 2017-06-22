#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;
using namespace NSGLES3;
NSDevilX::NSRenderSystem::NSGLES3::CEntityTechnique::CEntityTechnique(CEnum::ETechniqueType type,CEntityMaterial * material)
	:mType(type)
	,mMaterial(material)
{}

NSDevilX::NSRenderSystem::NSGLES3::CEntityTechnique::~CEntityTechnique()
{
	for(auto pass:mPasses)
		DEVILX_DELETE(pass);
}

NSDevilX::NSRenderSystem::NSGLES3::CEntityForwardTechnique::CEntityForwardTechnique(CEntityMaterial * material)
	:CEntityTechnique(CEnum::ETechniqueType_Forward,material)
{
	mPasses.resize(CEnum::EForwardPassType_Count);
	for(int i=0;i<CEnum::EForwardPassType_Count;++i)
	{
		mPasses[i]=DEVILX_NEW CEntityPass((CEnum::EForwardPassType)i,this);
	}
}

NSDevilX::NSRenderSystem::NSGLES3::CEntityForwardTechnique::~CEntityForwardTechnique()
{}
