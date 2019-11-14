#include "Precompiler.h"
using namespace NSDevilX;

#define SAVE_STATE(func,...) static_cast<CGLStateImp*>(state)->mStateChanges.push_back(new S##func(__VA_ARGS__))

NSDevilX::NSGraphicsAPI::CGLDeviceImp::CGLDeviceImp()
{
}

NSDevilX::NSGraphicsAPI::CGLDeviceImp::~CGLDeviceImp()
{
}

Bool NSDevilX::NSGraphicsAPI::CGLDeviceImp::createVertexBuffer(UINT length,DWORD usage,DWORD fvf,D3DPOOL pool,OUT IBuffer* buffer)
{
	return createBufferData(GL_ARRAY_BUFFER,length,nullptr,mappingGL(pool,usage),buffer);
}

Bool NSDevilX::NSGraphicsAPI::CGLDeviceImp::createIndexBuffer(UINT length,DWORD usage,D3DFORMAT format,D3DPOOL pool,OUT IBuffer* buffer)
{
	return createBufferData(GL_ELEMENT_ARRAY_BUFFER,length,nullptr,mappingGL(pool,usage),buffer);
}

Bool NSDevilX::NSGraphicsAPI::CGLDeviceImp::createBuffer(const D3D10_BUFFER_DESC& desc,const D3D10_SUBRESOURCE_DATA* initializeData,OUT IBuffer* buffer)
{
	GLenum target=0;
	switch(desc.BindFlags)
	{
	case D3D10_BIND_VERTEX_BUFFER:
		target=GL_ARRAY_BUFFER;
		break;
	case D3D10_BIND_INDEX_BUFFER:
		target=GL_ELEMENT_ARRAY_BUFFER;
		break;
	}
	ConstVoidPtr data=nullptr;
	if(initializeData)
	{
		data=initializeData->pSysMem;
	}
	return createBufferData(target,desc.ByteWidth,data,mappingGL(desc.Usage,desc.CPUAccessFlags),buffer);
}

Bool NSDevilX::NSGraphicsAPI::CGLDeviceImp::createBuffer(const D3D11_BUFFER_DESC& desc,const D3D11_SUBRESOURCE_DATA* initializeData,OUT IBuffer* buffer)
{
	GLenum target=0;
	switch(desc.BindFlags)
	{
	case D3D11_BIND_VERTEX_BUFFER:
		target=GL_ARRAY_BUFFER;
		break;
	case D3D11_BIND_INDEX_BUFFER:
		target=GL_ELEMENT_ARRAY_BUFFER;
		break;
	}
	ConstVoidPtr data=nullptr;
	if(initializeData)
	{
		data=initializeData->pSysMem;
	}
	return createBufferData(target,desc.ByteWidth,data,mappingGL(desc.Usage,desc.CPUAccessFlags),buffer);
}

Bool NSDevilX::NSGraphicsAPI::CGLDeviceImp::createBufferData(GLenum target,GLsizeiptr size,ConstVoidPtr intializeData,GLenum usage,OUT IBuffer* buffer)
{
	glGenBuffers(1,&static_cast<CGLBufferImp*>(buffer)->mInternal);
	glBindBuffer(target,static_cast<CGLBufferImp*>(buffer)->mInternal);
	glBufferData(target,size,intializeData,usage);
	glBindBuffer(target,0);
	return True;
}

Bool NSDevilX::NSGraphicsAPI::CGLDeviceImp::createBufferStorage(GLenum target,GLsizeiptr size,ConstVoidPtr intializeData,GLbitfield flags,OUT IBuffer* buffer)
{
	glGenBuffers(1,&static_cast<CGLBufferImp*>(buffer)->mInternal);
	glBindBuffer(target,static_cast<CGLBufferImp*>(buffer)->mInternal);
	glBufferStorage(target,size,intializeData,flags);
	glBindBuffer(target,0);
	return True;
}

Bool NSDevilX::NSGraphicsAPI::CGLDeviceImp::createTexture(UINT width,UINT height,UINT levels,DWORD usage,D3DFORMAT format,D3DPOOL pool,OUT ITexture* texture)
{
	if(isCompressedFormat(format))
	{
		if(height==1)
		{
			return createCompressedTexture1D(GL_TEXTURE_1D,levels,mappingGLInternalFormat(format),width,0,0,nullptr,texture);
		}
		else
		{
			return createCompressedTexture2D(GL_TEXTURE_2D,levels,mappingGLInternalFormat(format),width,height,0,0,nullptr,texture);
		}
	}
	else
	{
		if(height==1)
		{
			return createTexture1D(GL_TEXTURE_1D,levels,mappingGLInternalFormat(format),width,0,mappingGLFormat(format),GL_BYTE,nullptr,texture);
		}
		else
		{
			return createTexture2D(GL_TEXTURE_2D,levels,mappingGLInternalFormat(format),width,height,0,mappingGLFormat(format),GL_BYTE,nullptr,texture);
		}
	}
}

Bool NSDevilX::NSGraphicsAPI::CGLDeviceImp::createCubeTexture(UINT edageLength,UINT levels,DWORD usage,D3DFORMAT format,D3DPOOL pool,OUT ITexture* texture)
{
	if(isCompressedFormat(format))
	{
		Bool ret=createCompressedTexture2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X,levels,mappingGLInternalFormat(format),edageLength,edageLength,0,0,nullptr,texture);
		ret&=createCompressedTexture2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y,levels,mappingGLInternalFormat(format),edageLength,edageLength,0,0,nullptr,texture);
		ret&=createCompressedTexture2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z,levels,mappingGLInternalFormat(format),edageLength,edageLength,0,0,nullptr,texture);
		ret&=createCompressedTexture2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X,levels,mappingGLInternalFormat(format),edageLength,edageLength,0,0,nullptr,texture);
		ret&=createCompressedTexture2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,levels,mappingGLInternalFormat(format),edageLength,edageLength,0,0,nullptr,texture);
		ret&=createCompressedTexture2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,levels,mappingGLInternalFormat(format),edageLength,edageLength,0,0,nullptr,texture);
		return ret;
	}
	else
	{
		Bool ret=createTexture2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X,levels,mappingGLInternalFormat(format),edageLength,edageLength,0,mappingGLFormat(format),GL_BYTE,nullptr,texture);
		ret&=createTexture2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y,levels,mappingGLInternalFormat(format),edageLength,edageLength,0,mappingGLFormat(format),GL_BYTE,nullptr,texture);
		ret&=createTexture2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z,levels,mappingGLInternalFormat(format),edageLength,edageLength,0,mappingGLFormat(format),GL_BYTE,nullptr,texture);
		ret&=createTexture2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X,levels,mappingGLInternalFormat(format),edageLength,edageLength,0,mappingGLFormat(format),GL_BYTE,nullptr,texture);
		ret&=createTexture2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,levels,mappingGLInternalFormat(format),edageLength,edageLength,0,mappingGLFormat(format),GL_BYTE,nullptr,texture);
		ret&=createTexture2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,levels,mappingGLInternalFormat(format),edageLength,edageLength,0,mappingGLFormat(format),GL_BYTE,nullptr,texture);
		return ret;
	}
}

Bool NSDevilX::NSGraphicsAPI::CGLDeviceImp::createVolumeTexture(UINT width,UINT height,UINT depth,UINT levels,DWORD usage,D3DFORMAT format,D3DPOOL pool,OUT ITexture* texture)
{
	if(isCompressedFormat(format))
	{
		return createCompressedTexture3D(GL_TEXTURE_3D,levels,mappingGLInternalFormat(format),width,height,depth,0,0,nullptr,texture);
	}
	else
	{
		return createTexture3D(GL_TEXTURE_3D,levels,mappingGLInternalFormat(format),width,height,depth,0,mappingGLFormat(format),GL_BYTE,nullptr,texture);
	}
}

Bool NSDevilX::NSGraphicsAPI::CGLDeviceImp::createTexture1D(const D3D10_TEXTURE1D_DESC& desc,const D3D10_SUBRESOURCE_DATA* initializeData,OUT ITexture* texture)
{
	ConstVoidPtr data=nullptr;
	GLsizei data_size=0;
	if(initializeData)
	{
		data=initializeData->pSysMem;
		data_size=initializeData->SysMemSlicePitch*desc.ArraySize;
	}
	if(isCompressedFormat(desc.Format))
	{
		return createCompressedTexture1D(GL_TEXTURE_1D,desc.MipLevels,mappingGLInternalFormat(desc.Format),desc.Width,0,data_size,data,texture);
	}
	else
	{
		return createTexture1D(GL_TEXTURE_1D,desc.MipLevels,mappingGLInternalFormat(desc.Format),desc.Width,0,mappingGLFormat(desc.Format),GL_BYTE,data,texture);
	}
}

