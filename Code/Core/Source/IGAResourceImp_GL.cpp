#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSCore;
using namespace NSOpenGL;

NSDevilX::NSCore::NSOpenGL::IGABufferImp::IGABufferImp(GLenum target,GLuint sizeInByte,GLbitfield flags,ConstVoidPtr initialData)
{
	if(glCreateBuffers)
	{
		glCreateBuffers(1,&mInternal);
		CUtility::checkGLError();
		glNamedBufferStorage(mInternal,sizeInByte,initialData,flags);
		CUtility::checkGLError();
	}
	else
	{
		glGenBuffers(1,&mInternal);
		CUtility::checkGLError();
		CGAStateManager::activeInstance()->bindBuffer(GL_ARRAY_BUFFER,mInternal);
		if(glBufferStorage)
		{
			glBufferStorage(GL_ARRAY_BUFFER,sizeInByte,initialData,flags);
			CUtility::checkGLError();
		}
		else
		{
			glBufferData(GL_ARRAY_BUFFER,sizeInByte,initialData,flags);
			CUtility::checkGLError();
		}
	}
}

NSDevilX::NSCore::NSOpenGL::IGABufferImp::~IGABufferImp()
{
	glDeleteBuffers(1,&mInternal);
	CUtility::checkGLError();
	mInternal=0;
}

NSDevilX::NSCore::IGAHighLevelBuffer * NSDevilX::NSCore::NSOpenGL::IGABufferImp::queryInterface_IGAHighLevelBuffer()
{
	return this;
}

GLuint NSDevilX::NSCore::NSOpenGL::IGABufferImp::getInternal() const
{
	return mInternal;
}

NSDevilX::NSCore::NSOpenGL::IGATextureImp::IGATextureImp(GLsizei width,GLenum internalFormat,GLint mipLevel,UInt32 arrayCount,const IGAStruct::SSubResourceData* initialData)
{
	_initialize1D(width,internalFormat,mipLevel,arrayCount,initialData);
}

NSDevilX::NSCore::NSOpenGL::IGATextureImp::IGATextureImp(GLsizei width,GLsizei height,GLenum internalFormat,GLint mipLevel,UInt32 arrayCount,Bool cubemap,const IGAStruct::SSubResourceData* initialData)
{
	if(height<=1)
	{
		_initialize1D(width,internalFormat,mipLevel,arrayCount,initialData);
	}
	else
		_initialize2D(width,height,internalFormat,mipLevel,arrayCount,cubemap,initialData);
}

NSDevilX::NSCore::NSOpenGL::IGATextureImp::IGATextureImp(GLsizei width,GLsizei height,GLsizei depth,GLenum internalFormat,GLint mipLevel,const IGAStruct::SSubResourceData* initialData)
{
	if(depth<=1)
	{
		if(height<=1)
		{
			_initialize1D(width,internalFormat,mipLevel,1,initialData);
		}
		else
			_initialize2D(width,height,internalFormat,mipLevel,1,false,initialData);
	}
	else
		_initialize3D(width,height,depth,internalFormat,mipLevel,initialData);
}

NSDevilX::NSCore::NSOpenGL::IGATextureImp::~IGATextureImp()
{
	glDeleteTextures(1,&mInternal);
	mInternal=0;
}

NSDevilX::NSCore::IGATexture * NSDevilX::NSCore::NSOpenGL::IGATextureImp::queryInterface_IGATexture()
{
	return this;
}

