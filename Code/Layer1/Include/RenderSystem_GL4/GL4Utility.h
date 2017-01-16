#pragma once
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		namespace NSGL4
		{
			class CUtility
			{
			public:
				static GLint getInternalFormat(IEnum::ETextureFormat format)
				{
					switch(format)
					{
					case IEnum::ETextureFormat_R8G8B8A8:
					case IEnum::ETextureFormat_Environment:
						return GL_RGBA8;
					case IEnum::ETextureFormat_BC1:
						return GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
					case IEnum::ETextureFormat_BC2:
						return GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
					case IEnum::ETextureFormat_BC3:
						return GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
					case IEnum::ETextureFormat_Font:
						return GL_ALPHA8;
					case IEnum::ETextureFormat_Shadow:
						return GL_DEPTH_STENCIL;
					}
					return GL_RGBA;
				}
				static UInt32 getRowPitch(GLint internalFormat,UInt32 width)
				{
					switch(internalFormat)
					{
					case GL_RGBA8:
						return 4*width;
					}
					return 0;
				}
				static GLsizei getStride(CEnum::EVertexBufferType type)
				{
					switch(type)
					{
					case CEnum::EVertexBufferType_Position:
					case CEnum::EVertexBufferType_Normal:
					case CEnum::EVertexBufferType_Tangent:
						return sizeof(CFloat3);
					case CEnum::EVertexBufferType_TextureCoord0:
					case CEnum::EVertexBufferType_TextureCoord1:
						return sizeof(CFloat2);
					case CEnum::EVertexBufferType_BlendWeight:
						return sizeof(CFloat4);
					case CEnum::EVertexBufferType_BlendIndex:
					case CEnum::EVertexBufferType_Diffuse:
						return sizeof(UInt32);
					default:
						assert(0);
						return 0;
					}
				}
				static GLenum getFormat(CEnum::EVertexBufferType type)
				{
					switch(type)
					{
					case CEnum::EVertexBufferType_Position:
					case CEnum::EVertexBufferType_Normal:
					case CEnum::EVertexBufferType_Tangent:
					case CEnum::EVertexBufferType_TextureCoord0:
					case CEnum::EVertexBufferType_TextureCoord1:
					case CEnum::EVertexBufferType_BlendWeight:
						return GL_FLOAT;
					case CEnum::EVertexBufferType_BlendIndex:
					case CEnum::EVertexBufferType_Diffuse:
						return GL_UNSIGNED_BYTE;
					default:
						assert(0);
						return 0;
					}
				}
				static GLint getComponmentCount(CEnum::EVertexBufferType type)
				{
					switch(type)
					{
					case CEnum::EVertexBufferType_Position:
					case CEnum::EVertexBufferType_Normal:
					case CEnum::EVertexBufferType_Tangent:
						return 3;
					case CEnum::EVertexBufferType_TextureCoord0:
					case CEnum::EVertexBufferType_TextureCoord1:
						return 2;
					case CEnum::EVertexBufferType_BlendWeight:
					case CEnum::EVertexBufferType_BlendIndex:
					case CEnum::EVertexBufferType_Diffuse:
						return 4;
					default:
						assert(0);
						return 0;
					}
				}
			};
		}
	}
}