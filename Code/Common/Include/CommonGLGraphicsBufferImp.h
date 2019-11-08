#pragma once
#include "CommonGLGraphics.h"
namespace NSDevilX
{
	class CGLGraphicsBufferImp
		:public IGraphicsBuffer
		,public CGLGraphicsObject
	{
	protected:
	public:
		CGLGraphicsBufferImp();
		virtual ~CGLGraphicsBufferImp();
	};
}