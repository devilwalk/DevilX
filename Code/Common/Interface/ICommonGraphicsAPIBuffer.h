#pragma once
namespace NSDevilX
{
	namespace NSGraphicsAPI
	{
		class IBuffer
		{
		protected:
			virtual ~IBuffer()
			{
			}
		public:
		};

		class IVertexBuffer
		{
		protected:
			virtual ~IVertexBuffer()
			{
			}
		public:
			virtual IBuffer* queryInterface_IBuffer()const=0;
		};

		class IIndexBuffer
		{
		protected:
			virtual ~IIndexBuffer()
			{
			}
		public:
			virtual IBuffer* queryInterface_IBuffer()const=0;
		};
	}
}