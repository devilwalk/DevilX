#include "Precompiler.h"
using namespace NSDevilX;

NSDevilX::CGLGraphicsDeviceImp::CGLGraphicsDeviceImp()
{
}

NSDevilX::CGLGraphicsDeviceImp::~CGLGraphicsDeviceImp()
{
}

Bool NSDevilX::CGLGraphicsDeviceImp::createVertexBuffer(UINT length,DWORD usage,DWORD fvf,D3DPOOL pool,OUT IGraphicsBuffer* buffer)
{
	return createBufferData(GL_ARRAY_BUFFER,length,nullptr,IGraphicsCommon::mappingGL(pool,usage),buffer);
}

Bool NSDevilX::CGLGraphicsDeviceImp::createIndexBuffer(UINT length,DWORD usage,D3DFORMAT format,D3DPOOL pool,OUT IGraphicsBuffer* buffer)
{
	return createBufferData(GL_ELEMENT_ARRAY_BUFFER,length,nullptr,IGraphicsCommon::mappingGL(pool,usage),buffer);
}

Bool NSDevilX::CGLGraphicsDeviceImp::createBuffer(const D3D10_BUFFER_DESC& desc,const D3D10_SUBRESOURCE_DATA* initializeData,OUT IGraphicsBuffer* buffer)
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
	return createBufferData(target,desc.ByteWidth,data,IGraphicsCommon::mappingGL(desc.Usage,desc.CPUAccessFlags),buffer);
}

Bool NSDevilX::CGLGraphicsDeviceImp::createBuffer(const D3D11_BUFFER_DESC& desc,const D3D11_SUBRESOURCE_DATA* initializeData,OUT IGraphicsBuffer* buffer)
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
	return createBufferData(target,desc.ByteWidth,data,IGraphicsCommon::mappingGL(desc.Usage,desc.CPUAccessFlags),buffer);
}

Bool NSDevilX::CGLGraphicsDeviceImp::createBufferData(GLenum target,GLsizeiptr size,ConstVoidPtr intializeData,GLenum usage,OUT IGraphicsBuffer* buffer)
{
	glGenBuffers(1,&static_cast<CGLGraphicsBufferImp*>(buffer)->mInternal);
	glBindBuffer(target,static_cast<CGLGraphicsBufferImp*>(buffer)->mInternal);
	glBufferData(target,size,intializeData,usage);
	glBindBuffer(target,0);
	return True;
}

Bool NSDevilX::CGLGraphicsDeviceImp::createBufferStorage(GLenum target,GLsizeiptr size,ConstVoidPtr intializeData,GLbitfield flags,OUT IGraphicsBuffer* buffer)
{
	glGenBuffers(1,&static_cast<CGLGraphicsBufferImp*>(buffer)->mInternal);
	glBindBuffer(target,static_cast<CGLGraphicsBufferImp*>(buffer)->mInternal);
	glBufferStorage(target,size,intializeData,flags);
	glBindBuffer(target,0);
	return True;
}

Bool NSDevilX::CGLGraphicsDeviceImp::createTexture(UINT width,UINT height,UINT levels,DWORD usage,D3DFORMAT format,D3DPOOL pool,OUT IGraphicsTexture* texture)
{
	if(IGraphicsCommon::isCompressedFormat(format))
	{
		if(height==1)
		{
			return createCompressedTexture1D(GL_TEXTURE_1D,levels,IGraphicsCommon::mappingGLInternalFormat(format),width,0,0,nullptr,texture);
		}
		else
		{
			return createCompressedTexture2D(GL_TEXTURE_2D,levels,IGraphicsCommon::mappingGLInternalFormat(format),width,height,0,0,nullptr,texture);
		}
	}
	else
	{
		if(height==1)
		{
			return createTexture1D(GL_TEXTURE_1D,levels,IGraphicsCommon::mappingGLInternalFormat(format),width,0,IGraphicsCommon::mappingGLFormat(format),GL_BYTE,nullptr,texture);
		}
		else
		{
			return createTexture2D(GL_TEXTURE_2D,levels,IGraphicsCommon::mappingGLInternalFormat(format),width,height,0,IGraphicsCommon::mappingGLFormat(format),GL_BYTE,nullptr,texture);
		}
	}
}

