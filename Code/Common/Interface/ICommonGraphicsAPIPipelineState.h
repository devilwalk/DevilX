#pragma once
namespace NSDevilX
{
	namespace NSGraphicsAPI
	{
		class IBlendState
		{
		protected:
			virtual ~IBlendState()
			{
			}
		public:
		};

		class IDepthStencilState
		{
		protected:
			virtual ~IDepthStencilState()
			{
			}
		public:
		};

		class IRasterizerState
		{
		protected:
			virtual ~IRasterizerState()
			{
			}
		public:
		};
	}
}