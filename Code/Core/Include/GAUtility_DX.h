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
				static D3D11_PRIMITIVE_TOPOLOGY mapping(IGAEnum::EPrimitiveTopology value)
				{
					switch(value)
					{
					case IGAEnum::EPrimitiveTopology_TRIANGLELIST:
						return D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
					case IGAEnum::EPrimitiveTopology_TRIANGLESTRIP:
						return D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;
					case IGAEnum::EPrimitiveTopology_LINELIST:
						return D3D11_PRIMITIVE_TOPOLOGY_LINELIST;
					case IGAEnum::EPrimitiveTopology_LINESTRIP:
						return D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP;
					case IGAEnum::EPrimitiveTopology_POINTLIST:
						return D3D11_PRIMITIVE_TOPOLOGY_POINTLIST;
					default:
						assert(0);
						return D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
					}
				}
				static D3D11_BLEND mapping(IGAEnum::EBlend blend)
				{
					switch(blend)
					{
					case IGAEnum::EBlend_ZERO:
						return D3D11_BLEND_ZERO;
					case IGAEnum::EBlend_ONE:
						return D3D11_BLEND_ONE;
					case IGAEnum::EBlend_SRC_COLOR:
						return D3D11_BLEND_SRC_COLOR;
					case IGAEnum::EBlend_SRC_ALPHA:
						return D3D11_BLEND_SRC_ALPHA;
					case IGAEnum::EBlend_SRC_ALPHA_SAT:
						return D3D11_BLEND_SRC_ALPHA_SAT;
					case IGAEnum::EBlend_BLEND_FACTOR:
						return D3D11_BLEND_BLEND_FACTOR;
					case IGAEnum::EBlend_DEST_ALPHA:
						return D3D11_BLEND_DEST_ALPHA;
					case IGAEnum::EBlend_DEST_COLOR:
						return D3D11_BLEND_DEST_COLOR;
					case IGAEnum::EBlend_INV_BLEND_FACTOR:
						return D3D11_BLEND_INV_BLEND_FACTOR;
					case IGAEnum::EBlend_INV_DEST_ALPHA:
						return D3D11_BLEND_INV_DEST_ALPHA;
					case IGAEnum::EBlend_INV_DEST_COLOR:
						return D3D11_BLEND_INV_DEST_COLOR;
					case IGAEnum::EBlend_INV_SRC1_ALPHA:
						return D3D11_BLEND_INV_SRC1_ALPHA;
					case IGAEnum::EBlend_INV_SRC1_COLOR:
						return D3D11_BLEND_INV_SRC1_COLOR;
					case IGAEnum::EBlend_INV_SRC_ALPHA:
						return D3D11_BLEND_INV_SRC_ALPHA;
					case IGAEnum::EBlend_INV_SRC_COLOR:
						return D3D11_BLEND_INV_SRC_COLOR;
					default:
						assert(0);
						return D3D11_BLEND_ONE;
					}
				}
				static D3D11_BLEND_OP mapping(IGAEnum::EBlendOp blendOp)
				{
					switch(blendOp)
					{
					case IGAEnum::EBlendOp_ADD:
						return D3D11_BLEND_OP_ADD;
					case IGAEnum::EBlendOp_MAX:
						return D3D11_BLEND_OP_MAX;
					case IGAEnum::EBlendOp_MIN:
						return D3D11_BLEND_OP_MIN;
					case IGAEnum::EBlendOp_REV_SUBTRACT:
						return D3D11_BLEND_OP_REV_SUBTRACT;
					case IGAEnum::EBlendOp_SUBTRACT:
						return D3D11_BLEND_OP_SUBTRACT;
					default:
						assert(0);
						return D3D11_BLEND_OP_ADD;
					}
				}
				static CD3D11_BLEND_DESC & mapping(const IGAStruct::SBlendDesc & src,CD3D11_BLEND_DESC & dest)
				{
					dest.AlphaToCoverageEnable=src.AlphaToCoverageEnable;
					dest.IndependentBlendEnable=src.IndependentBlendEnable;
					for(int i=0;i<sizeof(dest.RenderTarget)/sizeof(decltype(dest.RenderTarget[0]));++i)
					{
						dest.RenderTarget[i].BlendEnable=src.RenderTarget[i].BlendEnable;
						dest.RenderTarget[i].BlendOp=mapping(src.RenderTarget[i].BlendOp);
						dest.RenderTarget[i].BlendOpAlpha=mapping(src.RenderTarget[i].BlendOpAlpha);
						dest.RenderTarget[i].DestBlend=mapping(src.RenderTarget[i].DestBlend);
						dest.RenderTarget[i].DestBlendAlpha=mapping(src.RenderTarget[i].DestBlendAlpha);
						dest.RenderTarget[i].RenderTargetWriteMask=src.RenderTarget[i].RenderTargetWriteMask;
						dest.RenderTarget[i].SrcBlend=mapping(src.RenderTarget[i].SrcBlend);
						dest.RenderTarget[i].SrcBlendAlpha=mapping(src.RenderTarget[i].SrcBlendAlpha);
					}
				}
				static CD3D11_BLEND_DESC mapping(const IGAStruct::SBlendDesc & desc)
				{
					CD3D11_BLEND_DESC ret;
					return mapping(desc,ret);
				}
			};
		}
	}
}