Bool NSDevilX::CGLGraphicsDeviceImp::createCubeTexture(UINT edageLength,UINT levels,DWORD usage,D3DFORMAT format,D3DPOOL pool,OUT IGraphicsTexture* texture)
{
	if(IGraphicsCommon::isCompressedFormat(format))
	{
		Bool ret=createCompressedTexture2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X,levels,IGraphicsCommon::mappingGLInternalFormat(format),edageLength,edageLength,0,0,nullptr,texture);
		ret&=createCompressedTexture2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y,levels,IGraphicsCommon::mappingGLInternalFormat(format),edageLength,edageLength,0,0,nullptr,texture);
		ret&=createCompressedTexture2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z,levels,IGraphicsCommon::mappingGLInternalFormat(format),edageLength,edageLength,0,0,nullptr,texture);
		ret&=createCompressedTexture2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X,levels,IGraphicsCommon::mappingGLInternalFormat(format),edageLength,edageLength,0,0,nullptr,texture);
		ret&=createCompressedTexture2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,levels,IGraphicsCommon::mappingGLInternalFormat(format),edageLength,edageLength,0,0,nullptr,texture);
		ret&=createCompressedTexture2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,levels,IGraphicsCommon::mappingGLInternalFormat(format),edageLength,edageLength,0,0,nullptr,texture);
		return ret;
	}
	else
	{
		Bool ret=createTexture2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X,levels,IGraphicsCommon::mappingGLInternalFormat(format),edageLength,edageLength,0,IGraphicsCommon::mappingGLFormat(format),GL_BYTE,nullptr,texture);
		ret&=createTexture2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y,levels,IGraphicsCommon::mappingGLInternalFormat(format),edageLength,edageLength,0,IGraphicsCommon::mappingGLFormat(format),GL_BYTE,nullptr,texture);
		ret&=createTexture2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z,levels,IGraphicsCommon::mappingGLInternalFormat(format),edageLength,edageLength,0,IGraphicsCommon::mappingGLFormat(format),GL_BYTE,nullptr,texture);
		ret&=createTexture2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X,levels,IGraphicsCommon::mappingGLInternalFormat(format),edageLength,edageLength,0,IGraphicsCommon::mappingGLFormat(format),GL_BYTE,nullptr,texture);
		ret&=createTexture2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,levels,IGraphicsCommon::mappingGLInternalFormat(format),edageLength,edageLength,0,IGraphicsCommon::mappingGLFormat(format),GL_BYTE,nullptr,texture);
		ret&=createTexture2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,levels,IGraphicsCommon::mappingGLInternalFormat(format),edageLength,edageLength,0,IGraphicsCommon::mappingGLFormat(format),GL_BYTE,nullptr,texture);
		return ret;
	}
}

Bool NSDevilX::CGLGraphicsDeviceImp::createVolumeTexture(UINT width,UINT height,UINT depth,UINT levels,DWORD usage,D3DFORMAT format,D3DPOOL pool,OUT IGraphicsTexture* texture)
{
	if(IGraphicsCommon::isCompressedFormat(format))
	{
		return createCompressedTexture3D(GL_TEXTURE_3D,levels,IGraphicsCommon::mappingGLInternalFormat(format),width,height,depth,0,0,nullptr,texture);
	}
	else
	{
		return createTexture3D(GL_TEXTURE_3D,levels,IGraphicsCommon::mappingGLInternalFormat(format),width,height,depth,0,IGraphicsCommon::mappingGLFormat(format),GL_BYTE,nullptr,texture);
	}
}

Bool NSDevilX::CGLGraphicsDeviceImp::createTexture1D(const D3D10_TEXTURE1D_DESC& desc,const D3D10_SUBRESOURCE_DATA* initializeData,OUT IGraphicsTexture* texture)
{
	ConstVoidPtr data=nullptr;
	GLsizei data_size=0;
	if(initializeData)
	{
		data=initializeData->pSysMem;
		data_size=initializeData->SysMemSlicePitch*desc.ArraySize;
	}
	if(IGraphicsCommon::isCompressedFormat(desc.Format))
	{
		return createCompressedTexture1D(GL_TEXTURE_1D,desc.MipLevels,IGraphicsCommon::mappingGLInternalFormat(desc.Format),desc.Width,0,data_size,data,texture);
	}
	else
	{
		return createTexture1D(GL_TEXTURE_1D,desc.MipLevels,IGraphicsCommon::mappingGLInternalFormat(desc.Format),desc.Width,0,IGraphicsCommon::mappingGLFormat(desc.Format),GL_BYTE,data,texture);
	}
}

