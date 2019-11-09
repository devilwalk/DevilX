#pragma once
namespace NSDevilX
{
	class CGLGraphicsVertexArrayObjectImp
		:public IGraphicsInputLayout
		,public CGLGraphicsObject
	{
	protected:
	public:
		CGLGraphicsVertexArrayObjectImp();
		virtual ~CGLGraphicsVertexArrayObjectImp();
	};
}