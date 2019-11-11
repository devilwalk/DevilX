#include "Precompiler.h"
using namespace NSDevilX;

NSDevilX::NSGraphicsAPI::CGLDeviceImp::CGLDeviceImp()
{
}

NSDevilX::NSGraphicsAPI::CGLDeviceImp::~CGLDeviceImp()
{
}

Bool NSDevilX::NSGraphicsAPI::CGLDeviceImp::createVertexBuffer(UINT length,DWORD usage,DWORD fvf,D3DPOOL pool,OUT IBuffer* buffer)
{
	return createBufferData(GL_ARRAY_BUFFER,length,nullptr,ICommon::mappingGL(pool,usage),buffer);
}

Bool NSDevilX::NSGraphicsAPI::CGLDeviceImp::createIndexBuffer(UINT length,DWORD usage,D3DFORMAT format,D3DPOOL pool,OUT IBuffer* buffer)
{
	return createBufferData(GL_ELEMENT_ARRAY_BUFFER,length,nullptr,ICommon::mappingGL(pool,usage),buffer);
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
	return createBufferData(target,desc.ByteWidth,data,ICommon::mappingGL(desc.Usage,desc.CPUAccessFlags),buffer);
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
	return createBufferData(target,desc.ByteWidth,data,ICommon::mappingGL(desc.Usage,desc.CPUAccessFlags),buffer);
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
	if(ICommon::isCompressedFormat(format))
	{
		if(height==1)
		{
			return createCompressedTexture1D(GL_TEXTURE_1D,levels,ICommon::mappingGLInternalFormat(format),width,0,0,nullptr,texture);
		}
		else
		{
			return createCompressedTexture2D(GL_TEXTURE_2D,levels,ICommon::mappingGLInternalFormat(format),width,height,0,0,nullptr,texture);
		}
	}
	else
	{
		if(height==1)
		{
			return createTexture1D(GL_TEXTURE_1D,levels,ICommon::mappingGLInternalFormat(format),width,0,ICommon::mappingGLFormat(format),GL_BYTE,nullptr,texture);
		}
		else
		{
			return createTexture2D(GL_TEXTURE_2D,levels,ICommon::mappingGLInternalFormat(format),width,height,0,ICommon::mappingGLFormat(format),GL_BYTE,nullptr,texture);
		}
	}
}

Bool NSDevilX::NSGraphicsAPI::CGLDeviceImp::createCubeTexture(UINT edageLength,UINT levels,DWORD usage,D3DFORMAT format,D3DPOOL pool,OUT ITexture* texture)
{
	if(ICommon::isCompressedFormat(format))
	{
		Bool ret=createCompressedTexture2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X,levels,ICommon::mappingGLInternalFormat(format),edageLength,edageLength,0,0,nullptr,texture);
		ret&=createCompressedTexture2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y,levels,ICommon::mappingGLInternalFormat(format),edageLength,edageLength,0,0,nullptr,texture);
		ret&=createCompressedTexture2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z,levels,ICommon::mappingGLInternalFormat(format),edageLength,edageLength,0,0,nullptr,texture);
		ret&=createCompressedTexture2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X,levels,ICommon::mappingGLInternalFormat(format),edageLength,edageLength,0,0,nullptr,texture);
		ret&=createCompressedTexture2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,levels,ICommon::mappingGLInternalFormat(format),edageLength,edageLength,0,0,nullptr,texture);
		ret&=createCompressedTexture2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,levels,ICommon::mappingGLInternalFormat(format),edageLength,edageLength,0,0,nullptr,texture);
		return ret;
	}
	else
	{
		Bool ret=createTexture2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X,levels,ICommon::mappingGLInternalFormat(format),edageLength,edageLength,0,ICommon::mappingGLFormat(format),GL_BYTE,nullptr,texture);
		ret&=createTexture2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y,levels,ICommon::mappingGLInternalFormat(format),edageLength,edageLength,0,ICommon::mappingGLFormat(format),GL_BYTE,nullptr,texture);
		ret&=createTexture2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z,levels,ICommon::mappingGLInternalFormat(format),edageLength,edageLength,0,ICommon::mappingGLFormat(format),GL_BYTE,nullptr,texture);
		ret&=createTexture2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X,levels,ICommon::mappingGLInternalFormat(format),edageLength,edageLength,0,ICommon::mappingGLFormat(format),GL_BYTE,nullptr,texture);
		ret&=createTexture2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,levels,ICommon::mappingGLInternalFormat(format),edageLength,edageLength,0,ICommon::mappingGLFormat(format),GL_BYTE,nullptr,texture);
		ret&=createTexture2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,levels,ICommon::mappingGLInternalFormat(format),edageLength,edageLength,0,ICommon::mappingGLFormat(format),GL_BYTE,nullptr,texture);
		return ret;
	}
}