Bool NSDevilX::NSGraphicsAPI::CGLDeviceImp::createTexture2D(const D3D10_TEXTURE2D_DESC& desc,const D3D10_SUBRESOURCE_DATA* initializeData,OUT ITexture* texture)
{
	ConstVoidPtr data=nullptr;
	GLsizei data_size=0;
	GLsizei slice_pitch=0;
	if(initializeData)
	{
		data=initializeData->pSysMem;
		data_size=initializeData->SysMemSlicePitch*desc.ArraySize;
		slice_pitch=initializeData->SysMemSlicePitch;
	}
	if(desc.ArraySize>1)
	{
		if(desc.MiscFlags&D3D11_RESOURCE_MISC_TEXTURECUBE)
		{
			if((desc.ArraySize%6!=0)
				||(desc.SampleDesc.Count>1))
			{
				return False;
			}
			if(desc.ArraySize==6)
			{
				if(isCompressedFormat(desc.Format))
				{
					Bool ret=createCompressedTexture2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X,desc.MipLevels,mappingGLInternalFormat(desc.Format),desc.Width,desc.Height,0,slice_pitch,static_cast<ConstBytePtr>(data)+slice_pitch*0,texture);
					ret&=createCompressedTexture2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y,desc.MipLevels,mappingGLInternalFormat(desc.Format),desc.Width,desc.Height,0,slice_pitch,static_cast<ConstBytePtr>(data)+slice_pitch*1,texture);
					ret&=createCompressedTexture2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z,desc.MipLevels,mappingGLInternalFormat(desc.Format),desc.Width,desc.Height,0,slice_pitch,static_cast<ConstBytePtr>(data)+slice_pitch*2,texture);
					ret&=createCompressedTexture2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X,desc.MipLevels,mappingGLInternalFormat(desc.Format),desc.Width,desc.Height,0,slice_pitch,static_cast<ConstBytePtr>(data)+slice_pitch*3,texture);
					ret&=createCompressedTexture2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,desc.MipLevels,mappingGLInternalFormat(desc.Format),desc.Width,desc.Height,0,slice_pitch,static_cast<ConstBytePtr>(data)+slice_pitch*4,texture);
					ret&=createCompressedTexture2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,desc.MipLevels,mappingGLInternalFormat(desc.Format),desc.Width,desc.Height,0,slice_pitch,static_cast<ConstBytePtr>(data)+slice_pitch*5,texture);
					return ret;
				}
				else
				{
					Bool ret=createTexture2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X,desc.MipLevels,mappingGLInternalFormat(desc.Format),desc.Width,desc.Height,0,mappingGLFormat(desc.Format),GL_BYTE,static_cast<ConstBytePtr>(data)+slice_pitch*0,texture);
					ret&=createTexture2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y,desc.MipLevels,mappingGLInternalFormat(desc.Format),desc.Width,desc.Height,0,mappingGLFormat(desc.Format),GL_BYTE,static_cast<ConstBytePtr>(data)+slice_pitch*1,texture);
					ret&=createTexture2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z,desc.MipLevels,mappingGLInternalFormat(desc.Format),desc.Width,desc.Height,0,mappingGLFormat(desc.Format),GL_BYTE,static_cast<ConstBytePtr>(data)+slice_pitch*2,texture);
					ret&=createTexture2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X,desc.MipLevels,mappingGLInternalFormat(desc.Format),desc.Width,desc.Height,0,mappingGLFormat(desc.Format),GL_BYTE,static_cast<ConstBytePtr>(data)+slice_pitch*3,texture);
					ret&=createTexture2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,desc.MipLevels,mappingGLInternalFormat(desc.Format),desc.Width,desc.Height,0,mappingGLFormat(desc.Format),GL_BYTE,static_cast<ConstBytePtr>(data)+slice_pitch*4,texture);
					ret&=createTexture2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,desc.MipLevels,mappingGLInternalFormat(desc.Format),desc.Width,desc.Height,0,mappingGLFormat(desc.Format),GL_BYTE,static_cast<ConstBytePtr>(data)+slice_pitch*5,texture);
					return ret;
				}
			}
			else
			{
				if(isCompressedFormat(desc.Format))
				{
					return createCompressedTexture3D(GL_TEXTURE_CUBE_MAP_ARRAY,desc.MipLevels,mappingGLInternalFormat(desc.Format),desc.Width,desc.Height,desc.ArraySize,0,data_size,data,texture);
				}
				else
				{
					return createTexture3D(GL_TEXTURE_CUBE_MAP_ARRAY,desc.MipLevels,mappingGLInternalFormat(desc.Format),desc.Width,desc.Height,desc.ArraySize,0,mappingGLFormat(desc.Format),GL_BYTE,data,texture);
				}
			}
		}
		else
		{
			if(isCompressedFormat(desc.Format))
			{
				return createCompressedTexture3D(GL_TEXTURE_2D_ARRAY,desc.MipLevels,mappingGLInternalFormat(desc.Format),desc.Width,desc.Height,desc.ArraySize,0,data_size,data,texture);
			}
			else if(desc.SampleDesc.Count>1)
			{
				return createTexture3DMSAA(GL_TEXTURE_2D_MULTISAMPLE_ARRAY,desc.SampleDesc.Count,mappingGLInternalFormat(desc.Format),desc.Width,desc.Height,desc.ArraySize,true,texture);
			}
			else
			{
				return createTexture3D(GL_TEXTURE_2D_ARRAY,desc.MipLevels,mappingGLInternalFormat(desc.Format),desc.Width,desc.Height,desc.ArraySize,0,mappingGLFormat(desc.Format),GL_BYTE,data,texture);
			}
		}
	}
	else
	{
		if(isCompressedFormat(desc.Format))
		{
			return createCompressedTexture2D(GL_TEXTURE_2D,desc.MipLevels,mappingGLInternalFormat(desc.Format),desc.Width,desc.Height,0,data_size,data,texture);
		}
		else if(desc.SampleDesc.Count>1)
		{
			return createTexture2DMSAA(GL_TEXTURE_2D_MULTISAMPLE,desc.SampleDesc.Count,mappingGLInternalFormat(desc.Format),desc.Width,desc.Height,true,texture);
		}
		else
		{
			return createTexture2D(GL_TEXTURE_2D,desc.MipLevels,mappingGLInternalFormat(desc.Format),desc.Width,desc.Height,0,mappingGLFormat(desc.Format),GL_BYTE,data,texture);
		}
	}
}

Bool NSDevilX::NSGraphicsAPI::CGLDeviceImp::createTexture3D(const D3D10_TEXTURE3D_DESC& desc,const D3D10_SUBRESOURCE_DATA* initializeData,OUT ITexture* texture)
{
	ConstVoidPtr data=nullptr;
	if(initializeData)
	{
		data=initializeData->pSysMem;
	}
	return createTexture3D(GL_TEXTURE_3D,desc.MipLevels,mappingGLInternalFormat(desc.Format),desc.Width,desc.Height,desc.Depth,0,mappingGLFormat(desc.Format),GL_BYTE,data,texture);
}

Bool NSDevilX::NSGraphicsAPI::CGLDeviceImp::createTexture1D(const D3D11_TEXTURE1D_DESC& desc,const D3D11_SUBRESOURCE_DATA* initializeData,OUT ITexture* texture)
{
	ConstVoidPtr data=nullptr;
	GLsizei data_size=0;
	if(initializeData)
	{
		data=initializeData->pSysMem;
		data_size=initializeData->SysMemSlicePitch*desc.ArraySize;
	}
	if(isCompressedFormat(desc.Format))
	{
		return createCompressedTexture1D(GL_TEXTURE_1D,desc.MipLevels,mappingGLInternalFormat(desc.Format),desc.Width,0,data_size,data,texture);
	}
	else
	{
		return createTexture1D(GL_TEXTURE_1D,desc.MipLevels,mappingGLInternalFormat(desc.Format),desc.Width,0,mappingGLFormat(desc.Format),GL_BYTE,data,texture);
	}
}

Bool NSDevilX::NSGraphicsAPI::CGLDeviceImp::createTexture2D(const D3D11_TEXTURE2D_DESC& desc,const D3D11_SUBRESOURCE_DATA* initializeData,OUT ITexture* texture)
{
	ConstVoidPtr data=nullptr;
	GLsizei data_size=0;
	GLsizei slice_pitch=0;
	if(initializeData)
	{
		data=initializeData->pSysMem;
		data_size=initializeData->SysMemSlicePitch*desc.ArraySize;
		slice_pitch=initializeData->SysMemSlicePitch;
	}
	if(desc.ArraySize>1)
	{
		if(desc.MiscFlags&D3D11_RESOURCE_MISC_TEXTURECUBE)
		{
			if((desc.ArraySize%6!=0)
				||(desc.SampleDesc.Count>1))
			{
				return False;
			}
			if(desc.ArraySize==6)
			{
				if(isCompressedFormat(desc.Format))
				{
					Bool ret=createCompressedTexture2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X,desc.MipLevels,mappingGLInternalFormat(desc.Format),desc.Width,desc.Height,0,slice_pitch,static_cast<ConstBytePtr>(data)+slice_pitch*0,texture);
					ret&=createCompressedTexture2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y,desc.MipLevels,mappingGLInternalFormat(desc.Format),desc.Width,desc.Height,0,slice_pitch,static_cast<ConstBytePtr>(data)+slice_pitch*1,texture);
					ret&=createCompressedTexture2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z,desc.MipLevels,mappingGLInternalFormat(desc.Format),desc.Width,desc.Height,0,slice_pitch,static_cast<ConstBytePtr>(data)+slice_pitch*2,texture);
					ret&=createCompressedTexture2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X,desc.MipLevels,mappingGLInternalFormat(desc.Format),desc.Width,desc.Height,0,slice_pitch,static_cast<ConstBytePtr>(data)+slice_pitch*3,texture);
					ret&=createCompressedTexture2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,desc.MipLevels,mappingGLInternalFormat(desc.Format),desc.Width,desc.Height,0,slice_pitch,static_cast<ConstBytePtr>(data)+slice_pitch*4,texture);
					ret&=createCompressedTexture2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,desc.MipLevels,mappingGLInternalFormat(desc.Format),desc.Width,desc.Height,0,slice_pitch,static_cast<ConstBytePtr>(data)+slice_pitch*5,texture);
					return ret;
				}
				else
				{
					Bool ret=createTexture2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X,desc.MipLevels,mappingGLInternalFormat(desc.Format),desc.Width,desc.Height,0,mappingGLFormat(desc.Format),GL_BYTE,static_cast<ConstBytePtr>(data)+slice_pitch*0,texture);
					ret&=createTexture2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y,desc.MipLevels,mappingGLInternalFormat(desc.Format),desc.Width,desc.Height,0,mappingGLFormat(desc.Format),GL_BYTE,static_cast<ConstBytePtr>(data)+slice_pitch*1,texture);
					ret&=createTexture2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z,desc.MipLevels,mappingGLInternalFormat(desc.Format),desc.Width,desc.Height,0,mappingGLFormat(desc.Format),GL_BYTE,static_cast<ConstBytePtr>(data)+slice_pitch*2,texture);
					ret&=createTexture2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X,desc.MipLevels,mappingGLInternalFormat(desc.Format),desc.Width,desc.Height,0,mappingGLFormat(desc.Format),GL_BYTE,static_cast<ConstBytePtr>(data)+slice_pitch*3,texture);
					ret&=createTexture2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,desc.MipLevels,mappingGLInternalFormat(desc.Format),desc.Width,desc.Height,0,mappingGLFormat(desc.Format),GL_BYTE,static_cast<ConstBytePtr>(data)+slice_pitch*4,texture);
					ret&=createTexture2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,desc.MipLevels,mappingGLInternalFormat(desc.Format),desc.Width,desc.Height,0,mappingGLFormat(desc.Format),GL_BYTE,static_cast<ConstBytePtr>(data)+slice_pitch*5,texture);
					return ret;
				}
			}
			else
			{
				if(isCompressedFormat(desc.Format))
				{
					return createCompressedTexture3D(GL_TEXTURE_CUBE_MAP_ARRAY,desc.MipLevels,mappingGLInternalFormat(desc.Format),desc.Width,desc.Height,desc.ArraySize,0,data_size,data,texture);
				}
				else
				{
					return createTexture3D(GL_TEXTURE_CUBE_MAP_ARRAY,desc.MipLevels,mappingGLInternalFormat(desc.Format),desc.Width,desc.Height,desc.ArraySize,0,mappingGLFormat(desc.Format),GL_BYTE,data,texture);
				}
			}
		}
		else
		{
			if(isCompressedFormat(desc.Format))
			{
				return createCompressedTexture3D(GL_TEXTURE_2D_ARRAY,desc.MipLevels,mappingGLInternalFormat(desc.Format),desc.Width,desc.Height,desc.ArraySize,0,data_size,data,texture);
			}
			else if(desc.SampleDesc.Count>1)
			{
				return createTexture3DMSAA(GL_TEXTURE_2D_MULTISAMPLE_ARRAY,desc.SampleDesc.Count,mappingGLInternalFormat(desc.Format),desc.Width,desc.Height,desc.ArraySize,true,texture);
			}
			else
			{
				return createTexture3D(GL_TEXTURE_2D_ARRAY,desc.MipLevels,mappingGLInternalFormat(desc.Format),desc.Width,desc.Height,desc.ArraySize,0,mappingGLFormat(desc.Format),GL_BYTE,data,texture);
			}
		}
	}
	else
	{
		if(isCompressedFormat(desc.Format))
		{
			return createCompressedTexture2D(GL_TEXTURE_2D,desc.MipLevels,mappingGLInternalFormat(desc.Format),desc.Width,desc.Height,0,data_size,data,texture);
		}
		else if(desc.SampleDesc.Count>1)
		{
			return createTexture2DMSAA(GL_TEXTURE_2D_MULTISAMPLE,desc.SampleDesc.Count,mappingGLInternalFormat(desc.Format),desc.Width,desc.Height,true,texture);
		}
		else
		{
			return createTexture2D(GL_TEXTURE_2D,desc.MipLevels,mappingGLInternalFormat(desc.Format),desc.Width,desc.Height,0,mappingGLFormat(desc.Format),GL_BYTE,data,texture);
		}
	}
}

