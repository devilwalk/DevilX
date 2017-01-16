#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;
using namespace NSD3D11;
NSDevilX::NSRenderSystem::NSD3D11::CTechnique::CTechnique(CEnum::ETechniqueType type,CMaterial * material)
	:mType(type)
	,mMaterial(material)
{}

NSDevilX::NSRenderSystem::NSD3D11::CTechnique::~CTechnique()
{
	for(auto pass:mPasses)
		DEVILX_DELETE(pass);
}

NSDevilX::NSRenderSystem::NSD3D11::CForwardTechnique::CForwardTechnique(CMaterial * material)
	:CTechnique(CEnum::ETechniqueType_Forward,material)
{
	mPasses.resize(CEnum::EForwardPassType_Count);
	for(int i=0;i<CEnum::EForwardPassType_Count;++i)
	{
		mPasses[i]=DEVILX_NEW CPass((CEnum::EForwardPassType)i,this);
	}
}

NSDevilX::NSRenderSystem::NSD3D11::CForwardTechnique::~CForwardTechnique()
{}
