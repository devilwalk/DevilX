#pragma once
namespace NSDevilX
{
	namespace NSGraphicsAPI
	{
		class CGLRenderBufferImp
			:public CGLObject
			,public ISurface
		{
		protected:
		public:
			CGLRenderBufferImp();
			~CGLRenderBufferImp();
		};

		class CGLFrameBufferObjectImp
			:public CGLObject
			,public IRenderTargetView
			,public IDepthStencilView
		{
		protected:
		public:
			CGLFrameBufferObjectImp();
			~CGLFrameBufferObjectImp();
		};
	}
}