Bool NSDevilX::CGLGraphicsDeviceImp::createTexture2D(const D3D10_TEXTURE2D_DESC& desc,const D3D10_SUBRESOURCE_DATA* initializeData,OUT IGraphicsTexture* texture)
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
				if(IGraphicsCommon::isCompressedFormat(desc.Format))
				{
					Bool ret=createCompressedTexture2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X,desc.MipLevels,IGraphicsCommon::mappingGLInternalFormat(desc.Format),desc.Width,desc.Height,0,slice_pitch,static_cast<ConstBytePtr>(data)+slice_pitch*0,texture);
					ret&=createCompressedTexture2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y,desc.MipLevels,IGraphicsCommon::mappingGLInternalFormat(desc.Format),desc.Width,desc.Height,0,slice_pitch,static_cast<ConstBytePtr>(data)+slice_pitch*1,texture);
					ret&=createCompressedTexture2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z,desc.MipLevels,IGraphicsCommon::mappingGLInternalFormat(desc.Format),desc.Width,desc.Height,0,slice_pitch,static_cast<ConstBytePtr>(data)+slice_pitch*2,texture);
					ret&=createCompressedTexture2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X,desc.MipLevels,IGraphicsCommon::mappingGLInternalFormat(desc.Format),desc.Width,desc.Height,0,slice_pitch,static_cast<ConstBytePtr>(data)+slice_pitch*3,texture);
					ret&=createCompressedTexture2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,desc.MipLevels,IGraphicsCommon::mappingGLInternalFormat(desc.Format),desc.Width,desc.Height,0,slice_pitch,static_cast<ConstBytePtr>(data)+slice_pitch*4,texture);
					ret&=createCompressedTexture2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,desc.MipLevels,IGraphicsCommon::mappingGLInternalFormat(desc.Format),desc.Width,desc.Height,0,slice_pitch,static_cast<ConstBytePtr>(data)+slice_pitch*5,texture);
					return ret;
				}
				else
				{
					Bool ret=createTexture2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X,desc.MipLevels,IGraphicsCommon::mappingGLInternalFormat(desc.Format),desc.Width,desc.Height,0,IGraphicsCommon::mappingGLFormat(desc.Format),GL_BYTE,static_cast<ConstBytePtr>(data)+slice_pitch*0,texture);
					ret&=createTexture2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y,desc.MipLevels,IGraphicsCommon::mappingGLInternalFormat(desc.Format),desc.Width,desc.Height,0,IGraphicsCommon::mappingGLFormat(desc.Format),GL_BYTE,static_cast<ConstBytePtr>(data)+slice_pitch*1,texture);
					ret&=createTexture2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z,desc.MipLevels,IGraphicsCommon::mappingGLInternalFormat(desc.Format),desc.Width,desc.Height,0,IGraphicsCommon::mappingGLFormat(desc.Format),GL_BYTE,static_cast<ConstBytePtr>(data)+slice_pitch*2,texture);
					ret&=createTexture2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X,desc.MipLevels,IGraphicsCommon::mappingGLInternalFormat(desc.Format),desc.Width,desc.Height,0,IGraphicsCommon::mappingGLFormat(desc.Format),GL_BYTE,static_cast<ConstBytePtr>(data)+slice_pitch*3,texture);
					ret&=createTexture2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,desc.MipLevels,IGraphicsCommon::mappingGLInternalFormat(desc.Format),desc.Width,desc.Height,0,IGraphicsCommon::mappingGLFormat(desc.Format),GL_BYTE,static_cast<ConstBytePtr>(data)+slice_pitch*4,texture);
					ret&=createTexture2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,desc.MipLevels,IGraphicsCommon::mappingGLInternalFormat(desc.Format),desc.Width,desc.Height,0,IGraphicsCommon::mappingGLFormat(desc.Format),GL_BYTE,static_cast<ConstBytePtr>(data)+slice_pitch*5,texture);
					return ret;
				}
			}
			else
			{
				if(IGraphicsCommon::isCompressedFormat(desc.Format))
				{
					return createCompressedTexture3D(GL_TEXTURE_CUBE_MAP_ARRAY,desc.MipLevels,IGraphicsCommon::mappingGLInternalFormat(desc.Format),desc.Width,desc.Height,desc.ArraySize,0,data_size,data,texture);
				}
				else
				{
					return createTexture3D(GL_TEXTURE_CUBE_MAP_ARRAY,desc.MipLevels,IGraphicsCommon::mappingGLInternalFormat(desc.Format),desc.Width,desc.Height,desc.ArraySize,0,IGraphicsCommon::mappingGLFormat(desc.Format),GL_BYTE,data,texture);
				}
			}
		}
		else
		{
			if(IGraphicsCommon::isCompressedFormat(desc.Format))
			{
				return createCompressedTexture3D(GL_TEXTURE_2D_ARRAY,desc.MipLevels,IGraphicsCommon::mappingGLInternalFormat(desc.Format),desc.Width,desc.Height,desc.ArraySize,0,data_size,data,texture);
			}
			else if(desc.SampleDesc.Count>1)
			{
				return createTexture3DMSAA(GL_TEXTURE_2D_MULTISAMPLE_ARRAY,desc.SampleDesc.Count,IGraphicsCommon::mappingGLInternalFormat(desc.Format),desc.Width,desc.Height,desc.ArraySize,true,texture);
			}
			else
			{
				return createTexture3D(GL_TEXTURE_2D_ARRAY,desc.MipLevels,IGraphicsCommon::mappingGLInternalFormat(desc.Format),desc.Width,desc.Height,desc.ArraySize,0,IGraphicsCommon::mappingGLFormat(desc.Format),GL_BYTE,data,texture);
			}
		}
	}
	else
	{
		if(IGraphicsCommon::isCompressedFormat(desc.Format))
		{
			return createCompressedTexture2D(GL_TEXTURE_2D,desc.MipLevels,IGraphicsCommon::mappingGLInternalFormat(desc.Format),desc.Width,desc.Height,0,data_size,data,texture);
		}
		else if(desc.SampleDesc.Count>1)
		{
			return createTexture2DMSAA(GL_TEXTURE_2D_MULTISAMPLE,desc.SampleDesc.Count,IGraphicsCommon::mappingGLInternalFormat(desc.Format),desc.Width,desc.Height,true,texture);
		}
		else
		{
			return createTexture2D(GL_TEXTURE_2D,desc.MipLevels,IGraphicsCommon::mappingGLInternalFormat(desc.Format),desc.Width,desc.Height,0,IGraphicsCommon::mappingGLFormat(desc.Format),GL_BYTE,data,texture);
		}
	}
}