Void NSDevilX::NSCore::NSOpenGL::IGATextureImp::_initialize1D(GLsizei width,GLenum internalFormat,GLint mipLevel,UInt32 arrayCount,const IGAStruct::SSubResourceData* initialData)
{
	GLenum target=0;
	if(arrayCount<=1)
	{
		target=GL_TEXTURE_1D;
	}
	else
	{
		target=GL_TEXTURE_1D_ARRAY;
	}
	ConstVoidPtr mem_ptr=nullptr;
	if(initialData)
		mem_ptr=initialData->pSysMem;
	if(glCreateTextures)
	{
		glCreateTextures(target,1,&mInternal);
		CUtility::checkGLError();
		switch(target)
		{
		case GL_TEXTURE_1D:
		{
			if((GL_COMPRESSED_RGBA_S3TC_DXT1_EXT==internalFormat)
				||(GL_COMPRESSED_RGBA_S3TC_DXT3_EXT==internalFormat)
				||(GL_COMPRESSED_RGBA_S3TC_DXT5_EXT==internalFormat)
				)
				glCompressedTextureImage1DEXT(mInternal,target,0,internalFormat,width,0,initialData->SysMemSlicePitch,mem_ptr);
			else
				glTextureImage1DEXT(mInternal,target,0,internalFormat,width,0,CUtility::getColourFormat(internalFormat),GL_UNSIGNED_BYTE,mem_ptr);
			CUtility::checkGLError();
			if(initialData&&(mipLevel==0))
			{
				glGenerateTextureMipmap(mInternal);
				CUtility::checkGLError();
			}
		}
		break;
		case GL_TEXTURE_1D_ARRAY:
		{
			if((GL_COMPRESSED_RGBA_S3TC_DXT1_EXT==internalFormat)
				||(GL_COMPRESSED_RGBA_S3TC_DXT3_EXT==internalFormat)
				||(GL_COMPRESSED_RGBA_S3TC_DXT5_EXT==internalFormat)
				)
				glCompressedTextureImage2DEXT(mInternal,target,0,internalFormat,width,arrayCount,0,initialData->SysMemSlicePitch,mem_ptr);
			else
				glTextureImage2DEXT(mInternal,target,0,internalFormat,width,arrayCount,0,CUtility::getColourFormat(internalFormat),GL_UNSIGNED_BYTE,mem_ptr);
			CUtility::checkGLError();
			if(initialData&&(mipLevel==0))
			{
				glGenerateTextureMipmap(mInternal);
				CUtility::checkGLError();
			}
		}
		break;
		}
	}
	else
	{
		glGenTextures(1,&mInternal);
		CUtility::checkGLError();
		CGAStateManager::activeInstance()->bindTexture(target,mInternal);
		switch(target)
		{
		case GL_TEXTURE_1D:
		{
			if((GL_COMPRESSED_RGBA_S3TC_DXT1_EXT==internalFormat)
				||(GL_COMPRESSED_RGBA_S3TC_DXT3_EXT==internalFormat)
				||(GL_COMPRESSED_RGBA_S3TC_DXT5_EXT==internalFormat)
				)
				glCompressedTexImage1D(target,0,internalFormat,width,0,initialData->SysMemSlicePitch,mem_ptr);
			else
				glTexImage1D(target,0,internalFormat,width,0,CUtility::getColourFormat(internalFormat),GL_UNSIGNED_BYTE,mem_ptr);
			CUtility::checkGLError();
			if(initialData&&(mipLevel==0))
			{
				glGenerateMipmap(target);
				CUtility::checkGLError();
			}
		}
		break;
		case GL_TEXTURE_1D_ARRAY:
		{
			if((GL_COMPRESSED_RGBA_S3TC_DXT1_EXT==internalFormat)
				||(GL_COMPRESSED_RGBA_S3TC_DXT3_EXT==internalFormat)
				||(GL_COMPRESSED_RGBA_S3TC_DXT5_EXT==internalFormat)
				)
				glCompressedTexImage2D(target,0,internalFormat,width,arrayCount,0,initialData->SysMemSlicePitch,mem_ptr);
			else
				glTexImage2D(target,0,internalFormat,width,arrayCount,0,CUtility::getColourFormat(internalFormat),GL_UNSIGNED_BYTE,mem_ptr);
			CUtility::checkGLError();
			if(initialData&&(mipLevel==0))
			{
				glGenerateMipmap(target);
				CUtility::checkGLError();
			}
		}
		break;
		}
		CGAStateManager::activeInstance()->bindTexture(target,0);
	}
}

