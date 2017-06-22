#pragma once
#include "GLES3RenderTarget.h"
#include "GLES3DepthStencil.h"
#include "GLES3ViewportImp.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		namespace NSGLES3
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