Bool NSDevilX::CGLGraphicsDeviceImp::createTexture3D(const D3D10_TEXTURE3D_DESC& desc,const D3D10_SUBRESOURCE_DATA* initializeData,OUT IGraphicsTexture* texture)
{
	ConstVoidPtr data=nullptr;
	if(initializeData)
	{
		data=initializeData->pSysMem;
	}
	return createTexture3D(GL_TEXTURE_3D,desc.MipLevels,IGraphicsCommon::mappingGLInternalFormat(desc.Format),desc.Width,desc.Height,desc.Depth,0,IGraphicsCommon::mappingGLFormat(desc.Format),GL_BYTE,data,texture);
}

Bool NSDevilX::CGLGraphicsDeviceImp::createTexture1D(const D3D11_TEXTURE1D_DESC& desc,const D3D11_SUBRESOURCE_DATA* initializeData,OUT IGraphicsTexture* texture)
{
	ConstVoidPtr data=nullptr;
	GLsizei data_size=0;
	if(initializeData)
	{
		data=initializeData->pSysMem;
		data_size=initializeData->SysMemSlicePitch*desc.ArraySize;
	}
	if(IGraphicsCommon::isCompressedFormat(desc.Format))
	{
		return createCompressedTexture1D(GL_TEXTURE_1D,desc.MipLevels,IGraphicsCommon::mappingGLInternalFormat(desc.Format),desc.Width,0,data_size,data,texture);
	}
	else
	{
		return createTexture1D(GL_TEXTURE_1D,desc.MipLevels,IGraphicsCommon::mappingGLInternalFormat(desc.Format),desc.Width,0,IGraphicsCommon::mappingGLFormat(desc.Format),GL_BYTE,data,texture);
	}
}