Bool NSDevilX::NSGraphicsAPI::CGLDeviceImp::createTexture3D(const D3D11_TEXTURE3D_DESC& desc,const D3D11_SUBRESOURCE_DATA* initializeData,OUT ITexture* texture)
{
	ConstVoidPtr data=nullptr;
	if(initializeData)
	{
		data=initializeData->pSysMem;
	}
	return createTexture3D(GL_TEXTURE_3D,desc.MipLevels,mappingGLInternalFormat(desc.Format),desc.Width,desc.Height,desc.Depth,0,mappingGLFormat(desc.Format),GL_BYTE,data,texture);
}

Bool NSDevilX::NSGraphicsAPI::CGLDeviceImp::createTexture1D(GLenum target,GLint level,GLint internalformat,GLsizei width,GLint border,GLenum format,GLenum type,ConstVoidPtr initializeData,OUT ITexture* texture)
{
	glGenTextures(1,&static_cast<CGLTextureImp*>(texture)->mInternal);
	glBindTexture(target,static_cast<CGLTextureImp*>(texture)->mInternal);
	glTexImage1D(target,level,internalformat,width,border,format,type,initializeData);
	glBindTexture(target,0);
	return True;
}

Bool NSDevilX::NSGraphicsAPI::CGLDeviceImp::createTexture2D(GLenum target,GLint level,GLint internalformat,GLsizei width,GLsizei height,GLint border,GLenum format,GLenum type,ConstVoidPtr initializeData,OUT ITexture* texture)
{
	glGenTextures(1,&static_cast<CGLTextureImp*>(texture)->mInternal);
	glBindTexture(target,static_cast<CGLTextureImp*>(texture)->mInternal);
	glTexImage2D(target,level,internalformat,width,height,border,format,type,initializeData);
	glBindTexture(target,0);
	return True;
}

Bool NSDevilX::NSGraphicsAPI::CGLDeviceImp::createTexture3D(GLenum target,GLint level,GLint internalformat,GLsizei width,GLsizei height,GLsizei depth,GLint border,GLenum format,GLenum type,ConstVoidPtr initializeData,OUT ITexture* texture)
{
	glGenTextures(1,&static_cast<CGLTextureImp*>(texture)->mInternal);
	glBindTexture(target,static_cast<CGLTextureImp*>(texture)->mInternal);
	glTexImage3D(target,level,internalformat,width,height,depth,border,format,type,initializeData);
	glBindTexture(target,0);
	return True;
}

Bool NSDevilX::NSGraphicsAPI::CGLDeviceImp::createTexture2DMSAA(GLenum target,GLsizei samplers,GLenum internalformat,GLsizei width,GLsizei height,GLboolean fixedsamplelocations,OUT ITexture* texture)
{
	glGenTextures(1,&static_cast<CGLTextureImp*>(texture)->mInternal);
	glBindTexture(target,static_cast<CGLTextureImp*>(texture)->mInternal);
	glTexStorage2DMultisample(target,samplers,internalformat,width,height,fixedsamplelocations);
	glBindTexture(target,0);
	return True;
}

Bool NSDevilX::NSGraphicsAPI::CGLDeviceImp::createTexture3DMSAA(GLenum target,GLsizei samplers,GLenum internalformat,GLsizei width,GLsizei height,GLsizei depth,GLboolean fixedsamplelocations,OUT ITexture* texture)
{
	glGenTextures(1,&static_cast<CGLTextureImp*>(texture)->mInternal);
	glBindTexture(target,static_cast<CGLTextureImp*>(texture)->mInternal);
	glTexStorage3DMultisample(target,samplers,internalformat,width,height,depth,fixedsamplelocations);
	glBindTexture(target,0);
	return True;
}

Bool NSDevilX::NSGraphicsAPI::CGLDeviceImp::createCompressedTexture1D(GLenum target,GLint level,GLint internalformat,GLsizei width,GLint border,GLsizei imageSize,ConstVoidPtr initializeData,OUT ITexture* texture)
{
	glGenTextures(1,&static_cast<CGLTextureImp*>(texture)->mInternal);
	glBindTexture(target,static_cast<CGLTextureImp*>(texture)->mInternal);
	glCompressedTexImage1D(target,level,internalformat,width,border,imageSize,initializeData);
	glBindTexture(target,0);
	return True;
}

Bool NSDevilX::NSGraphicsAPI::CGLDeviceImp::createCompressedTexture2D(GLenum target,GLint level,GLint internalformat,GLsizei width,GLsizei height,GLint border,GLsizei imageSize,ConstVoidPtr initializeData,OUT ITexture* texture)
{
	glGenTextures(1,&static_cast<CGLTextureImp*>(texture)->mInternal);
	glBindTexture(target,static_cast<CGLTextureImp*>(texture)->mInternal);
	glCompressedTexImage2D(target,level,internalformat,width,height,border,imageSize,initializeData);
	glBindTexture(target,0);
	return True;
}

Bool NSDevilX::NSGraphicsAPI::CGLDeviceImp::createCompressedTexture3D(GLenum target,GLint level,GLint internalformat,GLsizei width,GLsizei height,GLsizei depth,GLint border,GLsizei imageSize,ConstVoidPtr initializeData,OUT ITexture* texture)
{
	glGenTextures(1,&static_cast<CGLTextureImp*>(texture)->mInternal);
	glBindTexture(target,static_cast<CGLTextureImp*>(texture)->mInternal);
	glCompressedTexImage3D(target,level,internalformat,width,height,depth,border,imageSize,initializeData);
	glBindTexture(target,0);
	return True;
}

Bool NSDevilX::NSGraphicsAPI::CGLDeviceImp::createVertexDeclaration(const D3DVERTEXELEMENT9* elements,OUT IInputLayout* layout)
{
	Bool ret=True;
	D3DVERTEXELEMENT9 end=D3DDECL_END();
	while(elements&&(0!=memcmp(elements,&end,sizeof(D3DVERTEXELEMENT9))))
	{
		ret&=vertexAttribFormat(elements->Stream,getComponentCount((D3DDECLTYPE)elements->Type),getComponentType((D3DDECLTYPE)elements->Type),needNormalize((D3DDECLTYPE)elements->Type),elements->Offset,layout);
		++elements;
	}
	return ret;
}

Bool NSDevilX::NSGraphicsAPI::CGLDeviceImp::createInputLayout(const D3D10_INPUT_ELEMENT_DESC* descs,UINT numElements,ConstVoidPtr shaderBytecodeWithInputSignature,SIZE_T bytecodeLength,OUT IInputLayout* layout)
{
	Bool ret=True;
	for(UINT i=0;i<numElements;++i)
	{
		ret&=vertexAttribFormat(descs[i].InputSlot,getComponentCount(descs[i].Format),getComponentType(descs[i].Format),needNormalize(descs[i].Format),descs[i].AlignedByteOffset,layout);
	}
	return ret;
}

Bool NSDevilX::NSGraphicsAPI::CGLDeviceImp::createInputLayout(const D3D11_INPUT_ELEMENT_DESC* descs,UINT numElements,ConstVoidPtr shaderBytecodeWithInputSignature,SIZE_T bytecodeLength,OUT IInputLayout* layout)
{
	Bool ret=True;
	for(UINT i=0;i<numElements;++i)
	{
		ret&=vertexAttribFormat(descs[i].InputSlot,getComponentCount(descs[i].Format),getComponentType(descs[i].Format),needNormalize(descs[i].Format),descs[i].AlignedByteOffset,layout);
	}
	return ret;
}

Bool NSDevilX::NSGraphicsAPI::CGLDeviceImp::vertexAttribFormat(GLuint attribindex,GLint size,GLenum type,GLboolean normalized,GLuint relativeoffset,OUT IInputLayout* layout)
{
	if(0==static_cast<CGLVertexArrayObjectImp*>(layout)->mInternal)
	{
		glGenVertexArrays(1,&static_cast<CGLVertexArrayObjectImp*>(layout)->mInternal);
	}
	glBindVertexArray(static_cast<CGLVertexArrayObjectImp*>(layout)->mInternal);
	glVertexAttribFormat(attribindex,size,type,normalized,relativeoffset);
	glBindVertexArray(0);
	return True;
}

Bool NSDevilX::NSGraphicsAPI::CGLDeviceImp::vertexAttribIFormat(GLuint attribindex,GLint size,GLenum type,GLuint relativeoffset,OUT IInputLayout* layout)
{
	if(0==static_cast<CGLVertexArrayObjectImp*>(layout)->mInternal)
	{
		glGenVertexArrays(1,&static_cast<CGLVertexArrayObjectImp*>(layout)->mInternal);
	}
	glBindVertexArray(static_cast<CGLVertexArrayObjectImp*>(layout)->mInternal);
	glVertexAttribIFormat(attribindex,size,type,relativeoffset);
	glBindVertexArray(0);
	return True;
}

