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
				Void setShader(IGAShaderImp* shader,IGAProgramParameterImp* parameter);
				Void setProgram(CGAProgramImp* program,IGAProgramParameterImp* parameter);
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
				virtual Void setShader(IGAShaderImp* shader,IGAProgramParameterImp* parameter);
				virtual Void setProgram(CGAProgramImp* program,IGAProgramParameterImp* parameter);
			};
			class CGAEnvironmentCommon
				:public CGAEnvironmentMultiImp
				,public TBaseObject<CGAEnvironmentCommon>
			{
			public:
				CGAEnvironmentCommon(){ }
				~CGAEnvironmentCommon(){ }
			};
			class CGAEnvironmentGL41Base
				:public CGAEnvironmentMultiImp
			{
			protected:
				GLuint mPipeline;
			public:
				CGAEnvironmentGL41Base();
				virtual ~CGAEnvironmentGL41Base();

				virtual Void setShader(IGAShaderImp* shader,IGAProgramParameterImp* parameter) override;
			};
			class CGAEnvironmentGL41
				:public CGAEnvironmentGL41Base
				,public TBaseObject<CGAEnvironmentGL41>
			{
			protected:
			public:
				CGAEnvironmentGL41(){ }
				~CGAEnvironmentGL41(){ }
			};
			class CGAEnvironmentGL45Base
				:public CGAEnvironmentGL41Base
			{
			protected:
			public:
				CGAEnvironmentGL45Base();
				virtual ~CGAEnvironmentGL45Base();

				virtual Void clear(IGADepthStencilViewImp* view,Float depth) override;
				virtual Void clear(IGADepthStencilViewImp* view,UInt8 stencil) override;
				virtual Void clear(IGADepthStencilViewImp* view,Float depth,UInt8 stencil) override;
				virtual Void clear(IGARenderTargetViewImp* view,const Float colourRGBA[4]) override;
				virtual Void setRenderTarget(UInt32 index,IGARenderTargetViewImp* view) override;
				virtual Void setDepthStencil(IGADepthStencilViewImp* view) override;
				virtual Void setShader(IGAShaderImp* shader,IGAProgramParameterImp* parameter) override;
			};
			class CGAEnvironmentGL45
				:public CGAEnvironmentGL45Base
				,public TBaseObject<CGAEnvironmentGL45>
			{
			public:
				CGAEnvironmentGL45(){ }
				~CGAEnvironmentGL45(){ }
			};
		}
	}
}