#pragma once
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		namespace NSD3D11
		{
			class CUtility
			{
			public:
				static DXGI_FORMAT getDXGIFormat(IEnum::ETexture2DFormat format)
				{
					switch(format)
					{
					case IEnum::ETexture2DFormat_R8G8B8A8:
						return DXGI_FORMAT_R8G8B8A8_UNORM;
					case IEnum::ETexture2DFormat_A8:
						return DXGI_FORMAT_R8_UNORM;
					case IEnum::ETexture2DFormat_BC1:
						return DXGI_FORMAT_BC1_UNORM;
					case IEnum::ETexture2DFormat_BC2:
						return DXGI_FORMAT_BC2_UNORM;
					case IEnum::ETexture2DFormat_BC3:
						return DXGI_FORMAT_BC3_UNORM;
					default:
						assert(0);
					}
					return DXGI_FORMAT_UNKNOWN;
				}
				static DXGI_FORMAT getDXGIFormat(IEnum::ERenderableSurfaceFormat format)
				{
					switch(format)
					{
					case IEnum::ERenderableSurfaceFormat_R8G8B8A8:
						return DXGI_FORMAT_R8G8B8A8_UNORM;
					default:
						assert(0);
					}
					return DXGI_FORMAT_UNKNOWN;
				}
				static UInt32 getRowPitch(DXGI_FORMAT format,UInt32 width)
				{
					switch(format)
					{
					case DXGI_FORMAT_R8G8B8A8_UNORM:
						return 4*width;
					case DXGI_FORMAT_R8_UNORM:
						return width;
					default:
						assert(0);
					}
					return 0;
				}
				static UInt32 getStride(CEnum::EVertexBufferType type)
				{
					UInt32 ret=0;
					switch(type)
					{
					case CEnum::EVertexBufferType_Position:
					case CEnum::EVertexBufferType_Normal:
					case CEnum::EVertexBufferType_Tangent:
						ret=sizeof(CFloat3);
						break;
					case CEnum::EVertexBufferType_TextureCoord0:
					case CEnum::EVertexBufferType_TextureCoord1:
						ret=sizeof(CFloat2);
						break;
					case CEnum::EVertexBufferType_BlendWeight:
						ret=sizeof(CFloat4);
						break;
					case CEnum::EVertexBufferType_BlendIndex:
					case CEnum::EVertexBufferType_Diffuse:
						ret=sizeof(UInt32);
						break;
					default:
						assert(0);
					}
					return ret;
				}
				static D3D11_FILTER map(IEnum::ESamplerFilter filter)
				{
					D3D11_FILTER ret;
					switch(filter)
					{
					case IEnum::ESamplerFilter_MIN_MAG_MIP_POINT:ret=D3D11_FILTER_MIN_MAG_MIP_POINT;break;
					case IEnum::ESamplerFilter_MIN_MAG_POINT_MIP_LINEAR:ret=D3D11_FILTER_MIN_MAG_POINT_MIP_LINEAR;break;
					case IEnum::ESamplerFilter_MIN_POINT_MAG_LINEAR_MIP_POINT:ret=D3D11_FILTER_MIN_POINT_MAG_LINEAR_MIP_POINT;break;
					case IEnum::ESamplerFilter_MIN_POINT_MAG_MIP_LINEAR:ret=D3D11_FILTER_MIN_POINT_MAG_MIP_LINEAR;break;
					case IEnum::ESamplerFilter_MIN_LINEAR_MAG_MIP_POINT:ret=D3D11_FILTER_MIN_LINEAR_MAG_MIP_POINT;break;
					case IEnum::ESamplerFilter_MIN_LINEAR_MAG_POINT_MIP_LINEAR:ret=D3D11_FILTER_MIN_LINEAR_MAG_POINT_MIP_LINEAR;break;
					case IEnum::ESamplerFilter_MIN_MAG_LINEAR_MIP_POINT:ret=D3D11_FILTER_MIN_MAG_LINEAR_MIP_POINT;break;
					case IEnum::ESamplerFilter_MIN_MAG_MIP_LINEAR:ret=D3D11_FILTER_MIN_MAG_MIP_LINEAR;break;
					case IEnum::ESamplerFilter_ANISOTROPIC:ret=D3D11_FILTER_ANISOTROPIC;break;
					case IEnum::ESamplerFilter_COMPARISON_MIN_MAG_MIP_POINT:ret=D3D11_FILTER_COMPARISON_MIN_MAG_MIP_POINT;break;
					case IEnum::ESamplerFilter_COMPARISON_MIN_MAG_POINT_MIP_LINEAR:ret=D3D11_FILTER_COMPARISON_MIN_MAG_POINT_MIP_LINEAR;break;
					case IEnum::ESamplerFilter_COMPARISON_MIN_POINT_MAG_LINEAR_MIP_POINT:ret=D3D11_FILTER_COMPARISON_MIN_POINT_MAG_LINEAR_MIP_POINT;break;
					case IEnum::ESamplerFilter_COMPARISON_MIN_POINT_MAG_MIP_LINEAR:ret=D3D11_FILTER_COMPARISON_MIN_POINT_MAG_MIP_LINEAR;break;
					case IEnum::ESamplerFilter_COMPARISON_MIN_LINEAR_MAG_MIP_POINT:ret=D3D11_FILTER_COMPARISON_MIN_LINEAR_MAG_MIP_POINT;break;
					case IEnum::ESamplerFilter_COMPARISON_MIN_LINEAR_MAG_POINT_MIP_LINEAR:ret=D3D11_FILTER_COMPARISON_MIN_LINEAR_MAG_POINT_MIP_LINEAR;break;
					case IEnum::ESamplerFilter_COMPARISON_MIN_MAG_LINEAR_MIP_POINT:ret=D3D11_FILTER_COMPARISON_MIN_MAG_LINEAR_MIP_POINT;break;
					case IEnum::ESamplerFilter_COMPARISON_MIN_MAG_MIP_LINEAR:ret=D3D11_FILTER_COMPARISON_MIN_MAG_MIP_LINEAR;break;
					case IEnum::ESamplerFilter_COMPARISON_ANISOTROPIC:ret=D3D11_FILTER_COMPARISON_ANISOTROPIC;break;
					case IEnum::ESamplerFilter_MINIMUM_MIN_MAG_MIP_POINT:ret=D3D11_FILTER_MINIMUM_MIN_MAG_MIP_POINT;break;
					case IEnum::ESamplerFilter_MINIMUM_MIN_MAG_POINT_MIP_LINEAR:ret=D3D11_FILTER_MINIMUM_MIN_MAG_POINT_MIP_LINEAR;break;
					case IEnum::ESamplerFilter_MINIMUM_MIN_POINT_MAG_LINEAR_MIP_POINT:ret=D3D11_FILTER_MINIMUM_MIN_POINT_MAG_LINEAR_MIP_POINT;break;
					case IEnum::ESamplerFilter_MINIMUM_MIN_POINT_MAG_MIP_LINEAR:ret=D3D11_FILTER_MINIMUM_MIN_POINT_MAG_MIP_LINEAR;break;
					case IEnum::ESamplerFilter_MINIMUM_MIN_LINEAR_MAG_MIP_POINT:ret=D3D11_FILTER_MINIMUM_MIN_LINEAR_MAG_MIP_POINT;break;
					case IEnum::ESamplerFilter_MINIMUM_MIN_LINEAR_MAG_POINT_MIP_LINEAR:ret=D3D11_FILTER_MINIMUM_MIN_LINEAR_MAG_POINT_MIP_LINEAR;break;
					case IEnum::ESamplerFilter_MINIMUM_MIN_MAG_LINEAR_MIP_POINT:ret=D3D11_FILTER_MINIMUM_MIN_MAG_LINEAR_MIP_POINT;break;
					case IEnum::ESamplerFilter_MINIMUM_MIN_MAG_MIP_LINEAR:ret=D3D11_FILTER_MINIMUM_MIN_MAG_MIP_LINEAR;break;
					case IEnum::ESamplerFilter_MINIMUM_ANISOTROPIC:ret=D3D11_FILTER_MINIMUM_ANISOTROPIC;break;
					case IEnum::ESamplerFilter_MAXIMUM_MIN_MAG_MIP_POINT:ret=D3D11_FILTER_MAXIMUM_MIN_MAG_MIP_POINT;break;
					case IEnum::ESamplerFilter_MAXIMUM_MIN_MAG_POINT_MIP_LINEAR:ret=D3D11_FILTER_MAXIMUM_MIN_MAG_POINT_MIP_LINEAR;break;
					case IEnum::ESamplerFilter_MAXIMUM_MIN_POINT_MAG_LINEAR_MIP_POINT:ret=D3D11_FILTER_MAXIMUM_MIN_POINT_MAG_LINEAR_MIP_POINT;break;
					case IEnum::ESamplerFilter_MAXIMUM_MIN_POINT_MAG_MIP_LINEAR:ret=D3D11_FILTER_MAXIMUM_MIN_POINT_MAG_MIP_LINEAR;break;
					case IEnum::ESamplerFilter_MAXIMUM_MIN_LINEAR_MAG_MIP_POINT:ret=D3D11_FILTER_MAXIMUM_MIN_LINEAR_MAG_MIP_POINT;break;
					case IEnum::ESamplerFilter_MAXIMUM_MIN_LINEAR_MAG_POINT_MIP_LINEAR:ret=D3D11_FILTER_MAXIMUM_MIN_LINEAR_MAG_POINT_MIP_LINEAR;break;
					case IEnum::ESamplerFilter_MAXIMUM_MIN_MAG_LINEAR_MIP_POINT:ret=D3D11_FILTER_MAXIMUM_MIN_MAG_LINEAR_MIP_POINT;break;
					case IEnum::ESamplerFilter_MAXIMUM_MIN_MAG_MIP_LINEAR:ret=D3D11_FILTER_MAXIMUM_MIN_MAG_MIP_LINEAR;break;
					case IEnum::ESamplerFilter_MAXIMUM_ANISOTROPIC:ret=D3D11_FILTER_MAXIMUM_ANISOTROPIC;break;
					default:
						assert(false);
					}
					return ret;
				}
				static IEnum::ESamplerFilter map(D3D11_FILTER filter)
				{
					IEnum::ESamplerFilter ret;
					switch(filter)
					{
					case D3D11_FILTER_MIN_MAG_MIP_POINT:ret=IEnum::ESamplerFilter_MIN_MAG_MIP_POINT;break;
					case D3D11_FILTER_MIN_MAG_POINT_MIP_LINEAR:ret=IEnum::ESamplerFilter_MIN_MAG_POINT_MIP_LINEAR;break;
					case D3D11_FILTER_MIN_POINT_MAG_LINEAR_MIP_POINT:ret=IEnum::ESamplerFilter_MIN_POINT_MAG_LINEAR_MIP_POINT;break;
					case D3D11_FILTER_MIN_POINT_MAG_MIP_LINEAR:ret=IEnum::ESamplerFilter_MIN_POINT_MAG_MIP_LINEAR;break;
					case D3D11_FILTER_MIN_LINEAR_MAG_MIP_POINT:ret=IEnum::ESamplerFilter_MIN_LINEAR_MAG_MIP_POINT;break;
					case D3D11_FILTER_MIN_LINEAR_MAG_POINT_MIP_LINEAR:ret=IEnum::ESamplerFilter_MIN_LINEAR_MAG_POINT_MIP_LINEAR;break;
					case D3D11_FILTER_MIN_MAG_LINEAR_MIP_POINT:ret=IEnum::ESamplerFilter_MIN_MAG_LINEAR_MIP_POINT;break;
					case D3D11_FILTER_MIN_MAG_MIP_LINEAR:ret=IEnum::ESamplerFilter_MIN_MAG_MIP_LINEAR;break;
					case D3D11_FILTER_ANISOTROPIC:ret=IEnum::ESamplerFilter_ANISOTROPIC;break;
					case D3D11_FILTER_COMPARISON_MIN_MAG_MIP_POINT:ret=IEnum::ESamplerFilter_COMPARISON_MIN_MAG_MIP_POINT;break;
					case D3D11_FILTER_COMPARISON_MIN_MAG_POINT_MIP_LINEAR:ret=IEnum::ESamplerFilter_COMPARISON_MIN_MAG_POINT_MIP_LINEAR;break;
					case D3D11_FILTER_COMPARISON_MIN_POINT_MAG_LINEAR_MIP_POINT:ret=IEnum::ESamplerFilter_COMPARISON_MIN_POINT_MAG_LINEAR_MIP_POINT;break;
					case D3D11_FILTER_COMPARISON_MIN_POINT_MAG_MIP_LINEAR:ret=IEnum::ESamplerFilter_COMPARISON_MIN_POINT_MAG_MIP_LINEAR;break;
					case D3D11_FILTER_COMPARISON_MIN_LINEAR_MAG_MIP_POINT:ret=IEnum::ESamplerFilter_COMPARISON_MIN_LINEAR_MAG_MIP_POINT;break;
					case D3D11_FILTER_COMPARISON_MIN_LINEAR_MAG_POINT_MIP_LINEAR:ret=IEnum::ESamplerFilter_COMPARISON_MIN_LINEAR_MAG_POINT_MIP_LINEAR;break;
					case D3D11_FILTER_COMPARISON_MIN_MAG_LINEAR_MIP_POINT:ret=IEnum::ESamplerFilter_COMPARISON_MIN_MAG_LINEAR_MIP_POINT;break;
					case D3D11_FILTER_COMPARISON_MIN_MAG_MIP_LINEAR:ret=IEnum::ESamplerFilter_COMPARISON_MIN_MAG_MIP_LINEAR;break;
					case D3D11_FILTER_COMPARISON_ANISOTROPIC:ret=IEnum::ESamplerFilter_COMPARISON_ANISOTROPIC;break;
					case D3D11_FILTER_MINIMUM_MIN_MAG_MIP_POINT:ret=IEnum::ESamplerFilter_MINIMUM_MIN_MAG_MIP_POINT;break;
					case D3D11_FILTER_MINIMUM_MIN_MAG_POINT_MIP_LINEAR:ret=IEnum::ESamplerFilter_MINIMUM_MIN_MAG_POINT_MIP_LINEAR;break;
					case D3D11_FILTER_MINIMUM_MIN_POINT_MAG_LINEAR_MIP_POINT:ret=IEnum::ESamplerFilter_MINIMUM_MIN_POINT_MAG_LINEAR_MIP_POINT;break;
					case D3D11_FILTER_MINIMUM_MIN_POINT_MAG_MIP_LINEAR:ret=IEnum::ESamplerFilter_MINIMUM_MIN_POINT_MAG_MIP_LINEAR;break;
					case D3D11_FILTER_MINIMUM_MIN_LINEAR_MAG_MIP_POINT:ret=IEnum::ESamplerFilter_MINIMUM_MIN_LINEAR_MAG_MIP_POINT;break;
					case D3D11_FILTER_MINIMUM_MIN_LINEAR_MAG_POINT_MIP_LINEAR:ret=IEnum::ESamplerFilter_MINIMUM_MIN_LINEAR_MAG_POINT_MIP_LINEAR;break;
					case D3D11_FILTER_MINIMUM_MIN_MAG_LINEAR_MIP_POINT:ret=IEnum::ESamplerFilter_MINIMUM_MIN_MAG_LINEAR_MIP_POINT;break;
					case D3D11_FILTER_MINIMUM_MIN_MAG_MIP_LINEAR:ret=IEnum::ESamplerFilter_MINIMUM_MIN_MAG_MIP_LINEAR;break;
					case D3D11_FILTER_MINIMUM_ANISOTROPIC:ret=IEnum::ESamplerFilter_MINIMUM_ANISOTROPIC;break;
					case D3D11_FILTER_MAXIMUM_MIN_MAG_MIP_POINT:ret=IEnum::ESamplerFilter_MAXIMUM_MIN_MAG_MIP_POINT;break;
					case D3D11_FILTER_MAXIMUM_MIN_MAG_POINT_MIP_LINEAR:ret=IEnum::ESamplerFilter_MAXIMUM_MIN_MAG_POINT_MIP_LINEAR;break;
					case D3D11_FILTER_MAXIMUM_MIN_POINT_MAG_LINEAR_MIP_POINT:ret=IEnum::ESamplerFilter_MAXIMUM_MIN_POINT_MAG_LINEAR_MIP_POINT;break;
					case D3D11_FILTER_MAXIMUM_MIN_POINT_MAG_MIP_LINEAR:ret=IEnum::ESamplerFilter_MAXIMUM_MIN_POINT_MAG_MIP_LINEAR;break;
					case D3D11_FILTER_MAXIMUM_MIN_LINEAR_MAG_MIP_POINT:ret=IEnum::ESamplerFilter_MAXIMUM_MIN_LINEAR_MAG_MIP_POINT;break;
					case D3D11_FILTER_MAXIMUM_MIN_LINEAR_MAG_POINT_MIP_LINEAR:ret=IEnum::ESamplerFilter_MAXIMUM_MIN_LINEAR_MAG_POINT_MIP_LINEAR;break;
					case D3D11_FILTER_MAXIMUM_MIN_MAG_LINEAR_MIP_POINT:ret=IEnum::ESamplerFilter_MAXIMUM_MIN_MAG_LINEAR_MIP_POINT;break;
					case D3D11_FILTER_MAXIMUM_MIN_MAG_MIP_LINEAR:ret=IEnum::ESamplerFilter_MAXIMUM_MIN_MAG_MIP_LINEAR;break;
					case D3D11_FILTER_MAXIMUM_ANISOTROPIC:ret=IEnum::ESamplerFilter_MAXIMUM_ANISOTROPIC;break;
					default:
						assert(false);
					}
					return ret;
				}
				static D3D11_TEXTURE_ADDRESS_MODE map(IEnum::ETextureAddressMode mode)
				{
					D3D11_TEXTURE_ADDRESS_MODE ret;
					switch(mode)
					{
					case IEnum::ETextureAddressMode_WRAP:ret=D3D11_TEXTURE_ADDRESS_WRAP;break;
					case IEnum::ETextureAddressMode_MIRROR:ret=D3D11_TEXTURE_ADDRESS_MIRROR;break;
					case IEnum::ETextureAddressMode_CLAMP:ret=D3D11_TEXTURE_ADDRESS_CLAMP;break;
					case IEnum::ETextureAddressMode_BORDER:ret=D3D11_TEXTURE_ADDRESS_BORDER;break;
					case IEnum::ETextureAddressMode_MIRROR_ONCE:ret=D3D11_TEXTURE_ADDRESS_MIRROR_ONCE;break;
					default:
						assert(false);
					}
					return ret;
				}
				static IEnum::ETextureAddressMode map(D3D11_TEXTURE_ADDRESS_MODE mode)
				{
					IEnum::ETextureAddressMode ret;
					switch(mode)
					{
					case D3D11_TEXTURE_ADDRESS_WRAP:ret=IEnum::ETextureAddressMode_WRAP;break;
					case D3D11_TEXTURE_ADDRESS_MIRROR:ret=IEnum::ETextureAddressMode_MIRROR;break;
					case D3D11_TEXTURE_ADDRESS_CLAMP:ret=IEnum::ETextureAddressMode_CLAMP;break;
					case D3D11_TEXTURE_ADDRESS_BORDER:ret=IEnum::ETextureAddressMode_BORDER;break;
					case D3D11_TEXTURE_ADDRESS_MIRROR_ONCE:ret=IEnum::ETextureAddressMode_MIRROR_ONCE;break;
					}
					return ret;
				}
				static D3D11_COMPARISON_FUNC map(IEnum::EComparisonFunction func)
				{
					D3D11_COMPARISON_FUNC ret;
					switch(func)
					{
					case IEnum::EComparisonFunction_NEVER:ret=D3D11_COMPARISON_NEVER;break;
					case IEnum::EComparisonFunction_LESS:ret=D3D11_COMPARISON_LESS;break;
					case IEnum::EComparisonFunction_EQUAL:ret=D3D11_COMPARISON_EQUAL;break;
					case IEnum::EComparisonFunction_LESS_EQUAL:ret=D3D11_COMPARISON_LESS_EQUAL;break;
					case IEnum::EComparisonFunction_GREATER:ret=D3D11_COMPARISON_GREATER;break;
					case IEnum::EComparisonFunction_NOT_EQUAL:ret=D3D11_COMPARISON_NOT_EQUAL;break;
					case IEnum::EComparisonFunction_GREATER_EQUAL:ret=D3D11_COMPARISON_GREATER_EQUAL;break;
					case IEnum::EComparisonFunction_ALWAYS:ret=D3D11_COMPARISON_ALWAYS;break;
					}
					return ret;
				}
				static IEnum::EComparisonFunction map(D3D11_COMPARISON_FUNC func)
				{
					IEnum::EComparisonFunction ret;
					switch(func)
					{
					case D3D11_COMPARISON_NEVER:ret=IEnum::EComparisonFunction_NEVER;break;
					case D3D11_COMPARISON_LESS:ret=IEnum::EComparisonFunction_LESS;break;
					case D3D11_COMPARISON_EQUAL:ret=IEnum::EComparisonFunction_EQUAL;break;
					case D3D11_COMPARISON_LESS_EQUAL:ret=IEnum::EComparisonFunction_LESS_EQUAL;break;
					case D3D11_COMPARISON_GREATER:ret=IEnum::EComparisonFunction_GREATER;break;
					case D3D11_COMPARISON_NOT_EQUAL:ret=IEnum::EComparisonFunction_NOT_EQUAL;break;
					case D3D11_COMPARISON_GREATER_EQUAL:ret=IEnum::EComparisonFunction_GREATER_EQUAL;break;
					case D3D11_COMPARISON_ALWAYS:ret=IEnum::EComparisonFunction_ALWAYS;break;
					}
					return ret;
				}
			};
		}
	}
}