Void NSDevilX::NSCore::NSOpenGL::IGATextureImp::_initialize2D(GLsizei width,GLsizei height,GLenum internalFormat,GLint mipLevel,UInt32 arrayCount,Bool cubemap,const IGAStruct::SSubResourceData* initialData)
{
	GLenum target=0;
	if(arrayCount<=1)
	{
		target=cubemap?GL_TEXTURE_CUBE_MAP:GL_TEXTURE_2D;
	}
	else
	{
		target=cubemap?GL_TEXTURE_CUBE_MAP_ARRAY:GL_TEXTURE_2D_ARRAY;
	}
	ConstVoidPtr mem_ptr=nullptr;
	if(initialData)
		mem_ptr=initialData->pSysMem;
	if(glCreateTextures)
	{
		glCreateTextures(target,1,&mInternal);
		CUtility::checkGLError();
		switch(target)
		{
		case GL_TEXTURE_2D:
		case GL_TEXTURE_CUBE_MAP:
		{
			if((GL_COMPRESSED_RGBA_S3TC_DXT1_EXT==internalFormat)
				||(GL_COMPRESSED_RGBA_S3TC_DXT3_EXT==internalFormat)
				||(GL_COMPRESSED_RGBA_S3TC_DXT5_EXT==internalFormat)
				)
				glCompressedTextureImage2DEXT(mInternal,target,0,internalFormat,width,height,0,initialData->SysMemSlicePitch,mem_ptr);
			else
				glTextureImage2DEXT(mInternal,target,0,internalFormat,width,height,0,CUtility::getColourFormat(internalFormat),GL_UNSIGNED_BYTE,mem_ptr);
			CUtility::checkGLError();
			if(initialData&&(mipLevel==0))
			{
				glGenerateTextureMipmap(mInternal);
				CUtility::checkGLError();
			}
		}
		break;
		case GL_TEXTURE_2D_ARRAY:
		{
			if((GL_COMPRESSED_RGBA_S3TC_DXT1_EXT==internalFormat)
				||(GL_COMPRESSED_RGBA_S3TC_DXT3_EXT==internalFormat)
				||(GL_COMPRESSED_RGBA_S3TC_DXT5_EXT==internalFormat)
				)
				glCompressedTextureImage3DEXT(mInternal,target,0,internalFormat,width,height,arrayCount,0,initialData->SysMemSlicePitch,mem_ptr);
			else
				glTextureImage3DEXT(mInternal,target,0,internalFormat,width,height,arrayCount,0,CUtility::getColourFormat(internalFormat),GL_UNSIGNED_BYTE,mem_ptr);
			CUtility::checkGLError();
			if(initialData&&(mipLevel==0))
			{
				glGenerateTextureMipmap(mInternal);
				CUtility::checkGLError();
			}
		}
		break;
		case GL_TEXTURE_CUBE_MAP_ARRAY:
			assert(0);
			break;
		}
	}
	else
	{
		glGenTextures(1,&mInternal);
		CUtility::checkGLError();
		CGAStateManager::activeInstance()->bindTexture(target,mInternal);
		switch(target)
		{
		case GL_TEXTURE_2D:
		case GL_TEXTURE_CUBE_MAP:
		{
			if((GL_COMPRESSED_RGBA_S3TC_DXT1_EXT==internalFormat)
				||(GL_COMPRESSED_RGBA_S3TC_DXT3_EXT==internalFormat)
				||(GL_COMPRESSED_RGBA_S3TC_DXT5_EXT==internalFormat)
				)
				glCompressedTexImage2D(target,0,internalFormat,width,height,0,initialData->SysMemSlicePitch,mem_ptr);
			else
				glTexImage2D(target,0,internalFormat,width,height,0,CUtility::getColourFormat(internalFormat),GL_UNSIGNED_BYTE,mem_ptr);
			CUtility::checkGLError();
			if(initialData&&(mipLevel==0))
			{
				glGenerateMipmap(target);
				CUtility::checkGLError();
			}
		}
		break;
		case GL_TEXTURE_2D_ARRAY:
		{
			if((GL_COMPRESSED_RGBA_S3TC_DXT1_EXT==internalFormat)
				||(GL_COMPRESSED_RGBA_S3TC_DXT3_EXT==internalFormat)
				||(GL_COMPRESSED_RGBA_S3TC_DXT5_EXT==internalFormat)
				)
				glCompressedTexImage3D(target,0,internalFormat,width,height,arrayCount,0,initialData->SysMemSlicePitch,mem_ptr);
			else
				glTexImage3D(target,0,internalFormat,width,height,arrayCount,0,CUtility::getColourFormat(internalFormat),GL_UNSIGNED_BYTE,mem_ptr);
			CUtility::checkGLError();
			if(initialData&&(mipLevel==0))
			{
				glGenerateMipmap(target);
				CUtility::checkGLError();
			}
		}
		break;
		case GL_TEXTURE_CUBE_MAP_ARRAY:
			assert(0);
			break;
		}
		CGAStateManager::activeInstance()->bindTexture(target,0);
	}
}

