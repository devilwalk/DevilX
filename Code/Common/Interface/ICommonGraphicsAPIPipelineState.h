#pragma once
namespace NSDevilX
{
	namespace NSGraphicsAPI
	{
		class IStateBlock
		{
		protected:
			virtual ~IStateBlock(){ }
		public:
		};

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

		class ISamplerState
		{
		protected:
			virtual ~ISamplerState()
			{
			}
		public:
		};
	}
}