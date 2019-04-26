#pragma once
namespace NSDevilX
{
	namespace NSCore
	{
		namespace NSOpenGL
		{
			class IGADeviceImp;
			class IGASwapChainImp;
			class CGAEnvironment
				:public TBaseObject<CGAEnvironment>
			{
			protected:
				EGLDisplay mDisplay;
				EGLSurface mSurface;
				EGLContext mContext;
			public:
				CGAEnvironment(EGLNativeWindowType window,Bool isGLES=False);
				~CGAEnvironment();

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
			};
		}
	}
}