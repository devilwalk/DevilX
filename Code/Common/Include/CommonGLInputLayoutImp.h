#pragma once
namespace NSDevilX
{
	namespace NSGraphicsAPI
	{
		class CGLInputLayoutImp
			:public IInputLayout
		{
		protected:
		public:
			CGLInputLayoutImp();
			virtual ~CGLInputLayoutImp();
		};

		class CGLVertexArrayObjectImp
			:public CGLObject
			,public IVertexArrayObject
			,public IInputLayout
		{
		protected:
		public:
			CGLVertexArrayObjectImp();
			virtual ~CGLVertexArrayObjectImp();
		};
	}
}