Void NSDevilX::NSCore::NSOpenGL::IGATextureImp::_initialize3D(GLsizei width,GLsizei height,GLsizei depth,GLenum internalFormat,GLint mipLevel,const IGAStruct::SSubResourceData* initialData)
{
	ConstVoidPtr mem_ptr=nullptr;
	if(initialData)
		mem_ptr=initialData->pSysMem;
	if(glCreateTextures)
	{
		glCreateTextures(GL_TEXTURE_3D,1,&mInternal);
		CUtility::checkGLError();
		if((GL_COMPRESSED_RGBA_S3TC_DXT1_EXT==internalFormat)
			||(GL_COMPRESSED_RGBA_S3TC_DXT3_EXT==internalFormat)
			||(GL_COMPRESSED_RGBA_S3TC_DXT5_EXT==internalFormat)
			)
			glCompressedTextureImage3DEXT(mInternal,GL_TEXTURE_3D,0,internalFormat,width,height,depth,0,initialData->SysMemSlicePitch,mem_ptr);
		else
			glTextureImage3DEXT(mInternal,GL_TEXTURE_3D,mipLevel,internalFormat,width,height,depth,0,CUtility::getColourFormat(internalFormat),GL_UNSIGNED_BYTE,mem_ptr);
		CUtility::checkGLError();
		if(initialData&&(mipLevel==0))
		{
			glGenerateMipmap(GL_TEXTURE_3D);
			CUtility::checkGLError();
		}
	}
	else
	{
		glGenTextures(1,&mInternal);
		CUtility::checkGLError();
		CGAStateManager::activeInstance()->bindTexture(GL_TEXTURE_3D,mInternal);
		if((GL_COMPRESSED_RGBA_S3TC_DXT1_EXT==internalFormat)
			||(GL_COMPRESSED_RGBA_S3TC_DXT3_EXT==internalFormat)
			||(GL_COMPRESSED_RGBA_S3TC_DXT5_EXT==internalFormat)
			)
			glCompressedTexImage3D(GL_TEXTURE_3D,0,internalFormat,width,height,depth,0,initialData->SysMemSlicePitch,mem_ptr);
		else
			glTexImage3D(GL_TEXTURE_3D,mipLevel,internalFormat,width,height,depth,0,CUtility::getColourFormat(internalFormat),GL_UNSIGNED_BYTE,mem_ptr);
		CUtility::checkGLError();
		if(initialData&&(mipLevel==0))
		{
			glGenerateMipmap(GL_TEXTURE_3D);
			CUtility::checkGLError();
		}
		CGAStateManager::activeInstance()->bindTexture(GL_TEXTURE_3D,0);
	}
}

GLuint NSDevilX::NSCore::NSOpenGL::IGATextureImp::getInternal() const
{
	return mInternal;
}

