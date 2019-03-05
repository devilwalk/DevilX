#pragma once
namespace NSDevilX
{
	namespace NSCore
	{
		class IGAView
		{
		protected:
			virtual ~IGAView(){ }
		public:
		};
		class IGARenderTargetView
		{
		protected:
			virtual ~IGARenderTargetView()
			{
			}
		public:
			virtual IGAView * queryInterface_IGAView()=0;
		};
		class IGADepthStencilView
		{
		protected:
			virtual ~IGADepthStencilView(){ }
		public:
			virtual IGAView * queryInterface_IGAView()=0;
		};
		class IGAUnorderedAccessView
		{
		protected:
			virtual ~IGAUnorderedAccessView(){ }
		public:
			virtual IGAView * queryInterface_IGAView()=0;
		};
		class IGAShaderResourceView
		{
		protected:
			virtual ~IGAShaderResourceView(){ }
		public:
			virtual IGAView * queryInterface_IGAView()=0;
		};
	}
}