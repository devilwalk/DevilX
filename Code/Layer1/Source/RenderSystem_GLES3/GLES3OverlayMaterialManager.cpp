#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;
using namespace NSGLES3;

NSDevilX::NSRenderSystem::NSGLES3::COverlayMaterialManager::COverlayMaterialManager()
{}

NSDevilX::NSRenderSystem::NSGLES3::COverlayMaterialManager::~COverlayMaterialManager()
{}

COverlayMaterial * NSDevilX::NSRenderSystem::NSGLES3::COverlayMaterialManager::getMaterial(IOverlayElementImp * element)
{
	COverlayMaterial * ret=nullptr;
	CTexture * tex=nullptr;
	if(const_cast<const IOverlayElementImp*>(element)->getTextureUnitState()&&const_cast<const IOverlayElementImp*>(element)->getTextureUnitState()->getTexture())
		tex=CSystemImp::getSingleton().getTexture(static_cast<ITextureImp*>(const_cast<const IOverlayElementImp*>(element)->getTextureUnitState()->getTexture()));
	for(auto material:mMaterials)
	{
		if(nullptr==tex)
		{
			if(material->getPSTextures().empty())
			{
				ret=material;
				break;
			}
		}
		else
		{
			if((!material->getPSTextures().empty())&&(material->getPSTextures()[0]==tex))
			{
				ret=material;
				break;
			}
		}
	}
	if(!ret)
	{
		ret=DEVILX_NEW COverlayMaterial(tex);
		mMaterials.push_back(ret);
	}
	return ret;
}