Bool NSDevilX::NSGraphicsAPI::CGLDeviceImp::createVolumeTexture(UINT width,UINT height,UINT depth,UINT levels,DWORD usage,D3DFORMAT format,D3DPOOL pool,OUT ITexture* texture)
{
	if(ICommon::isCompressedFormat(format))
	{
		return createCompressedTexture3D(GL_TEXTURE_3D,levels,ICommon::mappingGLInternalFormat(format),width,height,depth,0,0,nullptr,texture);
	}
	else
	{
		return createTexture3D(GL_TEXTURE_3D,levels,ICommon::mappingGLInternalFormat(format),width,height,depth,0,ICommon::mappingGLFormat(format),GL_BYTE,nullptr,texture);
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
	if(ICommon::isCompressedFormat(desc.Format))
	{
		return createCompressedTexture1D(GL_TEXTURE_1D,desc.MipLevels,ICommon::mappingGLInternalFormat(desc.Format),desc.Width,0,data_size,data,texture);
	}
	else
	{
		return createTexture1D(GL_TEXTURE_1D,desc.MipLevels,ICommon::mappingGLInternalFormat(desc.Format),desc.Width,0,ICommon::mappingGLFormat(desc.Format),GL_BYTE,data,texture);
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
				if(ICommon::isCompressedFormat(desc.Format))
				{
					Bool ret=createCompressedTexture2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X,desc.MipLevels,ICommon::mappingGLInternalFormat(desc.Format),desc.Width,desc.Height,0,slice_pitch,static_cast<ConstBytePtr>(data)+slice_pitch*0,texture);
					ret&=createCompressedTexture2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y,desc.MipLevels,ICommon::mappingGLInternalFormat(desc.Format),desc.Width,desc.Height,0,slice_pitch,static_cast<ConstBytePtr>(data)+slice_pitch*1,texture);
					ret&=createCompressedTexture2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z,desc.MipLevels,ICommon::mappingGLInternalFormat(desc.Format),desc.Width,desc.Height,0,slice_pitch,static_cast<ConstBytePtr>(data)+slice_pitch*2,texture);
					ret&=createCompressedTexture2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X,desc.MipLevels,ICommon::mappingGLInternalFormat(desc.Format),desc.Width,desc.Height,0,slice_pitch,static_cast<ConstBytePtr>(data)+slice_pitch*3,texture);
					ret&=createCompressedTexture2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,desc.MipLevels,ICommon::mappingGLInternalFormat(desc.Format),desc.Width,desc.Height,0,slice_pitch,static_cast<ConstBytePtr>(data)+slice_pitch*4,texture);
					ret&=createCompressedTexture2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,desc.MipLevels,ICommon::mappingGLInternalFormat(desc.Format),desc.Width,desc.Height,0,slice_pitch,static_cast<ConstBytePtr>(data)+slice_pitch*5,texture);
					return ret;
				}
				else
				{
					Bool ret=createTexture2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X,desc.MipLevels,ICommon::mappingGLInternalFormat(desc.Format),desc.Width,desc.Height,0,ICommon::mappingGLFormat(desc.Format),GL_BYTE,static_cast<ConstBytePtr>(data)+slice_pitch*0,texture);
					ret&=createTexture2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y,desc.MipLevels,ICommon::mappingGLInternalFormat(desc.Format),desc.Width,desc.Height,0,ICommon::mappingGLFormat(desc.Format),GL_BYTE,static_cast<ConstBytePtr>(data)+slice_pitch*1,texture);
					ret&=createTexture2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z,desc.MipLevels,ICommon::mappingGLInternalFormat(desc.Format),desc.Width,desc.Height,0,ICommon::mappingGLFormat(desc.Format),GL_BYTE,static_cast<ConstBytePtr>(data)+slice_pitch*2,texture);
					ret&=createTexture2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X,desc.MipLevels,ICommon::mappingGLInternalFormat(desc.Format),desc.Width,desc.Height,0,ICommon::mappingGLFormat(desc.Format),GL_BYTE,static_cast<ConstBytePtr>(data)+slice_pitch*3,texture);
					ret&=createTexture2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,desc.MipLevels,ICommon::mappingGLInternalFormat(desc.Format),desc.Width,desc.Height,0,ICommon::mappingGLFormat(desc.Format),GL_BYTE,static_cast<ConstBytePtr>(data)+slice_pitch*4,texture);
					ret&=createTexture2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,desc.MipLevels,ICommon::mappingGLInternalFormat(desc.Format),desc.Width,desc.Height,0,ICommon::mappingGLFormat(desc.Format),GL_BYTE,static_cast<ConstBytePtr>(data)+slice_pitch*5,texture);
					return ret;
				}
			}
			else
			{
				if(ICommon::isCompressedFormat(desc.Format))
				{
					return createCompressedTexture3D(GL_TEXTURE_CUBE_MAP_ARRAY,desc.MipLevels,ICommon::mappingGLInternalFormat(desc.Format),desc.Width,desc.Height,desc.ArraySize,0,data_size,data,texture);
				}
				else
				{
					return createTexture3D(GL_TEXTURE_CUBE_MAP_ARRAY,desc.MipLevels,ICommon::mappingGLInternalFormat(desc.Format),desc.Width,desc.Height,desc.ArraySize,0,ICommon::mappingGLFormat(desc.Format),GL_BYTE,data,texture);
				}
			}
		}
		else
		{
			if(ICommon::isCompressedFormat(desc.Format))
			{
				return createCompressedTexture3D(GL_TEXTURE_2D_ARRAY,desc.MipLevels,ICommon::mappingGLInternalFormat(desc.Format),desc.Width,desc.Height,desc.ArraySize,0,data_size,data,texture);
			}
			else if(desc.SampleDesc.Count>1)
			{
				return createTexture3DMSAA(GL_TEXTURE_2D_MULTISAMPLE_ARRAY,desc.SampleDesc.Count,ICommon::mappingGLInternalFormat(desc.Format),desc.Width,desc.Height,desc.ArraySize,true,texture);
			}
			else
			{
				return createTexture3D(GL_TEXTURE_2D_ARRAY,desc.MipLevels,ICommon::mappingGLInternalFormat(desc.Format),desc.Width,desc.Height,desc.ArraySize,0,ICommon::mappingGLFormat(desc.Format),GL_BYTE,data,texture);
			}
		}
	}
	else
	{
		if(ICommon::isCompressedFormat(desc.Format))
		{
			return createCompressedTexture2D(GL_TEXTURE_2D,desc.MipLevels,ICommon::mappingGLInternalFormat(desc.Format),desc.Width,desc.Height,0,data_size,data,texture);
		}
		else if(desc.SampleDesc.Count>1)
		{
			return createTexture2DMSAA(GL_TEXTURE_2D_MULTISAMPLE,desc.SampleDesc.Count,ICommon::mappingGLInternalFormat(desc.Format),desc.Width,desc.Height,true,texture);
		}
		else
		{
			return createTexture2D(GL_TEXTURE_2D,desc.MipLevels,ICommon::mappingGLInternalFormat(desc.Format),desc.Width,desc.Height,0,ICommon::mappingGLFormat(desc.Format),GL_BYTE,data,texture);
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
	return createTexture3D(GL_TEXTURE_3D,desc.MipLevels,ICommon::mappingGLInternalFormat(desc.Format),desc.Width,desc.Height,desc.Depth,0,ICommon::mappingGLFormat(desc.Format),GL_BYTE,data,texture);
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
	if(ICommon::isCompressedFormat(desc.Format))
	{
		return createCompressedTexture1D(GL_TEXTURE_1D,desc.MipLevels,ICommon::mappingGLInternalFormat(desc.Format),desc.Width,0,data_size,data,texture);
	}
	else
	{
		return createTexture1D(GL_TEXTURE_1D,desc.MipLevels,ICommon::mappingGLInternalFormat(desc.Format),desc.Width,0,ICommon::mappingGLFormat(desc.Format),GL_BYTE,data,texture);
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
				if(ICommon::isCompressedFormat(desc.Format))
				{
					Bool ret=createCompressedTexture2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X,desc.MipLevels,ICommon::mappingGLInternalFormat(desc.Format),desc.Width,desc.Height,0,slice_pitch,static_cast<ConstBytePtr>(data)+slice_pitch*0,texture);
					ret&=createCompressedTexture2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y,desc.MipLevels,ICommon::mappingGLInternalFormat(desc.Format),desc.Width,desc.Height,0,slice_pitch,static_cast<ConstBytePtr>(data)+slice_pitch*1,texture);
					ret&=createCompressedTexture2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z,desc.MipLevels,ICommon::mappingGLInternalFormat(desc.Format),desc.Width,desc.Height,0,slice_pitch,static_cast<ConstBytePtr>(data)+slice_pitch*2,texture);
					ret&=createCompressedTexture2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X,desc.MipLevels,ICommon::mappingGLInternalFormat(desc.Format),desc.Width,desc.Height,0,slice_pitch,static_cast<ConstBytePtr>(data)+slice_pitch*3,texture);
					ret&=createCompressedTexture2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,desc.MipLevels,ICommon::mappingGLInternalFormat(desc.Format),desc.Width,desc.Height,0,slice_pitch,static_cast<ConstBytePtr>(data)+slice_pitch*4,texture);
					ret&=createCompressedTexture2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,desc.MipLevels,ICommon::mappingGLInternalFormat(desc.Format),desc.Width,desc.Height,0,slice_pitch,static_cast<ConstBytePtr>(data)+slice_pitch*5,texture);
					return ret;
				}
				else
				{
					Bool ret=createTexture2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X,desc.MipLevels,ICommon::mappingGLInternalFormat(desc.Format),desc.Width,desc.Height,0,ICommon::mappingGLFormat(desc.Format),GL_BYTE,static_cast<ConstBytePtr>(data)+slice_pitch*0,texture);
					ret&=createTexture2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y,desc.MipLevels,ICommon::mappingGLInternalFormat(desc.Format),desc.Width,desc.Height,0,ICommon::mappingGLFormat(desc.Format),GL_BYTE,static_cast<ConstBytePtr>(data)+slice_pitch*1,texture);
					ret&=createTexture2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z,desc.MipLevels,ICommon::mappingGLInternalFormat(desc.Format),desc.Width,desc.Height,0,ICommon::mappingGLFormat(desc.Format),GL_BYTE,static_cast<ConstBytePtr>(data)+slice_pitch*2,texture);
					ret&=createTexture2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X,desc.MipLevels,ICommon::mappingGLInternalFormat(desc.Format),desc.Width,desc.Height,0,ICommon::mappingGLFormat(desc.Format),GL_BYTE,static_cast<ConstBytePtr>(data)+slice_pitch*3,texture);
					ret&=createTexture2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,desc.MipLevels,ICommon::mappingGLInternalFormat(desc.Format),desc.Width,desc.Height,0,ICommon::mappingGLFormat(desc.Format),GL_BYTE,static_cast<ConstBytePtr>(data)+slice_pitch*4,texture);
					ret&=createTexture2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,desc.MipLevels,ICommon::mappingGLInternalFormat(desc.Format),desc.Width,desc.Height,0,ICommon::mappingGLFormat(desc.Format),GL_BYTE,static_cast<ConstBytePtr>(data)+slice_pitch*5,texture);
					return ret;
				}
			}
			else
			{
				if(ICommon::isCompressedFormat(desc.Format))
				{
					return createCompressedTexture3D(GL_TEXTURE_CUBE_MAP_ARRAY,desc.MipLevels,ICommon::mappingGLInternalFormat(desc.Format),desc.Width,desc.Height,desc.ArraySize,0,data_size,data,texture);
				}
				else
				{
					return createTexture3D(GL_TEXTURE_CUBE_MAP_ARRAY,desc.MipLevels,ICommon::mappingGLInternalFormat(desc.Format),desc.Width,desc.Height,desc.ArraySize,0,ICommon::mappingGLFormat(desc.Format),GL_BYTE,data,texture);
				}
			}
		}
		else
		{
			if(ICommon::isCompressedFormat(desc.Format))
			{
				return createCompressedTexture3D(GL_TEXTURE_2D_ARRAY,desc.MipLevels,ICommon::mappingGLInternalFormat(desc.Format),desc.Width,desc.Height,desc.ArraySize,0,data_size,data,texture);
			}
			else if(desc.SampleDesc.Count>1)
			{
				return createTexture3DMSAA(GL_TEXTURE_2D_MULTISAMPLE_ARRAY,desc.SampleDesc.Count,ICommon::mappingGLInternalFormat(desc.Format),desc.Width,desc.Height,desc.ArraySize,true,texture);
			}
			else
			{
				return createTexture3D(GL_TEXTURE_2D_ARRAY,desc.MipLevels,ICommon::mappingGLInternalFormat(desc.Format),desc.Width,desc.Height,desc.ArraySize,0,ICommon::mappingGLFormat(desc.Format),GL_BYTE,data,texture);
			}
		}
	}
	else
	{
		if(ICommon::isCompressedFormat(desc.Format))
		{
			return createCompressedTexture2D(GL_TEXTURE_2D,desc.MipLevels,ICommon::mappingGLInternalFormat(desc.Format),desc.Width,desc.Height,0,data_size,data,texture);
		}
		else if(desc.SampleDesc.Count>1)
		{
			return createTexture2DMSAA(GL_TEXTURE_2D_MULTISAMPLE,desc.SampleDesc.Count,ICommon::mappingGLInternalFormat(desc.Format),desc.Width,desc.Height,true,texture);
		}
		else
		{
			return createTexture2D(GL_TEXTURE_2D,desc.MipLevels,ICommon::mappingGLInternalFormat(desc.Format),desc.Width,desc.Height,0,ICommon::mappingGLFormat(desc.Format),GL_BYTE,data,texture);
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
	return createTexture3D(GL_TEXTURE_3D,desc.MipLevels,ICommon::mappingGLInternalFormat(desc.Format),desc.Width,desc.Height,desc.Depth,0,ICommon::mappingGLFormat(desc.Format),GL_BYTE,data,texture);
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
		ret&=vertexAttribFormat(elements->Stream,ICommon::getComponentCount((D3DDECLTYPE)elements->Type),ICommon::getComponentType((D3DDECLTYPE)elements->Type),ICommon::needNormalize((D3DDECLTYPE)elements->Type),elements->Offset,layout);
		++elements;
	}
	return ret;
}

