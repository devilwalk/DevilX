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
				struct SScissorRect
					:public TBaseObject<SScissorRect>
				{
					GLint mLeft;
					GLint mTop;
					GLsizei mWidth;
					GLsizei mHeight;
				};
				static Void checkGLError()
				{
#ifdef DEVILX_DEBUG
					auto err=glGetError();
					if(GL_NO_ERROR!=err)
					{
#if DEVILX_OPERATING_SYSTEM==DEVILX_OPERATING_SYSTEM_WINDOWS
						OutputDebugStringA(reinterpret_cast<LPCSTR>(gluErrorString(err)));
						OutputDebugStringA("\r\n");
#endif
					}
#endif
				}
				static GLint getInternalFormat(IEnum::ETexture2DFormat format)
				{
					switch(format)
					{
					case IEnum::ETexture2DFormat_R8G8B8A8:
						return GL_RGBA8;
					case IEnum::ETexture2DFormat_BC1:
						return GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
					case IEnum::ETexture2DFormat_BC2:
						return GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
					case IEnum::ETexture2DFormat_BC3:
						return GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
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
				static GLint getComponmentSize(CEnum::EVertexBufferType type)
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
						return 4;
					case CEnum::EVertexBufferType_Diffuse:
						return GL_BGRA;
					default:
						assert(0);
						return 0;
					}
				}
				static GLboolean needNormalized(CEnum::EVertexBufferType type)
				{
					return (CEnum::EVertexBufferType_Diffuse==type)?GL_TRUE:GL_FALSE;
				}
			};
		}
	}
}