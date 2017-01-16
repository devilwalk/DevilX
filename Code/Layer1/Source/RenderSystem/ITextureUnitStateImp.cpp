#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;

NSDevilX::NSRenderSystem::ITextureUnitStateImp::ITextureUnitStateImp(IEnum::ETextureUnitStateType type,IMaterialImp * material)
	:mType(type)
	,mMaterial(material)
	,mTexture(nullptr)
{}

NSDevilX::NSRenderSystem::ITextureUnitStateImp::~ITextureUnitStateImp()
{}

IEnum::ETextureUnitStateType NSDevilX::NSRenderSystem::ITextureUnitStateImp::getType() const
{
	return mType;
}

Void NSDevilX::NSRenderSystem::ITextureUnitStateImp::setTexture(ITexture * texture)
{
	if(texture!=getTexture())
	{
		notify(EMessage_BeginTextureChange);
		mTexture=texture;
		notify(EMessage_EndTextureChange);
	}
}

ITexture * NSDevilX::NSRenderSystem::ITextureUnitStateImp::getTexture() const
{
	return mTexture;
}