Bool NSDevilX::NSGraphicsAPI::CGLDeviceImp::createInputLayout(const D3D10_INPUT_ELEMENT_DESC* descs,UINT numElements,ConstVoidPtr shaderBytecodeWithInputSignature,SIZE_T bytecodeLength,OUT IInputLayout* layout)
{
	Bool ret=True;
	for(UINT i=0;i<numElements;++i)
	{
		ret&=vertexAttribFormat(descs[i].InputSlot,ICommon::getComponentCount(descs[i].Format),ICommon::getComponentType(descs[i].Format),ICommon::needNormalize(descs[i].Format),descs[i].AlignedByteOffset,layout);
	}
	return ret;
}

Bool NSDevilX::NSGraphicsAPI::CGLDeviceImp::createInputLayout(const D3D11_INPUT_ELEMENT_DESC* descs,UINT numElements,ConstVoidPtr shaderBytecodeWithInputSignature,SIZE_T bytecodeLength,OUT IInputLayout* layout)
{
	Bool ret=True;
	for(UINT i=0;i<numElements;++i)
	{
		ret&=vertexAttribFormat(descs[i].InputSlot,ICommon::getComponentCount(descs[i].Format),ICommon::getComponentType(descs[i].Format),ICommon::needNormalize(descs[i].Format),descs[i].AlignedByteOffset,layout);
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
		static_cast<CGLStateImp*>(state)->mStateChangeParameters_I[glEnable]=GL_SAMPLE_ALPHA_TO_COVERAGE;
	}
	if(desc.BlendOpAlpha!=D3D10_BLEND_OP_ADD)
	{
		static_cast<CGLStateImp*>(state)->mStateChangeParameters_II[glBlendEquationSeparate][0]=ICommon::mappingGL(desc.BlendOp);
		static_cast<CGLStateImp*>(state)->mStateChangeParameters_II[glBlendEquationSeparate][1]=ICommon::mappingGL(desc.BlendOpAlpha);
	}
	else if(desc.BlendOp!=D3D10_BLEND_OP_ADD)
	{
		static_cast<CGLStateImp*>(state)->mStateChangeParameters_I[glBlendEquation]=ICommon::mappingGL(desc.BlendOp);
	}
	if((desc.DestBlendAlpha!=D3D10_BLEND_ZERO)||(desc.SrcBlendAlpha!=D3D10_BLEND_ONE))
	{
		static_cast<CGLStateImp*>(state)->mStateChangeParameters_IIII[glBlendFuncSeparate][0]=ICommon::mappingGL(desc.SrcBlend);
		static_cast<CGLStateImp*>(state)->mStateChangeParameters_IIII[glBlendFuncSeparate][1]=ICommon::mappingGL(desc.DestBlend);
		static_cast<CGLStateImp*>(state)->mStateChangeParameters_IIII[glBlendFuncSeparate][2]=ICommon::mappingGL(desc.SrcBlendAlpha);
		static_cast<CGLStateImp*>(state)->mStateChangeParameters_IIII[glBlendFuncSeparate][3]=ICommon::mappingGL(desc.DestBlendAlpha);
	}
	else if((desc.DestBlend!=D3D10_BLEND_ZERO)||(desc.SrcBlend!=D3D10_BLEND_ONE))
	{
		static_cast<CGLStateImp*>(state)->mStateChangeParameters_II[glBlendFunc][0]=ICommon::mappingGL(desc.SrcBlend);
		static_cast<CGLStateImp*>(state)->mStateChangeParameters_II[glBlendFunc][1]=ICommon::mappingGL(desc.DestBlend);
	}
	if((desc.RenderTargetWriteMask[0]&D3D10_COLOR_WRITE_ENABLE_ALL)!=D3D10_COLOR_WRITE_ENABLE_ALL)
	{
		static_cast<CGLStateImp*>(state)->mStateChangeParameters_IIII[glColorMask][0]=desc.RenderTargetWriteMask[0]&D3D10_COLOR_WRITE_ENABLE_RED?true:false;
		static_cast<CGLStateImp*>(state)->mStateChangeParameters_IIII[glColorMask][1]=desc.RenderTargetWriteMask[0]&D3D10_COLOR_WRITE_ENABLE_GREEN?true:false;
		static_cast<CGLStateImp*>(state)->mStateChangeParameters_IIII[glColorMask][2]=desc.RenderTargetWriteMask[0]&D3D10_COLOR_WRITE_ENABLE_BLUE?true:false;
		static_cast<CGLStateImp*>(state)->mStateChangeParameters_IIII[glColorMask][3]=desc.RenderTargetWriteMask[0]&D3D10_COLOR_WRITE_ENABLE_ALPHA?true:false;
	}
	if(desc.BlendEnable[0])
	{
		static_cast<CGLStateImp*>(state)->mStateChangeParameters_I[glEnable]=GL_BLEND;
	}
	for(Int32 i=1;i<sizeof(desc.BlendEnable)/sizeof(desc.BlendEnable[0]);++i)
	{
		if((desc.RenderTargetWriteMask[i]&D3D10_COLOR_WRITE_ENABLE_ALL)!=D3D10_COLOR_WRITE_ENABLE_ALL)
		{
			static_cast<CGLStateImp*>(state)->mStateChangeParameters_IIII[glColorMaski][0]=i;
			static_cast<CGLStateImp*>(state)->mStateChangeParameters_IIII[glColorMaski][1]=desc.RenderTargetWriteMask[i]&D3D10_COLOR_WRITE_ENABLE_RED?true:false;
			static_cast<CGLStateImp*>(state)->mStateChangeParameters_IIII[glColorMaski][2]=desc.RenderTargetWriteMask[i]&D3D10_COLOR_WRITE_ENABLE_GREEN?true:false;
			static_cast<CGLStateImp*>(state)->mStateChangeParameters_IIII[glColorMaski][3]=desc.RenderTargetWriteMask[i]&D3D10_COLOR_WRITE_ENABLE_BLUE?true:false;
			static_cast<CGLStateImp*>(state)->mStateChangeParameters_IIII[glColorMaski][4]=desc.RenderTargetWriteMask[i]&D3D10_COLOR_WRITE_ENABLE_ALPHA?true:false;
		}
		if(desc.BlendEnable[i])
		{
			static_cast<CGLStateImp*>(state)->mStateChangeParameters_II[glEnablei][0]=GL_BLEND;
			static_cast<CGLStateImp*>(state)->mStateChangeParameters_II[glEnablei][1]=i;
		}
	}
	return True;
}

