#pragma once
namespace NSDevilX
{
	class CGLGraphicsObject
	{
		friend class CGLGraphicsDeviceImp;
	protected:
		GLuint mInternal;
	public:
		CGLGraphicsObject();
		virtual ~CGLGraphicsObject();
	};
}