NSDevilX::NSCore::NSOpenGL::IGAInputLayoutImp::IGAInputLayoutImp(const TVector(IGAStruct::SInputElementDesc)& inputElementDescs)
	:mInputElementDescs(inputElementDescs)
{
	if(glCreateVertexArrays)
	{
		glCreateVertexArrays(1,&mInternal);
		CUtility::checkGLError();
		for(UInt32 i=0,count=static_cast<UInt32>(mInputElementDescs.size());i<count;++i)
		{
			glVertexArrayAttribFormat(mInternal,mInputElementDescs[i].InputSlot,CUtility::getComponentCount(mInputElementDescs[i].Format),CUtility::getComponentType(mInputElementDescs[i].Format),CUtility::needNormalize(mInputElementDescs[i].Format),mInputElementDescs[i].AlignedByteOffset);
			CUtility::checkGLError();
			glVertexArrayAttribBinding(mInternal,mInputElementDescs[i].InputSlot,mInputElementDescs[i].InputSlot);
			CUtility::checkGLError();
			glEnableVertexArrayAttrib(mInternal,mInputElementDescs[i].InputSlot);
			CUtility::checkGLError();
		}
	}
	else if(glGenVertexArrays)
	{
		glGenVertexArrays(1,&mInternal);
		CUtility::checkGLError();
		CGAStateManager::activeInstance()->bindVertexArray(mInternal);
		for(UInt32 i=0,count=static_cast<UInt32>(mInputElementDescs.size());i<count;++i)
		{
			glVertexAttribFormat(mInputElementDescs[i].InputSlot,CUtility::getComponentCount(mInputElementDescs[i].Format),CUtility::getComponentType(mInputElementDescs[i].Format),CUtility::needNormalize(mInputElementDescs[i].Format),mInputElementDescs[i].AlignedByteOffset);
			CUtility::checkGLError();
			glVertexAttribBinding(mInputElementDescs[i].InputSlot,mInputElementDescs[i].InputSlot);
			CUtility::checkGLError();
			glEnableVertexAttribArray(mInputElementDescs[i].InputSlot);
			CUtility::checkGLError();
		}
		CGAStateManager::activeInstance()->bindVertexArray(0);
	}
}

NSDevilX::NSCore::NSOpenGL::IGAInputLayoutImp::~IGAInputLayoutImp()
{
	if(mInternal)
	{
		glDeleteVertexArrays(1,&mInternal);
		CUtility::checkGLError();
		mInternal=0;
	}
}

