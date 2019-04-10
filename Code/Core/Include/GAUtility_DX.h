#pragma once
namespace NSDevilX
{
	namespace NSCore
	{
		namespace NSDirectX
		{
			class CUtility
			{
			public:
				static UInt32 mappingToDXGIUsage(UInt32 usages)
				{
					UInt32 ret=0;
					if(usages&IGAEnum::EGIUsage_BackBuffer)
						ret|=DXGI_USAGE_BACK_BUFFER;
					if(usages&IGAEnum::EGIUsage_DiscardOnPresent)
						ret|=DXGI_USAGE_DISCARD_ON_PRESENT;
					if(usages&IGAEnum::EGIUsage_ReadOnly)
						ret|=DXGI_USAGE_READ_ONLY;
					if(usages&IGAEnum::EGIUsage_RenderTargetOutput)
						ret|=DXGI_USAGE_RENDER_TARGET_OUTPUT;
					if(usages&IGAEnum::EGIUsage_ShaderInput)
						ret|=DXGI_USAGE_SHADER_INPUT;
					if(usages&IGAEnum::EGIUsage_UnorderedAccess)
						ret|=DXGI_USAGE_UNORDERED_ACCESS;
					return ret;
				}
				static DXGI_FORMAT mapping(IGAEnum::EGIFormat format)
				{
					return (DXGI_FORMAT)format;
				}
				static D3D11_USAGE mapping(IGAEnum::EUsage usage)
				{
					switch(usage)
					{
					case IGAEnum::EUsage_DEFAULT:return D3D11_USAGE_DEFAULT;
					case IGAEnum::EUsage_DYNAMIC:return D3D11_USAGE_DYNAMIC;
					case IGAEnum::EUsage_IMMUTABLE:return D3D11_USAGE_IMMUTABLE;
					case IGAEnum::EUsage_STAGING:return D3D11_USAGE_STAGING;
					default:
						return D3D11_USAGE_DEFAULT;
					}
				}
				static D3D11_SUBRESOURCE_DATA & mapping(const IGAStruct::SSubResourceData & src,D3D11_SUBRESOURCE_DATA & dest)
				{
					dest.pSysMem=src.pSysMem;
					dest.SysMemPitch=src.SysMemPitch;
					dest.SysMemSlicePitch=src.SysMemSlicePitch;
					return dest;
				}
				static D3D11_SUBRESOURCE_DATA mapping(const IGAStruct::SSubResourceData & src)
				{
					D3D11_SUBRESOURCE_DATA ret={};
					return mapping(src,ret);
				}
				static DXGI_SWAP_CHAIN_DESC & mapping(const IGAStruct::SGISwapChainDesc & src,DXGI_SWAP_CHAIN_DESC & dest)
				{
					dest.BufferCount=1;
					dest.BufferDesc.Format=mapping(src.BufferDesc.Format);
					dest.BufferDesc.Height=src.BufferDesc.Height;
					dest.BufferDesc.RefreshRate.Denominator=1;
					dest.BufferDesc.RefreshRate.Numerator=src.BufferDesc.RefreshRate;
					dest.BufferDesc.Scaling=DXGI_MODE_SCALING_UNSPECIFIED;
					dest.BufferDesc.ScanlineOrdering=DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
					dest.BufferDesc.Width=src.BufferDesc.Width;
					dest.BufferUsage=mappingToDXGIUsage(src.BufferUsage);
					dest.Flags=DXGI_SWAP_CHAIN_FLAG_DISPLAY_ONLY;
					dest.OutputWindow=static_cast<HWND>(src.OutputWindow);
					dest.SampleDesc.Count=src.SampleDesc.Count;
					dest.SampleDesc.Quality=src.SampleDesc.Quality;
					dest.SwapEffect=DXGI_SWAP_EFFECT_DISCARD;
					dest.Windowed=FALSE;
					return dest;
				}
				static DXGI_SWAP_CHAIN_DESC mapping(const IGAStruct::SGISwapChainDesc & desc)
				{
					DXGI_SWAP_CHAIN_DESC ret={};
					return mapping(desc,ret);
				}
			};
		}
	}
}