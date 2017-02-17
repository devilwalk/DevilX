#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;

NSDevilX::NSRenderSystem::ITextureUnitStateImp::ITextureUnitStateImp()
	:mTexture(nullptr)
{}

NSDevilX::NSRenderSystem::ITextureUnitStateImp::~ITextureUnitStateImp()
{}

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