NSDevilX::NSCore::NSOpenGL::IGAShaderImp::IGAShaderImp(const String & glsl,IGAEnum::EShaderType type)
{
	GLenum shader_type;
	switch(type)
	{
	case IGAEnum::EShaderType_Vertex:
		shader_type=GL_VERTEX_SHADER;
		break;
	case IGAEnum::EShaderType_Geometry:
		shader_type=GL_GEOMETRY_SHADER;
		break;
	case IGAEnum::EShaderType_Pixel:
		shader_type=GL_FRAGMENT_SHADER;
		break;
	case IGAEnum::EShaderType_Hull:
		shader_type=GL_TESS_CONTROL_SHADER;
		break;
	case IGAEnum::EShaderType_Domain:
		shader_type=GL_TESS_EVALUATION_SHADER;
		break;
	}
	const GLchar * code_str=&glsl[0];
	if(glGenProgramPipelines)
	{
		if(glCreateShaderProgramv)
		{
			mInternal=glCreateShaderProgramv(shader_type,1,&code_str);
			CUtility::checkGLError();
		}
		else
		{
			auto shader=glCreateShader(shader_type);
			CUtility::checkGLError();
			glShaderSource(shader,1,&code_str,nullptr);
			CUtility::checkGLError();
			glCompileShader(shader);
			CUtility::checkGLError();
			GLint compiler_status=GL_FALSE;
			glGetShaderiv(shader,GL_COMPILE_STATUS,&compiler_status);
			CUtility::checkGLError();
			if(GL_TRUE!=compiler_status)
			{
				String shader_log;
				shader_log.resize(1024);
				glGetShaderInfoLog(shader,1024,nullptr,&shader_log[0]);
				CUtility::checkGLError();
#if DEVILX_DEBUG
#if DEVILX_OPERATING_SYSTEM==DEVILX_OPERATING_SYSTEM_WINDOWS
				OutputDebugStringA(shader_log.c_str());
				OutputDebugStringA("\r\n");
#endif
#endif
			}
			mInternal=glCreateProgram();
			CUtility::checkGLError();
			glProgramParameteri(mInternal,GL_PROGRAM_SEPARABLE,GL_TRUE);
			CUtility::checkGLError();
			glAttachShader(mInternal,shader);
			CUtility::checkGLError();
			glLinkProgram(mInternal);
			CUtility::checkGLError();
			glDetachShader(mInternal,shader);
			CUtility::checkGLError();
			glDeleteShader(shader);
			CUtility::checkGLError();
		}
		GLint link_status=GL_FALSE;
		glGetProgramiv(mInternal,GL_LINK_STATUS,&link_status);
		if(GL_TRUE!=link_status)
		{
			String shader_log;
			shader_log.resize(1024);
			glGetProgramInfoLog(mInternal,1024,nullptr,&shader_log[0]);
			CUtility::checkGLError();
#if DEVILX_DEBUG
#if DEVILX_OPERATING_SYSTEM==DEVILX_OPERATING_SYSTEM_WINDOWS
			OutputDebugStringA(("program log:"+shader_log).c_str());
			OutputDebugStringA("\r\n");
#endif
#endif
		}
	}
	else
	{
		mInternal=glCreateShader(shader_type);
		CUtility::checkGLError();
		glShaderSource(mInternal,1,&code_str,nullptr);
		CUtility::checkGLError();
		glCompileShader(mInternal);
		CUtility::checkGLError();
		GLint compiler_status=GL_FALSE;
		glGetShaderiv(mInternal,GL_COMPILE_STATUS,&compiler_status);
		CUtility::checkGLError();
		if(GL_TRUE!=compiler_status)
		{
			String shader_log;
			shader_log.resize(1024);
			glGetShaderInfoLog(mInternal,1024,nullptr,&shader_log[0]);
			CUtility::checkGLError();
#if DEVILX_DEBUG
#if DEVILX_OPERATING_SYSTEM==DEVILX_OPERATING_SYSTEM_WINDOWS
			OutputDebugStringA(shader_log.c_str());
			OutputDebugStringA("\r\n");
#endif
#endif
		}
	}
}

NSDevilX::NSCore::NSOpenGL::IGAShaderImp::~IGAShaderImp()
{
	if(mInternal)
	{
		if(glGenProgramPipelines)
			glDeleteProgram(mInternal);
		else
			glDeleteShader(mInternal);
		CUtility::checkGLError();
		mInternal=0;
	}
}

IGAShader* NSDevilX::NSCore::NSOpenGL::IGAShaderImp::queryInterface_IGAShader()
{
	return this;
}

IGAProgramReflectionImp* NSDevilX::NSCore::NSOpenGL::IGAShaderImp::createReflection()
{
	return DEVILX_NEW IGAProgramReflectionImp(&mInternal,1);
}

NSDevilX::NSCore::NSOpenGL::IGAProgramImp::IGAProgramImp()
{
}

NSDevilX::NSCore::NSOpenGL::IGAProgramImp::~IGAProgramImp()
{
}