Bool NSDevilX::NSGraphicsAPI::CGLDeviceImp::createBlendState(const D3D10_BLEND_DESC1& desc,OUT IBlendState* state)
{
	if(desc.AlphaToCoverageEnable)
	{
		static_cast<CGLStateImp*>(state)->mStateChangeParameters_I[glEnable]=GL_SAMPLE_ALPHA_TO_COVERAGE;
	}
	{
		if(desc.RenderTarget[0].BlendOpAlpha!=D3D10_BLEND_OP_ADD)
		{
			static_cast<CGLStateImp*>(state)->mStateChangeParameters_II[glBlendEquationSeparate][0]=ICommon::mappingGL(desc.RenderTarget[0].BlendOp);
			static_cast<CGLStateImp*>(state)->mStateChangeParameters_II[glBlendEquationSeparate][1]=ICommon::mappingGL(desc.RenderTarget[0].BlendOpAlpha);
		}
		else if(desc.RenderTarget[0].BlendOp!=D3D10_BLEND_OP_ADD)
		{
			static_cast<CGLStateImp*>(state)->mStateChangeParameters_I[glBlendEquation]=ICommon::mappingGL(desc.RenderTarget[0].BlendOp);
		}
		if((desc.RenderTarget[0].DestBlendAlpha!=D3D10_BLEND_ZERO)||(desc.RenderTarget[0].SrcBlendAlpha!=D3D10_BLEND_ONE))
		{
			static_cast<CGLStateImp*>(state)->mStateChangeParameters_IIII[glBlendFuncSeparate][0]=ICommon::mappingGL(desc.RenderTarget[0].SrcBlend);
			static_cast<CGLStateImp*>(state)->mStateChangeParameters_IIII[glBlendFuncSeparate][1]=ICommon::mappingGL(desc.RenderTarget[0].DestBlend);
			static_cast<CGLStateImp*>(state)->mStateChangeParameters_IIII[glBlendFuncSeparate][2]=ICommon::mappingGL(desc.RenderTarget[0].SrcBlendAlpha);
			static_cast<CGLStateImp*>(state)->mStateChangeParameters_IIII[glBlendFuncSeparate][3]=ICommon::mappingGL(desc.RenderTarget[0].DestBlendAlpha);
		}
		else if((desc.RenderTarget[0].DestBlend!=D3D10_BLEND_ZERO)||(desc.RenderTarget[0].SrcBlend!=D3D10_BLEND_ONE))
		{
			static_cast<CGLStateImp*>(state)->mStateChangeParameters_II[glBlendFunc][0]=ICommon::mappingGL(desc.RenderTarget[0].SrcBlend);
			static_cast<CGLStateImp*>(state)->mStateChangeParameters_II[glBlendFunc][1]=ICommon::mappingGL(desc.RenderTarget[0].DestBlend);
		}
	}
	if(desc.IndependentBlendEnable)
	{
		for(Int32 i=1;i<sizeof(desc.RenderTarget)/sizeof(desc.RenderTarget[0]);++i)
		{
			if(desc.RenderTarget[i].BlendOpAlpha!=D3D10_BLEND_OP_ADD)
			{
				static_cast<CGLStateImp*>(state)->mStateChangeParameters_III[glBlendEquationSeparatei][0]=i;
				static_cast<CGLStateImp*>(state)->mStateChangeParameters_III[glBlendEquationSeparatei][1]=ICommon::mappingGL(desc.RenderTarget[i].BlendOp);
				static_cast<CGLStateImp*>(state)->mStateChangeParameters_III[glBlendEquationSeparatei][2]=ICommon::mappingGL(desc.RenderTarget[i].BlendOpAlpha);
			}
			else if(desc.RenderTarget[i].BlendOp!=D3D10_BLEND_OP_ADD)
			{
				static_cast<CGLStateImp*>(state)->mStateChangeParameters_II[glBlendEquationi][0]=i;
				static_cast<CGLStateImp*>(state)->mStateChangeParameters_II[glBlendEquationi][1]=ICommon::mappingGL(desc.RenderTarget[i].BlendOp);
			}
			if((desc.RenderTarget[i].DestBlendAlpha!=D3D10_BLEND_ZERO)||(desc.RenderTarget[i].SrcBlendAlpha!=D3D10_BLEND_ONE))
			{
				static_cast<CGLStateImp*>(state)->mStateChangeParameters_IIIII[glBlendFuncSeparatei][0]=i;
				static_cast<CGLStateImp*>(state)->mStateChangeParameters_IIIII[glBlendFuncSeparatei][1]=ICommon::mappingGL(desc.RenderTarget[i].SrcBlend);
				static_cast<CGLStateImp*>(state)->mStateChangeParameters_IIIII[glBlendFuncSeparatei][2]=ICommon::mappingGL(desc.RenderTarget[i].DestBlend);
				static_cast<CGLStateImp*>(state)->mStateChangeParameters_IIIII[glBlendFuncSeparatei][3]=ICommon::mappingGL(desc.RenderTarget[i].SrcBlendAlpha);
				static_cast<CGLStateImp*>(state)->mStateChangeParameters_IIIII[glBlendFuncSeparatei][4]=ICommon::mappingGL(desc.RenderTarget[i].DestBlendAlpha);
			}
			else if((desc.RenderTarget[i].DestBlend!=D3D10_BLEND_ZERO)||(desc.RenderTarget[i].SrcBlend!=D3D10_BLEND_ONE))
			{
				static_cast<CGLStateImp*>(state)->mStateChangeParameters_II[glBlendFunci][0]=i;
				static_cast<CGLStateImp*>(state)->mStateChangeParameters_II[glBlendFunci][1]=ICommon::mappingGL(desc.RenderTarget[i].SrcBlend);
				static_cast<CGLStateImp*>(state)->mStateChangeParameters_II[glBlendFunci][2]=ICommon::mappingGL(desc.RenderTarget[i].DestBlend);
			}
		}
	}
	if((desc.RenderTarget[0].RenderTargetWriteMask&D3D10_COLOR_WRITE_ENABLE_ALL)!=D3D10_COLOR_WRITE_ENABLE_ALL)
	{
		static_cast<CGLStateImp*>(state)->mStateChangeParameters_IIII[glColorMask][0]=desc.RenderTarget[0].RenderTargetWriteMask&D3D10_COLOR_WRITE_ENABLE_RED?true:false;
		static_cast<CGLStateImp*>(state)->mStateChangeParameters_IIII[glColorMask][1]=desc.RenderTarget[0].RenderTargetWriteMask&D3D10_COLOR_WRITE_ENABLE_GREEN?true:false;
		static_cast<CGLStateImp*>(state)->mStateChangeParameters_IIII[glColorMask][2]=desc.RenderTarget[0].RenderTargetWriteMask&D3D10_COLOR_WRITE_ENABLE_BLUE?true:false;
		static_cast<CGLStateImp*>(state)->mStateChangeParameters_IIII[glColorMask][3]=desc.RenderTarget[0].RenderTargetWriteMask&D3D10_COLOR_WRITE_ENABLE_ALPHA?true:false;
	}
	if(desc.RenderTarget[0].BlendEnable)
	{
		static_cast<CGLStateImp*>(state)->mStateChangeParameters_I[glEnable]=GL_BLEND;
	}
	for(int i=1;i<sizeof(desc.RenderTarget)/sizeof(desc.RenderTarget[0]);++i)
	{
		if((desc.RenderTarget[i].RenderTargetWriteMask&D3D10_COLOR_WRITE_ENABLE_ALL)!=D3D10_COLOR_WRITE_ENABLE_ALL)
		{
			static_cast<CGLStateImp*>(state)->mStateChangeParameters_IIII[glColorMaski][0]=i;
			static_cast<CGLStateImp*>(state)->mStateChangeParameters_IIII[glColorMaski][1]=desc.RenderTarget[i].RenderTargetWriteMask&D3D10_COLOR_WRITE_ENABLE_RED?true:false;
			static_cast<CGLStateImp*>(state)->mStateChangeParameters_IIII[glColorMaski][2]=desc.RenderTarget[i].RenderTargetWriteMask&D3D10_COLOR_WRITE_ENABLE_GREEN?true:false;
			static_cast<CGLStateImp*>(state)->mStateChangeParameters_IIII[glColorMaski][3]=desc.RenderTarget[i].RenderTargetWriteMask&D3D10_COLOR_WRITE_ENABLE_BLUE?true:false;
			static_cast<CGLStateImp*>(state)->mStateChangeParameters_IIII[glColorMaski][4]=desc.RenderTarget[i].RenderTargetWriteMask&D3D10_COLOR_WRITE_ENABLE_ALPHA?true:false;
		}
		if(desc.RenderTarget[i].BlendEnable)
		{
			static_cast<CGLStateImp*>(state)->mStateChangeParameters_II[glEnablei][0]=GL_BLEND;
			static_cast<CGLStateImp*>(state)->mStateChangeParameters_II[glEnablei][1]=i;
		}
	}
	return True;
}