Bool NSDevilX::NSGraphicsAPI::CGLDeviceImp::vertexAttribPoint(GLuint index,GLint size,GLenum type,GLboolean normalized,GLsizei stride,ConstVoidPtr pointer,IBuffer* buffer,OUT IVertexArrayObject* layout)
{
	if(0==static_cast<CGLVertexArrayObjectImp*>(layout)->mInternal)
	{
		glGenVertexArrays(1,&static_cast<CGLVertexArrayObjectImp*>(layout)->mInternal);
	}
	glBindVertexArray(static_cast<CGLVertexArrayObjectImp*>(layout)->mInternal);
	glBindBuffer(GL_ARRAY_BUFFER,static_cast<CGLBufferImp*>(buffer)->mInternal);
	glVertexAttribPointer(index,size,type,normalized,stride,pointer);
	glBindBuffer(GL_ARRAY_BUFFER,0);
	glBindVertexArray(0);
	return True;
}

Bool NSDevilX::NSGraphicsAPI::CGLDeviceImp::vertexAttribIPoint(GLuint index,GLint size,GLenum type,GLsizei stride,ConstVoidPtr pointer,IBuffer* buffer,OUT IVertexArrayObject* layout)
{
	if(0==static_cast<CGLVertexArrayObjectImp*>(layout)->mInternal)
	{
		glGenVertexArrays(1,&static_cast<CGLVertexArrayObjectImp*>(layout)->mInternal);
	}
	glBindVertexArray(static_cast<CGLVertexArrayObjectImp*>(layout)->mInternal);
	glBindBuffer(GL_ARRAY_BUFFER,static_cast<CGLBufferImp*>(buffer)->mInternal);
	glVertexAttribIPointer(index,size,type,stride,pointer);
	glBindBuffer(GL_ARRAY_BUFFER,0);
	glBindVertexArray(0);
	return True;
}

Bool NSDevilX::NSGraphicsAPI::CGLDeviceImp::createVertexShader(ConstVoidPtr bytecode,SizeT bytecodeSize,OUT IProgram* shader)
{
	GLenum format;
	glGetIntegerv(GL_SHADER_BINARY_FORMATS,reinterpret_cast<GLint*>(&format));
	return createShader(GL_VERTEX_SHADER,format,bytecode,static_cast<GLsizei>(bytecodeSize),shader);
}

Bool NSDevilX::NSGraphicsAPI::CGLDeviceImp::createPixelShader(ConstVoidPtr bytecode,SizeT bytecodeSize,OUT IProgram* shader)
{
	GLenum format;
	glGetIntegerv(GL_SHADER_BINARY_FORMATS,reinterpret_cast<GLint*>(&format));
	return createShader(GL_FRAGMENT_SHADER,format,bytecode,static_cast<GLsizei>(bytecodeSize),shader);
}

Bool NSDevilX::NSGraphicsAPI::CGLDeviceImp::createGeometryShader(ConstVoidPtr bytecode,SizeT bytecodeSize,OUT IProgram* shader)
{
	GLenum format;
	glGetIntegerv(GL_SHADER_BINARY_FORMATS,reinterpret_cast<GLint*>(&format));
	return createShader(GL_GEOMETRY_SHADER,format,bytecode,static_cast<GLsizei>(bytecodeSize),shader);
}

Bool NSDevilX::NSGraphicsAPI::CGLDeviceImp::createHullShader(ConstVoidPtr bytecode,SizeT bytecodeSize,OUT IProgram* shader)
{
	GLenum format;
	glGetIntegerv(GL_SHADER_BINARY_FORMATS,reinterpret_cast<GLint*>(&format));
	return createShader(GL_TESS_CONTROL_SHADER,format,bytecode,static_cast<GLsizei>(bytecodeSize),shader);
}

Bool NSDevilX::NSGraphicsAPI::CGLDeviceImp::createDomainShader(ConstVoidPtr bytecode,SizeT bytecodeSize,OUT IProgram* shader)
{
	GLenum format;
	glGetIntegerv(GL_SHADER_BINARY_FORMATS,reinterpret_cast<GLint*>(&format));
	return createShader(GL_TESS_EVALUATION_SHADER,format,bytecode,static_cast<GLsizei>(bytecodeSize),shader);
}

Bool NSDevilX::NSGraphicsAPI::CGLDeviceImp::createComputeShader(ConstVoidPtr bytecode,SizeT bytecodeSize,OUT IProgram* shader)
{
	GLenum format;
	glGetIntegerv(GL_SHADER_BINARY_FORMATS,reinterpret_cast<GLint*>(&format));
	return createShader(GL_COMPUTE_SHADER,format,bytecode,static_cast<GLsizei>(bytecodeSize),shader);
}

Bool NSDevilX::NSGraphicsAPI::CGLDeviceImp::createShader(GLenum type,ConstCharPtr string,GLint length,OUT IShader* shader)
{
	static_cast<CGLShaderImp*>(shader)->mInternal=glCreateShader(type);
	glShaderSource(static_cast<CGLShaderImp*>(shader)->mInternal,1,&string,&length);
	glCompileShader(static_cast<CGLShaderImp*>(shader)->mInternal);
	GLint compiler_status=GL_FALSE;
	glGetShaderiv(static_cast<CGLShaderImp*>(shader)->mInternal,GL_COMPILE_STATUS,&compiler_status);
	if(GL_TRUE!=compiler_status)
	{
		std::string shader_log;
		shader_log.resize(1024);
		glGetShaderInfoLog(static_cast<CGLShaderImp*>(shader)->mInternal,1024,nullptr,&shader_log[0]);
#if DEVILX_DEBUG
#if DEVILX_OPERATING_SYSTEM==DEVILX_OPERATING_SYSTEM_WINDOWS
		OutputDebugStringA(shader_log.c_str());
		OutputDebugStringA("\r\n");
#endif
#endif
		return False;
	}
	else
	{
		return True;
	}
}

Bool NSDevilX::NSGraphicsAPI::CGLDeviceImp::createShader(GLenum type,ConstCharPtr string,GLint length,OUT IProgram* shader)
{
	auto shader_obj=glCreateShader(type);
	glShaderSource(shader_obj,1,&string,&length);
	glCompileShader(shader_obj);
	GLint compiler_status=GL_FALSE;
	glGetShaderiv(shader_obj,GL_COMPILE_STATUS,&compiler_status);
	if(GL_TRUE!=compiler_status)
	{
		std::string shader_log;
		shader_log.resize(1024);
		glGetShaderInfoLog(shader_obj,1024,nullptr,&shader_log[0]);
#if DEVILX_DEBUG
#if DEVILX_OPERATING_SYSTEM==DEVILX_OPERATING_SYSTEM_WINDOWS
		OutputDebugStringA(shader_log.c_str());
		OutputDebugStringA("\r\n");
#endif
#endif
		return False;
	}
	static_cast<CGLProgramImp*>(shader)->mInternal=glCreateProgram();
	glAttachShader(static_cast<CGLProgramImp*>(shader)->mInternal,shader_obj);
	glLinkProgram(static_cast<CGLProgramImp*>(shader)->mInternal);
	glDeleteShader(shader_obj);
	glGetProgramiv(static_cast<CGLProgramImp*>(shader)->mInternal,GL_LINK_STATUS,&compiler_status);
	if(GL_TRUE!=compiler_status)
	{
		std::string shader_log;
		shader_log.resize(1024);
		glGetProgramInfoLog(static_cast<CGLProgramImp*>(shader)->mInternal,1024,nullptr,&shader_log[0]);
#if DEVILX_DEBUG
#if DEVILX_OPERATING_SYSTEM==DEVILX_OPERATING_SYSTEM_WINDOWS
		OutputDebugStringA(shader_log.c_str());
		OutputDebugStringA("\r\n");
#endif
#endif
		return False;
	}
	return True;
}

Bool NSDevilX::NSGraphicsAPI::CGLDeviceImp::createShader(GLenum type,GLenum binaryFormat,ConstVoidPtr bytecode,GLsizei bytecodeSize,OUT IShader* shader)
{
	static_cast<CGLShaderImp*>(shader)->mInternal=glCreateShader(type);
	glShaderBinary(1,&static_cast<CGLShaderImp*>(shader)->mInternal,binaryFormat,bytecode,bytecodeSize);
	return True;
}

Bool NSDevilX::NSGraphicsAPI::CGLDeviceImp::createShader(GLenum type,GLenum binaryFormat,ConstVoidPtr bytecode,GLsizei bytecodeSize,OUT IProgram* shader)
{
	auto shader_obj=glCreateShader(type);
	glShaderBinary(1,&shader_obj,binaryFormat,bytecode,bytecodeSize);
	static_cast<CGLProgramImp*>(shader)->mInternal=glCreateProgram();
	glAttachShader(static_cast<CGLProgramImp*>(shader)->mInternal,shader_obj);
	glLinkProgram(static_cast<CGLProgramImp*>(shader)->mInternal);
	glDeleteShader(shader_obj);
	GLint compiler_status=GL_FALSE;
	glGetProgramiv(static_cast<CGLProgramImp*>(shader)->mInternal,GL_LINK_STATUS,&compiler_status);
	if(GL_TRUE!=compiler_status)
	{
		std::string shader_log;
		shader_log.resize(1024);
		glGetProgramInfoLog(static_cast<CGLProgramImp*>(shader)->mInternal,1024,nullptr,&shader_log[0]);
#if DEVILX_DEBUG
#if DEVILX_OPERATING_SYSTEM==DEVILX_OPERATING_SYSTEM_WINDOWS
		OutputDebugStringA(shader_log.c_str());
		OutputDebugStringA("\r\n");
#endif
#endif
		return False;
	}
	return True;
}

Bool NSDevilX::NSGraphicsAPI::CGLDeviceImp::attachProgram(GLenum type,IShader* shader,OUT IProgram* program)
{
	if(0==static_cast<CGLProgramImp*>(program)->mInternal)
	{
		static_cast<CGLProgramImp*>(program)->mInternal=glCreateProgram();
	}
	glAttachShader(static_cast<CGLProgramImp*>(program)->mInternal,static_cast<CGLShaderImp*>(shader)->mInternal);
	return True;
}

Bool NSDevilX::NSGraphicsAPI::CGLDeviceImp::linkProgram(OUT IProgram* program)
{
	glLinkProgram(static_cast<CGLProgramImp*>(program)->mInternal);
	GLint compiler_status=GL_FALSE;
	glGetProgramiv(static_cast<CGLProgramImp*>(program)->mInternal,GL_LINK_STATUS,&compiler_status);
	if(GL_TRUE!=compiler_status)
	{
		std::string shader_log;
		shader_log.resize(1024);
		glGetProgramInfoLog(static_cast<CGLProgramImp*>(program)->mInternal,1024,nullptr,&shader_log[0]);
#if DEVILX_DEBUG
#if DEVILX_OPERATING_SYSTEM==DEVILX_OPERATING_SYSTEM_WINDOWS
		OutputDebugStringA(shader_log.c_str());
		OutputDebugStringA("\r\n");
#endif
#endif
		return False;
	}
	return True;
}