NSDevilX::NSCore::NSOpenGL::CGAProgramImp::CGAProgramImp(GLuint vertexShader,GLuint pixelShader,GLuint geometryShader,GLuint hullShader,GLuint domainShader)
{
	mInternal=glCreateProgram();
	CUtility::checkGLError();
	if(vertexShader)
	{
		glAttachShader(mInternal,vertexShader);
		CUtility::checkGLError();
	}
	if(pixelShader)
	{
		glAttachShader(mInternal,pixelShader);
		CUtility::checkGLError();
	}
	if(geometryShader)
	{
		glAttachShader(mInternal,geometryShader);
		CUtility::checkGLError();
	}
	if(hullShader)
	{
		glAttachShader(mInternal,hullShader);
		CUtility::checkGLError();
	}
	if(domainShader)
	{
		glAttachShader(mInternal,domainShader);
		CUtility::checkGLError();
	}
	glLinkProgram(mInternal);
	CUtility::checkGLError();
	GLint link_status=GL_FALSE;
	glGetProgramiv(mInternal,GL_LINK_STATUS,&link_status);
	if(GL_TRUE!=link_status)
	{
		String shader_log;
		shader_log.resize(1024);
		glGetProgramInfoLog(mInternal,1024,nullptr,&shader_log[0]);
		CUtility::checkGLError();
#if DEVILX_DEBUG
#if DEVILX_OPERATING_SYSTEM==DEVILX_OPERATING_SYSTEM_WINDOWS
		OutputDebugStringA(("program log:"+shader_log).c_str());
		OutputDebugStringA("\r\n");
#endif
#endif
	}
	if(vertexShader)
	{
		glDetachShader(mInternal,vertexShader);
		CUtility::checkGLError();
	}
	if(pixelShader)
	{
		glDetachShader(mInternal,pixelShader);
		CUtility::checkGLError();
	}
	if(geometryShader)
	{
		glDetachShader(mInternal,geometryShader);
		CUtility::checkGLError();
	}
	if(hullShader)
	{
		glDetachShader(mInternal,hullShader);
		CUtility::checkGLError();
	}
	if(domainShader)
	{
		glDetachShader(mInternal,domainShader);
		CUtility::checkGLError();
	}
}

NSDevilX::NSCore::NSOpenGL::CGAProgramImp::~CGAProgramImp()
{
	glDeleteProgram(mInternal);
}

IGAProgramReflectionImp* NSDevilX::NSCore::NSOpenGL::CGAProgramImp::createReflection()
{
	return DEVILX_NEW IGAProgramReflectionImp(&mInternal,1);
}

NSDevilX::NSCore::NSOpenGL::IGASamplerStateImp::IGASamplerStateImp(const IGAStruct::SSamplerDesc & desc)
	:mDescription(desc)
{
	if(glCreateSamplers)
	{
		glCreateSamplers(1,&mInternal);
		CUtility::checkGLError();
	}
	else if(glGenSamplers)
	{
		glGenSamplers(1,&mInternal);
		CUtility::checkGLError();
	}
	if(glBindSampler)
	{
		CGAStateManager::activeInstance()->bindSampler(0,mInternal);
		CUtility::checkGLError();
		glSamplerParameteri(0,GL_TEXTURE_MIN_FILTER,CUtility::mappingMinFilter(desc.Filter));
		CUtility::checkGLError();
		glSamplerParameteri(0,GL_TEXTURE_MAG_FILTER,CUtility::mappingMagFilter(desc.Filter));
		CUtility::checkGLError();
		glSamplerParameteri(0,GL_TEXTURE_WRAP_S,CUtility::mapping(desc.AddressU));
		CUtility::checkGLError();
		glSamplerParameteri(0,GL_TEXTURE_WRAP_T,CUtility::mapping(desc.AddressV));
		CUtility::checkGLError();
		glSamplerParameteri(0,GL_TEXTURE_WRAP_R,CUtility::mapping(desc.AddressW));
		CUtility::checkGLError();
		glSamplerParameterf(0,GL_TEXTURE_MIN_LOD,desc.MinLOD);
		CUtility::checkGLError();
		glSamplerParameterf(0,GL_TEXTURE_MAX_LOD,desc.MaxLOD);
		CUtility::checkGLError();
		glSamplerParameteri(0,GL_TEXTURE_COMPARE_MODE,CUtility::mappingCompareMode(desc.Filter));
		CUtility::checkGLError();
		glSamplerParameteri(0,GL_TEXTURE_COMPARE_FUNC,CUtility::mapping(desc.ComparisonFunc));
		CUtility::checkGLError();
		glSamplerParameterfv(0,GL_TEXTURE_BORDER_COLOR,desc.BorderColor);
		CUtility::checkGLError();
		glSamplerParameterf(0,GL_TEXTURE_LOD_BIAS,desc.MipLODBias);
		CUtility::checkGLError();
		CGAStateManager::activeInstance()->bindSampler(0,0);
		CUtility::checkGLError();
	}
}

