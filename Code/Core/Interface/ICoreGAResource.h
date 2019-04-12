#pragma once
namespace NSDevilX
{
	namespace NSCore
	{
		class IGAResource
		{
		protected:
			virtual ~IGAResource(){ }
		public:
		};
		class IGABuffer
		{
		protected:
			virtual ~IGABuffer()
			{
			}
		public:
			virtual IGAResource * queryInterface_IGAResource()=0;
		};
		class IGAVertexBuffer
		{
		protected:
			virtual ~IGAVertexBuffer(){ }
		public:
			virtual IGABuffer * queryInterface_IGABuffer()=0;
		};
		class IGAIndexBuffer
		{
		protected:
			virtual ~IGAIndexBuffer(){ }
		public:
			virtual IGABuffer * queryInterface_IGABuffer()=0;
		};
		class IGAConstantBuffer
		{
		protected:
			virtual ~IGAConstantBuffer(){ }
		public:
			virtual IGABuffer * queryInterface_IGABuffer()=0;
		};
		class IGAUnorderedAccessBuffer
		{
		protected:
			virtual ~IGAUnorderedAccessBuffer(){ }
		public:
			virtual IGABuffer * queryInterface_IGABuffer()=0;
		};
		class IGATexture
		{
		protected:
			virtual ~IGATexture(){}
		public:
			virtual IGAResource * queryInterface_IGAResource()=0;
		};
		class IGATexture1D
		{
		protected:
			virtual ~IGATexture1D()
			{}
		public:
			virtual IGATexture * queryInterface_IGATexture()=0;
		};
		class IGATexture2D
		{
		protected:
			virtual ~IGATexture2D()
			{}
		public:
			virtual IGATexture * queryInterface_IGATexture()=0;
		};
		class IGATexture3D
		{
		protected:
			virtual ~IGATexture3D()
			{}
		public:
			virtual IGATexture * queryInterface_IGATexture()=0;
		};
		class IGAInputLayout
		{
		protected:
			virtual ~IGAInputLayout()
			{}
		public:
			virtual IGAResource * queryInterface_IGAResource()=0;
		};
		class IGABlendState
		{
		protected:
			virtual ~IGABlendState()
			{}
		public:
			virtual IGAResource * queryInterface_IGAResource()=0;
		};
		class IGARasterizerState
		{
		protected:
			virtual ~IGARasterizerState()
			{
			}
		public:
			virtual IGAResource * queryInterface_IGAResource()=0;
		};
		class IGADepthStencilState
		{
		protected:
			virtual ~IGADepthStencilState(){ }
		public:
			virtual IGAResource * queryInterface_IGAResource()=0;
		};
		class IGAShader
		{
		protected:
			virtual ~IGAShader()
			{
			}
		public:
			virtual IGAResource * queryInterface_IGAResource()=0;
		};
		class IGAVertexShader
		{
		protected:
			virtual ~IGAVertexShader()
			{
			}
		public:
			virtual IGAShader * queryInterface_IGAShader()=0;
		};
		class IGAPixelShader
		{
		protected:
			virtual ~IGAPixelShader()
			{
			}
		public:
			virtual IGAShader * queryInterface_IGAShader()=0;
		};
		class IGAGeometryShader
		{
		protected:
			virtual ~IGAGeometryShader()
			{
			}
		public:
			virtual IGAShader * queryInterface_IGAShader()=0;
		};
		class IGAHullShader
		{
		protected:
			virtual ~IGAHullShader()
			{
			}
		public:
			virtual IGAShader * queryInterface_IGAShader()=0;
		};
		class IGADomainShader
		{
		protected:
			virtual ~IGADomainShader()
			{
			}
		public:
			virtual IGAShader * queryInterface_IGAShader()=0;
		};
		class IGAComputeShader
		{
		protected:
			virtual ~IGAComputeShader()
			{
			}
		public:
			virtual IGAShader * queryInterface_IGAShader()=0;
		};
		class IGASamplerState
		{
		protected:
			virtual ~IGASamplerState(){ }
		public:
			virtual IGAResource * queryInterface_IGAResource()=0;
		};
	}
}