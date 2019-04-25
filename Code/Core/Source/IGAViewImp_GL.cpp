#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSCore;
using namespace NSOpenGL;

NSDevilX::NSCore::NSOpenGL::IGARenderTargetViewImp::IGARenderTargetViewImp(GLuint texture,GLint mipLevel,GLint arrayIndex)
	:mTexture(texture)
	,mMipLevel(mipLevel)
	,mArrayIndex(arrayIndex)
{
}

NSDevilX::NSCore::NSOpenGL::IGARenderTargetViewImp::~IGARenderTargetViewImp()
{
}

NSDevilX::NSCore::NSOpenGL::IGADepthStencilViewImp::IGADepthStencilViewImp(GLuint texture,GLint mipLevel,GLint arrayIndex)
	:mTexture(texture)
	,mMipLevel(mipLevel)
	,mArrayIndex(arrayIndex)
{
}

NSDevilX::NSCore::NSOpenGL::IGADepthStencilViewImp::~IGADepthStencilViewImp()
{

}