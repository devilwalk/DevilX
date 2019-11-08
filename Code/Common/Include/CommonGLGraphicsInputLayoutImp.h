#pragma once
namespace NSDevilX
{
	class CGLGraphicsInputLayoutImp
		:public IGraphicsInputLayout
		,public CGLGraphicsObject
	{
	protected:
	public:
		CGLGraphicsInputLayoutImp();
		virtual ~CGLGraphicsInputLayoutImp();
	};
}