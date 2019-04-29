#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSCore;
using namespace NSOpenGL;

const std::array<UInt32, 5> NSDevilX::NSCore::NSOpenGL::IGAProgramReflectionImp::msConstantBufferSlotOffsets = { 0, static_cast<UInt16>(-1), static_cast<UInt16>(-1) * 2, static_cast<UInt16>(-1) * 3, static_cast<UInt16>(-1) * 4 };
const std::array<UInt32, 5> NSDevilX::NSCore::NSOpenGL::IGAProgramReflectionImp::msSamplerSlotOffsets = { 0, static_cast<UInt16>(-1), static_cast<UInt16>(-1) * 2, static_cast<UInt16>(-1) * 3, static_cast<UInt16>(-1) * 4 };
const std::array<UInt32, 5> NSDevilX::NSCore::NSOpenGL::IGAProgramReflectionImp::msShaderResourceSlotOffsets = { 0, static_cast<UInt16>(-1), static_cast<UInt16>(-1) * 2, static_cast<UInt16>(-1) * 3, static_cast<UInt16>(-1) * 4 };

NSDevilX::NSCore::NSOpenGL::IGAProgramReflectionImp::IGAProgramReflectionImp(const GLuint* programs,UInt32 numPrograms)
{
	for(UInt32 i=0;i<numPrograms;++i)
	{
		GLint num=0;
		glGetProgramiv(programs[i],GL_ACTIVE_ATTRIBUTES,&num);
	}
}

NSDevilX::NSCore::NSOpenGL::IGAProgramReflectionImp::~IGAProgramReflectionImp()
{
}
