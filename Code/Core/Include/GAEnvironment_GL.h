#pragma once
#include "IGAViewImp_GL.h"
#include "IGAResourceImp_GL.h"
namespace NSDevilX
{
	namespace NSCore
	{
		namespace NSOpenGL
		{
			class IGADeviceImp;
			class IGASwapChainImp;
			class CGAEnvironmentMultiImp;
			class CGAEnvironment
				:public TBaseObject<CGAEnvironment>
			{
			protected:
				EGLDisplay mDisplay;
				EGLSurface mSurface;
				EGLContext mContext;
				std::auto_ptr<CGAEnvironmentMultiImp> mMultiImp;
			public:
				CGAEnvironment(EGLNativeWindowType window,Bool isGLES=False);
				virtual ~CGAEnvironment();

				auto getDisplay()const
				{
					return mDisplay;
				}
				auto getSurface()const
				{
					return mSurface;
				}
				auto getContext()const
				{
					return mContext;
				}
				Void swapBuffer()
				{
					eglSwapBuffers(mDisplay,mSurface);
				}
				Void clear(IGADepthStencilViewImp* view,Float depth);
				Void clear(IGADepthStencilViewImp* view,UInt8 stencil);
				Void clear(IGADepthStencilViewImp* view,Float depth,UInt8 stencil);
				Void clear(IGARenderTargetViewImp* view,const Float colourRGBA[4]);
				Void setRenderTarget(UInt32 index,IGARenderTargetViewImp* view);
				Void setDepthStencil(IGADepthStencilViewImp* view);
				Void setInputLayout(IGAInputLayoutImp* layout);
			};
			class CGAEnvironmentMultiImp
			{
			public:
				CGAEnvironmentMultiImp();
				virtual ~CGAEnvironmentMultiImp();
				virtual Void clear(IGADepthStencilViewImp* view,Float depth);
				virtual Void clear(IGADepthStencilViewImp* view,UInt8 stencil);
				virtual Void clear(IGADepthStencilViewImp* view,Float depth,UInt8 stencil);
				virtual Void clear(IGARenderTargetViewImp* view,const Float colourRGBA[4]);
				virtual Void setRenderTarget(UInt32 index,IGARenderTargetViewImp* view);
				virtual Void setDepthStencil(IGADepthStencilViewImp* view);
			};
			class CGAEnvironmentCommon
				:public CGAEnvironmentMultiImp
				,public TBaseObject<CGAEnvironmentCommon>
			{
			public:
				CGAEnvironmentCommon();
				~CGAEnvironmentCommon();
			};
			class CGAEnvironmentDSA
				:public CGAEnvironmentMultiImp
				,public TBaseObject<CGAEnvironmentDSA>
			{
			protected:
			public:
				CGAEnvironmentDSA();
				~CGAEnvironmentDSA();

				virtual Void clear(IGADepthStencilViewImp* view,Float depth) override;
				virtual Void clear(IGADepthStencilViewImp* view,UInt8 stencil) override;
				virtual Void clear(IGADepthStencilViewImp* view,Float depth,UInt8 stencil) override;
				virtual Void clear(IGARenderTargetViewImp* view,const Float colourRGBA[4]) override;
				virtual Void setRenderTarget(UInt32 index,IGARenderTargetViewImp* view) override;
				virtual Void setDepthStencil(IGADepthStencilViewImp* view) override;
			};
		}
	}
}