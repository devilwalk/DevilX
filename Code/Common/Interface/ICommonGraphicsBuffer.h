#pragma once
namespace NSDevilX
{
	class IGraphicsBuffer
	{
	protected:
		virtual ~IGraphicsBuffer(){}
	public:
	};

	class IGraphicsVertexBuffer
	{
	protected:
		virtual ~IGraphicsVertexBuffer(){}
	public:
		virtual IGraphicsBuffer* queryInterface_IGraphicsBuffer()const=0;
	};

	class IGraphicsIndexBuffer
	{
	protected:
		virtual ~IGraphicsIndexBuffer(){}
	public:
		virtual IGraphicsBuffer* queryInterface_IGraphicsBuffer()const=0;
	};
}