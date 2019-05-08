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
		class IGATextureView
		{
		protected:
			virtual ~IGATextureView(){ }
		public:
			virtual IGAView * queryInterface_IGAView()=0;
		};
		class IGAShaderResourceBufferView
		{
		protected:
			virtual ~IGAShaderResourceBufferView()
			{
			}
		public:
			virtual IGAView* queryInterface_IGAView()=0;
		};
	}
}