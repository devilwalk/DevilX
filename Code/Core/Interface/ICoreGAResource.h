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
		class IGAHeap
		{
		protected:
			virtual ~IGAHeap(){}
		public:
			virtual IGAResource * queryInterface_IGAResource()=0;
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
		class IGAPipelineState
		{
		protected:
			virtual ~IGAPipelineState()
			{}
		public:
			virtual IGAResource * queryInterface_IGAResource()=0;
		};
		class IGAShader
		{
		protected:
			virtual ~IGAShader(){ }
		public:
			virtual IGAResource * queryInterface_IGAResource()=0;
		};
		class IGASampler
		{
		protected:
			virtual ~IGASampler(){ }
		public:
			virtual IGAResource * queryInterface_IGAResource()=0;
		};
	}
}