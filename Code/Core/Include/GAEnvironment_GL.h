#pragma once
namespace NSDevilX
{
	namespace NSCore
	{
		namespace NSOpenGL
		{
			class IGADeviceImp;
			class IGASwapChainImp;
			class IGADepthStencilViewImp;
			class IGARenderTargetViewImp;
			class CGAContextBase;
			class CGAEnvironment
				:public TBaseObject<CGAEnvironment>
			{
			protected:
				EGLDisplay mDisplay;
				EGLSurface mSurface;
				EGLContext mContext;
				std::auto_ptr<CGAContextBase> mImp;
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
			};
			class CGAContextBase
			{
			protected:
				GLuint mFrameBufferObject;
			public:
				CGAContextBase();
				virtual ~CGAContextBase();
				virtual Void clear(IGADepthStencilViewImp* view,Float depth);
				virtual Void clear(IGADepthStencilViewImp* view,UInt8 stencil);
				virtual Void clear(IGADepthStencilViewImp* view,Float depth,UInt8 stencil);
				virtual Void clear(IGARenderTargetViewImp* view,const Float colourRGBA[4]);
			};
			class CGAContextCommon
				:public CGAContextBase
				,public TBaseObject<CGAContextCommon>
			{
			public:
				CGAContextCommon();
				~CGAContextCommon();
			};
			class CGAContextGL45
				:public CGAContextBase
				,public TBaseObject<CGAContextGL45>
			{
			protected:
			public:
				CGAContextGL45();
				~CGAContextGL45();

				virtual Void clear(IGADepthStencilViewImp* view,Float depth) override;
				virtual Void clear(IGADepthStencilViewImp* view,UInt8 stencil) override;
				virtual Void clear(IGADepthStencilViewImp* view,Float depth,UInt8 stencil) override;
				virtual Void clear(IGARenderTargetViewImp* view,const Float colourRGBA[4]) override;
			};
		}
	}
}