Bool NSDevilX::NSGraphicsAPI::CGLDeviceImp::createBlendState(const D3D11_BLEND_DESC& desc,OUT IBlendState* state)
{
	if(desc.AlphaToCoverageEnable)
	{
		static_cast<CGLStateImp*>(state)->mStateChangeParameters_I[glEnable]=GL_SAMPLE_ALPHA_TO_COVERAGE;
	}
	{
		if(desc.RenderTarget[0].BlendOpAlpha!=D3D11_BLEND_OP_ADD)
		{
			static_cast<CGLStateImp*>(state)->mStateChangeParameters_II[glBlendEquationSeparate][0]=ICommon::mappingGL(desc.RenderTarget[0].BlendOp);
			static_cast<CGLStateImp*>(state)->mStateChangeParameters_II[glBlendEquationSeparate][1]=ICommon::mappingGL(desc.RenderTarget[0].BlendOpAlpha);
		}
		else if(desc.RenderTarget[0].BlendOp!=D3D11_BLEND_OP_ADD)
		{
			static_cast<CGLStateImp*>(state)->mStateChangeParameters_I[glBlendEquation]=ICommon::mappingGL(desc.RenderTarget[0].BlendOp);
		}
		if((desc.RenderTarget[0].DestBlendAlpha!=D3D11_BLEND_ZERO)||(desc.RenderTarget[0].SrcBlendAlpha!=D3D11_BLEND_ONE))
		{
			static_cast<CGLStateImp*>(state)->mStateChangeParameters_IIII[glBlendFuncSeparate][0]=ICommon::mappingGL(desc.RenderTarget[0].SrcBlend);
			static_cast<CGLStateImp*>(state)->mStateChangeParameters_IIII[glBlendFuncSeparate][1]=ICommon::mappingGL(desc.RenderTarget[0].DestBlend);
			static_cast<CGLStateImp*>(state)->mStateChangeParameters_IIII[glBlendFuncSeparate][2]=ICommon::mappingGL(desc.RenderTarget[0].SrcBlendAlpha);
			static_cast<CGLStateImp*>(state)->mStateChangeParameters_IIII[glBlendFuncSeparate][3]=ICommon::mappingGL(desc.RenderTarget[0].DestBlendAlpha);
		}
		else if((desc.RenderTarget[0].DestBlend!=D3D11_BLEND_ZERO)||(desc.RenderTarget[0].SrcBlend!=D3D11_BLEND_ONE))
		{
			static_cast<CGLStateImp*>(state)->mStateChangeParameters_II[glBlendFunc][0]=ICommon::mappingGL(desc.RenderTarget[0].SrcBlend);
			static_cast<CGLStateImp*>(state)->mStateChangeParameters_II[glBlendFunc][1]=ICommon::mappingGL(desc.RenderTarget[0].DestBlend);
		}
	}
	if(desc.IndependentBlendEnable)
	{
		for(Int32 i=1;i<sizeof(desc.RenderTarget)/sizeof(desc.RenderTarget[0]);++i)
		{
			if(desc.RenderTarget[i].BlendOpAlpha!=D3D11_BLEND_OP_ADD)
			{
				static_cast<CGLStateImp*>(state)->mStateChangeParameters_III[glBlendEquationSeparatei][0]=i;
				static_cast<CGLStateImp*>(state)->mStateChangeParameters_III[glBlendEquationSeparatei][1]=ICommon::mappingGL(desc.RenderTarget[i].BlendOp);
				static_cast<CGLStateImp*>(state)->mStateChangeParameters_III[glBlendEquationSeparatei][2]=ICommon::mappingGL(desc.RenderTarget[i].BlendOpAlpha);
			}
			else if(desc.RenderTarget[i].BlendOp!=D3D11_BLEND_OP_ADD)
			{
				static_cast<CGLStateImp*>(state)->mStateChangeParameters_II[glBlendEquationi][0]=i;
				static_cast<CGLStateImp*>(state)->mStateChangeParameters_II[glBlendEquationi][1]=ICommon::mappingGL(desc.RenderTarget[i].BlendOp);
			}
			if((desc.RenderTarget[i].DestBlendAlpha!=D3D11_BLEND_ZERO)||(desc.RenderTarget[i].SrcBlendAlpha!=D3D11_BLEND_ONE))
			{
				static_cast<CGLStateImp*>(state)->mStateChangeParameters_IIIII[glBlendFuncSeparatei][0]=i;
				static_cast<CGLStateImp*>(state)->mStateChangeParameters_IIIII[glBlendFuncSeparatei][1]=ICommon::mappingGL(desc.RenderTarget[i].SrcBlend);
				static_cast<CGLStateImp*>(state)->mStateChangeParameters_IIIII[glBlendFuncSeparatei][2]=ICommon::mappingGL(desc.RenderTarget[i].DestBlend);
				static_cast<CGLStateImp*>(state)->mStateChangeParameters_IIIII[glBlendFuncSeparatei][3]=ICommon::mappingGL(desc.RenderTarget[i].SrcBlendAlpha);
				static_cast<CGLStateImp*>(state)->mStateChangeParameters_IIIII[glBlendFuncSeparatei][4]=ICommon::mappingGL(desc.RenderTarget[i].DestBlendAlpha);
			}
			else if((desc.RenderTarget[i].DestBlend!=D3D11_BLEND_ZERO)||(desc.RenderTarget[i].SrcBlend!=D3D11_BLEND_ONE))
			{
				static_cast<CGLStateImp*>(state)->mStateChangeParameters_II[glBlendFunci][0]=i;
				static_cast<CGLStateImp*>(state)->mStateChangeParameters_II[glBlendFunci][1]=ICommon::mappingGL(desc.RenderTarget[i].SrcBlend);
				static_cast<CGLStateImp*>(state)->mStateChangeParameters_II[glBlendFunci][2]=ICommon::mappingGL(desc.RenderTarget[i].DestBlend);
			}
		}
	}
	if((desc.RenderTarget[0].RenderTargetWriteMask&D3D11_COLOR_WRITE_ENABLE_ALL)!=D3D11_COLOR_WRITE_ENABLE_ALL)
	{
		static_cast<CGLStateImp*>(state)->mStateChangeParameters_IIII[glColorMask][0]=desc.RenderTarget[0].RenderTargetWriteMask&D3D11_COLOR_WRITE_ENABLE_RED?true:false;
		static_cast<CGLStateImp*>(state)->mStateChangeParameters_IIII[glColorMask][1]=desc.RenderTarget[0].RenderTargetWriteMask&D3D11_COLOR_WRITE_ENABLE_GREEN?true:false;
		static_cast<CGLStateImp*>(state)->mStateChangeParameters_IIII[glColorMask][2]=desc.RenderTarget[0].RenderTargetWriteMask&D3D11_COLOR_WRITE_ENABLE_BLUE?true:false;
		static_cast<CGLStateImp*>(state)->mStateChangeParameters_IIII[glColorMask][3]=desc.RenderTarget[0].RenderTargetWriteMask&D3D11_COLOR_WRITE_ENABLE_ALPHA?true:false;
	}
	if(desc.RenderTarget[0].BlendEnable)
	{
		static_cast<CGLStateImp*>(state)->mStateChangeParameters_I[glEnable]=GL_BLEND;
	}
	for(int i=1;i<sizeof(desc.RenderTarget)/sizeof(desc.RenderTarget[0]);++i)
	{
		if((desc.RenderTarget[i].RenderTargetWriteMask&D3D11_COLOR_WRITE_ENABLE_ALL)!=D3D11_COLOR_WRITE_ENABLE_ALL)
		{
			static_cast<CGLStateImp*>(state)->mStateChangeParameters_IIII[glColorMaski][0]=i;
			static_cast<CGLStateImp*>(state)->mStateChangeParameters_IIII[glColorMaski][1]=desc.RenderTarget[i].RenderTargetWriteMask&D3D11_COLOR_WRITE_ENABLE_RED?true:false;
			static_cast<CGLStateImp*>(state)->mStateChangeParameters_IIII[glColorMaski][2]=desc.RenderTarget[i].RenderTargetWriteMask&D3D11_COLOR_WRITE_ENABLE_GREEN?true:false;
			static_cast<CGLStateImp*>(state)->mStateChangeParameters_IIII[glColorMaski][3]=desc.RenderTarget[i].RenderTargetWriteMask&D3D11_COLOR_WRITE_ENABLE_BLUE?true:false;
			static_cast<CGLStateImp*>(state)->mStateChangeParameters_IIII[glColorMaski][4]=desc.RenderTarget[i].RenderTargetWriteMask&D3D11_COLOR_WRITE_ENABLE_ALPHA?true:false;
		}
		if(desc.RenderTarget[i].BlendEnable)
		{
			static_cast<CGLStateImp*>(state)->mStateChangeParameters_II[glEnablei][0]=GL_BLEND;
			static_cast<CGLStateImp*>(state)->mStateChangeParameters_II[glEnablei][1]=i;
		}
	}
	return True;
}

