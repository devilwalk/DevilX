#pragma once
namespace NSDevilX
{
	namespace NSCore
	{
		namespace NSOpenGL
		{
			class IGAShaderReflectionImp
				:public IGAShaderReflection
				,public CGAObject
				,public TBaseObject<IGAShaderReflectionImp>
			{
			public:
				IGAShaderReflectionImp(GLuint program);
				~IGAShaderReflectionImp();
			};
			class IGAProgramReflectionImp
				:public IGAProgramReflection
				,public TBaseObject<IGAProgramReflectionImp>
				,public CGAObject
			{
			public:
				static const std::array<UInt32,5> msConstantBufferSlotOffsets;
				static const std::array<UInt32,5> msSamplerSlotOffsets;
				static const std::array<UInt32,5> msShaderResourceSlotOffsets;
			protected:
			public:
				IGAProgramReflectionImp(const GLuint * programs,UInt32 numPrograms);
				~IGAProgramReflectionImp();
			};
		}
	}
}