Bool NSDevilX::NSGraphicsAPI::CGLDeviceImp::createBlendState(const D3D10_BLEND_DESC& desc,OUT IBlendState* state)
{
	if(desc.AlphaToCoverageEnable)
	{
		SAVE_STATE(glEnable,GL_SAMPLE_ALPHA_TO_COVERAGE);
	}
	if(desc.BlendOpAlpha!=D3D10_BLEND_OP_ADD)
	{
		SAVE_STATE(glBlendEquationSeparate,mappingGL(desc.BlendOp),mappingGL(desc.BlendOpAlpha));
	}
	else if(desc.BlendOp!=D3D10_BLEND_OP_ADD)
	{
		SAVE_STATE(glBlendEquation,mappingGL(desc.BlendOp));
	}
	if((desc.DestBlendAlpha!=D3D10_BLEND_ZERO)||(desc.SrcBlendAlpha!=D3D10_BLEND_ONE))
	{
		SAVE_STATE(glBlendFuncSeparate,mappingGL(desc.SrcBlend),mappingGL(desc.DestBlend),mappingGL(desc.SrcBlendAlpha),mappingGL(desc.DestBlendAlpha));
	}
	else if((desc.DestBlend!=D3D10_BLEND_ZERO)||(desc.SrcBlend!=D3D10_BLEND_ONE))
	{
		SAVE_STATE(glBlendFunc,mappingGL(desc.SrcBlend),mappingGL(desc.DestBlend));
	}
	if((desc.RenderTargetWriteMask[0]&D3D10_COLOR_WRITE_ENABLE_ALL)!=D3D10_COLOR_WRITE_ENABLE_ALL)
	{
		SAVE_STATE(glColorMask,desc.RenderTargetWriteMask[0]&D3D10_COLOR_WRITE_ENABLE_RED?GL_TRUE:GL_FALSE
			,desc.RenderTargetWriteMask[0]&D3D10_COLOR_WRITE_ENABLE_GREEN?GL_TRUE:GL_FALSE
			,desc.RenderTargetWriteMask[0]&D3D10_COLOR_WRITE_ENABLE_BLUE?GL_TRUE:GL_FALSE
			,desc.RenderTargetWriteMask[0]&D3D10_COLOR_WRITE_ENABLE_ALPHA?GL_TRUE:GL_FALSE
		);
	}
	if(desc.BlendEnable[0])
	{
		SAVE_STATE(glEnable,GL_BLEND);
	}
	for(Int32 i=1;i<sizeof(desc.BlendEnable)/sizeof(desc.BlendEnable[0]);++i)
	{
		if((desc.RenderTargetWriteMask[i]&D3D10_COLOR_WRITE_ENABLE_ALL)!=D3D10_COLOR_WRITE_ENABLE_ALL)
		{
			SAVE_STATE(glColorMaski,i
			,desc.RenderTargetWriteMask[i]&D3D10_COLOR_WRITE_ENABLE_RED?GL_TRUE:GL_FALSE
			,desc.RenderTargetWriteMask[i]&D3D10_COLOR_WRITE_ENABLE_GREEN?GL_TRUE:GL_FALSE
			,desc.RenderTargetWriteMask[i]&D3D10_COLOR_WRITE_ENABLE_BLUE?GL_TRUE:GL_FALSE
			,desc.RenderTargetWriteMask[i]&D3D10_COLOR_WRITE_ENABLE_ALPHA?GL_TRUE:GL_FALSE);
		}
		if(desc.BlendEnable[i])
		{
			SAVE_STATE(glEnablei,GL_BLEND,i);
		}
	}
	return True;
}

Bool NSDevilX::NSGraphicsAPI::CGLDeviceImp::createBlendState(const D3D10_BLEND_DESC1& desc,OUT IBlendState* state)
{
	if(desc.AlphaToCoverageEnable)
	{
		SAVE_STATE(glEnable,GL_SAMPLE_ALPHA_TO_COVERAGE);
	}
	{
		if(desc.RenderTarget[0].BlendOpAlpha!=D3D10_BLEND_OP_ADD)
		{
			SAVE_STATE(glBlendEquationSeparate,mappingGL(desc.RenderTarget[0].BlendOp),mappingGL(desc.RenderTarget[0].BlendOpAlpha));
		}
		else if(desc.RenderTarget[0].BlendOp!=D3D10_BLEND_OP_ADD)
		{
			SAVE_STATE(glBlendEquation,mappingGL(desc.RenderTarget[0].BlendOp));
		}
		if((desc.RenderTarget[0].DestBlendAlpha!=D3D10_BLEND_ZERO)||(desc.RenderTarget[0].SrcBlendAlpha!=D3D10_BLEND_ONE))
		{
			SAVE_STATE(glBlendFuncSeparate,mappingGL(desc.RenderTarget[0].SrcBlend)
				,mappingGL(desc.RenderTarget[0].DestBlend)
				,mappingGL(desc.RenderTarget[0].SrcBlendAlpha)
				,mappingGL(desc.RenderTarget[0].DestBlendAlpha));
		}
		else if((desc.RenderTarget[0].DestBlend!=D3D10_BLEND_ZERO)||(desc.RenderTarget[0].SrcBlend!=D3D10_BLEND_ONE))
		{
			SAVE_STATE(glBlendFunc,mappingGL(desc.RenderTarget[0].SrcBlend),mappingGL(desc.RenderTarget[0].DestBlend));
		}
	}
	if(desc.IndependentBlendEnable)
	{
		for(Int32 i=1;i<sizeof(desc.RenderTarget)/sizeof(desc.RenderTarget[0]);++i)
		{
			if(desc.RenderTarget[i].BlendOpAlpha!=D3D10_BLEND_OP_ADD)
			{
				SAVE_STATE(glBlendEquationSeparatei,i,mappingGL(desc.RenderTarget[i].BlendOp),mappingGL(desc.RenderTarget[i].BlendOpAlpha));
			}
			else if(desc.RenderTarget[i].BlendOp!=D3D10_BLEND_OP_ADD)
			{
				SAVE_STATE(glBlendEquationi,i,mappingGL(desc.RenderTarget[i].BlendOp));
			}
			if((desc.RenderTarget[i].DestBlendAlpha!=D3D10_BLEND_ZERO)||(desc.RenderTarget[i].SrcBlendAlpha!=D3D10_BLEND_ONE))
			{
				SAVE_STATE(glBlendFuncSeparatei,i
					,mappingGL(desc.RenderTarget[i].SrcBlend),mappingGL(desc.RenderTarget[i].DestBlend)
					,mappingGL(desc.RenderTarget[i].SrcBlendAlpha),mappingGL(desc.RenderTarget[i].DestBlendAlpha));
			}
			else if((desc.RenderTarget[i].DestBlend!=D3D10_BLEND_ZERO)||(desc.RenderTarget[i].SrcBlend!=D3D10_BLEND_ONE))
			{
				SAVE_STATE(glBlendFunci,i,mappingGL(desc.RenderTarget[i].SrcBlend),mappingGL(desc.RenderTarget[i].DestBlend));
			}
		}
	}
	if((desc.RenderTarget[0].RenderTargetWriteMask&D3D10_COLOR_WRITE_ENABLE_ALL)!=D3D10_COLOR_WRITE_ENABLE_ALL)
	{
		SAVE_STATE(glColorMask,desc.RenderTarget[0].RenderTargetWriteMask&D3D10_COLOR_WRITE_ENABLE_RED?GL_TRUE:GL_FALSE,
			desc.RenderTarget[0].RenderTargetWriteMask&D3D10_COLOR_WRITE_ENABLE_GREEN?GL_TRUE:GL_FALSE,
			desc.RenderTarget[0].RenderTargetWriteMask&D3D10_COLOR_WRITE_ENABLE_BLUE?GL_TRUE:GL_FALSE,
			desc.RenderTarget[0].RenderTargetWriteMask&D3D10_COLOR_WRITE_ENABLE_ALPHA?GL_TRUE:GL_FALSE);
	}
	if(desc.RenderTarget[0].BlendEnable)
	{
		SAVE_STATE(glEnable,GL_BLEND);
	}
	for(int i=1;i<sizeof(desc.RenderTarget)/sizeof(desc.RenderTarget[0]);++i)
	{
		if((desc.RenderTarget[i].RenderTargetWriteMask&D3D10_COLOR_WRITE_ENABLE_ALL)!=D3D10_COLOR_WRITE_ENABLE_ALL)
		{
			SAVE_STATE(glColorMaski,i,
				desc.RenderTarget[i].RenderTargetWriteMask&D3D10_COLOR_WRITE_ENABLE_RED?GL_TRUE:GL_FALSE,
				desc.RenderTarget[i].RenderTargetWriteMask&D3D10_COLOR_WRITE_ENABLE_GREEN?GL_TRUE:GL_FALSE,
				desc.RenderTarget[i].RenderTargetWriteMask&D3D10_COLOR_WRITE_ENABLE_BLUE?GL_TRUE:GL_FALSE,
				desc.RenderTarget[i].RenderTargetWriteMask&D3D10_COLOR_WRITE_ENABLE_ALPHA?GL_TRUE:GL_FALSE);
		}
		if(desc.RenderTarget[i].BlendEnable)
		{
			SAVE_STATE(glEnablei,GL_BLEND,i);
		}
	}
	return True;
}

