#pragma once
namespace NSDevilX
{
	namespace NSCore
	{
		class IGPUView
		{
		protected:
			virtual ~IGPUView(){ }
		public:
		};
		class IGPURenderTargetView
		{
		protected:
			virtual ~IGPURenderTargetView()
			{
			}
		public:
			virtual IGPUView * queryInterface_IGPUView()=0;
		};
		class IGPUDepthStencilView
		{
		protected:
			virtual ~IGPUDepthStencilView(){ }
		public:
			virtual IGPUView * queryInterface_IGPUView()=0;
		};
		class IGPUUnorderedAccessView
		{
		protected:
			virtual ~IGPUUnorderedAccessView(){ }
		public:
			virtual IGPUView * queryInterface_IGPUView()=0;
		};
		class IGPUShaderResourceView
		{
		protected:
			virtual ~IGPUShaderResourceView(){ }
		public:
			virtual IGPUView * queryInterface_IGPUView()=0;
		};
	}
}