Bool NSDevilX::CGLGraphicsDeviceImp::createTexture2D(const D3D11_TEXTURE2D_DESC& desc,const D3D11_SUBRESOURCE_DATA* initializeData,OUT IGraphicsTexture* texture)
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
				if(IGraphicsCommon::isCompressedFormat(desc.Format))
				{
					Bool ret=createCompressedTexture2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X,desc.MipLevels,IGraphicsCommon::mappingGLInternalFormat(desc.Format),desc.Width,desc.Height,0,slice_pitch,static_cast<ConstBytePtr>(data)+slice_pitch*0,texture);
					ret&=createCompressedTexture2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y,desc.MipLevels,IGraphicsCommon::mappingGLInternalFormat(desc.Format),desc.Width,desc.Height,0,slice_pitch,static_cast<ConstBytePtr>(data)+slice_pitch*1,texture);
					ret&=createCompressedTexture2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z,desc.MipLevels,IGraphicsCommon::mappingGLInternalFormat(desc.Format),desc.Width,desc.Height,0,slice_pitch,static_cast<ConstBytePtr>(data)+slice_pitch*2,texture);
					ret&=createCompressedTexture2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X,desc.MipLevels,IGraphicsCommon::mappingGLInternalFormat(desc.Format),desc.Width,desc.Height,0,slice_pitch,static_cast<ConstBytePtr>(data)+slice_pitch*3,texture);
					ret&=createCompressedTexture2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,desc.MipLevels,IGraphicsCommon::mappingGLInternalFormat(desc.Format),desc.Width,desc.Height,0,slice_pitch,static_cast<ConstBytePtr>(data)+slice_pitch*4,texture);
					ret&=createCompressedTexture2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,desc.MipLevels,IGraphicsCommon::mappingGLInternalFormat(desc.Format),desc.Width,desc.Height,0,slice_pitch,static_cast<ConstBytePtr>(data)+slice_pitch*5,texture);
					return ret;
				}
				else
				{
					Bool ret=createTexture2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X,desc.MipLevels,IGraphicsCommon::mappingGLInternalFormat(desc.Format),desc.Width,desc.Height,0,IGraphicsCommon::mappingGLFormat(desc.Format),GL_BYTE,static_cast<ConstBytePtr>(data)+slice_pitch*0,texture);
					ret&=createTexture2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y,desc.MipLevels,IGraphicsCommon::mappingGLInternalFormat(desc.Format),desc.Width,desc.Height,0,IGraphicsCommon::mappingGLFormat(desc.Format),GL_BYTE,static_cast<ConstBytePtr>(data)+slice_pitch*1,texture);
					ret&=createTexture2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z,desc.MipLevels,IGraphicsCommon::mappingGLInternalFormat(desc.Format),desc.Width,desc.Height,0,IGraphicsCommon::mappingGLFormat(desc.Format),GL_BYTE,static_cast<ConstBytePtr>(data)+slice_pitch*2,texture);
					ret&=createTexture2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X,desc.MipLevels,IGraphicsCommon::mappingGLInternalFormat(desc.Format),desc.Width,desc.Height,0,IGraphicsCommon::mappingGLFormat(desc.Format),GL_BYTE,static_cast<ConstBytePtr>(data)+slice_pitch*3,texture);
					ret&=createTexture2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,desc.MipLevels,IGraphicsCommon::mappingGLInternalFormat(desc.Format),desc.Width,desc.Height,0,IGraphicsCommon::mappingGLFormat(desc.Format),GL_BYTE,static_cast<ConstBytePtr>(data)+slice_pitch*4,texture);
					ret&=createTexture2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,desc.MipLevels,IGraphicsCommon::mappingGLInternalFormat(desc.Format),desc.Width,desc.Height,0,IGraphicsCommon::mappingGLFormat(desc.Format),GL_BYTE,static_cast<ConstBytePtr>(data)+slice_pitch*5,texture);
					return ret;
				}
			}
			else
			{
				if(IGraphicsCommon::isCompressedFormat(desc.Format))
				{
					return createCompressedTexture3D(GL_TEXTURE_CUBE_MAP_ARRAY,desc.MipLevels,IGraphicsCommon::mappingGLInternalFormat(desc.Format),desc.Width,desc.Height,desc.ArraySize,0,data_size,data,texture);
				}
				else
				{
					return createTexture3D(GL_TEXTURE_CUBE_MAP_ARRAY,desc.MipLevels,IGraphicsCommon::mappingGLInternalFormat(desc.Format),desc.Width,desc.Height,desc.ArraySize,0,IGraphicsCommon::mappingGLFormat(desc.Format),GL_BYTE,data,texture);
				}
			}
		}
		else
		{
			if(IGraphicsCommon::isCompressedFormat(desc.Format))
			{
				return createCompressedTexture3D(GL_TEXTURE_2D_ARRAY,desc.MipLevels,IGraphicsCommon::mappingGLInternalFormat(desc.Format),desc.Width,desc.Height,desc.ArraySize,0,data_size,data,texture);
			}
			else if(desc.SampleDesc.Count>1)
			{
				return createTexture3DMSAA(GL_TEXTURE_2D_MULTISAMPLE_ARRAY,desc.SampleDesc.Count,IGraphicsCommon::mappingGLInternalFormat(desc.Format),desc.Width,desc.Height,desc.ArraySize,true,texture);
			}
			else
			{
				return createTexture3D(GL_TEXTURE_2D_ARRAY,desc.MipLevels,IGraphicsCommon::mappingGLInternalFormat(desc.Format),desc.Width,desc.Height,desc.ArraySize,0,IGraphicsCommon::mappingGLFormat(desc.Format),GL_BYTE,data,texture);
			}
		}
	}
	else
	{
		if(IGraphicsCommon::isCompressedFormat(desc.Format))
		{
			return createCompressedTexture2D(GL_TEXTURE_2D,desc.MipLevels,IGraphicsCommon::mappingGLInternalFormat(desc.Format),desc.Width,desc.Height,0,data_size,data,texture);
		}
		else if(desc.SampleDesc.Count>1)
		{
			return createTexture2DMSAA(GL_TEXTURE_2D_MULTISAMPLE,desc.SampleDesc.Count,IGraphicsCommon::mappingGLInternalFormat(desc.Format),desc.Width,desc.Height,true,texture);
		}
		else
		{
			return createTexture2D(GL_TEXTURE_2D,desc.MipLevels,IGraphicsCommon::mappingGLInternalFormat(desc.Format),desc.Width,desc.Height,0,IGraphicsCommon::mappingGLFormat(desc.Format),GL_BYTE,data,texture);
		}
	}
}