Bool NSDevilX::NSGraphicsAPI::CGLDeviceImp::createBlendState(const D3D11_BLEND_DESC& desc,OUT IBlendState* state)
{
	if(desc.AlphaToCoverageEnable)
	{
		SAVE_STATE(glEnable,GL_SAMPLE_ALPHA_TO_COVERAGE);
	}
	{
		if(desc.RenderTarget[0].BlendOpAlpha!=D3D11_BLEND_OP_ADD)
		{
			SAVE_STATE(glBlendEquationSeparate,mappingGL(desc.RenderTarget[0].BlendOp),mappingGL(desc.RenderTarget[0].BlendOpAlpha));
		}
		else if(desc.RenderTarget[0].BlendOp!=D3D11_BLEND_OP_ADD)
		{
			SAVE_STATE(glBlendEquation,mappingGL(desc.RenderTarget[0].BlendOp));
		}
		if((desc.RenderTarget[0].DestBlendAlpha!=D3D11_BLEND_ZERO)||(desc.RenderTarget[0].SrcBlendAlpha!=D3D11_BLEND_ONE))
		{
			SAVE_STATE(glBlendFuncSeparate,mappingGL(desc.RenderTarget[0].SrcBlend),
				mappingGL(desc.RenderTarget[0].DestBlend),
				mappingGL(desc.RenderTarget[0].SrcBlendAlpha),
				mappingGL(desc.RenderTarget[0].DestBlendAlpha));
		}
		else if((desc.RenderTarget[0].DestBlend!=D3D11_BLEND_ZERO)||(desc.RenderTarget[0].SrcBlend!=D3D11_BLEND_ONE))
		{
			SAVE_STATE(glBlendFunc,mappingGL(desc.RenderTarget[0].SrcBlend),mappingGL(desc.RenderTarget[0].DestBlend));
		}
	}
	if(desc.IndependentBlendEnable)
	{
		for(Int32 i=1;i<sizeof(desc.RenderTarget)/sizeof(desc.RenderTarget[0]);++i)
		{
			if(desc.RenderTarget[i].BlendOpAlpha!=D3D11_BLEND_OP_ADD)
			{
				SAVE_STATE(glBlendEquationSeparatei,i,mappingGL(desc.RenderTarget[i].BlendOp),mappingGL(desc.RenderTarget[i].BlendOpAlpha));
			}
			else if(desc.RenderTarget[i].BlendOp!=D3D11_BLEND_OP_ADD)
			{
				SAVE_STATE(glBlendEquationi,i,mappingGL(desc.RenderTarget[i].BlendOp));
			}
			if((desc.RenderTarget[i].DestBlendAlpha!=D3D11_BLEND_ZERO)||(desc.RenderTarget[i].SrcBlendAlpha!=D3D11_BLEND_ONE))
			{
				SAVE_STATE(glBlendFuncSeparatei,i,mappingGL(desc.RenderTarget[i].SrcBlend),
					mappingGL(desc.RenderTarget[i].DestBlend),mappingGL(desc.RenderTarget[i].SrcBlendAlpha),mappingGL(desc.RenderTarget[i].DestBlendAlpha));
			}
			else if((desc.RenderTarget[i].DestBlend!=D3D11_BLEND_ZERO)||(desc.RenderTarget[i].SrcBlend!=D3D11_BLEND_ONE))
			{
				SAVE_STATE(glBlendFunci,i,mappingGL(desc.RenderTarget[i].SrcBlend),mappingGL(desc.RenderTarget[i].DestBlend));
			}
		}
	}
	if((desc.RenderTarget[0].RenderTargetWriteMask&D3D11_COLOR_WRITE_ENABLE_ALL)!=D3D11_COLOR_WRITE_ENABLE_ALL)
	{
		SAVE_STATE(glColorMask,desc.RenderTarget[0].RenderTargetWriteMask&D3D11_COLOR_WRITE_ENABLE_RED?GL_TRUE:GL_FALSE,
			desc.RenderTarget[0].RenderTargetWriteMask&D3D11_COLOR_WRITE_ENABLE_GREEN?GL_TRUE:GL_FALSE,desc.RenderTarget[0].RenderTargetWriteMask&D3D11_COLOR_WRITE_ENABLE_BLUE?GL_TRUE:GL_FALSE,
			desc.RenderTarget[0].RenderTargetWriteMask&D3D11_COLOR_WRITE_ENABLE_ALPHA?GL_TRUE:GL_FALSE);
	}
	if(desc.RenderTarget[0].BlendEnable)
	{
		SAVE_STATE(glEnable,GL_BLEND);
	}
	for(int i=1;i<sizeof(desc.RenderTarget)/sizeof(desc.RenderTarget[0]);++i)
	{
		if((desc.RenderTarget[i].RenderTargetWriteMask&D3D11_COLOR_WRITE_ENABLE_ALL)!=D3D11_COLOR_WRITE_ENABLE_ALL)
		{
			SAVE_STATE(glColorMaski,i,desc.RenderTarget[i].RenderTargetWriteMask&D3D11_COLOR_WRITE_ENABLE_RED?GL_TRUE:GL_FALSE,
				desc.RenderTarget[i].RenderTargetWriteMask&D3D11_COLOR_WRITE_ENABLE_GREEN?GL_TRUE:GL_FALSE,desc.RenderTarget[i].RenderTargetWriteMask&D3D11_COLOR_WRITE_ENABLE_BLUE?GL_TRUE:GL_FALSE,
				desc.RenderTarget[i].RenderTargetWriteMask&D3D11_COLOR_WRITE_ENABLE_ALPHA?GL_TRUE:GL_FALSE);
		}
		if(desc.RenderTarget[i].BlendEnable)
		{
			SAVE_STATE(glEnablei,GL_BLEND,i);
		}
	}
	return True;
}

Bool NSDevilX::NSGraphicsAPI::CGLDeviceImp::createBlendState(const D3D11_BLEND_DESC1& desc,OUT IBlendState* state)
{
	if(desc.AlphaToCoverageEnable)
	{
		SAVE_STATE(glEnable,GL_SAMPLE_ALPHA_TO_COVERAGE);
	}
	{
		if(desc.RenderTarget[0].BlendOpAlpha!=D3D11_BLEND_OP_ADD)
		{
			SAVE_STATE(glBlendEquationSeparate,mappingGL(desc.RenderTarget[0].BlendOp),mappingGL(desc.RenderTarget[0].BlendOpAlpha));
		}
		else if(desc.RenderTarget[0].BlendOp!=D3D11_BLEND_OP_ADD)
		{
			SAVE_STATE(glBlendEquation,mappingGL(desc.RenderTarget[0].BlendOp));
		}
		if((desc.RenderTarget[0].DestBlendAlpha!=D3D11_BLEND_ZERO)||(desc.RenderTarget[0].SrcBlendAlpha!=D3D11_BLEND_ONE))
		{
			SAVE_STATE(glBlendFuncSeparate,mappingGL(desc.RenderTarget[0].SrcBlend),mappingGL(desc.RenderTarget[0].DestBlend),
				mappingGL(desc.RenderTarget[0].SrcBlendAlpha),mappingGL(desc.RenderTarget[0].DestBlendAlpha));
		}
		else if((desc.RenderTarget[0].DestBlend!=D3D11_BLEND_ZERO)||(desc.RenderTarget[0].SrcBlend!=D3D11_BLEND_ONE))
		{
			SAVE_STATE(glBlendFunc,mappingGL(desc.RenderTarget[0].SrcBlend),mappingGL(desc.RenderTarget[0].DestBlend));
		}
	}
	if(desc.RenderTarget[0].LogicOpEnable)
	{
		if(D3D11_LOGIC_OP_NOOP!=desc.RenderTarget[0].LogicOp)
		{
			SAVE_STATE(glLogicOp,mappingGL(desc.RenderTarget[0].LogicOp));
		}
	}
	if(desc.IndependentBlendEnable)
	{
		for(Int32 i=1;i<sizeof(desc.RenderTarget)/sizeof(desc.RenderTarget[0]);++i)
		{
			if(desc.RenderTarget[i].BlendOpAlpha!=D3D11_BLEND_OP_ADD)
			{
				SAVE_STATE(glBlendEquationSeparatei,i,mappingGL(desc.RenderTarget[i].BlendOp),mappingGL(desc.RenderTarget[i].BlendOpAlpha));
			}
			else if(desc.RenderTarget[i].BlendOp!=D3D11_BLEND_OP_ADD)
			{
				SAVE_STATE(glBlendEquationi,i,mappingGL(desc.RenderTarget[i].BlendOp));
			}
			if((desc.RenderTarget[i].DestBlendAlpha!=D3D11_BLEND_ZERO)||(desc.RenderTarget[i].SrcBlendAlpha!=D3D11_BLEND_ONE))
			{
				SAVE_STATE(glBlendFuncSeparatei,i,mappingGL(desc.RenderTarget[i].SrcBlend),
					mappingGL(desc.RenderTarget[i].DestBlend),mappingGL(desc.RenderTarget[i].SrcBlendAlpha),
					mappingGL(desc.RenderTarget[i].DestBlendAlpha));
			}
			else if((desc.RenderTarget[i].DestBlend!=D3D11_BLEND_ZERO)||(desc.RenderTarget[i].SrcBlend!=D3D11_BLEND_ONE))
			{
				SAVE_STATE(glBlendFunci,i,
					mappingGL(desc.RenderTarget[i].SrcBlend),mappingGL(desc.RenderTarget[i].DestBlend));
			}
		}
	}
	if((desc.RenderTarget[0].RenderTargetWriteMask&D3D11_COLOR_WRITE_ENABLE_ALL)!=D3D11_COLOR_WRITE_ENABLE_ALL)
	{
		SAVE_STATE(glColorMask,desc.RenderTarget[0].RenderTargetWriteMask&D3D11_COLOR_WRITE_ENABLE_RED?GL_TRUE:GL_FALSE,
			desc.RenderTarget[0].RenderTargetWriteMask&D3D11_COLOR_WRITE_ENABLE_GREEN?GL_TRUE:GL_FALSE,desc.RenderTarget[0].RenderTargetWriteMask&D3D11_COLOR_WRITE_ENABLE_BLUE?GL_TRUE:GL_FALSE,
			desc.RenderTarget[0].RenderTargetWriteMask&D3D11_COLOR_WRITE_ENABLE_ALPHA?GL_TRUE:GL_FALSE);
	}
	if(desc.RenderTarget[0].BlendEnable)
	{
		SAVE_STATE(glEnable,GL_BLEND);
	}
	for(int i=1;i<sizeof(desc.RenderTarget)/sizeof(desc.RenderTarget[0]);++i)
	{
		if((desc.RenderTarget[i].RenderTargetWriteMask&D3D11_COLOR_WRITE_ENABLE_ALL)!=D3D11_COLOR_WRITE_ENABLE_ALL)
		{
			SAVE_STATE(glColorMaski,i,
				desc.RenderTarget[i].RenderTargetWriteMask&D3D11_COLOR_WRITE_ENABLE_RED?GL_TRUE:GL_FALSE,desc.RenderTarget[i].RenderTargetWriteMask&D3D11_COLOR_WRITE_ENABLE_GREEN?GL_TRUE:GL_FALSE,
				desc.RenderTarget[i].RenderTargetWriteMask&D3D11_COLOR_WRITE_ENABLE_BLUE?GL_TRUE:GL_FALSE,desc.RenderTarget[i].RenderTargetWriteMask&D3D11_COLOR_WRITE_ENABLE_ALPHA?GL_TRUE:GL_FALSE);
		}
		if(desc.RenderTarget[i].BlendEnable)
		{
			SAVE_STATE(glEnablei,GL_BLEND,i);
		}
	}
	return True;
}

