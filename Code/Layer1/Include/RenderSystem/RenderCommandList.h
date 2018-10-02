#pragma once
#include "RenderTarget.h"
#include "RenderOperation.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		class CRenderCommandList
		{
		public:
			CRenderCommandList(){ }
			virtual ~CRenderCommandList(){ }
			virtual Void clearRenderTarget(CRenderTarget * renderTarget)=0;
			virtual Void renderOperation(const CRenderOperation & op)=0;
			virtual Void execute(Bool sync=False)=0;
		};
	}
}