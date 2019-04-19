#pragma once
namespace NSDevilX
{
	namespace NSCore
	{
		namespace NSOpenGL
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
#if DEVILX_DEBUG
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
				static GLint getInternalFormat(IGAEnum::EGIFormat format)
				{
					switch(format)
					{
					case IGAEnum::EGIFormat_R8_UNORM:
						return GL_R8;
					case IGAEnum::EGIFormat_R8G8B8A8_UNORM:
						return GL_RGBA8;
					case IGAEnum::EGIFormat_BC1_UNORM:
						return GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
					case IGAEnum::EGIFormat_BC2_UNORM:
						return GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
					case IGAEnum::EGIFormat_BC3_UNORM:
						return GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
					default:
						assert(0);
					}
					return GL_RGBA8;
				}
				static GLenum getFormat(IGAEnum::EGIFormat format)
				{
					switch(format)
					{
					case IGAEnum::EGIFormat_R8_UNORM:
						return GL_RED;
					case IGAEnum::EGIFormat_R8G8B8A8_UNORM:
					case IGAEnum::EGIFormat_BC1_UNORM:
					case IGAEnum::EGIFormat_BC2_UNORM:
					case IGAEnum::EGIFormat_BC3_UNORM:
						return GL_RGBA;
					default:
						assert(0);
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
				static GLint mappingMinFilter(IGAEnum::EFilter filter)
				{
					switch(filter)
					{
					case IGAEnum::EFilter_MIN_MAG_MIP_POINT:
					case IGAEnum::EFilter_MIN_POINT_MAG_LINEAR_MIP_POINT:
					case IGAEnum::EFilter_COMPARISON_MIN_MAG_MIP_POINT:
					case IGAEnum::EFilter_COMPARISON_MIN_POINT_MAG_LINEAR_MIP_POINT:
					case IGAEnum::EFilter_MINIMUM_MIN_MAG_MIP_POINT:
					case IGAEnum::EFilter_MINIMUM_MIN_POINT_MAG_LINEAR_MIP_POINT:
					case IGAEnum::EFilter_MAXIMUM_MIN_MAG_MIP_POINT:
					case IGAEnum::EFilter_MAXIMUM_MIN_POINT_MAG_LINEAR_MIP_POINT:
						return GL_NEAREST_MIPMAP_NEAREST;
					case IGAEnum::EFilter_MIN_MAG_POINT_MIP_LINEAR:
					case IGAEnum::EFilter_MIN_POINT_MAG_MIP_LINEAR:
					case IGAEnum::EFilter_COMPARISON_MIN_MAG_POINT_MIP_LINEAR:
					case IGAEnum::EFilter_COMPARISON_MIN_POINT_MAG_MIP_LINEAR:
					case IGAEnum::EFilter_MINIMUM_MIN_MAG_POINT_MIP_LINEAR:
					case IGAEnum::EFilter_MINIMUM_MIN_POINT_MAG_MIP_LINEAR:
					case IGAEnum::EFilter_MAXIMUM_MIN_MAG_POINT_MIP_LINEAR:
					case IGAEnum::EFilter_MAXIMUM_MIN_POINT_MAG_MIP_LINEAR:
						return GL_NEAREST_MIPMAP_LINEAR;
					case IGAEnum::EFilter_MIN_LINEAR_MAG_MIP_POINT:
					case IGAEnum::EFilter_MIN_MAG_LINEAR_MIP_POINT:
					case IGAEnum::EFilter_COMPARISON_MIN_LINEAR_MAG_MIP_POINT:
					case IGAEnum::EFilter_COMPARISON_MIN_MAG_LINEAR_MIP_POINT:
					case IGAEnum::EFilter_MINIMUM_MIN_LINEAR_MAG_MIP_POINT:
					case IGAEnum::EFilter_MINIMUM_MIN_MAG_LINEAR_MIP_POINT:
					case IGAEnum::EFilter_MAXIMUM_MIN_LINEAR_MAG_MIP_POINT:
					case IGAEnum::EFilter_MAXIMUM_MIN_MAG_LINEAR_MIP_POINT:
						return GL_LINEAR_MIPMAP_NEAREST;
					case IGAEnum::EFilter_MIN_LINEAR_MAG_POINT_MIP_LINEAR:
					case IGAEnum::EFilter_MIN_MAG_MIP_LINEAR:
					case IGAEnum::EFilter_COMPARISON_MIN_LINEAR_MAG_POINT_MIP_LINEAR:
					case IGAEnum::EFilter_COMPARISON_MIN_MAG_MIP_LINEAR:
					case IGAEnum::EFilter_MINIMUM_MIN_LINEAR_MAG_POINT_MIP_LINEAR:
					case IGAEnum::EFilter_MINIMUM_MIN_MAG_MIP_LINEAR:
					case IGAEnum::EFilter_MAXIMUM_MIN_LINEAR_MAG_POINT_MIP_LINEAR:
					case IGAEnum::EFilter_MAXIMUM_MIN_MAG_MIP_LINEAR:
						return GL_LINEAR_MIPMAP_LINEAR;
					default:
						return GL_LINEAR_MIPMAP_LINEAR;
					}
				}
				static GLint mappingMagFilter(IGAEnum::EFilter filter)
				{
					switch(filter)
					{
					case IGAEnum::EFilter_MIN_MAG_MIP_POINT:
					case IGAEnum::EFilter_MIN_POINT_MAG_LINEAR_MIP_POINT:
					case IGAEnum::EFilter_COMPARISON_MIN_MAG_MIP_POINT:
					case IGAEnum::EFilter_COMPARISON_MIN_POINT_MAG_LINEAR_MIP_POINT:
					case IGAEnum::EFilter_MINIMUM_MIN_MAG_MIP_POINT:
					case IGAEnum::EFilter_MINIMUM_MIN_POINT_MAG_LINEAR_MIP_POINT:
					case IGAEnum::EFilter_MAXIMUM_MIN_MAG_MIP_POINT:
					case IGAEnum::EFilter_MAXIMUM_MIN_POINT_MAG_LINEAR_MIP_POINT:
					case IGAEnum::EFilter_MIN_MAG_POINT_MIP_LINEAR:
					case IGAEnum::EFilter_MIN_POINT_MAG_MIP_LINEAR:
					case IGAEnum::EFilter_COMPARISON_MIN_MAG_POINT_MIP_LINEAR:
					case IGAEnum::EFilter_COMPARISON_MIN_POINT_MAG_MIP_LINEAR:
					case IGAEnum::EFilter_MINIMUM_MIN_MAG_POINT_MIP_LINEAR:
					case IGAEnum::EFilter_MINIMUM_MIN_POINT_MAG_MIP_LINEAR:
					case IGAEnum::EFilter_MAXIMUM_MIN_MAG_POINT_MIP_LINEAR:
					case IGAEnum::EFilter_MAXIMUM_MIN_POINT_MAG_MIP_LINEAR:
						return GL_NEAREST;
					case IGAEnum::EFilter_MIN_LINEAR_MAG_MIP_POINT:
					case IGAEnum::EFilter_MIN_MAG_LINEAR_MIP_POINT:
					case IGAEnum::EFilter_COMPARISON_MIN_LINEAR_MAG_MIP_POINT:
					case IGAEnum::EFilter_COMPARISON_MIN_MAG_LINEAR_MIP_POINT:
					case IGAEnum::EFilter_MINIMUM_MIN_LINEAR_MAG_MIP_POINT:
					case IGAEnum::EFilter_MINIMUM_MIN_MAG_LINEAR_MIP_POINT:
					case IGAEnum::EFilter_MAXIMUM_MIN_LINEAR_MAG_MIP_POINT:
					case IGAEnum::EFilter_MAXIMUM_MIN_MAG_LINEAR_MIP_POINT:
					case IGAEnum::EFilter_MIN_LINEAR_MAG_POINT_MIP_LINEAR:
					case IGAEnum::EFilter_MIN_MAG_MIP_LINEAR:
					case IGAEnum::EFilter_COMPARISON_MIN_LINEAR_MAG_POINT_MIP_LINEAR:
					case IGAEnum::EFilter_COMPARISON_MIN_MAG_MIP_LINEAR:
					case IGAEnum::EFilter_MINIMUM_MIN_LINEAR_MAG_POINT_MIP_LINEAR:
					case IGAEnum::EFilter_MINIMUM_MIN_MAG_MIP_LINEAR:
					case IGAEnum::EFilter_MAXIMUM_MIN_LINEAR_MAG_POINT_MIP_LINEAR:
					case IGAEnum::EFilter_MAXIMUM_MIN_MAG_MIP_LINEAR:
						return GL_LINEAR;
					default:
						return GL_LINEAR;
					}
				}
				static GLint mapping(IGAEnum::ETextureAddressMode mode)
				{
					switch(mode)
					{
					case IGAEnum::ETextureAddressMode_BORDER:
						return GL_CLAMP_TO_BORDER;
					case IGAEnum::ETextureAddressMode_CLAMP:
						return GL_CLAMP_TO_EDGE;
					case IGAEnum::ETextureAddressMode_MIRROR:
						return GL_MIRRORED_REPEAT;
					case IGAEnum::ETextureAddressMode_MIRROR_ONCE:
						return GL_MIRROR_CLAMP_TO_EDGE;
					case IGAEnum::ETextureAddressMode_WRAP:
						return GL_REPEAT;
					default:
						assert(0);
						return GL_REPEAT;
					}
				}
				static GLint mappingCompareMode(IGAEnum::EFilter filter)
				{
					switch(filter)
					{
					case IGAEnum::EFilter_COMPARISON_MIN_MAG_MIP_POINT:
					case IGAEnum::EFilter_COMPARISON_MIN_POINT_MAG_LINEAR_MIP_POINT:
					case IGAEnum::EFilter_COMPARISON_MIN_MAG_POINT_MIP_LINEAR:
					case IGAEnum::EFilter_COMPARISON_MIN_POINT_MAG_MIP_LINEAR:
					case IGAEnum::EFilter_COMPARISON_MIN_LINEAR_MAG_MIP_POINT:
					case IGAEnum::EFilter_COMPARISON_MIN_MAG_LINEAR_MIP_POINT:
					case IGAEnum::EFilter_COMPARISON_MIN_LINEAR_MAG_POINT_MIP_LINEAR:
					case IGAEnum::EFilter_COMPARISON_MIN_MAG_MIP_LINEAR:
					case IGAEnum::EFilter_COMPARISON_ANISOTROPIC:
						return GL_COMPARE_REF_TO_TEXTURE;
					default:
						return GL_NONE;
					}
				}
				static GLint mapping(IGAEnum::EComparisonFunc func)
				{
					switch(func)
					{
					case IGAEnum::EComparisonFunc_ALWAYS:
						return GL_ALWAYS;
					case IGAEnum::EComparisonFunc_EQUAL:
						return GL_EQUAL;
					case IGAEnum::EComparisonFunc_GREATER:
						return GL_GREATER;
					case IGAEnum::EComparisonFunc_GREATER_EQUAL:
						return GL_GEQUAL;
					case IGAEnum::EComparisonFunc_LESS:
						return GL_LESS;
					case IGAEnum::EComparisonFunc_LESS_EQUAL:
						return GL_LEQUAL;
					case IGAEnum::EComparisonFunc_NEVER:
						return GL_NEVER;
					case IGAEnum::EComparisonFunc_NOT_EQUAL:
						return GL_NOTEQUAL;
					default:
						assert(0);
						return GL_ALWAYS;
					}
				}
				static GLint getComponentCount(IGAEnum::EGIFormat format)
				{
					switch(format)
					{
					case IGAEnum::EGIFormat_R8_UNORM:
					case IGAEnum::EGIFormat_R8_SNORM:
					case IGAEnum::EGIFormat_R8_UINT:
					case IGAEnum::EGIFormat_R8_SINT:
					case IGAEnum::EGIFormat_R16_UNORM:
					case IGAEnum::EGIFormat_R16_SNORM:
					case IGAEnum::EGIFormat_R16_UINT:
					case IGAEnum::EGIFormat_R16_SINT:
					case IGAEnum::EGIFormat_R16_FLOAT:
					case IGAEnum::EGIFormat_R32_UINT:
					case IGAEnum::EGIFormat_R32_SINT:
					case IGAEnum::EGIFormat_R32_FLOAT:
						return 1;
					case IGAEnum::EGIFormat_R8G8_UNORM:
					case IGAEnum::EGIFormat_R8G8_SNORM:
					case IGAEnum::EGIFormat_R8G8_UINT:
					case IGAEnum::EGIFormat_R8G8_SINT:
					case IGAEnum::EGIFormat_R16G16_UNORM:
					case IGAEnum::EGIFormat_R16G16_SNORM:
					case IGAEnum::EGIFormat_R16G16_UINT:
					case IGAEnum::EGIFormat_R16G16_SINT:
					case IGAEnum::EGIFormat_R16G16_FLOAT:
					case IGAEnum::EGIFormat_R32G32_UINT:
					case IGAEnum::EGIFormat_R32G32_SINT:
					case IGAEnum::EGIFormat_R32G32_FLOAT:
						return 2;
					case IGAEnum::EGIFormat_R32G32B32_UINT:
					case IGAEnum::EGIFormat_R32G32B32_SINT:
					case IGAEnum::EGIFormat_R32G32B32_FLOAT:
						return 3;
					case IGAEnum::EGIFormat_R8G8B8A8_UNORM:
					case IGAEnum::EGIFormat_R8G8B8A8_UNORM_SRGB:
					case IGAEnum::EGIFormat_R8G8B8A8_SNORM:
					case IGAEnum::EGIFormat_R8G8B8A8_UINT:
					case IGAEnum::EGIFormat_R8G8B8A8_SINT:
					case IGAEnum::EGIFormat_R16G16B16A16_UNORM:
					case IGAEnum::EGIFormat_R16G16B16A16_SNORM:
					case IGAEnum::EGIFormat_R16G16B16A16_UINT:
					case IGAEnum::EGIFormat_R16G16B16A16_SINT:
					case IGAEnum::EGIFormat_R16G16B16A16_FLOAT:
					case IGAEnum::EGIFormat_R32G32B32A32_UINT:
					case IGAEnum::EGIFormat_R32G32B32A32_SINT:
					case IGAEnum::EGIFormat_R32G32B32A32_FLOAT:
						return 4;
					default:
						assert(0);
						return 0;
					}
				}
				static GLenum getComponentType(IGAEnum::EGIFormat format)
				{
					switch(format)
					{
					case IGAEnum::EGIFormat_R8_UINT:
					case IGAEnum::EGIFormat_R8_SINT:
					case IGAEnum::EGIFormat_R8_UNORM:
					case IGAEnum::EGIFormat_R8_SNORM:
					case IGAEnum::EGIFormat_R16_UNORM:
					case IGAEnum::EGIFormat_R16_SNORM:
					case IGAEnum::EGIFormat_R8G8_UNORM:
					case IGAEnum::EGIFormat_R8G8_SNORM:
					case IGAEnum::EGIFormat_R16G16_UNORM:
					case IGAEnum::EGIFormat_R16G16_SNORM:
					case IGAEnum::EGIFormat_R8G8B8A8_UNORM:
					case IGAEnum::EGIFormat_R8G8B8A8_UNORM_SRGB:
					case IGAEnum::EGIFormat_R8G8B8A8_SNORM:
					case IGAEnum::EGIFormat_R16G16B16A16_UNORM:
					case IGAEnum::EGIFormat_R16G16B16A16_SNORM:
						return GL_BYTE;
					case IGAEnum::EGIFormat_R16_UINT:
					case IGAEnum::EGIFormat_R16_SINT:
					case IGAEnum::EGIFormat_R16G16_UINT:
					case IGAEnum::EGIFormat_R16G16_SINT:
					case IGAEnum::EGIFormat_R16G16B16A16_UINT:
					case IGAEnum::EGIFormat_R16G16B16A16_SINT:
						return GL_SHORT;
					case IGAEnum::EGIFormat_R32G32_UINT:
					case IGAEnum::EGIFormat_R32G32_SINT:
					case IGAEnum::EGIFormat_R32G32B32_UINT:
					case IGAEnum::EGIFormat_R32G32B32_SINT:
					case IGAEnum::EGIFormat_R32G32B32A32_UINT:
					case IGAEnum::EGIFormat_R32G32B32A32_SINT:
						return GL_INT;
					case IGAEnum::EGIFormat_R32G32B32_FLOAT:
					case IGAEnum::EGIFormat_R32G32B32A32_FLOAT:
						return GL_FLOAT;
					case IGAEnum::EGIFormat_R16G16B16A16_FLOAT:
						return GL_HALF_FLOAT;
					default:
						assert(0);
						return 0;
					}
				}
				static GLboolean needNormalize(IGAEnum::EGIFormat format)
				{
					switch(format)
					{
					case IGAEnum::EGIFormat_R8_UNORM:
					case IGAEnum::EGIFormat_R8_SNORM:
					case IGAEnum::EGIFormat_R16_UNORM:
					case IGAEnum::EGIFormat_R16_SNORM:
					case IGAEnum::EGIFormat_R8G8_UNORM:
					case IGAEnum::EGIFormat_R8G8_SNORM:
					case IGAEnum::EGIFormat_R16G16_UNORM:
					case IGAEnum::EGIFormat_R16G16_SNORM:
					case IGAEnum::EGIFormat_R8G8B8A8_UNORM:
					case IGAEnum::EGIFormat_R8G8B8A8_UNORM_SRGB:
					case IGAEnum::EGIFormat_R8G8B8A8_SNORM:
					case IGAEnum::EGIFormat_R16G16B16A16_UNORM:
					case IGAEnum::EGIFormat_R16G16B16A16_SNORM:
						return GL_TRUE;
					default:
						return GL_FALSE;
					}
				}
				static GLenum mapping(IGAEnum::EPrimitiveTopology value)
				{
					switch(value)
					{
					case IGAEnum::EPrimitiveTopology_TRIANGLELIST:
						return GL_TRIANGLES;
					case IGAEnum::EPrimitiveTopology_TRIANGLESTRIP:
						return GL_TRIANGLE_STRIP;
					case IGAEnum::EPrimitiveTopology_LINELIST:
						return GL_LINES;
					case IGAEnum::EPrimitiveTopology_LINESTRIP:
						return GL_LINE_STRIP;
					case IGAEnum::EPrimitiveTopology_POINTLIST:
						return GL_POINTS;
					default:
						assert(0);
						return GL_TRIANGLES;
					}
				}
				static GLenum mapping(IGAEnum::EBlend blend,Bool alpha=False)
				{
					switch(blend)
					{
					case IGAEnum::EBlend_ZERO:
						return GL_ZERO;
					case IGAEnum::EBlend_ONE:
						return GL_ONE;
					case IGAEnum::EBlend_SRC_COLOR:
						return GL_SRC_COLOR;
					case IGAEnum::EBlend_SRC_ALPHA:
						return GL_SRC_ALPHA;
					case IGAEnum::EBlend_SRC_ALPHA_SAT:
						return GL_SRC_ALPHA_SATURATE;
					case IGAEnum::EBlend_BLEND_FACTOR:
						return alpha?GL_CONSTANT_ALPHA:GL_CONSTANT_COLOR;
					case IGAEnum::EBlend_DEST_ALPHA:
						return GL_DST_ALPHA;
					case IGAEnum::EBlend_DEST_COLOR:
						return GL_DST_COLOR;
					case IGAEnum::EBlend_INV_BLEND_FACTOR:
						return alpha?GL_ONE_MINUS_CONSTANT_ALPHA:GL_ONE_MINUS_CONSTANT_COLOR;
					case IGAEnum::EBlend_INV_DEST_ALPHA:
						return GL_ONE_MINUS_DST_ALPHA;
					case IGAEnum::EBlend_INV_DEST_COLOR:
						return GL_ONE_MINUS_DST_COLOR;
					case IGAEnum::EBlend_INV_SRC1_ALPHA:
						return GL_ONE_MINUS_SRC1_ALPHA;
					case IGAEnum::EBlend_INV_SRC1_COLOR:
						return GL_ONE_MINUS_SRC1_COLOR;
					case IGAEnum::EBlend_INV_SRC_ALPHA:
						return GL_ONE_MINUS_SRC_ALPHA;
					case IGAEnum::EBlend_INV_SRC_COLOR:
						return GL_ONE_MINUS_SRC_COLOR;
					default:
						assert(0);
						return GL_ONE;
					}
				}
				static GLenum mapping(IGAEnum::EBlendOp blendOp)
				{
					switch(blendOp)
					{
					case IGAEnum::EBlendOp_ADD:
						return GL_FUNC_ADD;
					case IGAEnum::EBlendOp_MAX:
						return GL_MAX;
					case IGAEnum::EBlendOp_MIN:
						return GL_MIN;
					case IGAEnum::EBlendOp_REV_SUBTRACT:
						return GL_FUNC_REVERSE_SUBTRACT;
					case IGAEnum::EBlendOp_SUBTRACT:
						return GL_FUNC_SUBTRACT;
					default:
						assert(0);
						return GL_FUNC_ADD;
					}
				}
				static GLenum mapping(IGAEnum::ECullMode mode)
				{
					switch(mode)
					{
					case IGAEnum::ECullMode_BACK:
						return GL_BACK;
					case IGAEnum::ECullMode_FRONT:
						return GL_FRONT;
					default:
						assert(0);
						return GL_BACK;
					}
				}
				static GLenum mapping(IGAEnum::EFillMode mode)
				{
					switch(mode)
					{
					case IGAEnum::EFillMode_SOLID:
						return GL_FILL;
					case IGAEnum::EFillMode_WIREFRAME:
						return GL_LINE;
					default:
						return GL_FILL;
					}
				}
				static GLenum mapping(IGAEnum::EStencilOp op)
				{
					switch(op)
					{
					case IGAEnum::EStencilOp_DECR:
						return GL_DECR_WRAP;
					case IGAEnum::EStencilOp_DECR_SAT:
						return GL_DECR;
					case IGAEnum::EStencilOp_INCR:
						return GL_INCR_WRAP;
					case IGAEnum::EStencilOp_INCR_SAT:
						return GL_INCR;
					case IGAEnum::EStencilOp_INVERT:
						return GL_INVERT;
					case IGAEnum::EStencilOp_KEEP:
						return GL_KEEP;
					case IGAEnum::EStencilOp_REPLACE:
						return GL_REPLACE;
					case IGAEnum::EStencilOp_ZERO:
						return GL_ZERO;
					default:
						assert(0);
						return GL_KEEP;
					}
				}
				static GLboolean mapping(IGAEnum::EDepthWriteMask mask)
				{
					switch(mask)
					{
					case IGAEnum::EDepthWriteMask_ALL:
						return GL_TRUE;
					case IGAEnum::EDepthWriteMask_ZERO:
						return GL_FALSE;
					default:
						assert(0);
						return GL_TRUE;
					}
				}
			};
		}
	}
}