Bool NSDevilX::NSGraphicsAPI::CGLDeviceImp::createDepthStencilState(const D3D10_DEPTH_STENCIL_DESC& desc,OUT IDepthStencilState* state)
{
	if((desc.FrontFace.StencilDepthFailOp==desc.BackFace.StencilDepthFailOp)
		&&(desc.FrontFace.StencilFailOp==desc.BackFace.StencilFailOp)
		&&(desc.FrontFace.StencilPassOp==desc.BackFace.StencilPassOp)
		)
	{
		SAVE_STATE(glStencilOp,mappingGL(desc.BackFace.StencilFailOp),mappingGL(desc.BackFace.StencilDepthFailOp),mappingGL(desc.BackFace.StencilPassOp));
	}
	else
	{
		if((desc.BackFace.StencilDepthFailOp!=D3D10_STENCIL_OP_KEEP)
			||(desc.BackFace.StencilFailOp!=D3D10_STENCIL_OP_KEEP)
			||(desc.BackFace.StencilPassOp!=D3D10_STENCIL_OP_KEEP)
			)
		{
			SAVE_STATE(glStencilOpSeparate,GL_BACK,mappingGL(desc.BackFace.StencilFailOp),
				mappingGL(desc.BackFace.StencilDepthFailOp),mappingGL(desc.BackFace.StencilPassOp));
		}
		if((desc.FrontFace.StencilDepthFailOp!=D3D10_STENCIL_OP_KEEP)
			||(desc.FrontFace.StencilFailOp!=D3D10_STENCIL_OP_KEEP)
			||(desc.FrontFace.StencilPassOp!=D3D10_STENCIL_OP_KEEP)
			)
		{
			SAVE_STATE(glStencilOpSeparate,GL_FRONT,mappingGL(desc.FrontFace.StencilFailOp),
				mappingGL(desc.FrontFace.StencilDepthFailOp),mappingGL(desc.FrontFace.StencilPassOp));
		}
	}
	if(desc.BackFace.StencilFunc==desc.FrontFace.StencilFunc)
	{
		if((desc.BackFace.StencilFunc!=D3D10_COMPARISON_ALWAYS)
			||(desc.FrontFace.StencilFunc!=D3D10_COMPARISON_ALWAYS)
			)
		{
			SAVE_STATE(glStencilFunc,mappingGL(desc.BackFace.StencilFunc),0,desc.StencilReadMask);
		}
	}
	else
	{
		if((desc.BackFace.StencilFunc!=D3D10_COMPARISON_ALWAYS)
			||(desc.FrontFace.StencilFunc!=D3D10_COMPARISON_ALWAYS)
			)
		{
			SAVE_STATE(glStencilFuncSeparate,mappingGL(desc.FrontFace.StencilFunc),mappingGL(desc.BackFace.StencilFunc),0,desc.StencilReadMask);
		}
	}
	if(!desc.DepthEnable)
	{
		SAVE_STATE(glDisable,GL_DEPTH_TEST);
	}
	if(desc.DepthFunc!=D3D10_COMPARISON_LESS_EQUAL)
	{
		SAVE_STATE(glDepthFunc,mappingGL(desc.DepthFunc));
	}
	if(desc.DepthWriteMask!=D3D10_DEPTH_WRITE_MASK_ALL)
	{
		SAVE_STATE(glDepthMask,GL_FALSE);
	}
	if(desc.StencilEnable)
	{
		SAVE_STATE(glEnable,GL_STENCIL_TEST);
	}
	if(desc.StencilWriteMask!=0xff)
	{
		SAVE_STATE(glStencilMask,desc.StencilWriteMask);
	}
	return True;
}

Bool NSDevilX::NSGraphicsAPI::CGLDeviceImp::createDepthStencilState(const D3D11_DEPTH_STENCIL_DESC& desc,OUT IDepthStencilState* state)
{
	if((desc.FrontFace.StencilDepthFailOp==desc.BackFace.StencilDepthFailOp)
		&&(desc.FrontFace.StencilFailOp==desc.BackFace.StencilFailOp)
		&&(desc.FrontFace.StencilPassOp==desc.BackFace.StencilPassOp)
		)
	{
		SAVE_STATE(glStencilOp,mappingGL(desc.BackFace.StencilFailOp),mappingGL(desc.BackFace.StencilDepthFailOp),
			mappingGL(desc.BackFace.StencilPassOp));
	}
	else
	{
		if((desc.BackFace.StencilDepthFailOp!=D3D11_STENCIL_OP_KEEP)
			||(desc.BackFace.StencilFailOp!=D3D11_STENCIL_OP_KEEP)
			||(desc.BackFace.StencilPassOp!=D3D11_STENCIL_OP_KEEP)
			)
		{
			SAVE_STATE(glStencilOpSeparate,GL_BACK,mappingGL(desc.BackFace.StencilFailOp),
				mappingGL(desc.BackFace.StencilDepthFailOp),mappingGL(desc.BackFace.StencilPassOp));
		}
		if((desc.FrontFace.StencilDepthFailOp!=D3D11_STENCIL_OP_KEEP)
			||(desc.FrontFace.StencilFailOp!=D3D11_STENCIL_OP_KEEP)
			||(desc.FrontFace.StencilPassOp!=D3D11_STENCIL_OP_KEEP)
			)
		{
			SAVE_STATE(glStencilOpSeparate,GL_FRONT,mappingGL(desc.FrontFace.StencilFailOp),
				mappingGL(desc.FrontFace.StencilDepthFailOp),mappingGL(desc.FrontFace.StencilPassOp));
		}
	}
	if(desc.BackFace.StencilFunc==desc.FrontFace.StencilFunc)
	{
		if((desc.BackFace.StencilFunc!=D3D11_COMPARISON_ALWAYS)
			||(desc.FrontFace.StencilFunc!=D3D11_COMPARISON_ALWAYS)
			)
		{
			SAVE_STATE(glStencilFunc,mappingGL(desc.BackFace.StencilFunc),0,desc.StencilReadMask);
		}
	}
	else
	{
		if((desc.BackFace.StencilFunc!=D3D11_COMPARISON_ALWAYS)
			||(desc.FrontFace.StencilFunc!=D3D11_COMPARISON_ALWAYS)
			)
		{
			SAVE_STATE(glStencilFuncSeparate,mappingGL(desc.FrontFace.StencilFunc),mappingGL(desc.BackFace.StencilFunc),0,
				desc.StencilReadMask);
		}
	}
	if(!desc.DepthEnable)
	{
		SAVE_STATE(glDisable,GL_DEPTH_TEST);
	}
	if(desc.DepthFunc!=D3D11_COMPARISON_LESS_EQUAL)
	{
		SAVE_STATE(glDepthFunc,mappingGL(desc.DepthFunc));
	}
	if(desc.DepthWriteMask!=D3D11_DEPTH_WRITE_MASK_ALL)
	{
		SAVE_STATE(glDepthMask,GL_FALSE);
	}
	if(desc.StencilEnable)
	{
		SAVE_STATE(glEnable,GL_STENCIL_TEST);
	}
	if(desc.StencilWriteMask!=0xff)
	{
		SAVE_STATE(glStencilMask,desc.StencilWriteMask);
	}
	return True;
}

Bool NSDevilX::NSGraphicsAPI::CGLDeviceImp::createRasterizerState(const D3D10_RASTERIZER_DESC& desc,OUT IRasterizerState* state)
{
	if(desc.AntialiasedLineEnable)
	{
		SAVE_STATE(glEnable,GL_LINE_SMOOTH);
	}
	if(desc.CullMode!=D3D10_CULL_BACK)
	{
		SAVE_STATE(glCullFace,mappingGL(desc.CullMode));
	}
	if(desc.DepthBiasClamp!=0)
	{
		SAVE_STATE(glPolygonOffsetClamp,desc.SlopeScaledDepthBias,*reinterpret_cast<const GLfloat*>(&desc.DepthBias),desc.DepthBiasClamp);
	}
	else if((desc.DepthBias!=0)||(desc.SlopeScaledDepthBias!=0))
	{
		SAVE_STATE(glPolygonOffset,desc.SlopeScaledDepthBias,*reinterpret_cast<const GLfloat*>(&desc.DepthBias));
	}
	if(!desc.DepthClipEnable)
	{
	}
	if(desc.FillMode!=D3D10_FILL_SOLID)
	{
		SAVE_STATE(glPolygonMode,GL_FRONT_AND_BACK,mappingGL(desc.FillMode));
	}
	if(desc.FrontCounterClockwise)
	{
		SAVE_STATE(glFrontFace,GL_CW);
	}
	if(desc.MultisampleEnable)
	{
		SAVE_STATE(glEnable,GL_POLYGON_SMOOTH);
	}
	if(desc.ScissorEnable)
	{
		SAVE_STATE(glEnable,GL_SCISSOR_TEST);
	}
	return True;
}

Bool NSDevilX::NSGraphicsAPI::CGLDeviceImp::createRasterizerState(const D3D11_RASTERIZER_DESC& desc,OUT IRasterizerState* state)
{
	if(desc.AntialiasedLineEnable)
	{
		SAVE_STATE(glEnable,GL_LINE_SMOOTH);
	}
	if(desc.CullMode!=D3D11_CULL_BACK)
	{
		SAVE_STATE(glCullFace,mappingGL(desc.CullMode));
	}
	if(desc.DepthBiasClamp!=0)
	{
		SAVE_STATE(glPolygonOffsetClamp,desc.SlopeScaledDepthBias,*reinterpret_cast<const GLfloat*>(&desc.DepthBias),desc.DepthBiasClamp);
	}
	else if((desc.DepthBias!=0)||(desc.SlopeScaledDepthBias!=0))
	{
		SAVE_STATE(glPolygonOffset,desc.SlopeScaledDepthBias,*reinterpret_cast<const GLfloat*>(&desc.DepthBias));
	}
	if(!desc.DepthClipEnable)
	{
	}
	if(desc.FillMode!=D3D11_FILL_SOLID)
	{
		SAVE_STATE(glPolygonMode,GL_FRONT_AND_BACK,mappingGL(desc.FillMode));
	}
	if(desc.FrontCounterClockwise)
	{
		SAVE_STATE(glFrontFace,GL_CW);
	}
	if(desc.MultisampleEnable)
	{
		SAVE_STATE(glEnable,GL_MULTISAMPLE);
	}
	if(desc.ScissorEnable)
	{
		SAVE_STATE(glEnable,GL_SCISSOR_TEST);
	}
	return True;
}

Bool NSDevilX::NSGraphicsAPI::CGLDeviceImp::createRasterizerState(const D3D11_RASTERIZER_DESC1& desc,OUT IRasterizerState* state)
{
	if(desc.ForcedSampleCount>0)
	{
		SAVE_STATE(glMinSampleShading,*reinterpret_cast<const GLfloat*>(&desc.ForcedSampleCount));
	}
	return createRasterizerState(*reinterpret_cast<const D3D11_RASTERIZER_DESC*>(&desc),state);
}

