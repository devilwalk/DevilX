#pragma once
namespace NSDevilX
{
	namespace NSGraphicsAPI
	{
		class ISurface
		{
		protected:
			virtual ~ISurface(){ }
		public:
		};

		class IRenderTargetView
		{
		protected:
			virtual ~IRenderTargetView()
			{
			}
		public:
		};

		class IDepthStencilView
		{
		protected:
			virtual ~IDepthStencilView()
			{
			}
		public:
		};

		class IFrameBufferObject
		{
		protected:
			virtual ~IFrameBufferObject(){ }
		public:
		};
	}
}