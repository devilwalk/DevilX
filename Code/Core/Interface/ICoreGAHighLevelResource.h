#pragma once
#include "ICoreGAView.h"
#include "ICoreGABase.h"
namespace NSDevilX
{
	namespace NSCore
	{
		class IGAHighLevelBuffer
		{
		protected:
			virtual ~IGAHighLevelBuffer()
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
			virtual IGAHighLevelBuffer* queryInterface_IGAHighLevelBuffer()=0;
		};
		class IGAIndexBuffer
		{
		protected:
			virtual ~IGAIndexBuffer(){ }
		public:
			virtual IGAHighLevelBuffer* queryInterface_IGAHighLevelBuffer()=0;
		};
		class IGAConstantBuffer
		{
		protected:
			virtual ~IGAConstantBuffer(){ }
		public:
			virtual IGAHighLevelBuffer* queryInterface_IGAHighLevelBuffer()=0;
		};
		class IGAShaderResourceBuffer
		{
		protected:
			virtual ~IGAShaderResourceBuffer(){}
		public:
			virtual IGAHighLevelBuffer* queryInterface_IGAHighLevelBuffer() = 0;
		};
		class IGAUnorderedAccessBuffer
		{
		protected:
			virtual ~IGAUnorderedAccessBuffer(){ }
		public:
			virtual IGAHighLevelBuffer* queryInterface_IGAHighLevelBuffer()=0;
		};
		class IGATextureBuffer
		{
		protected:
			virtual ~IGATextureBuffer(){ }
		public:
			virtual IGAHighLevelBuffer* queryInterface_IGAHighLevelBuffer()=0;
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
		class IGAVertexArrayObject
		{
		protected:
			virtual ~IGAVertexArrayObject()
			{
			}
		public:
			virtual IGAResource* queryInterface_IGAResource()=0;
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
		class IGASamplerState
		{
		protected:
			virtual ~IGASamplerState()
			{}
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
		class IGAProgram
		{
		protected:
			virtual ~IGAProgram(){}
		public:
			virtual IGAResource * queryInterface_IGAResource()=0;
		};
		class IGAProgramParameter
		{
		protected:
			virtual ~IGAProgramParameter()
			{
			}
		public:
			virtual IGAResource * queryInterface_IGAResource()=0;
			virtual Void setResource(UInt32 slot,IGAConstantBuffer * resource)=0;
			virtual Void setResource(UInt32 slot,IGASamplerState * resource)=0;
			virtual Void setResource(UInt32 slot,IGATextureView* resource)=0;
			virtual Void setResource(UInt32 slot,IGAShaderResourceBufferView* resource)=0;
		};
		class IGAShaderParameter
		{
		protected:
			virtual ~IGAShaderParameter()
			{
			}
		public:
			virtual IGAResource* queryInterface_IGAResource()=0;
			virtual Void setResource(UInt32 slot,IGAConstantBuffer* buffer)=0;
			virtual Void setResource(UInt32 slot,IGASamplerState* sampler)=0;
			virtual Void setResource(UInt32 slot,IGATextureView* view)=0;
			virtual Void setResource(UInt32 slot,IGAShaderResourceBufferView* resource)=0;
		};
		class IGAComputeShaderParameter
		{
		protected:
			virtual ~IGAComputeShaderParameter(){ }
		public:
			virtual IGAShaderParameter* queryInterface_IGAShaderParameter()=0;
			virtual Void setResource(UInt32 slot,IGAUnorderedAccessView* view)=0;
		};

		class IGAHeap
		{
		protected:
			virtual ~IGAHeap(){ }
		public:
			virtual IGAResource* queryInterface_IGAResource()=0;
		};
	}
}