Bool NSDevilX::NSGraphicsAPI::CGLDeviceImp::createRasterizerState(const D3D11_RASTERIZER_DESC2& desc,OUT IRasterizerState* state)
{
	if(desc.ConservativeRaster!=D3D11_CONSERVATIVE_RASTERIZATION_MODE_OFF)
	{
		SAVE_STATE(glEnable,mappingGL(desc.ConservativeRaster));
	}
	return createRasterizerState(*reinterpret_cast<const D3D11_RASTERIZER_DESC1*>(&desc),state);
}

Bool NSDevilX::NSGraphicsAPI::CGLDeviceImp::createSamplerState(const D3D10_SAMPLER_DESC& desc,OUT ISamplerState* state)
{
	SAVE_STATE(glTexParameteri,0,GL_TEXTURE_WRAP_S,mappingGL(desc.AddressU));
	SAVE_STATE(glTexParameteri,0,GL_TEXTURE_WRAP_T,mappingGL(desc.AddressV));
	SAVE_STATE(glTexParameteri,0,GL_TEXTURE_WRAP_R,mappingGL(desc.AddressW));
	auto border_color=new GLfloat[4];
	memcpy(border_color,desc.BorderColor,sizeof(desc.BorderColor));
	SAVE_STATE(glTexParameterfv,0,GL_TEXTURE_BORDER_COLOR,border_color);
	SAVE_STATE(glTexParameteri,0,GL_TEXTURE_COMPARE_FUNC,mappingGL(desc.ComparisonFunc));
	SAVE_STATE(glTexParameteri,0,GL_TEXTURE_MAG_FILTER,mappingGLMag(desc.Filter));
	SAVE_STATE(glTexParameteri,0,GL_TEXTURE_MIN_FILTER,mappingGLMag(desc.Filter));
	SAVE_STATE(glTexParameterf,0,GL_TEXTURE_MAX_ANISOTROPY,static_cast<GLfloat>(desc.MaxAnisotropy));
	return True;
}

Bool NSDevilX::NSGraphicsAPI::CGLDeviceImp::createSamplerState(const D3D11_SAMPLER_DESC& desc,OUT ISamplerState* state)
{
	return createSamplerState(*reinterpret_cast<const D3D10_SAMPLER_DESC*>(&desc),state);
}

Bool NSDevilX::NSGraphicsAPI::CGLDeviceImp::getSurfaceLevel(ITexture* texture,UINT level,OUT ISurface* surface)
{
	return Bool();
}

Bool NSDevilX::NSGraphicsAPI::CGLDeviceImp::getCubeMapSurface(ITexture* texture,D3DCUBEMAP_FACES faceType,UINT level,OUT ISurface* surface)
{
	return Bool();
}

Bool NSDevilX::NSGraphicsAPI::CGLDeviceImp::createRenderTarget(UINT width,UINT height,D3DFORMAT format,D3DMULTISAMPLE_TYPE multiSample,DWORD multiSampleQuality,BOOL lockable,OUT ISurface* surface)
{
	return Bool();
}

Bool NSDevilX::NSGraphicsAPI::CGLDeviceImp::createDepthStencilSurface(UINT width,UINT height,D3DFORMAT format,D3DMULTISAMPLE_TYPE multiSample,DWORD multiSampleQuality,BOOL discard,OUT ISurface* surface)
{
	return Bool();
}

Bool NSDevilX::NSGraphicsAPI::CGLDeviceImp::renderbufferStorage(GLenum target,GLenum internalformat,GLsizei width,GLsizei height,OUT ISurface* surface)
{
	return Bool();
}

Bool NSDevilX::NSGraphicsAPI::CGLDeviceImp::renderbufferStorageMultisample(GLenum target,GLsizei samples,GLenum internalformat,GLsizei width,GLsizei height,OUT ISurface* surface)
{
	return Bool();
}

Bool NSDevilX::NSGraphicsAPI::CGLDeviceImp::createRenderTargetView(ITexture* resource,const D3D10_RENDER_TARGET_VIEW_DESC* desc,OUT IRenderTargetView* view)
{
	return Bool();
}

Bool NSDevilX::NSGraphicsAPI::CGLDeviceImp::createRenderTargetView(ITexture* resource,const D3D11_RENDER_TARGET_VIEW_DESC* desc,OUT IRenderTargetView* view)
{
	return Bool();
}

Bool NSDevilX::NSGraphicsAPI::CGLDeviceImp::createDepthStencilView(ITexture* resource,const D3D10_DEPTH_STENCIL_VIEW_DESC* desc,OUT IDepthStencilView* view)
{
	return Bool();
}

Bool NSDevilX::NSGraphicsAPI::CGLDeviceImp::createDepthStencilView(ITexture* resource,const D3D11_DEPTH_STENCIL_VIEW_DESC* desc,OUT IDepthStencilView* view)
{
	return Bool();
}

Bool NSDevilX::NSGraphicsAPI::CGLDeviceImp::framebufferTexture2D(GLenum target,GLenum attachment,GLenum textarget,ITexture* texture,GLint level,OUT IFrameBufferObject* fbo)
{
	return Bool();
}

Bool NSDevilX::NSGraphicsAPI::CGLDeviceImp::framebufferTextureLayer(GLenum target,GLenum attachment,ITexture* texture,GLint level,GLint layer,OUT IFrameBufferObject* fbo)
{
	return Bool();
}

Bool NSDevilX::NSGraphicsAPI::CGLDeviceImp::framebufferTexture(GLenum target,GLenum attachment,ITexture* texture,GLint level,OUT IFrameBufferObject* fbo)
{
	return Bool();
}

Bool NSDevilX::NSGraphicsAPI::CGLDeviceImp::framebufferRenderbuffer(GLenum target,GLenum attachment,GLenum renderbuffertarget,ISurface* surface,OUT IFrameBufferObject* fbo)
{
	return Bool();
}

Bool NSDevilX::NSGraphicsAPI::CGLDeviceImp::createShaderResourceView(IBuffer* resource,const D3D10_SHADER_RESOURCE_VIEW_DESC* desc,OUT IShaderResourceView* view)
{
	return Bool();
}

Bool NSDevilX::NSGraphicsAPI::CGLDeviceImp::createShaderResourceView(ITexture* resource,const D3D10_SHADER_RESOURCE_VIEW_DESC* desc,OUT IShaderResourceView* view)
{
	return Bool();
}

Bool NSDevilX::NSGraphicsAPI::CGLDeviceImp::createShaderResourceView(ITexture* resource,const D3D10_SHADER_RESOURCE_VIEW_DESC1* desc,OUT IShaderResourceView* view)
{
	return Bool();
}

Bool NSDevilX::NSGraphicsAPI::CGLDeviceImp::createShaderResourceView(IBuffer* resource,const D3D11_SHADER_RESOURCE_VIEW_DESC* desc,OUT IShaderResourceView* view)
{
	return Bool();
}

Bool NSDevilX::NSGraphicsAPI::CGLDeviceImp::createShaderResourceView(ITexture* resource,const D3D11_SHADER_RESOURCE_VIEW_DESC* desc,OUT IShaderResourceView* view)
{
	return Bool();
}

NSDevilX::NSGraphicsAPI::CGLES2GraphicsDeviceImp::CGLES2GraphicsDeviceImp()
{
}

NSDevilX::NSGraphicsAPI::CGLES2GraphicsDeviceImp::~CGLES2GraphicsDeviceImp()
{
}

Bool NSDevilX::NSGraphicsAPI::CGLES2GraphicsDeviceImp::createBufferStorage(GLenum target,GLsizeiptr size,ConstVoidPtr initializeData,GLbitfield flags,OUT IBuffer* buffer)
{
	return createBufferData(target,size,initializeData,mappingGLBufferStorageFlagsToBufferDataUsage(flags),buffer);
}

Bool NSDevilX::NSGraphicsAPI::CGLES2GraphicsDeviceImp::createTexture1D(GLenum target,GLint level,GLint internalformat,GLsizei width,GLint border,GLenum format,GLenum type,ConstVoidPtr initializeData,OUT ITexture* texture)
{
	return createTexture2D(target,level,internalformat,width,1,border,format,type,initializeData,texture);
}

Bool NSDevilX::NSGraphicsAPI::CGLES2GraphicsDeviceImp::createTexture3D(GLenum target,GLint level,GLint internalformat,GLsizei width,GLsizei height,GLsizei depth,GLint border,GLenum format,GLenum type,ConstVoidPtr initializeData,OUT ITexture* texture)
{
	return False;
}

Bool NSDevilX::NSGraphicsAPI::CGLES2GraphicsDeviceImp::createTexture2DMSAA(GLenum target,GLsizei samplers,GLenum internalformat,GLsizei width,GLsizei height,GLboolean fixedsamplelocations,OUT ITexture* texture)
{
	return False;
}

Bool NSDevilX::NSGraphicsAPI::CGLES2GraphicsDeviceImp::createTexture3DMSAA(GLenum target,GLsizei samplers,GLenum internalformat,GLsizei width,GLsizei height,GLsizei depth,GLboolean fixedsamplelocations,OUT ITexture* texture)
{
	return False;
}

Bool NSDevilX::NSGraphicsAPI::CGLES2GraphicsDeviceImp::createCompressedTexture1D(GLenum target,GLint level,GLint internalformat,GLsizei width,GLint border,GLsizei imageSize,ConstVoidPtr initializeData,OUT ITexture* texture)
{
	return createCompressedTexture2D(target,level,internalformat,width,1,border,imageSize,initializeData,texture);
}

Bool NSDevilX::NSGraphicsAPI::CGLES2GraphicsDeviceImp::createCompressedTexture3D(GLenum target,GLint level,GLint internalformat,GLsizei width,GLsizei height,GLsizei depth,GLint border,GLsizei imageSize,ConstVoidPtr initializeData,OUT ITexture* texture)
{
	return False;
}

NSDevilX::NSGraphicsAPI::CGLES3GraphicsDeviceImp::CGLES3GraphicsDeviceImp()
{
}

NSDevilX::NSGraphicsAPI::CGLES3GraphicsDeviceImp::~CGLES3GraphicsDeviceImp()
{
}

NSDevilX::NSGraphicsAPI::CGLES3_1GraphicsDeviceImp::CGLES3_1GraphicsDeviceImp()
{
}

NSDevilX::NSGraphicsAPI::CGLES3_1GraphicsDeviceImp::~CGLES3_1GraphicsDeviceImp()
{
}

NSDevilX::NSGraphicsAPI::CGLES3_2GraphicsDeviceImp::CGLES3_2GraphicsDeviceImp()
{
}

NSDevilX::NSGraphicsAPI::CGLES3_2GraphicsDeviceImp::~CGLES3_2GraphicsDeviceImp()
{
}
