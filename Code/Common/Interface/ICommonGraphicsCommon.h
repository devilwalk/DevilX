#pragma once
namespace NSDevilX
{
	class IGraphicsCommon
	{
	public:
#if DEVILX_WINDOW_SYSTEM==DEVILX_WINDOW_SYSTEM_WINDOWS
#else
#ifndef MAKEFOURCC
#define MAKEFOURCC(ch0, ch1, ch2, ch3)                              \
                ((DWORD)(BYTE)(ch0) | ((DWORD)(BYTE)(ch1) << 8) |       \
                ((DWORD)(BYTE)(ch2) << 16) | ((DWORD)(BYTE)(ch3) << 24 ))
#endif /* defined(MAKEFOURCC) */
		//d3d9
		typedef enum _D3DPOOL {
			D3DPOOL_DEFAULT=0,
			D3DPOOL_MANAGED=1,
			D3DPOOL_SYSTEMMEM=2,
			D3DPOOL_SCRATCH=3,

			D3DPOOL_FORCE_DWORD=0x7fffffff
		} D3DPOOL;
		typedef enum _D3DFORMAT
		{
			D3DFMT_UNKNOWN=0,

			D3DFMT_R8G8B8=20,
			D3DFMT_A8R8G8B8=21,
			D3DFMT_X8R8G8B8=22,
			D3DFMT_R5G6B5=23,
			D3DFMT_X1R5G5B5=24,
			D3DFMT_A1R5G5B5=25,
			D3DFMT_A4R4G4B4=26,
			D3DFMT_R3G3B2=27,
			D3DFMT_A8=28,
			D3DFMT_A8R3G3B2=29,
			D3DFMT_X4R4G4B4=30,
			D3DFMT_A2B10G10R10=31,
			D3DFMT_A8B8G8R8=32,
			D3DFMT_X8B8G8R8=33,
			D3DFMT_G16R16=34,
			D3DFMT_A2R10G10B10=35,
			D3DFMT_A16B16G16R16=36,

			D3DFMT_A8P8=40,
			D3DFMT_P8=41,

			D3DFMT_L8=50,
			D3DFMT_A8L8=51,
			D3DFMT_A4L4=52,

			D3DFMT_V8U8=60,
			D3DFMT_L6V5U5=61,
			D3DFMT_X8L8V8U8=62,
			D3DFMT_Q8W8V8U8=63,
			D3DFMT_V16U16=64,
			D3DFMT_A2W10V10U10=67,

			D3DFMT_UYVY=MAKEFOURCC('U','Y','V','Y'),
			D3DFMT_R8G8_B8G8=MAKEFOURCC('R','G','B','G'),
			D3DFMT_YUY2=MAKEFOURCC('Y','U','Y','2'),
			D3DFMT_G8R8_G8B8=MAKEFOURCC('G','R','G','B'),
			D3DFMT_DXT1=MAKEFOURCC('D','X','T','1'),
			D3DFMT_DXT2=MAKEFOURCC('D','X','T','2'),
			D3DFMT_DXT3=MAKEFOURCC('D','X','T','3'),
			D3DFMT_DXT4=MAKEFOURCC('D','X','T','4'),
			D3DFMT_DXT5=MAKEFOURCC('D','X','T','5'),

			D3DFMT_D16_LOCKABLE=70,
			D3DFMT_D32=71,
			D3DFMT_D15S1=73,
			D3DFMT_D24S8=75,
			D3DFMT_D24X8=77,
			D3DFMT_D24X4S4=79,
			D3DFMT_D16=80,

			D3DFMT_D32F_LOCKABLE=82,
			D3DFMT_D24FS8=83,

			/* D3D9Ex only -- */
//#if !defined(D3D_DISABLE_9EX)

	/* Z-Stencil formats valid for CPU access */
	D3DFMT_D32_LOCKABLE=84,
	D3DFMT_S8_LOCKABLE=85,

//#endif // !D3D_DISABLE_9EX
	/* -- D3D9Ex only */


	D3DFMT_L16=81,

	D3DFMT_VERTEXDATA=100,
	D3DFMT_INDEX16=101,
	D3DFMT_INDEX32=102,

	D3DFMT_Q16W16V16U16=110,

	D3DFMT_MULTI2_ARGB8=MAKEFOURCC('M','E','T','1'),

	// Floating point surface formats

	// s10e5 formats (16-bits per channel)
	D3DFMT_R16F=111,
	D3DFMT_G16R16F=112,
	D3DFMT_A16B16G16R16F=113,

	// IEEE s23e8 formats (32-bits per channel)
	D3DFMT_R32F=114,
	D3DFMT_G32R32F=115,
	D3DFMT_A32B32G32R32F=116,

	D3DFMT_CxV8U8=117,

	/* D3D9Ex only -- */
//#if !defined(D3D_DISABLE_9EX)

	// Monochrome 1 bit per pixel format
	D3DFMT_A1=118,

	// 2.8 biased fixed point
	D3DFMT_A2B10G10R10_XR_BIAS=119,


	// Binary format indicating that the data has no inherent type
	D3DFMT_BINARYBUFFER=199,

//#endif // !D3D_DISABLE_9EX
	/* -- D3D9Ex only */


	D3DFMT_FORCE_DWORD=0x7fffffff
	} D3DFORMAT;
		//d3d10
		typedef struct D3D10_BUFFER_DESC
		{
			UINT ByteWidth;
			D3D10_USAGE Usage;
			UINT BindFlags;
			UINT CPUAccessFlags;
			UINT MiscFlags;
		} 	D3D10_BUFFER_DESC;
		//d3d10.1
		//d3d11
		//d3d11.1
		//d3d12
#endif
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
			D3D11_USAGE ret =D3D11_USAGE_DEFAULT;
			switch(pool)
			{
			case D3DPOOL_DEFAULT:
				if(usage&D3DUSAGE_DYNAMIC)
				{
					ret=D3D11_USAGE_DYNAMIC;
				}
				else
				{
					ret=D3D11_USAGE_IMMUTABLE;
				}
				break;
			case D3DPOOL_MANAGED:ret=D3D11_USAGE_DEFAULT;break;
			case D3DPOOL_SYSTEMMEM:
			case D3DPOOL_SCRATCH:
				ret=D3D11_USAGE_STAGING;break;
			}
			return ret;
		}
		static GLenum mappingGL(D3DPOOL pool,DWORD usage)
		{
			GLenum ret=GL_STATIC_DRAW;
			switch(pool)
			{
			case D3DPOOL_DEFAULT:
				if(usage&D3DUSAGE_DYNAMIC)
				{
					ret=GL_DYNAMIC_DRAW;
				}
				break;
			case D3DPOOL_SYSTEMMEM:
			case D3DPOOL_SCRATCH:
				ret=GL_STREAM_DRAW;break;
			}
			return ret;
		}
		static GLenum mappingGL(D3D10_USAGE usage,UINT cpuAccessFlags)
		{
			GLenum ret=GL_STATIC_DRAW;
			switch(usage)
			{
			case D3D10_USAGE_DYNAMIC:
				ret=GL_DYNAMIC_DRAW;
				break;
			case D3D10_USAGE_STAGING:
				ret=GL_STREAM_DRAW;
				break;
			}
			return ret;
		}
		static GLenum mappingGL(D3D11_USAGE usage,UINT cpuAccessFlags)
		{
			GLenum ret=GL_STATIC_DRAW;
			switch(usage)
			{
			case D3D11_USAGE_DYNAMIC:
				ret=GL_DYNAMIC_DRAW;
				break;
			case D3D11_USAGE_STAGING:
				ret=GL_STREAM_DRAW;
				break;
			}
			return ret;
		}
		static Void mapping(const D3D10_BUFFER_DESC& src,OUT D3D11_BUFFER_DESC& dest)
		{
			memcpy(&dest,&src,sizeof(D3D10_BUFFER_DESC));
			dest.StructureByteStride=0;
		}
		static D3D11_BUFFER_DESC mapping(const D3D10_BUFFER_DESC& desc)
		{
			D3D11_BUFFER_DESC ret={0};
			mapping(desc,ret);
			return ret;
		}
		static Void mapping(const D3D10_SUBRESOURCE_DATA& src,OUT D3D11_SUBRESOURCE_DATA& dest)
		{
			memcpy(&dest,&src,sizeof(D3D10_SUBRESOURCE_DATA));
		}
		static D3D11_SUBRESOURCE_DATA mapping(const D3D10_SUBRESOURCE_DATA& desc)
		{
			D3D11_SUBRESOURCE_DATA ret={0};
			mapping(desc,ret);
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
	};
}