Bool NSDevilX::CGLGraphicsDeviceImp::createTexture3D(const D3D11_TEXTURE3D_DESC& desc,const D3D11_SUBRESOURCE_DATA* initializeData,OUT IGraphicsTexture* texture)
{
	ConstVoidPtr data=nullptr;
	if(initializeData)
	{
		data=initializeData->pSysMem;
	}
	return createTexture3D(GL_TEXTURE_3D,desc.MipLevels,IGraphicsCommon::mappingGLInternalFormat(desc.Format),desc.Width,desc.Height,desc.Depth,0,IGraphicsCommon::mappingGLFormat(desc.Format),GL_BYTE,data,texture);
}

Bool NSDevilX::CGLGraphicsDeviceImp::createTexture1D(GLenum target,GLint level,GLint internalformat,GLsizei width,GLint border,GLenum format,GLenum type,ConstVoidPtr initializeData,OUT IGraphicsTexture* texture)
{
	glGenTextures(1,&static_cast<CGLGraphicsTextureImp*>(texture)->mInternal);
	glBindTexture(target,static_cast<CGLGraphicsTextureImp*>(texture)->mInternal);
	glTexImage1D(target,level,internalformat,width,border,format,type,initializeData);
	glBindTexture(target,0);
	return True;
}

Bool NSDevilX::CGLGraphicsDeviceImp::createTexture2D(GLenum target,GLint level,GLint internalformat,GLsizei width,GLsizei height,GLint border,GLenum format,GLenum type,ConstVoidPtr initializeData,OUT IGraphicsTexture* texture)
{
	glGenTextures(1,&static_cast<CGLGraphicsTextureImp*>(texture)->mInternal);
	glBindTexture(target,static_cast<CGLGraphicsTextureImp*>(texture)->mInternal);
	glTexImage2D(target,level,internalformat,width,height,border,format,type,initializeData);
	glBindTexture(target,0);
	return True;
}

Bool NSDevilX::CGLGraphicsDeviceImp::createTexture3D(GLenum target,GLint level,GLint internalformat,GLsizei width,GLsizei height,GLsizei depth,GLint border,GLenum format,GLenum type,ConstVoidPtr initializeData,OUT IGraphicsTexture* texture)
{
	glGenTextures(1,&static_cast<CGLGraphicsTextureImp*>(texture)->mInternal);
	glBindTexture(target,static_cast<CGLGraphicsTextureImp*>(texture)->mInternal);
	glTexImage3D(target,level,internalformat,width,height,depth,border,format,type,initializeData);
	glBindTexture(target,0);
	return True;
}

