#pragma once
#include "CommonGL.h"
namespace NSDevilX
{
	namespace NSGraphicsAPI
	{
		static Bool isCompressedFormat(D3DFORMAT fmt)
		{
			Bool ret=False;
			switch(fmt)
			{
			case D3DFMT_DXT1:
			case D3DFMT_DXT2:
			case D3DFMT_DXT3:
			case D3DFMT_DXT4:
			case D3DFMT_DXT5:
				ret=True;
			}
			return ret;
		}
		static Bool isCompressedFormat(DXGI_FORMAT fmt)
		{
			Bool ret=False;
			if((fmt>=DXGI_FORMAT_BC1_TYPELESS)&&(fmt<=DXGI_FORMAT_BC5_SNORM))
			{
				ret=True;
			}
			return ret;
		}
		static D3D10_USAGE mappingD3D10(D3DPOOL pool,DWORD usage)
		{
			D3D10_USAGE ret=D3D10_USAGE_DEFAULT;
			switch(pool)
			{
			case D3DPOOL_DEFAULT:
				if(usage&D3DUSAGE_DYNAMIC)
				{
					ret=D3D10_USAGE_DYNAMIC;
				}
				else
				{
					ret=D3D10_USAGE_IMMUTABLE;
				}
				break;
			case D3DPOOL_MANAGED:ret=D3D10_USAGE_DEFAULT;break;
			case D3DPOOL_SYSTEMMEM:
			case D3DPOOL_SCRATCH:
				ret=D3D10_USAGE_STAGING;break;
			}
			return ret;
		}
		static D3D11_USAGE mappingD3D11(D3DPOOL pool,DWORD usage)
		{
			auto ret=mappingD3D10(pool,usage);
			return *reinterpret_cast<D3D11_USAGE*>(&ret);
		}
		static TGLCompatible<GLenum> mappingGL(D3DPOOL pool,DWORD usage)
		{
			TGLCompatible<GLenum> ret;
			if((D3DPOOL_DEFAULT==pool)&&(usage&D3DUSAGE_DYNAMIC))
			{
				ret.setProfile(CGLGlobal::EESProfile_Core_GLES2,GL_DYNAMIC_DRAW);
				ret.setProfile(CGLGlobal::EProfile_Core_GL3,GL_DYNAMIC_DRAW);
			}
			else if(D3DPOOL_DEFAULT==pool)
			{
				ret.setProfile(CGLGlobal::EESProfile_Core_GLES2,GL_STATIC_DRAW);
				ret.setProfile(CGLGlobal::EProfile_Core_GL3,GL_STATIC_DRAW);
			}
			else
			{
				ret.setProfile(CGLGlobal::EESProfile_Core_GLES2,GL_STREAM_DRAW);
				ret.setProfile(CGLGlobal::EProfile_Core_GL3,GL_STREAM_DRAW);
			}
			return ret;
		}
		static TGLCompatible<GLenum> mappingGL(D3D10_USAGE usage,UINT cpuAccessFlags)
		{
			TGLCompatible<GLenum> ret;
			if(D3D10_USAGE_DYNAMIC==usage)
			{
				ret.setProfile(CGLGlobal::EESProfile_Core_GLES2,GL_DYNAMIC_DRAW);
				ret.setProfile(CGLGlobal::EProfile_Core_GL3,GL_DYNAMIC_DRAW);
			}
			else if(D3DPOOL_DEFAULT==usage)
			{
				ret.setProfile(CGLGlobal::EESProfile_Core_GLES2,GL_STATIC_DRAW);
				ret.setProfile(CGLGlobal::EProfile_Core_GL3,GL_STATIC_DRAW);
			}
			else
			{
				ret.setProfile(CGLGlobal::EESProfile_Core_GLES2,GL_STREAM_DRAW);
				ret.setProfile(CGLGlobal::EProfile_Core_GL3,GL_STREAM_DRAW);
			}
			return ret;
		}
		static TGLCompatible<GLenum> mappingGL(D3D11_USAGE usage,UINT cpuAccessFlags)
		{
			return mappingGL(*reinterpret_cast<D3D10_USAGE*>(&usage),cpuAccessFlags);
		}
		static Void mapping(const D3D10_BUFFER_DESC& src,OUT D3D11_BUFFER_DESC& dest)
		{
			memcpy(&dest,&src,sizeof(D3D10_BUFFER_DESC));
			dest.StructureByteStride=0;
		}
		static D3D11_BUFFER_DESC mapping(const D3D10_BUFFER_DESC& desc)
		{
			D3D11_BUFFER_DESC ret;
			mapping(desc,ret);
			return ret;
		}
		static D3D11_SUBRESOURCE_DATA mapping(const D3D10_SUBRESOURCE_DATA& desc)
		{
			return *reinterpret_cast<const D3D11_SUBRESOURCE_DATA*>(&desc);
		}
		static DXGI_FORMAT mappingDXGIFormat(D3DFORMAT fmt)
		{
			DXGI_FORMAT ret=DXGI_FORMAT_UNKNOWN;
			switch(fmt)
			{
			case D3DFMT_A1:
				break;
			case D3DFMT_A8:
				ret=DXGI_FORMAT_A8_UNORM;
				break;
			case D3DFMT_R16F:
				ret=DXGI_FORMAT_R16_FLOAT;
				break;
			case D3DFMT_R32F:
				ret=DXGI_FORMAT_R32_FLOAT;
				break;
			case D3DFMT_G16R16:
				ret=DXGI_FORMAT_R16G16_UNORM;
				break;
			case D3DFMT_G16R16F:
				ret=DXGI_FORMAT_R16G16_FLOAT;
				break;
			case D3DFMT_G32R32F:
				ret=DXGI_FORMAT_R32G32_FLOAT;
				break;
			case D3DFMT_G8R8_G8B8:
				ret=DXGI_FORMAT_G8R8_G8B8_UNORM;
				break;
			case D3DFMT_R5G6B5:
				ret=DXGI_FORMAT_B5G6R5_UNORM;
				break;
			case D3DFMT_A4R4G4B4:
				ret=DXGI_FORMAT_B4G4R4A4_UNORM;
				break;
			case D3DFMT_A1R5G5B5:
				ret=DXGI_FORMAT_B5G5R5A1_UNORM;
				break;
			case D3DFMT_A8R8G8B8:
				ret=DXGI_FORMAT_B8G8R8A8_UNORM;
				break;
			case D3DFMT_A8B8G8R8:
				ret=DXGI_FORMAT_R8G8B8A8_UNORM;
				break;
			case D3DFMT_D16:
			case D3DFMT_D16_LOCKABLE:
				ret=DXGI_FORMAT_D16_UNORM;
				break;
			case D3DFMT_D24X8:
			case D3DFMT_D24S8:
			case D3DFMT_D24FS8:
			case D3DFMT_D24X4S4:
				ret=DXGI_FORMAT_D24_UNORM_S8_UINT;
				break;
			case D3DFMT_D32:
			case D3DFMT_D32F_LOCKABLE:
			case D3DFMT_D32_LOCKABLE:
				ret=DXGI_FORMAT_D32_FLOAT;
				break;
			case D3DFMT_D15S1:
				break;
			case D3DFMT_S8_LOCKABLE:
				ret=DXGI_FORMAT_D32_FLOAT_S8X24_UINT;
				break;
			case D3DFMT_DXT1:
				ret=DXGI_FORMAT_BC1_UNORM;
				break;
			case D3DFMT_DXT3:
				ret=DXGI_FORMAT_BC2_UNORM;
				break;
			case D3DFMT_DXT5:
				ret=DXGI_FORMAT_BC3_UNORM;
				break;
			}
			return ret;
		}
		static GLenum mappingGLInternalFormat(D3DFORMAT fmt)
		{
			GLenum ret=0;
			switch(fmt)
			{
			case D3DFMT_A1:
				ret=GL_ALPHA;
				break;
			case D3DFMT_A8:
				ret=GL_ALPHA8;
				break;
			case D3DFMT_R16F:
				ret=GL_R16F;
				break;
			case D3DFMT_R32F:
				ret=GL_R32F;
				break;
			case D3DFMT_G16R16:
				ret=GL_RG16;
				break;
			case D3DFMT_G16R16F:
				ret=GL_RG16F;
				break;
			case D3DFMT_G32R32F:
				ret=GL_RG32F;
				break;
			case D3DFMT_G8R8_G8B8:
				ret=GL_RG8;
				break;
			case D3DFMT_R5G6B5:
				ret=GL_RGB565;
				break;
			case D3DFMT_A4R4G4B4:
				ret=GL_RGBA4;
				break;
			case D3DFMT_A1R5G5B5:
				ret=GL_RGB5_A1;
				break;
			case D3DFMT_A8R8G8B8:
				ret=GL_RGBA8;
				break;
			case D3DFMT_A8B8G8R8:
				ret=GL_RGBA8;
				break;
			case D3DFMT_D16:
			case D3DFMT_D16_LOCKABLE:
			case D3DFMT_D24X8:
			case D3DFMT_D32:
			case D3DFMT_D32F_LOCKABLE:
			case D3DFMT_D32_LOCKABLE:
				ret=GL_DEPTH_COMPONENT;
				break;
			case D3DFMT_D15S1:
			case D3DFMT_D24FS8:
			case D3DFMT_D24X4S4:
			case D3DFMT_D24S8:
				ret=GL_DEPTH_STENCIL;
				break;
			case D3DFMT_S8_LOCKABLE:
				ret=GL_STENCIL_INDEX;
				break;
			case D3DFMT_DXT1:
				ret=GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
				break;
			case D3DFMT_DXT3:
				ret=GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
				break;
			case D3DFMT_DXT5:
				ret=GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
				break;
			}
			return ret;
		}
		static GLenum mappingGLFormat(D3DFORMAT fmt)
		{
			GLenum ret=0;
			switch(fmt)
			{
			case D3DFMT_A1:
			case D3DFMT_A8:
				ret=GL_ALPHA;
				break;
			case D3DFMT_R16F:
			case D3DFMT_R32F:
				ret=GL_RED;
				break;
			case D3DFMT_G16R16:
			case D3DFMT_G16R16F:
			case D3DFMT_G32R32F:
			case D3DFMT_G8R8_G8B8:
				ret=GL_RG;
				break;
			case D3DFMT_R5G6B5:
				ret=GL_BGR;
				break;
			case D3DFMT_A4R4G4B4:
			case D3DFMT_A1R5G5B5:
			case D3DFMT_A8R8G8B8:
				ret=GL_BGRA;
				break;
			case D3DFMT_A8B8G8R8:
			case D3DFMT_DXT1:
			case D3DFMT_DXT3:
			case D3DFMT_DXT5:
				ret=GL_RGBA;
				break;
			case D3DFMT_D16:
			case D3DFMT_D16_LOCKABLE:
			case D3DFMT_D24X8:
			case D3DFMT_D32:
			case D3DFMT_D32F_LOCKABLE:
			case D3DFMT_D32_LOCKABLE:
				ret=GL_DEPTH_COMPONENT;
				break;
			case D3DFMT_D15S1:
			case D3DFMT_D24FS8:
			case D3DFMT_D24X4S4:
			case D3DFMT_D24S8:
				ret=GL_DEPTH_STENCIL;
				break;
			case D3DFMT_S8_LOCKABLE:
				ret=GL_STENCIL_INDEX;
				break;
			}
			return ret;
		}
		static GLenum mappingGLInternalFormat(DXGI_FORMAT fmt)
		{
			GLenum ret=0;
			switch(fmt)
			{
			case DXGI_FORMAT_A8_UNORM:
				ret=GL_ALPHA8;
				break;
			case DXGI_FORMAT_R1_UNORM:
				ret=GL_RED;
				break;
			case DXGI_FORMAT_R8_TYPELESS:
			case DXGI_FORMAT_R8_UNORM:
			case DXGI_FORMAT_R8_SINT:
			case DXGI_FORMAT_R8_UINT:
				ret=GL_R8;
				break;
			case DXGI_FORMAT_R8_SNORM:
				ret=GL_R8_SNORM;
				break;
			case DXGI_FORMAT_R24_UNORM_X8_TYPELESS:
				ret=GL_RED;
				break;
			case DXGI_FORMAT_R8G8_TYPELESS:
			case DXGI_FORMAT_R8G8_UNORM:
				ret=GL_RG8;
				break;
			case DXGI_FORMAT_R8G8_SNORM:
				ret=GL_RG8_SNORM;
				break;
			case DXGI_FORMAT_R16G16_TYPELESS:
			case DXGI_FORMAT_R16G16_UNORM:
				ret=GL_RG16;
				break;
			case DXGI_FORMAT_R16G16_SNORM:
				ret=GL_RG16_SNORM;
				break;
			case DXGI_FORMAT_R16G16_FLOAT:
				ret=GL_RG16F;
				break;
			case DXGI_FORMAT_R24G8_TYPELESS:
				break;
			case DXGI_FORMAT_R32G32_TYPELESS:
			case DXGI_FORMAT_R32G32_FLOAT:
				ret=GL_RG32F;
				break;
			case DXGI_FORMAT_R8G8_SINT:
				ret=GL_RG8I;
				break;
			case DXGI_FORMAT_R8G8_UINT:
				ret=GL_RG8UI;
				break;
			case DXGI_FORMAT_R16G16_SINT:
				ret=GL_RG16I;
				break;
			case DXGI_FORMAT_R16G16_UINT:
				ret=GL_RG16UI;
				break;
			case DXGI_FORMAT_R32G32_SINT:
				ret=GL_RG32I;
				break;
			case DXGI_FORMAT_R32G32_UINT:
				ret=GL_RG32UI;
				break;
			case DXGI_FORMAT_R11G11B10_FLOAT:
				ret=GL_R11F_G11F_B10F;
				break;
			case DXGI_FORMAT_R32G32B32_TYPELESS:
			case DXGI_FORMAT_R32G32B32_FLOAT:
				ret=GL_RGB32F;
				break;
			case DXGI_FORMAT_R32G32B32_SINT:
				ret=GL_RGB32I;
				break;
			case DXGI_FORMAT_R32G32B32_UINT:
				ret=GL_RGB32UI;
				break;
			case DXGI_FORMAT_B5G6R5_UNORM:
				ret=GL_RGB565;
				break;
			case DXGI_FORMAT_B8G8R8X8_TYPELESS:
			case DXGI_FORMAT_B8G8R8X8_UNORM:
			case DXGI_FORMAT_B8G8R8X8_UNORM_SRGB:
				ret=GL_RGB8;
				break;
			case DXGI_FORMAT_R8G8B8A8_TYPELESS:
			case DXGI_FORMAT_R8G8B8A8_UNORM:
			case DXGI_FORMAT_R8G8B8A8_UNORM_SRGB:
			case DXGI_FORMAT_B8G8R8A8_TYPELESS:
			case DXGI_FORMAT_B8G8R8A8_UNORM:
			case DXGI_FORMAT_B8G8R8A8_UNORM_SRGB:
				ret=GL_RGBA8;
				break;
			case DXGI_FORMAT_R8G8B8A8_SNORM:
				ret=GL_RGBA8_SNORM;
				break;
			case DXGI_FORMAT_R10G10B10A2_TYPELESS:
			case DXGI_FORMAT_R10G10B10A2_UNORM:
				ret=GL_RGB10_A2;
				break;
			case DXGI_FORMAT_R16G16B16A16_TYPELESS:
			case DXGI_FORMAT_R16G16B16A16_UNORM:
				ret=GL_RGBA16;
				break;
			case DXGI_FORMAT_R16G16B16A16_SNORM:
				ret=GL_RGBA16_SNORM;
				break;
			case DXGI_FORMAT_R16G16B16A16_FLOAT:
				ret=GL_RGBA16F;
				break;
			case DXGI_FORMAT_R32G32B32A32_TYPELESS:
			case DXGI_FORMAT_R32G32B32A32_FLOAT:
				ret=GL_RGBA32F;
				break;
			case DXGI_FORMAT_R8G8B8A8_SINT:
				ret=GL_RGBA8I;
				break;
			case DXGI_FORMAT_R8G8B8A8_UINT:
				ret=GL_RGBA8UI;
				break;
			case DXGI_FORMAT_R10G10B10A2_UINT:
				ret=GL_RGB10_A2UI;
				break;
			case DXGI_FORMAT_R16G16B16A16_SINT:
				ret=GL_RGBA16I;
				break;
			case DXGI_FORMAT_R16G16B16A16_UINT:
				ret=GL_RGBA16UI;
				break;
			case DXGI_FORMAT_R32G32B32A32_SINT:
				ret=GL_RGBA32I;
				break;
			case DXGI_FORMAT_R32G32B32A32_UINT:
				ret=GL_RGBA32UI;
				break;
			case DXGI_FORMAT_BC1_TYPELESS:
			case DXGI_FORMAT_BC1_UNORM:
			case DXGI_FORMAT_BC1_UNORM_SRGB:
				ret=GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
				break;
			case DXGI_FORMAT_BC2_TYPELESS:
			case DXGI_FORMAT_BC2_UNORM:
			case DXGI_FORMAT_BC2_UNORM_SRGB:
				ret=GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
				break;
			case DXGI_FORMAT_BC3_TYPELESS:
			case DXGI_FORMAT_BC3_UNORM:
			case DXGI_FORMAT_BC3_UNORM_SRGB:
				ret=GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
				break;
			}
			return ret;
		}
		static GLenum mappingGLFormat(DXGI_FORMAT fmt)
		{
			GLenum ret=0;
			switch(fmt)
			{
			case DXGI_FORMAT_A8_UNORM:
				ret=GL_ALPHA;
				break;
			case DXGI_FORMAT_R1_UNORM:
			case DXGI_FORMAT_R8_TYPELESS:
			case DXGI_FORMAT_R8_SNORM:
			case DXGI_FORMAT_R8_UNORM:
			case DXGI_FORMAT_R24_UNORM_X8_TYPELESS:
				ret=GL_RED;
				break;
			case DXGI_FORMAT_R8_SINT:
			case DXGI_FORMAT_R8_UINT:
				ret=GL_RED_INTEGER;
				break;
			case DXGI_FORMAT_R8G8_TYPELESS:
			case DXGI_FORMAT_R8G8_SNORM:
			case DXGI_FORMAT_R8G8_UNORM:
			case DXGI_FORMAT_R16G16_TYPELESS:
			case DXGI_FORMAT_R16G16_SNORM:
			case DXGI_FORMAT_R16G16_UNORM:
			case DXGI_FORMAT_R16G16_FLOAT:
			case DXGI_FORMAT_R24G8_TYPELESS:
			case DXGI_FORMAT_R32G32_TYPELESS:
			case DXGI_FORMAT_R32G32_FLOAT:
				ret=GL_RG;
				break;
			case DXGI_FORMAT_R8G8_SINT:
			case DXGI_FORMAT_R8G8_UINT:
			case DXGI_FORMAT_R16G16_SINT:
			case DXGI_FORMAT_R16G16_UINT:
			case DXGI_FORMAT_R32G32_SINT:
			case DXGI_FORMAT_R32G32_UINT:
				ret=GL_RG_INTEGER;
				break;
			case DXGI_FORMAT_R11G11B10_FLOAT:
			case DXGI_FORMAT_R32G32B32_TYPELESS:
			case DXGI_FORMAT_R32G32B32_FLOAT:
				ret=GL_RGB;
				break;
			case DXGI_FORMAT_R32G32B32_SINT:
			case DXGI_FORMAT_R32G32B32_UINT:
				ret=GL_RGB_INTEGER;
				break;
			case DXGI_FORMAT_B5G6R5_UNORM:
			case DXGI_FORMAT_B8G8R8X8_TYPELESS:
			case DXGI_FORMAT_B8G8R8X8_UNORM:
			case DXGI_FORMAT_B8G8R8X8_UNORM_SRGB:
				ret=GL_BGR;
				break;
			case DXGI_FORMAT_R8G8B8A8_TYPELESS:
			case DXGI_FORMAT_R8G8B8A8_SNORM:
			case DXGI_FORMAT_R8G8B8A8_UNORM:
			case DXGI_FORMAT_R8G8B8A8_UNORM_SRGB:
			case DXGI_FORMAT_R10G10B10A2_TYPELESS:
			case DXGI_FORMAT_R10G10B10A2_UNORM:
			case DXGI_FORMAT_R16G16B16A16_TYPELESS:
			case DXGI_FORMAT_R16G16B16A16_SNORM:
			case DXGI_FORMAT_R16G16B16A16_UNORM:
			case DXGI_FORMAT_R16G16B16A16_FLOAT:
			case DXGI_FORMAT_R32G32B32A32_TYPELESS:
			case DXGI_FORMAT_R32G32B32A32_FLOAT:
			case DXGI_FORMAT_BC1_TYPELESS:
			case DXGI_FORMAT_BC1_UNORM:
			case DXGI_FORMAT_BC1_UNORM_SRGB:
			case DXGI_FORMAT_BC2_TYPELESS:
			case DXGI_FORMAT_BC2_UNORM:
			case DXGI_FORMAT_BC2_UNORM_SRGB:
			case DXGI_FORMAT_BC3_TYPELESS:
			case DXGI_FORMAT_BC3_UNORM:
			case DXGI_FORMAT_BC3_UNORM_SRGB:
				ret=GL_RGBA;
				break;
			case DXGI_FORMAT_R8G8B8A8_SINT:
			case DXGI_FORMAT_R8G8B8A8_UINT:
			case DXGI_FORMAT_R10G10B10A2_UINT:
			case DXGI_FORMAT_R16G16B16A16_SINT:
			case DXGI_FORMAT_R16G16B16A16_UINT:
			case DXGI_FORMAT_R32G32B32A32_SINT:
			case DXGI_FORMAT_R32G32B32A32_UINT:
				ret=GL_RGBA_INTEGER;
				break;
			case DXGI_FORMAT_B8G8R8A8_TYPELESS:
			case DXGI_FORMAT_B8G8R8A8_UNORM:
			case DXGI_FORMAT_B8G8R8A8_UNORM_SRGB:
				ret=GL_BGRA;
				break;
			}
			return ret;
		}
		static GLint getComponentCount(D3DDECLTYPE format)
		{
			switch(format)
			{
			case D3DDECLTYPE_FLOAT1:
				return 1;
			case D3DDECLTYPE_SHORT2:
			case D3DDECLTYPE_SHORT2N:
			case D3DDECLTYPE_USHORT2N:
			case D3DDECLTYPE_FLOAT16_2:
			case D3DDECLTYPE_FLOAT2:
				return 2;
			case D3DDECLTYPE_UDEC3:
			case D3DDECLTYPE_DEC3N:
			case D3DDECLTYPE_FLOAT3:
				return 3;
			case D3DDECLTYPE_D3DCOLOR:
			case D3DDECLTYPE_UBYTE4:
			case D3DDECLTYPE_SHORT4:
			case D3DDECLTYPE_SHORT4N:
			case D3DDECLTYPE_USHORT4N:
			case D3DDECLTYPE_FLOAT16_4:
			case D3DDECLTYPE_FLOAT4:
				return 4;
			default:
				assert(0);
				return 0;
			}
		}
		static GLint getComponentCount(DXGI_FORMAT format)
		{
			switch(format)
			{
			case DXGI_FORMAT_R8_UNORM:
			case DXGI_FORMAT_R8_SNORM:
			case DXGI_FORMAT_R8_UINT:
			case DXGI_FORMAT_R8_SINT:
			case DXGI_FORMAT_R16_UNORM:
			case DXGI_FORMAT_R16_SNORM:
			case DXGI_FORMAT_R16_UINT:
			case DXGI_FORMAT_R16_SINT:
			case DXGI_FORMAT_R16_FLOAT:
			case DXGI_FORMAT_R32_UINT:
			case DXGI_FORMAT_R32_SINT:
			case DXGI_FORMAT_R32_FLOAT:
				return 1;
			case DXGI_FORMAT_R8G8_UNORM:
			case DXGI_FORMAT_R8G8_SNORM:
			case DXGI_FORMAT_R8G8_UINT:
			case DXGI_FORMAT_R8G8_SINT:
			case DXGI_FORMAT_R16G16_UNORM:
			case DXGI_FORMAT_R16G16_SNORM:
			case DXGI_FORMAT_R16G16_UINT:
			case DXGI_FORMAT_R16G16_SINT:
			case DXGI_FORMAT_R16G16_FLOAT:
			case DXGI_FORMAT_R32G32_UINT:
			case DXGI_FORMAT_R32G32_SINT:
			case DXGI_FORMAT_R32G32_FLOAT:
				return 2;
			case DXGI_FORMAT_R32G32B32_UINT:
			case DXGI_FORMAT_R32G32B32_SINT:
			case DXGI_FORMAT_R32G32B32_FLOAT:
				return 3;
			case DXGI_FORMAT_R8G8B8A8_UNORM:
			case DXGI_FORMAT_R8G8B8A8_UNORM_SRGB:
			case DXGI_FORMAT_R8G8B8A8_SNORM:
			case DXGI_FORMAT_R8G8B8A8_UINT:
			case DXGI_FORMAT_R8G8B8A8_SINT:
			case DXGI_FORMAT_R16G16B16A16_UNORM:
			case DXGI_FORMAT_R16G16B16A16_SNORM:
			case DXGI_FORMAT_R16G16B16A16_UINT:
			case DXGI_FORMAT_R16G16B16A16_SINT:
			case DXGI_FORMAT_R16G16B16A16_FLOAT:
			case DXGI_FORMAT_R32G32B32A32_UINT:
			case DXGI_FORMAT_R32G32B32A32_SINT:
			case DXGI_FORMAT_R32G32B32A32_FLOAT:
				return 4;
			default:
				assert(0);
				return 0;
			}
		}
		static GLenum getComponentType(D3DDECLTYPE format)
		{
			switch(format)
			{
			case D3DDECLTYPE_D3DCOLOR:
			case D3DDECLTYPE_UBYTE4:
			case D3DDECLTYPE_UDEC3:
			case D3DDECLTYPE_DEC3N:
				return GL_BYTE;
			case D3DDECLTYPE_FLOAT16_2:
			case D3DDECLTYPE_FLOAT16_4:
				return GL_HALF_FLOAT;
			case D3DDECLTYPE_FLOAT1:
			case D3DDECLTYPE_FLOAT2:
			case D3DDECLTYPE_FLOAT3:
			case D3DDECLTYPE_FLOAT4:
				return GL_FLOAT;
			case D3DDECLTYPE_SHORT2:
			case D3DDECLTYPE_SHORT2N:
			case D3DDECLTYPE_USHORT2N:
			case D3DDECLTYPE_SHORT4:
			case D3DDECLTYPE_SHORT4N:
			case D3DDECLTYPE_USHORT4N:
				return GL_SHORT;
			default:
				assert(0);
				return 0;
			}
		}
		static GLenum getComponentType(DXGI_FORMAT format)
		{
			switch(format)
			{
			case DXGI_FORMAT_R8_UINT:
			case DXGI_FORMAT_R8_SINT:
			case DXGI_FORMAT_R8_UNORM:
			case DXGI_FORMAT_R8_SNORM:
			case DXGI_FORMAT_R16_UNORM:
			case DXGI_FORMAT_R16_SNORM:
			case DXGI_FORMAT_R8G8_UNORM:
			case DXGI_FORMAT_R8G8_SNORM:
			case DXGI_FORMAT_R16G16_UNORM:
			case DXGI_FORMAT_R16G16_SNORM:
			case DXGI_FORMAT_R8G8B8A8_UNORM:
			case DXGI_FORMAT_R8G8B8A8_UNORM_SRGB:
			case DXGI_FORMAT_R8G8B8A8_SNORM:
			case DXGI_FORMAT_R16G16B16A16_UNORM:
			case DXGI_FORMAT_R16G16B16A16_SNORM:
				return GL_BYTE;
			case DXGI_FORMAT_R16_UINT:
			case DXGI_FORMAT_R16_SINT:
			case DXGI_FORMAT_R16G16_UINT:
			case DXGI_FORMAT_R16G16_SINT:
			case DXGI_FORMAT_R16G16B16A16_UINT:
			case DXGI_FORMAT_R16G16B16A16_SINT:
				return GL_SHORT;
			case DXGI_FORMAT_R32G32_UINT:
			case DXGI_FORMAT_R32G32_SINT:
			case DXGI_FORMAT_R32G32B32_UINT:
			case DXGI_FORMAT_R32G32B32_SINT:
			case DXGI_FORMAT_R32G32B32A32_UINT:
			case DXGI_FORMAT_R32G32B32A32_SINT:
				return GL_INT;
			case DXGI_FORMAT_R32G32B32_FLOAT:
			case DXGI_FORMAT_R32G32B32A32_FLOAT:
				return GL_FLOAT;
			case DXGI_FORMAT_R16G16B16A16_FLOAT:
				return GL_HALF_FLOAT;
			default:
				assert(0);
				return 0;
			}
		}
		static GLboolean needNormalize(D3DDECLTYPE format)
		{
			GLboolean ret=false;
			switch(format)
			{
			case D3DDECLTYPE_D3DCOLOR:
			case D3DDECLTYPE_UDEC3:
			case D3DDECLTYPE_DEC3N:
			case D3DDECLTYPE_SHORT2N:
			case D3DDECLTYPE_USHORT2N:
			case D3DDECLTYPE_SHORT4N:
			case D3DDECLTYPE_USHORT4N:
				ret=true;
			}
			return ret;
		}
		static GLboolean needNormalize(DXGI_FORMAT format)
		{
			switch(format)
			{
			case DXGI_FORMAT_R8_UNORM:
			case DXGI_FORMAT_R8_SNORM:
			case DXGI_FORMAT_R16_UNORM:
			case DXGI_FORMAT_R16_SNORM:
			case DXGI_FORMAT_R8G8_UNORM:
			case DXGI_FORMAT_R8G8_SNORM:
			case DXGI_FORMAT_R16G16_UNORM:
			case DXGI_FORMAT_R16G16_SNORM:
			case DXGI_FORMAT_R8G8B8A8_UNORM:
			case DXGI_FORMAT_R8G8B8A8_UNORM_SRGB:
			case DXGI_FORMAT_R8G8B8A8_SNORM:
			case DXGI_FORMAT_R16G16B16A16_UNORM:
			case DXGI_FORMAT_R16G16B16A16_SNORM:
				return GL_TRUE;
			default:
				return GL_FALSE;
			}
		}
		static GLsizei getStride(GLenum componentType,GLint componentCount)
		{
			GLsizei base_stride=0;
			switch(componentType)
			{
			case GL_BYTE:
				base_stride=1;
				break;
			case GL_SHORT:
			case GL_HALF_FLOAT:
				base_stride=2;
				break;
			case GL_FLOAT:
				base_stride=4;
				break;
			}
			return base_stride*componentCount;
		}
		static D3D11_BLEND mappingD3D11(D3D10_BLEND blend)
		{
			return *reinterpret_cast<D3D11_BLEND*>(&blend);
		}
		static D3D10_BLEND mappingD3D10(D3D11_BLEND blend)
		{
			return *reinterpret_cast<D3D10_BLEND*>(&blend);
		}
		static GLint mappingGL(D3D10_BLEND blend)
		{
			GLint ret=0;
			switch(blend)
			{
			case D3D10_BLEND_ZERO:ret=GL_ZERO;break;
			case D3D10_BLEND_ONE:ret=GL_ONE;break;
			case D3D10_BLEND_SRC_COLOR:ret=GL_SRC_COLOR;break;
			case D3D10_BLEND_INV_SRC_COLOR:ret=GL_ONE_MINUS_SRC_COLOR;break;
			case D3D10_BLEND_SRC_ALPHA:ret=GL_SRC_ALPHA;break;
			case D3D10_BLEND_INV_SRC_ALPHA:ret=GL_ONE_MINUS_SRC_ALPHA;break;
			case D3D10_BLEND_DEST_ALPHA:ret=GL_DST_ALPHA;break;
			case D3D10_BLEND_INV_DEST_ALPHA:ret=GL_ONE_MINUS_DST_ALPHA;break;
			case D3D10_BLEND_DEST_COLOR:ret=GL_DST_COLOR;break;
			case D3D10_BLEND_INV_DEST_COLOR:ret=GL_ONE_MINUS_DST_COLOR;break;
			case D3D10_BLEND_SRC_ALPHA_SAT:ret=GL_SRC_ALPHA_SATURATE;break;
			case D3D10_BLEND_BLEND_FACTOR:break;
			case D3D10_BLEND_INV_BLEND_FACTOR:break;
			case D3D10_BLEND_SRC1_COLOR:ret=GL_SRC1_COLOR;break;
			case D3D10_BLEND_INV_SRC1_COLOR:ret=GL_ONE_MINUS_SRC1_COLOR;break;
			case D3D10_BLEND_SRC1_ALPHA:ret=GL_SRC1_ALPHA;break;
			case D3D10_BLEND_INV_SRC1_ALPHA:ret=GL_ONE_MINUS_SRC1_ALPHA;break;
			}
			return ret;
		}
		static GLint mappingGL(D3D11_BLEND blend)
		{
			return mappingGL(*reinterpret_cast<D3D10_BLEND*>(&blend));
		}
		static D3D11_BLEND_OP mappingD3D11(D3D10_BLEND_OP op)
		{
			return *reinterpret_cast<D3D11_BLEND_OP*>(&op);
		}
		static D3D10_BLEND_OP mappingD3D10(D3D11_BLEND_OP op)
		{
			return *reinterpret_cast<D3D10_BLEND_OP*>(&op);
		}
		static GLenum mappingGL(D3D10_BLEND_OP op)
		{
			GLenum ret=0;
			switch(op)
			{
			case D3D10_BLEND_OP_ADD:ret=GL_FUNC_ADD;break;
			case D3D10_BLEND_OP_SUBTRACT:ret=GL_FUNC_SUBTRACT;break;
			case D3D10_BLEND_OP_REV_SUBTRACT:ret=GL_FUNC_REVERSE_SUBTRACT;break;
			case D3D10_BLEND_OP_MIN:ret=GL_MIN;break;
			case D3D10_BLEND_OP_MAX:ret=GL_MAX;break;
			}
			return ret;
		}
		static GLenum mappingGL(D3D11_BLEND_OP op)
		{
			return mappingGL(*reinterpret_cast<D3D10_BLEND_OP*>(&op));
		}
		static GLint mappingGL(D3D11_LOGIC_OP op)
		{
			GLint ret=0;
			switch(op)
			{
			case D3D11_LOGIC_OP_CLEAR:ret=GL_CLEAR;break;
			case D3D11_LOGIC_OP_SET:ret=GL_SET;break;
			case D3D11_LOGIC_OP_COPY:ret=GL_COPY;break;
			case D3D11_LOGIC_OP_COPY_INVERTED:ret=GL_COPY_INVERTED;break;
			case D3D11_LOGIC_OP_NOOP:ret=GL_NOOP;break;
			case D3D11_LOGIC_OP_INVERT:ret=GL_INVERT;break;
			case D3D11_LOGIC_OP_AND:ret=GL_AND;break;
			case D3D11_LOGIC_OP_NAND:ret=GL_NAND;break;
			case D3D11_LOGIC_OP_OR:ret=GL_OR;break;
			case D3D11_LOGIC_OP_NOR:ret=GL_NOR;break;
			case D3D11_LOGIC_OP_XOR:ret=GL_XOR;break;
			case D3D11_LOGIC_OP_EQUIV:ret=GL_EQUIV;break;
			case D3D11_LOGIC_OP_AND_REVERSE:ret=GL_AND_REVERSE;break;
			case D3D11_LOGIC_OP_AND_INVERTED:ret=GL_AND_INVERTED;break;
			case D3D11_LOGIC_OP_OR_REVERSE:ret=GL_OR_REVERSE;break;
			case D3D11_LOGIC_OP_OR_INVERTED:ret=GL_OR_INVERTED;break;
			}
			return ret;
		}
		static D3D11_STENCIL_OP mappingD3D11(D3D10_STENCIL_OP op)
		{
			return *reinterpret_cast<D3D11_STENCIL_OP*>(&op);
		}
		static D3D10_STENCIL_OP mappingD3D10(D3D11_STENCIL_OP op)
		{
			return *reinterpret_cast<D3D10_STENCIL_OP*>(&op);
		}
		static GLint mappingGL(D3D10_STENCIL_OP op)
		{
			GLint ret=0;
			switch(op)
			{
			case D3D10_STENCIL_OP_KEEP:ret=GL_KEEP;break;
			case D3D10_STENCIL_OP_ZERO:ret=GL_ZERO;break;
			case D3D10_STENCIL_OP_REPLACE:ret=GL_REPLACE;break;
			case D3D10_STENCIL_OP_INCR_SAT:ret=GL_INCR;break;
			case D3D10_STENCIL_OP_DECR_SAT:ret=GL_DECR;break;
			case D3D10_STENCIL_OP_INVERT:ret=GL_INVERT;break;
			case D3D10_STENCIL_OP_INCR:ret=GL_INCR_WRAP;break;
			case D3D10_STENCIL_OP_DECR:ret=GL_DECR_WRAP;break;
			}
			return ret;
		}
		static GLint mappingGL(D3D11_STENCIL_OP op)
		{
			return mappingGL(*reinterpret_cast<D3D10_STENCIL_OP*>(&op));
		}
		static D3D11_COMPARISON_FUNC mappingD3D11(D3D10_COMPARISON_FUNC op)
		{
			return *reinterpret_cast<D3D11_COMPARISON_FUNC*>(&op);
		}
		static D3D10_COMPARISON_FUNC mappingD3D10(D3D11_COMPARISON_FUNC op)
		{
			return *reinterpret_cast<D3D10_COMPARISON_FUNC*>(&op);
		}
		static GLint mappingGL(D3D10_COMPARISON_FUNC func)
		{
			GLint ret=0;
			switch(func)
			{
			case D3D10_COMPARISON_NEVER:ret=GL_NEVER;break;
			case D3D10_COMPARISON_LESS:ret=GL_LESS;break;
			case D3D10_COMPARISON_EQUAL:ret=GL_EQUAL;break;
			case D3D10_COMPARISON_LESS_EQUAL:ret=GL_LEQUAL;break;
			case D3D10_COMPARISON_GREATER:ret=GL_GREATER;break;
			case D3D10_COMPARISON_NOT_EQUAL:ret=GL_NOTEQUAL;break;
			case D3D10_COMPARISON_GREATER_EQUAL:ret=GL_GEQUAL;break;
			case D3D10_COMPARISON_ALWAYS:ret=GL_ALWAYS;break;
			}
			return ret;
		}
		static GLint mappingGL(D3D11_COMPARISON_FUNC func)
		{
			return mappingGL(*reinterpret_cast<D3D10_COMPARISON_FUNC*>(&func));
		}
		static D3D11_CULL_MODE mappingD3D11(D3D10_CULL_MODE op)
		{
			return *reinterpret_cast<D3D11_CULL_MODE*>(&op);
		}
		static D3D10_CULL_MODE mappingD3D10(D3D11_CULL_MODE op)
		{
			return *reinterpret_cast<D3D10_CULL_MODE*>(&op);
		}
		static GLint mappingGL(D3D10_CULL_MODE mode)
		{
			GLint ret=0;
			switch(mode)
			{
			case D3D10_CULL_NONE:ret=GL_NONE;break;
			case D3D10_CULL_FRONT:ret=GL_FRONT;break;
			case D3D10_CULL_BACK:ret=GL_BACK;break;
			}
			return ret;
		}
		static GLint mappingGL(D3D11_CULL_MODE mode)
		{
			return mappingGL(*reinterpret_cast<D3D10_CULL_MODE*>(&mode));
		}
		static D3D11_FILL_MODE mappingD3D11(D3D10_FILL_MODE op)
		{
			return *reinterpret_cast<D3D11_FILL_MODE*>(&op);
		}
		static D3D10_FILL_MODE mappingD3D10(D3D11_FILL_MODE op)
		{
			return *reinterpret_cast<D3D10_FILL_MODE*>(&op);
		}
		static GLint mappingGL(D3D10_FILL_MODE mode)
		{
			GLint ret=0;
			switch(mode)
			{
			case D3D10_FILL_WIREFRAME:ret=GL_LINE;break;
			case D3D10_FILL_SOLID:ret=GL_FILL;break;
			}
			return ret;
		}
		static GLint mappingGL(D3D11_FILL_MODE mode)
		{
			return mappingGL(*reinterpret_cast<D3D10_FILL_MODE*>(&mode));
		}
		static GLint mappingGL(D3D11_CONSERVATIVE_RASTERIZATION_MODE mode)
		{
			GLint ret=0;
			switch(mode)
			{
			case D3D11_CONSERVATIVE_RASTERIZATION_MODE_ON:
				ret=GL_CONSERVATIVE_RASTER_MODE_NV;
				break;
			}
			return ret;
		}
		static GLenum mappingGLBufferStorageFlagsToBufferDataUsage(GLbitfield flags)
		{
			GLenum ret=0;
			if((flags&GL_MAP_WRITE_BIT))
			{
				ret=GL_DYNAMIC_DRAW;
			}
			else if(flags&GL_MAP_READ_BIT)
			{
				ret=GL_STREAM_DRAW;
			}
			else
			{
				ret=GL_STATIC_DRAW;
			}
			return ret;
		}

