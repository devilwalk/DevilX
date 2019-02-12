#pragma once
namespace NSDevilX
{
	namespace NSCore
	{
		class IGPUResource
		{
		protected:
			virtual ~IGPUResource(){ }
		public:
		};
		class IGPUHeap
		{
		protected:
			virtual ~IGPUHeap(){}
		public:
			virtual IGPUResource * queryInterface_IGPUResource()=0;
		};
		class IGPUDeviceResource
		{
		protected:
			virtual ~IGPUDeviceResource(){}
		public:
			virtual IGPUResource * queryInterface_IGPUResource()=0;
		};
		class IGPUBuffer
		{
		protected:
			virtual ~IGPUBuffer()
			{
			}
		public:
			virtual IGPUResource * queryInterface_IGPUResource()=0;
		};
		class IGPUTexture
		{
		protected:
			virtual ~IGPUTexture(){}
		public:
			virtual IGPUResource * queryInterface_IGPUResource()=0;
		};
		class IGPUTexture1D
		{
		protected:
			virtual ~IGPUTexture1D()
			{}
		public:
			virtual IGPUTexture * queryInterface_IGPUTexture()=0;
		};
		class IGPUTexture2D
		{
		protected:
			virtual ~IGPUTexture2D()
			{}
		public:
			virtual IGPUTexture * queryInterface_IGPUTexture()=0;
		};
		class IGPUTexture3D
		{
		protected:
			virtual ~IGPUTexture3D()
			{}
		public:
			virtual IGPUTexture * queryInterface_IGPUTexture()=0;
		};
		class IGPUInputLayout
		{
		protected:
			virtual ~IGPUInputLayout()
			{}
		public:
			virtual IGPUResource * queryInterface_IGPUResource()=0;
		};
		class IGPUPipelineState
		{
		protected:
			virtual ~IGPUPipelineState()
			{}
		public:
			virtual IGPUResource * queryInterface_IGPUResource()=0;
		};
		class IGPUShader
		{
		protected:
			virtual ~IGPUShader(){ }
		public:
			virtual IGPUResource * queryInterface_IGPUResource()=0;
		};
		class IGPUSampler
		{
		protected:
			virtual ~IGPUSampler(){ }
		public:
			virtual IGPUResource * queryInterface_IGPUResource()=0;
		};
		class IGPURootSignature
		{
		protected:
			virtual ~IGPURootSignature(){ }
		public:
			virtual IGPUResource * queryInterface_IGPUResource()=0;
		};
	}
}