Bool NSDevilX::CGLGraphicsDeviceImp::createTexture2DMSAA(GLenum target,GLsizei samplers,GLenum internalformat,GLsizei width,GLsizei height,GLboolean fixedsamplelocations,OUT IGraphicsTexture* texture)
{
	glGenTextures(1,&static_cast<CGLGraphicsTextureImp*>(texture)->mInternal);
	glBindTexture(target,static_cast<CGLGraphicsTextureImp*>(texture)->mInternal);
	glTexStorage2DMultisample(target,samplers,internalformat,width,height,fixedsamplelocations);
	glBindTexture(target,0);
	return True;
}

Bool NSDevilX::CGLGraphicsDeviceImp::createTexture3DMSAA(GLenum target,GLsizei samplers,GLenum internalformat,GLsizei width,GLsizei height,GLsizei depth,GLboolean fixedsamplelocations,OUT IGraphicsTexture* texture)
{
	glGenTextures(1,&static_cast<CGLGraphicsTextureImp*>(texture)->mInternal);
	glBindTexture(target,static_cast<CGLGraphicsTextureImp*>(texture)->mInternal);
	glTexStorage3DMultisample(target,samplers,internalformat,width,height,depth,fixedsamplelocations);
	glBindTexture(target,0);
	return True;
}

Bool NSDevilX::CGLGraphicsDeviceImp::createCompressedTexture1D(GLenum target,GLint level,GLint internalformat,GLsizei width,GLint border,GLsizei imageSize,ConstVoidPtr initializeData,OUT IGraphicsTexture* texture)
{
	glGenTextures(1,&static_cast<CGLGraphicsTextureImp*>(texture)->mInternal);
	glBindTexture(target,static_cast<CGLGraphicsTextureImp*>(texture)->mInternal);
	glCompressedTexImage1D(target,level,internalformat,width,border,imageSize,initializeData);
	glBindTexture(target,0);
	return True;
}

Bool NSDevilX::CGLGraphicsDeviceImp::createCompressedTexture2D(GLenum target,GLint level,GLint internalformat,GLsizei width,GLsizei height,GLint border,GLsizei imageSize,ConstVoidPtr initializeData,OUT IGraphicsTexture* texture)
{
	glGenTextures(1,&static_cast<CGLGraphicsTextureImp*>(texture)->mInternal);
	glBindTexture(target,static_cast<CGLGraphicsTextureImp*>(texture)->mInternal);
	glCompressedTexImage2D(target,level,internalformat,width,height,border,imageSize,initializeData);
	glBindTexture(target,0);
	return True;
}

Bool NSDevilX::CGLGraphicsDeviceImp::createCompressedTexture3D(GLenum target,GLint level,GLint internalformat,GLsizei width,GLsizei height,GLsizei depth,GLint border,GLsizei imageSize,ConstVoidPtr initializeData,OUT IGraphicsTexture* texture)
{
	glGenTextures(1,&static_cast<CGLGraphicsTextureImp*>(texture)->mInternal);
	glBindTexture(target,static_cast<CGLGraphicsTextureImp*>(texture)->mInternal);
	glCompressedTexImage3D(target,level,internalformat,width,height,depth,border,imageSize,initializeData);
	glBindTexture(target,0);
	return True;
}

Bool NSDevilX::CGLGraphicsDeviceImp::createVertexDeclaration(const D3DVERTEXELEMENT9* elements,OUT IGraphicsInputLayout* layout)
{
	Bool ret=True;
	D3DVERTEXELEMENT9 end=D3DDECL_END();
	while(elements&&(0!=memcmp(elements,&end,sizeof(D3DVERTEXELEMENT9))))
	{
		ret&=vertexAttribFormat(elements->Stream,IGraphicsCommon::getComponentCount((D3DDECLTYPE)elements->Type),IGraphicsCommon::getComponentType((D3DDECLTYPE)elements->Type),IGraphicsCommon::needNormalize((D3DDECLTYPE)elements->Type),elements->Offset,layout);
		++elements;
	}
	return ret;
}

Bool NSDevilX::CGLGraphicsDeviceImp::createInputLayout(const D3D10_INPUT_ELEMENT_DESC* descs,UINT numElements,ConstVoidPtr shaderBytecodeWithInputSignature,SIZE_T bytecodeLength,OUT IGraphicsInputLayout* layout)
{
	Bool ret=True;
	for(UINT i=0;i<numElements;++i)
	{
		ret&=vertexAttribFormat(descs[i].InputSlot,IGraphicsCommon::getComponentCount(descs[i].Format),IGraphicsCommon::getComponentType(descs[i].Format),IGraphicsCommon::needNormalize(descs[i].Format),descs[i].AlignedByteOffset,layout);
	}
	return ret;
}

