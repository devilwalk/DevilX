#pragma once
#include "GL4RenderTarget.h"
#include "GL4DepthStencil.h"
#include "GL4ViewportImp.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		namespace NSGL4
		{
			class CRenderTargetImp
				:public TInternalObject<CRenderTarget>
			{
			protected:
				TResourcePtrMap<IViewportImp*const,CViewportImp> mViewports;
			public:
				CRenderTargetImp(GLuint rt);
				virtual ~CRenderTargetImp();
				virtual Void prepare();
				virtual Void render();
			};
		}
	}
}