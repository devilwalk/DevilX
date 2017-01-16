#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;

NSDevilX::NSRenderSystem::CMipmapRenderTarget2D::CMipmapRenderTarget2D(UInt32 mipmapLevel,ITexture2DImp * texture)
	:mMipmapLevel(mipmapLevel)
	,mTexture(texture)
{}

NSDevilX::NSRenderSystem::CMipmapRenderTarget2D::~CMipmapRenderTarget2D()
{}