Bool NSDevilX::CGLGraphicsDeviceImp::createInputLayout(const D3D11_INPUT_ELEMENT_DESC* descs,UINT numElements,ConstVoidPtr shaderBytecodeWithInputSignature,SIZE_T bytecodeLength,OUT IGraphicsInputLayout* layout)
{
	Bool ret=True;
	for(UINT i=0;i<numElements;++i)
	{
		ret&=vertexAttribFormat(descs[i].InputSlot,IGraphicsCommon::getComponentCount(descs[i].Format),IGraphicsCommon::getComponentType(descs[i].Format),IGraphicsCommon::needNormalize(descs[i].Format),descs[i].AlignedByteOffset,layout);
	}
	return ret;
}

Bool NSDevilX::CGLGraphicsDeviceImp::vertexAttribFormat(GLuint attribindex,GLint size,GLenum type,GLboolean normalized,GLuint relativeoffset,OUT IGraphicsInputLayout* layout)
{
	if(0==static_cast<CGLGraphicsVertexArrayObjectImp*>(layout)->mInternal)
	{
		glGenVertexArrays(1,&static_cast<CGLGraphicsVertexArrayObjectImp*>(layout)->mInternal);
	}
	glBindVertexArray(static_cast<CGLGraphicsVertexArrayObjectImp*>(layout)->mInternal);
	glVertexAttribFormat(attribindex,size,type,normalized,relativeoffset);
	glBindVertexArray(0);
	return True;
}

Bool NSDevilX::CGLGraphicsDeviceImp::vertexAttribIFormat(GLuint attribindex,GLint size,GLenum type,GLuint relativeoffset,OUT IGraphicsInputLayout* layout)
{
	if(0==static_cast<CGLGraphicsVertexArrayObjectImp*>(layout)->mInternal)
	{
		glGenVertexArrays(1,&static_cast<CGLGraphicsVertexArrayObjectImp*>(layout)->mInternal);
	}
	glBindVertexArray(static_cast<CGLGraphicsVertexArrayObjectImp*>(layout)->mInternal);
	glVertexAttribIFormat(attribindex,size,type,relativeoffset);
	glBindVertexArray(0);
	return True;
}

Bool NSDevilX::CGLGraphicsDeviceImp::vertexAttribPoint(GLuint index,GLint size,GLenum type,GLboolean normalized,GLsizei stride,ConstVoidPtr pointer,IGraphicsBuffer* buffer,OUT IGraphicsInputLayout* layout)
{
	if(0==static_cast<CGLGraphicsVertexArrayObjectImp*>(layout)->mInternal)
	{
		glGenVertexArrays(1,&static_cast<CGLGraphicsVertexArrayObjectImp*>(layout)->mInternal);
	}
	glBindVertexArray(static_cast<CGLGraphicsVertexArrayObjectImp*>(layout)->mInternal);
	glBindBuffer(GL_ARRAY_BUFFER,static_cast<CGLGraphicsBufferImp*>(buffer)->mInternal);
	glVertexAttribPointer(index,size,type,normalized,stride,pointer);
	glBindBuffer(GL_ARRAY_BUFFER,0);
	glBindVertexArray(0);
	return True;
}

Bool NSDevilX::CGLGraphicsDeviceImp::vertexAttribIPoint(GLuint index,GLint size,GLenum type,GLsizei stride,ConstVoidPtr pointer,IGraphicsBuffer* buffer,OUT IGraphicsInputLayout* layout)
{
	if(0==static_cast<CGLGraphicsVertexArrayObjectImp*>(layout)->mInternal)
	{
		glGenVertexArrays(1,&static_cast<CGLGraphicsVertexArrayObjectImp*>(layout)->mInternal);
	}
	glBindVertexArray(static_cast<CGLGraphicsVertexArrayObjectImp*>(layout)->mInternal);
	glBindBuffer(GL_ARRAY_BUFFER,static_cast<CGLGraphicsBufferImp*>(buffer)->mInternal);
	glVertexAttribIPointer(index,size,type,stride,pointer);
	glBindBuffer(GL_ARRAY_BUFFER,0);
	glBindVertexArray(0);
	return True;
}