Bool NSDevilX::NSGraphicsAPI::CGLDeviceImp::createBlendState(const D3D11_BLEND_DESC1& desc,OUT IBlendState* state)
{
	if(desc.AlphaToCoverageEnable)
	{
		static_cast<CGLStateImp*>(state)->mStateChangeParameters_I[glEnable]=GL_SAMPLE_ALPHA_TO_COVERAGE;
	}
	{
		if(desc.RenderTarget[0].BlendOpAlpha!=D3D11_BLEND_OP_ADD)
		{
			static_cast<CGLStateImp*>(state)->mStateChangeParameters_II[glBlendEquationSeparate][0]=ICommon::mappingGL(desc.RenderTarget[0].BlendOp);
			static_cast<CGLStateImp*>(state)->mStateChangeParameters_II[glBlendEquationSeparate][1]=ICommon::mappingGL(desc.RenderTarget[0].BlendOpAlpha);
		}
		else if(desc.RenderTarget[0].BlendOp!=D3D11_BLEND_OP_ADD)
		{
			static_cast<CGLStateImp*>(state)->mStateChangeParameters_I[glBlendEquation]=ICommon::mappingGL(desc.RenderTarget[0].BlendOp);
		}
		if((desc.RenderTarget[0].DestBlendAlpha!=D3D11_BLEND_ZERO)||(desc.RenderTarget[0].SrcBlendAlpha!=D3D11_BLEND_ONE))
		{
			static_cast<CGLStateImp*>(state)->mStateChangeParameters_IIII[glBlendFuncSeparate][0]=ICommon::mappingGL(desc.RenderTarget[0].SrcBlend);
			static_cast<CGLStateImp*>(state)->mStateChangeParameters_IIII[glBlendFuncSeparate][1]=ICommon::mappingGL(desc.RenderTarget[0].DestBlend);
			static_cast<CGLStateImp*>(state)->mStateChangeParameters_IIII[glBlendFuncSeparate][2]=ICommon::mappingGL(desc.RenderTarget[0].SrcBlendAlpha);
			static_cast<CGLStateImp*>(state)->mStateChangeParameters_IIII[glBlendFuncSeparate][3]=ICommon::mappingGL(desc.RenderTarget[0].DestBlendAlpha);
		}
		else if((desc.RenderTarget[0].DestBlend!=D3D11_BLEND_ZERO)||(desc.RenderTarget[0].SrcBlend!=D3D11_BLEND_ONE))
		{
			static_cast<CGLStateImp*>(state)->mStateChangeParameters_II[glBlendFunc][0]=ICommon::mappingGL(desc.RenderTarget[0].SrcBlend);
			static_cast<CGLStateImp*>(state)->mStateChangeParameters_II[glBlendFunc][1]=ICommon::mappingGL(desc.RenderTarget[0].DestBlend);
		}
	}
	if(desc.RenderTarget[0].LogicOpEnable)
	{
		if(D3D11_LOGIC_OP_NOOP!=desc.RenderTarget[0].LogicOp)
		{
			static_cast<CGLStateImp*>(state)->mStateChangeParameters_I[glLogicOp]=ICommon::mappingGL(desc.RenderTarget[0].LogicOp);
		}
	}
	if(desc.IndependentBlendEnable)
	{
		for(Int32 i=1;i<sizeof(desc.RenderTarget)/sizeof(desc.RenderTarget[0]);++i)
		{
			if(desc.RenderTarget[i].BlendOpAlpha!=D3D11_BLEND_OP_ADD)
			{
				static_cast<CGLStateImp*>(state)->mStateChangeParameters_III[glBlendEquationSeparatei][0]=i;
				static_cast<CGLStateImp*>(state)->mStateChangeParameters_III[glBlendEquationSeparatei][1]=ICommon::mappingGL(desc.RenderTarget[i].BlendOp);
				static_cast<CGLStateImp*>(state)->mStateChangeParameters_III[glBlendEquationSeparatei][2]=ICommon::mappingGL(desc.RenderTarget[i].BlendOpAlpha);
			}
			else if(desc.RenderTarget[i].BlendOp!=D3D11_BLEND_OP_ADD)
			{
				static_cast<CGLStateImp*>(state)->mStateChangeParameters_II[glBlendEquationi][0]=i;
				static_cast<CGLStateImp*>(state)->mStateChangeParameters_II[glBlendEquationi][1]=ICommon::mappingGL(desc.RenderTarget[i].BlendOp);
			}
			if((desc.RenderTarget[i].DestBlendAlpha!=D3D11_BLEND_ZERO)||(desc.RenderTarget[i].SrcBlendAlpha!=D3D11_BLEND_ONE))
			{
				static_cast<CGLStateImp*>(state)->mStateChangeParameters_IIIII[glBlendFuncSeparatei][0]=i;
				static_cast<CGLStateImp*>(state)->mStateChangeParameters_IIIII[glBlendFuncSeparatei][1]=ICommon::mappingGL(desc.RenderTarget[i].SrcBlend);
				static_cast<CGLStateImp*>(state)->mStateChangeParameters_IIIII[glBlendFuncSeparatei][2]=ICommon::mappingGL(desc.RenderTarget[i].DestBlend);
				static_cast<CGLStateImp*>(state)->mStateChangeParameters_IIIII[glBlendFuncSeparatei][3]=ICommon::mappingGL(desc.RenderTarget[i].SrcBlendAlpha);
				static_cast<CGLStateImp*>(state)->mStateChangeParameters_IIIII[glBlendFuncSeparatei][4]=ICommon::mappingGL(desc.RenderTarget[i].DestBlendAlpha);
			}
			else if((desc.RenderTarget[i].DestBlend!=D3D11_BLEND_ZERO)||(desc.RenderTarget[i].SrcBlend!=D3D11_BLEND_ONE))
			{
				static_cast<CGLStateImp*>(state)->mStateChangeParameters_III[glBlendFunci][0]=i;
				static_cast<CGLStateImp*>(state)->mStateChangeParameters_III[glBlendFunci][1]=ICommon::mappingGL(desc.RenderTarget[i].SrcBlend);
				static_cast<CGLStateImp*>(state)->mStateChangeParameters_III[glBlendFunci][2]=ICommon::mappingGL(desc.RenderTarget[i].DestBlend);
			}
		}
	}
	if((desc.RenderTarget[0].RenderTargetWriteMask&D3D11_COLOR_WRITE_ENABLE_ALL)!=D3D11_COLOR_WRITE_ENABLE_ALL)
	{
		static_cast<CGLStateImp*>(state)->mStateChangeParameters_IIII[glColorMask][0]=desc.RenderTarget[0].RenderTargetWriteMask&D3D11_COLOR_WRITE_ENABLE_RED?true:false;
		static_cast<CGLStateImp*>(state)->mStateChangeParameters_IIII[glColorMask][1]=desc.RenderTarget[0].RenderTargetWriteMask&D3D11_COLOR_WRITE_ENABLE_GREEN?true:false;
		static_cast<CGLStateImp*>(state)->mStateChangeParameters_IIII[glColorMask][2]=desc.RenderTarget[0].RenderTargetWriteMask&D3D11_COLOR_WRITE_ENABLE_BLUE?true:false;
		static_cast<CGLStateImp*>(state)->mStateChangeParameters_IIII[glColorMask][3]=desc.RenderTarget[0].RenderTargetWriteMask&D3D11_COLOR_WRITE_ENABLE_ALPHA?true:false;
	}
	if(desc.RenderTarget[0].BlendEnable)
	{
		static_cast<CGLStateImp*>(state)->mStateChangeParameters_I[glEnable]=GL_BLEND;
	}
	for(int i=1;i<sizeof(desc.RenderTarget)/sizeof(desc.RenderTarget[0]);++i)
	{
		if((desc.RenderTarget[i].RenderTargetWriteMask&D3D11_COLOR_WRITE_ENABLE_ALL)!=D3D11_COLOR_WRITE_ENABLE_ALL)
		{
			static_cast<CGLStateImp*>(state)->mStateChangeParameters_IIIII[glColorMaski][0]=i;
			static_cast<CGLStateImp*>(state)->mStateChangeParameters_IIIII[glColorMaski][1]=desc.RenderTarget[i].RenderTargetWriteMask&D3D11_COLOR_WRITE_ENABLE_RED?true:false;
			static_cast<CGLStateImp*>(state)->mStateChangeParameters_IIIII[glColorMaski][2]=desc.RenderTarget[i].RenderTargetWriteMask&D3D11_COLOR_WRITE_ENABLE_GREEN?true:false;
			static_cast<CGLStateImp*>(state)->mStateChangeParameters_IIIII[glColorMaski][3]=desc.RenderTarget[i].RenderTargetWriteMask&D3D11_COLOR_WRITE_ENABLE_BLUE?true:false;
			static_cast<CGLStateImp*>(state)->mStateChangeParameters_IIIII[glColorMaski][4]=desc.RenderTarget[i].RenderTargetWriteMask&D3D11_COLOR_WRITE_ENABLE_ALPHA?true:false;
		}
		if(desc.RenderTarget[i].BlendEnable)
		{
			static_cast<CGLStateImp*>(state)->mStateChangeParameters_II[glEnablei][0]=GL_BLEND;
			static_cast<CGLStateImp*>(state)->mStateChangeParameters_II[glEnablei][1]=i;
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
		static_cast<CGLStateImp*>(state)->mStateChangeParameters_III[glStencilOp][0]=ICommon::mappingGL(desc.BackFace.StencilFailOp);
		static_cast<CGLStateImp*>(state)->mStateChangeParameters_III[glStencilOp][1]=ICommon::mappingGL(desc.BackFace.StencilDepthFailOp);
		static_cast<CGLStateImp*>(state)->mStateChangeParameters_III[glStencilOp][2]=ICommon::mappingGL(desc.BackFace.StencilPassOp);
	}
	else
	{
		if((desc.BackFace.StencilDepthFailOp!=D3D10_STENCIL_OP_KEEP)
			||(desc.BackFace.StencilFailOp!=D3D10_STENCIL_OP_KEEP)
			||(desc.BackFace.StencilPassOp!=D3D10_STENCIL_OP_KEEP)
			)
		{
			static_cast<CGLStateImp*>(state)->mStateChangeParameters_IIII[glStencilOpSeparate][0]=GL_BACK;
			static_cast<CGLStateImp*>(state)->mStateChangeParameters_IIII[glStencilOpSeparate][1]=ICommon::mappingGL(desc.BackFace.StencilFailOp);
			static_cast<CGLStateImp*>(state)->mStateChangeParameters_IIII[glStencilOpSeparate][2]=ICommon::mappingGL(desc.BackFace.StencilDepthFailOp);
			static_cast<CGLStateImp*>(state)->mStateChangeParameters_IIII[glStencilOpSeparate][3]=ICommon::mappingGL(desc.BackFace.StencilPassOp);
		}
		if((desc.FrontFace.StencilDepthFailOp!=D3D10_STENCIL_OP_KEEP)
			||(desc.FrontFace.StencilFailOp!=D3D10_STENCIL_OP_KEEP)
			||(desc.FrontFace.StencilPassOp!=D3D10_STENCIL_OP_KEEP)
			)
		{
			static_cast<CGLStateImp*>(state)->mStateChangeParameters_IIII[glStencilOpSeparate][0]=GL_FRONT;
			static_cast<CGLStateImp*>(state)->mStateChangeParameters_IIII[glStencilOpSeparate][1]=ICommon::mappingGL(desc.FrontFace.StencilFailOp);
			static_cast<CGLStateImp*>(state)->mStateChangeParameters_IIII[glStencilOpSeparate][2]=ICommon::mappingGL(desc.FrontFace.StencilDepthFailOp);
			static_cast<CGLStateImp*>(state)->mStateChangeParameters_IIII[glStencilOpSeparate][3]=ICommon::mappingGL(desc.FrontFace.StencilPassOp);
		}
	}
	if(desc.BackFace.StencilFunc==desc.FrontFace.StencilFunc)
	{
		if((desc.BackFace.StencilFunc!=D3D10_COMPARISON_ALWAYS)
			||(desc.FrontFace.StencilFunc!=D3D10_COMPARISON_ALWAYS)
			)
		{
			static_cast<CGLStateImp*>(state)->mStateChangeParameters_III[glStencilFunc][0]=ICommon::mappingGL(desc.BackFace.StencilFunc);
			static_cast<CGLStateImp*>(state)->mStateChangeParameters_III[glStencilFunc][2]=desc.StencilReadMask;
		}
	}
	else
	{
		if((desc.BackFace.StencilFunc!=D3D10_COMPARISON_ALWAYS)
			||(desc.FrontFace.StencilFunc!=D3D10_COMPARISON_ALWAYS)
			)
		{
			static_cast<CGLStateImp*>(state)->mStateChangeParameters_IIII[glStencilFuncSeparate][0]=ICommon::mappingGL(desc.FrontFace.StencilFunc);
			static_cast<CGLStateImp*>(state)->mStateChangeParameters_IIII[glStencilFuncSeparate][1]=ICommon::mappingGL(desc.BackFace.StencilFunc);
			static_cast<CGLStateImp*>(state)->mStateChangeParameters_IIII[glStencilFuncSeparate][3]=desc.StencilReadMask;
		}
	}
	if(!desc.DepthEnable)
	{
		static_cast<CGLStateImp*>(state)->mStateChangeParameters_I[glDisable]=GL_DEPTH_TEST;
	}
	if(desc.DepthFunc!=D3D10_COMPARISON_LESS_EQUAL)
	{
		static_cast<CGLStateImp*>(state)->mStateChangeParameters_I[glDepthFunc]=ICommon::mappingGL(desc.DepthFunc);
	}
	if(desc.DepthWriteMask!=D3D10_DEPTH_WRITE_MASK_ALL)
	{
		static_cast<CGLStateImp*>(state)->mStateChangeParameters_I[glDepthMask]=false;
	}
	if(desc.StencilEnable)
	{
		static_cast<CGLStateImp*>(state)->mStateChangeParameters_I[glEnable]=GL_STENCIL_TEST;
	}
	if(desc.StencilWriteMask!=0xff)
	{
		static_cast<CGLStateImp*>(state)->mStateChangeParameters_I[glStencilMask]=desc.StencilWriteMask;
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
		static_cast<CGLStateImp*>(state)->mStateChangeParameters_III[glStencilOp][0]=ICommon::mappingGL(desc.BackFace.StencilFailOp);
		static_cast<CGLStateImp*>(state)->mStateChangeParameters_III[glStencilOp][1]=ICommon::mappingGL(desc.BackFace.StencilDepthFailOp);
		static_cast<CGLStateImp*>(state)->mStateChangeParameters_III[glStencilOp][2]=ICommon::mappingGL(desc.BackFace.StencilPassOp);
	}
	else
	{
		if((desc.BackFace.StencilDepthFailOp!=D3D11_STENCIL_OP_KEEP)
			||(desc.BackFace.StencilFailOp!=D3D11_STENCIL_OP_KEEP)
			||(desc.BackFace.StencilPassOp!=D3D11_STENCIL_OP_KEEP)
			)
		{
			static_cast<CGLStateImp*>(state)->mStateChangeParameters_IIII[glStencilOpSeparate][0]=GL_BACK;
			static_cast<CGLStateImp*>(state)->mStateChangeParameters_IIII[glStencilOpSeparate][1]=ICommon::mappingGL(desc.BackFace.StencilFailOp);
			static_cast<CGLStateImp*>(state)->mStateChangeParameters_IIII[glStencilOpSeparate][2]=ICommon::mappingGL(desc.BackFace.StencilDepthFailOp);
			static_cast<CGLStateImp*>(state)->mStateChangeParameters_IIII[glStencilOpSeparate][3]=ICommon::mappingGL(desc.BackFace.StencilPassOp);
		}
		if((desc.FrontFace.StencilDepthFailOp!=D3D11_STENCIL_OP_KEEP)
			||(desc.FrontFace.StencilFailOp!=D3D11_STENCIL_OP_KEEP)
			||(desc.FrontFace.StencilPassOp!=D3D11_STENCIL_OP_KEEP)
			)
		{
			static_cast<CGLStateImp*>(state)->mStateChangeParameters_IIII[glStencilOpSeparate][0]=GL_FRONT;
			static_cast<CGLStateImp*>(state)->mStateChangeParameters_IIII[glStencilOpSeparate][1]=ICommon::mappingGL(desc.FrontFace.StencilFailOp);
			static_cast<CGLStateImp*>(state)->mStateChangeParameters_IIII[glStencilOpSeparate][2]=ICommon::mappingGL(desc.FrontFace.StencilDepthFailOp);
			static_cast<CGLStateImp*>(state)->mStateChangeParameters_IIII[glStencilOpSeparate][3]=ICommon::mappingGL(desc.FrontFace.StencilPassOp);
		}
	}
	if(desc.BackFace.StencilFunc==desc.FrontFace.StencilFunc)
	{
		if((desc.BackFace.StencilFunc!=D3D11_COMPARISON_ALWAYS)
			||(desc.FrontFace.StencilFunc!=D3D11_COMPARISON_ALWAYS)
			)
		{
			static_cast<CGLStateImp*>(state)->mStateChangeParameters_III[glStencilFunc][0]=ICommon::mappingGL(desc.BackFace.StencilFunc);
			static_cast<CGLStateImp*>(state)->mStateChangeParameters_III[glStencilFunc][2]=desc.StencilReadMask;
		}
	}
	else
	{
		if((desc.BackFace.StencilFunc!=D3D11_COMPARISON_ALWAYS)
			||(desc.FrontFace.StencilFunc!=D3D11_COMPARISON_ALWAYS)
			)
		{
			static_cast<CGLStateImp*>(state)->mStateChangeParameters_IIII[glStencilFuncSeparate][0]=ICommon::mappingGL(desc.FrontFace.StencilFunc);
			static_cast<CGLStateImp*>(state)->mStateChangeParameters_IIII[glStencilFuncSeparate][1]=ICommon::mappingGL(desc.BackFace.StencilFunc);
			static_cast<CGLStateImp*>(state)->mStateChangeParameters_IIII[glStencilFuncSeparate][3]=desc.StencilReadMask;
		}
	}
	if(!desc.DepthEnable)
	{
		static_cast<CGLStateImp*>(state)->mStateChangeParameters_I[glDisable]=GL_DEPTH_TEST;
	}
	if(desc.DepthFunc!=D3D11_COMPARISON_LESS_EQUAL)
	{
		static_cast<CGLStateImp*>(state)->mStateChangeParameters_I[glDepthFunc]=ICommon::mappingGL(desc.DepthFunc);
	}
	if(desc.DepthWriteMask!=D3D11_DEPTH_WRITE_MASK_ALL)
	{
		static_cast<CGLStateImp*>(state)->mStateChangeParameters_I[glDepthMask]=false;
	}
	if(desc.StencilEnable)
	{
		static_cast<CGLStateImp*>(state)->mStateChangeParameters_I[glEnable]=GL_STENCIL_TEST;
	}
	if(desc.StencilWriteMask!=0xff)
	{
		static_cast<CGLStateImp*>(state)->mStateChangeParameters_I[glStencilMask]=desc.StencilWriteMask;
	}
	return True;
}

Bool NSDevilX::NSGraphicsAPI::CGLDeviceImp::createRasterizerState(const D3D10_RASTERIZER_DESC& desc,OUT IRasterizerState* state)
{
	if(desc.AntialiasedLineEnable)
	{
		static_cast<CGLStateImp*>(state)->mStateChangeParameters_I[glEnable]=GL_LINE_SMOOTH;
	}
	if(desc.CullMode!=D3D10_CULL_BACK)
	{
		static_cast<CGLStateImp*>(state)->mStateChangeParameters_I[glCullFace]=ICommon::mappingGL(desc.CullMode);
	}
	if(desc.DepthBiasClamp!=0)
	{
		static_cast<CGLStateImp*>(state)->mStateChangeParameters_III[glPolygonOffsetClamp][0]=*reinterpret_cast<const GLint*>(&desc.SlopeScaledDepthBias);
		static_cast<CGLStateImp*>(state)->mStateChangeParameters_III[glPolygonOffsetClamp][1]=desc.DepthBias;
		static_cast<CGLStateImp*>(state)->mStateChangeParameters_III[glPolygonOffsetClamp][2]=*reinterpret_cast<const GLint*>(&desc.DepthBiasClamp);
	}
	else if((desc.DepthBias!=0)||(desc.SlopeScaledDepthBias!=0))
	{
		static_cast<CGLStateImp*>(state)->mStateChangeParameters_II[glPolygonOffset][0]=*reinterpret_cast<const GLint*>(&desc.SlopeScaledDepthBias);
		static_cast<CGLStateImp*>(state)->mStateChangeParameters_II[glPolygonOffset][1]=desc.DepthBias;
	}
	if(!desc.DepthClipEnable)
	{
	}
	if(desc.FillMode!=D3D10_FILL_SOLID)
	{
		static_cast<CGLStateImp*>(state)->mStateChangeParameters_II[glPolygonMode][0]=GL_FRONT_AND_BACK;
		static_cast<CGLStateImp*>(state)->mStateChangeParameters_II[glPolygonMode][1]=ICommon::mappingGL(desc.FillMode);
	}
	if(desc.FrontCounterClockwise)
	{
		static_cast<CGLStateImp*>(state)->mStateChangeParameters_I[glFrontFace]=GL_CW;
	}
	if(desc.MultisampleEnable)
	{
		static_cast<CGLStateImp*>(state)->mStateChangeParameters_I[glEnable]=GL_POLYGON_SMOOTH;
	}
	if(desc.ScissorEnable)
	{
		static_cast<CGLStateImp*>(state)->mStateChangeParameters_I[glEnable]=GL_SCISSOR_TEST;
	}
	return True;
}

Bool NSDevilX::NSGraphicsAPI::CGLDeviceImp::createRasterizerState(const D3D11_RASTERIZER_DESC& desc,OUT IRasterizerState* state)
{
	if(desc.AntialiasedLineEnable)
	{
		static_cast<CGLStateImp*>(state)->mStateChangeParameters_I[glEnable]=GL_LINE_SMOOTH;
	}
	if(desc.CullMode!=D3D11_CULL_BACK)
	{
		static_cast<CGLStateImp*>(state)->mStateChangeParameters_I[glCullFace]=ICommon::mappingGL(desc.CullMode);
	}
	if(desc.DepthBiasClamp!=0)
	{
		static_cast<CGLStateImp*>(state)->mStateChangeParameters_III[glPolygonOffsetClamp][0]=*reinterpret_cast<const GLint*>(&desc.SlopeScaledDepthBias);
		static_cast<CGLStateImp*>(state)->mStateChangeParameters_III[glPolygonOffsetClamp][1]=desc.DepthBias;
		static_cast<CGLStateImp*>(state)->mStateChangeParameters_III[glPolygonOffsetClamp][2]=*reinterpret_cast<const GLint*>(&desc.DepthBiasClamp);
	}
	else if((desc.DepthBias!=0)||(desc.SlopeScaledDepthBias!=0))
	{
		static_cast<CGLStateImp*>(state)->mStateChangeParameters_II[glPolygonOffset][0]=*reinterpret_cast<const GLint*>(&desc.SlopeScaledDepthBias);
		static_cast<CGLStateImp*>(state)->mStateChangeParameters_II[glPolygonOffset][1]=desc.DepthBias;
	}
	if(!desc.DepthClipEnable)
	{
	}
	if(desc.FillMode!=D3D11_FILL_SOLID)
	{
		static_cast<CGLStateImp*>(state)->mStateChangeParameters_II[glPolygonMode][0]=GL_FRONT_AND_BACK;
		static_cast<CGLStateImp*>(state)->mStateChangeParameters_II[glPolygonMode][1]=ICommon::mappingGL(desc.FillMode);
	}
	if(desc.FrontCounterClockwise)
	{
		static_cast<CGLStateImp*>(state)->mStateChangeParameters_I[glFrontFace]=GL_CW;
	}
	if(desc.MultisampleEnable)
	{
		static_cast<CGLStateImp*>(state)->mStateChangeParameters_I[glEnable]=GL_MULTISAMPLE;
	}
	if(desc.ScissorEnable)
	{
		static_cast<CGLStateImp*>(state)->mStateChangeParameters_I[glEnable]=GL_SCISSOR_TEST;
	}
	return True;
}

Bool NSDevilX::NSGraphicsAPI::CGLDeviceImp::createRasterizerState(const D3D11_RASTERIZER_DESC1& desc,OUT IRasterizerState* state)
{
	if(desc.ForcedSampleCount>0)
	{
		static_cast<CGLStateImp*>(state)->mStateChangeParameters_F[glMinSampleShading]=*reinterpret_cast<const GLfloat*>(&desc.ForcedSampleCount);
	}
	return createRasterizerState(*reinterpret_cast<const D3D11_RASTERIZER_DESC*>(&desc),state);
}

Bool NSDevilX::NSGraphicsAPI::CGLDeviceImp::createRasterizerState(const D3D11_RASTERIZER_DESC2& desc,OUT IRasterizerState* state)
{
	return createRasterizerState(*reinterpret_cast<const D3D11_RASTERIZER_DESC1*>(&desc),state);
}

NSDevilX::NSGraphicsAPI::CGLES2GraphicsDeviceImp::CGLES2GraphicsDeviceImp()
{
}

NSDevilX::NSGraphicsAPI::CGLES2GraphicsDeviceImp::~CGLES2GraphicsDeviceImp()
{
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
