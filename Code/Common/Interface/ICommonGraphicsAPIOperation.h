#pragma once
namespace NSDevilX
{
	namespace NSGraphicsAPI
	{
		class IGraphicsOperation
		{
		protected:
			virtual ~IGraphicsOperation()
			{
			}
		public:
		};

		class IGraphicsRenderOperation
		{
		protected:
			virtual ~IGraphicsRenderOperation()
			{
			}
		public:
			virtual IGraphicsOperation* queryInterface_IGraphicsOperation()const=0;
		};

		class IGraphicsComputeOperation
		{
		protected:
			virtual ~IGraphicsComputeOperation()
			{
			}
		public:
			virtual IGraphicsOperation* queryInterface_IGraphicsOperation()const=0;
		};
	}
}