NSDevilX::NSCore::NSOpenGL::IGASamplerStateImp::~IGASamplerStateImp()
{
	if(mInternal)
	{
		glDeleteSamplers(1,&mInternal);
		CUtility::checkGLError();
		mInternal=0;
	}
}

NSDevilX::NSCore::NSOpenGL::IGABlendStateImp::IGABlendStateImp(const IGAStruct::SBlendDesc& desc)
	:mDescription(desc)
{
}

NSDevilX::NSCore::NSOpenGL::IGABlendStateImp::~IGABlendStateImp()
{
}

NSDevilX::NSCore::NSOpenGL::IGARasterizerStateImp::IGARasterizerStateImp(const IGAStruct::SRasterizerDesc& desc)
	:mDescription(desc)
{
}

NSDevilX::NSCore::NSOpenGL::IGARasterizerStateImp::~IGARasterizerStateImp()
{
}

NSDevilX::NSCore::NSOpenGL::IGADepthStencilStateImp::IGADepthStencilStateImp(const IGAStruct::SDepthStencilDesc& desc)
	:mDescription(desc)
{
}

NSDevilX::NSCore::NSOpenGL::IGADepthStencilStateImp::~IGADepthStencilStateImp()
{
}

NSDevilX::NSCore::NSOpenGL::IGAProgramParameterImp::IGAProgramParameterImp()
{
}

NSDevilX::NSCore::NSOpenGL::IGAProgramParameterImp::~IGAProgramParameterImp()
{
}

Void NSDevilX::NSCore::NSOpenGL::IGAProgramParameterImp::setResource(UInt32 slot,IGAConstantBuffer* resource)
{
	if(mConstantBuffers.size()<=slot)
		mConstantBuffers.resize(slot+1);
	mConstantBuffers[slot]=static_cast<IGABufferImp*>(resource)->getInternal();
}

Void NSDevilX::NSCore::NSOpenGL::IGAProgramParameterImp::setResource(UInt32 slot,IGASamplerState* resource)
{
	if(mSamplers.size()<=slot)
		mSamplers.resize(slot+1);
	mSamplers[slot]=static_cast<IGASamplerStateImp*>(resource)->getInternal();
}

Void NSDevilX::NSCore::NSOpenGL::IGAProgramParameterImp::setResource(UInt32 slot,IGATextureView* resource)
{
	if(mTextures.size()<=slot)
		mTextures.resize(slot+1);
	mTextures[slot]=static_cast<IGATextureViewImp*>(resource)->getInternal();
}

IGAShaderParameter* NSDevilX::NSCore::NSOpenGL::IGAProgramParameterImp::queryInterface_IGAShaderParameter()
{
	return this;
}

Void NSDevilX::NSCore::NSOpenGL::IGAProgramParameterImp::setResource(UInt32 slot,IGAUnorderedAccessView* view)
{
	if(mShaderStorageBuffers.size()<=slot)
		mShaderStorageBuffers.resize(slot+1);
}

Void NSDevilX::NSCore::NSOpenGL::IGAProgramParameterImp::setResource(UInt32 slot,IGAShaderResourceBufferView* resource)
{
	if(mShaderStorageBuffers.size()<=slot)
		mShaderStorageBuffers.resize(slot+1);
	mShaderStorageBuffers[slot]=static_cast<IGAShaderResourceBufferViewImp*>(resource);
}
