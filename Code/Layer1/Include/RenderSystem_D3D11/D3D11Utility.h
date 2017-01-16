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
				static DXGI_FORMAT getDXGIFormat(IEnum::ETextureFormat format)
				{
					switch(format)
					{
					case IEnum::ETextureFormat_R8G8B8A8:
						return DXGI_FORMAT_R8G8B8A8_UNORM;
					case IEnum::ETextureFormat_BC1:
						return DXGI_FORMAT_BC1_UNORM;
					case IEnum::ETextureFormat_BC2:
						return DXGI_FORMAT_BC2_UNORM;
					case IEnum::ETextureFormat_BC3:
						return DXGI_FORMAT_BC3_UNORM;
					case IEnum::ETextureFormat_Font:
						return DXGI_FORMAT_A8_UNORM;
					case IEnum::ETextureFormat_Shadow:
						return DXGI_FORMAT_D32_FLOAT;
					case IEnum::ETextureFormat_Environment:
						return DXGI_FORMAT_R8G8B8A8_UNORM;
					}
					return DXGI_FORMAT_UNKNOWN;
				}
				static UInt32 getRowPitch(DXGI_FORMAT format,UInt32 width)
				{
					switch(format)
					{
					case DXGI_FORMAT_R8G8B8A8_UNORM:
						return 4*width;
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
			};
		}
	}
}