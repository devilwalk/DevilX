#pragma once
namespace NSDevilX
{
	namespace NSGraphicsAPI
	{
		class IShader
		{
		protected:
			virtual ~IShader()
			{
			}
		public:
		};

		class IGraphicsVertexShader
		{
		protected:
			virtual ~IGraphicsVertexShader()
			{
			}
		public:
			virtual IShader* queryInterface_IGraphicsShader()const=0;
		};

		class IGraphicsHullShader
		{
		protected:
			virtual ~IGraphicsHullShader()
			{
			}
		public:
			virtual IShader* queryInterface_IGraphicsShader()const=0;
		};

		class IGraphicsDomainShader
		{
		protected:
			virtual ~IGraphicsDomainShader()
			{
			}
		public:
			virtual IShader* queryInterface_IGraphicsShader()const=0;
		};

		class IGraphicsGeometryShader
		{
		protected:
			virtual ~IGraphicsGeometryShader()
			{
			}
		public:
			virtual IShader* queryInterface_IGraphicsShader()const=0;
		};

		class IGraphicsPixelShader
		{
		protected:
			virtual ~IGraphicsPixelShader()
			{
			}
		public:
			virtual IShader* queryInterface_IGraphicsShader()const=0;
		};

		class IProgram
		{
		protected:
			virtual ~IProgram()
			{
			}
		public:
		};

		class IProgramPipeline
		{
		protected:
			virtual ~IProgramPipeline(){ }
		public:
		};
	}
}