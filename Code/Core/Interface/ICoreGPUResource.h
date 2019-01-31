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
		class IGPUBuffer
		{
		protected:
			virtual ~IGPUBuffer()
			{
			}
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
		class IGPUInputLayout
		{
		protected:
			virtual ~IGPUInputLayout(){ }
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