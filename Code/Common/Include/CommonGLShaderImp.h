#pragma once
namespace NSDevilX
{
	namespace NSGraphicsAPI
	{
		class CGLShaderImp
			:public CGLObject
			,public IShader
		{
		protected:
		public:
			CGLShaderImp();
			virtual ~CGLShaderImp();
		};

		class CGLProgramImp
			:public CGLObject
			,public IProgram
		{
		protected:
		public:
			CGLProgramImp();
			virtual ~CGLProgramImp();
		};
	}
}