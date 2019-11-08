#pragma once
#include "CommonGLGraphics.h"
namespace NSDevilX
{
	class CGLGraphicsTextureImp
		:public IGraphicsTexture
		,public CGLGraphicsObject
	{
	protected:
	public:
		CGLGraphicsTextureImp();
		virtual ~CGLGraphicsTextureImp();
	};
}