		static GLint mappingGL(D3D10_TEXTURE_ADDRESS_MODE mode)
		{
			GLint ret=0;
			switch(mode)
			{
			case D3D10_TEXTURE_ADDRESS_WRAP:
				ret=GL_REPEAT;
				break;
			case D3D10_TEXTURE_ADDRESS_MIRROR:
				ret=GL_MIRRORED_REPEAT;
				break;
			case D3D10_TEXTURE_ADDRESS_CLAMP:
				ret=GL_CLAMP_TO_EDGE;
				break;
			case D3D10_TEXTURE_ADDRESS_BORDER:
				ret=GL_CLAMP_TO_BORDER;
				break;
			case D3D10_TEXTURE_ADDRESS_MIRROR_ONCE:
				ret=GL_MIRROR_CLAMP_TO_EDGE;
				break;
			}
			return ret;
		}
		static GLint mappingGL(D3D11_TEXTURE_ADDRESS_MODE mode)
		{
			return mappingGL(*reinterpret_cast<D3D10_TEXTURE_ADDRESS_MODE*>(&mode));
		}
		static GLint mappingGLMag(D3D10_FILTER filter)
		{
			GLint ret=0;
			switch(filter)
			{
			case D3D10_FILTER_MIN_MAG_MIP_POINT:
			case D3D10_FILTER_MIN_MAG_POINT_MIP_LINEAR:
			case D3D10_FILTER_MIN_LINEAR_MAG_MIP_POINT:
			case D3D10_FILTER_MIN_LINEAR_MAG_POINT_MIP_LINEAR:
			case D3D10_FILTER_COMPARISON_MIN_MAG_MIP_POINT:
			case D3D10_FILTER_COMPARISON_MIN_MAG_POINT_MIP_LINEAR:
			case D3D10_FILTER_COMPARISON_MIN_LINEAR_MAG_MIP_POINT:
			case D3D10_FILTER_COMPARISON_MIN_LINEAR_MAG_POINT_MIP_LINEAR:
			case D3D10_FILTER_TEXT_1BIT:
				ret=GL_NEAREST;
				break;
			case D3D10_FILTER_MIN_POINT_MAG_LINEAR_MIP_POINT:
			case D3D10_FILTER_MIN_POINT_MAG_MIP_LINEAR:
			case D3D10_FILTER_MIN_MAG_LINEAR_MIP_POINT:
			case D3D10_FILTER_MIN_MAG_MIP_LINEAR:
			case D3D10_FILTER_COMPARISON_MIN_POINT_MAG_LINEAR_MIP_POINT:
			case D3D10_FILTER_COMPARISON_MIN_POINT_MAG_MIP_LINEAR:
			case D3D10_FILTER_COMPARISON_MIN_MAG_LINEAR_MIP_POINT:
			case D3D10_FILTER_COMPARISON_MIN_MAG_MIP_LINEAR:
			case D3D10_FILTER_ANISOTROPIC:
			case D3D10_FILTER_COMPARISON_ANISOTROPIC:
				ret=GL_LINEAR;
				break;
			}
			return ret;
		}
		static GLint mappingGLMin(D3D10_FILTER filter)
		{
			GLint ret=0;
			switch(filter)
			{
			case D3D10_FILTER_MIN_MAG_MIP_POINT:
			case D3D10_FILTER_MIN_POINT_MAG_LINEAR_MIP_POINT:
			case D3D10_FILTER_COMPARISON_MIN_MAG_MIP_POINT:
			case D3D10_FILTER_COMPARISON_MIN_POINT_MAG_LINEAR_MIP_POINT:
			case D3D10_FILTER_TEXT_1BIT:
				ret=GL_NEAREST_MIPMAP_NEAREST;
				break;
			case D3D10_FILTER_MIN_MAG_POINT_MIP_LINEAR:
			case D3D10_FILTER_MIN_POINT_MAG_MIP_LINEAR:
			case D3D10_FILTER_COMPARISON_MIN_MAG_POINT_MIP_LINEAR:
			case D3D10_FILTER_COMPARISON_MIN_POINT_MAG_MIP_LINEAR:
				ret=GL_NEAREST_MIPMAP_LINEAR;
				break;
				break;
				break;
			case D3D10_FILTER_MIN_LINEAR_MAG_MIP_POINT:
			case D3D10_FILTER_MIN_MAG_LINEAR_MIP_POINT:
			case D3D10_FILTER_COMPARISON_MIN_LINEAR_MAG_MIP_POINT:
			case D3D10_FILTER_COMPARISON_MIN_MAG_LINEAR_MIP_POINT:
				ret=GL_LINEAR_MIPMAP_NEAREST;
				break;
			case D3D10_FILTER_MIN_LINEAR_MAG_POINT_MIP_LINEAR:
			case D3D10_FILTER_MIN_MAG_MIP_LINEAR:
			case D3D10_FILTER_ANISOTROPIC:
			case D3D10_FILTER_COMPARISON_MIN_LINEAR_MAG_POINT_MIP_LINEAR:
			case D3D10_FILTER_COMPARISON_MIN_MAG_MIP_LINEAR:
			case D3D10_FILTER_COMPARISON_ANISOTROPIC:
				ret=GL_LINEAR_MIPMAP_LINEAR;
				break;
			}
			return ret;
		}
	}
}