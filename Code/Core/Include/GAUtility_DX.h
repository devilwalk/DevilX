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
				template<typename TDesc,typename TRet>
				static TRet mappingT(const TDesc & desc)
				{
					TRet ret;
					return mapping(desc,ret);
				}
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
					dest.OutputWindow=src.OutputWindow;
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
				static D3D11_LOGIC_OP mapping(IGAEnum::ELogicOp op)
				{
					switch(op)
					{
					case IGAEnum::ELogicOp_AND:
						return D3D11_LOGIC_OP_AND;
					case IGAEnum::ELogicOp_AND_INVERTED:
						return D3D11_LOGIC_OP_AND_INVERTED;
					case IGAEnum::ELogicOp_AND_REVERSE:
						return D3D11_LOGIC_OP_AND_REVERSE;
					case IGAEnum::ELogicOp_CLEAR:
						return D3D11_LOGIC_OP_CLEAR;
					case IGAEnum::ELogicOp_COPY:
						return D3D11_LOGIC_OP_COPY;
					case IGAEnum::ELogicOp_COPY_INVERTED:
						return D3D11_LOGIC_OP_COPY_INVERTED;
					case IGAEnum::ELogicOp_EQUIV:
						return D3D11_LOGIC_OP_EQUIV;
					case IGAEnum::ELogicOp_INVERT:
						return D3D11_LOGIC_OP_INVERT;
					case IGAEnum::ELogicOp_NAND:
						return D3D11_LOGIC_OP_NAND;
					case IGAEnum::ELogicOp_NOOP:
						return D3D11_LOGIC_OP_NOOP;
					case IGAEnum::ELogicOp_NOR:
						return D3D11_LOGIC_OP_NOR;
					case IGAEnum::ELogicOp_OR:
						return D3D11_LOGIC_OP_OR;
					case IGAEnum::ELogicOp_OR_INVERTED:
						return D3D11_LOGIC_OP_OR_INVERTED;
					case IGAEnum::ELogicOp_OR_REVERSE:
						return D3D11_LOGIC_OP_OR_REVERSE;
					case IGAEnum::ELogicOp_SET:
						return D3D11_LOGIC_OP_SET;
					case IGAEnum::ELogicOp_XOR:
						return D3D11_LOGIC_OP_XOR;
					default:
						assert(0);
						return D3D11_LOGIC_OP_CLEAR;
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
					return dest;
				}
				static CD3D11_BLEND_DESC1 & mapping(const IGAStruct::SBlendDesc1 & src,CD3D11_BLEND_DESC1 & dest)
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
						dest.RenderTarget[i].LogicOpEnable=src.RenderTarget[i].LogicOpEnable;
						dest.RenderTarget[i].LogicOp=mapping(src.RenderTarget[i].LogicOp);
					}
					return dest;
				}
				static D3D11_CONSERVATIVE_RASTERIZATION_MODE mapping(IGAEnum::EConservativeRasterizationMode mode)
				{
					switch(mode)
					{
					case IGAEnum::EConservativeRasterizationMode_OFF:
						return D3D11_CONSERVATIVE_RASTERIZATION_MODE_OFF;
					case IGAEnum::EConservativeRasterizationMode_ON:
						return D3D11_CONSERVATIVE_RASTERIZATION_MODE_ON;
					default:
						assert(0);
						return D3D11_CONSERVATIVE_RASTERIZATION_MODE_OFF;
					}
				}
				static D3D11_CULL_MODE mapping(IGAEnum::ECullMode mode)
				{
					switch(mode)
					{
					case IGAEnum::ECullMode_BACK:
						return D3D11_CULL_BACK;
					case IGAEnum::ECullMode_FRONT:
						return D3D11_CULL_FRONT;
					case IGAEnum::ECullMode_NONE:
						return D3D11_CULL_NONE;
					default:
						assert(0);
						return D3D11_CULL_BACK;
					}
				}
				static D3D11_FILL_MODE mapping(IGAEnum::EFillMode mode)
				{
					switch(mode)
					{
					case IGAEnum::EFillMode_SOLID:
						return D3D11_FILL_SOLID;
					case IGAEnum::EFillMode_WIREFRAME:
						return D3D11_FILL_WIREFRAME;
					default:
						return D3D11_FILL_SOLID;
					}
				}
				static CD3D11_RASTERIZER_DESC & mapping(const IGAStruct::SRasterizerDesc & src,CD3D11_RASTERIZER_DESC & dest)
				{
					dest.AntialiasedLineEnable=src.AntialiasedLineEnable;
					dest.CullMode=mapping(src.CullMode);
					dest.DepthBias=src.DepthBias;
					dest.DepthBiasClamp=src.DepthBiasClamp;
					dest.DepthClipEnable=src.DepthClipEnable;
					dest.FillMode=mapping(src.FillMode);
					dest.FrontCounterClockwise=src.FrontCounterClockwise;
					dest.MultisampleEnable=src.MultisampleEnable;
					dest.ScissorEnable=src.ScissorEnable;
					dest.SlopeScaledDepthBias=src.SlopeScaledDepthBias;
					return dest;
				}
				static CD3D11_RASTERIZER_DESC1 & mapping(const IGAStruct::SRasterizerDesc1 & src,CD3D11_RASTERIZER_DESC1 & dest)
				{
					dest.AntialiasedLineEnable=src.AntialiasedLineEnable;
					dest.CullMode=mapping(src.CullMode);
					dest.DepthBias=src.DepthBias;
					dest.DepthBiasClamp=src.DepthBiasClamp;
					dest.DepthClipEnable=src.DepthClipEnable;
					dest.FillMode=mapping(src.FillMode);
					dest.ForcedSampleCount=src.ForcedSampleCount;
					dest.FrontCounterClockwise=src.FrontCounterClockwise;
					dest.MultisampleEnable=src.MultisampleEnable;
					dest.ScissorEnable=src.ScissorEnable;
					dest.SlopeScaledDepthBias=src.SlopeScaledDepthBias;
					return dest;
				}
				static CD3D11_RASTERIZER_DESC2 & mapping(const IGAStruct::SRasterizerDesc2 & src,CD3D11_RASTERIZER_DESC2 & dest)
				{
					dest.AntialiasedLineEnable=src.AntialiasedLineEnable;
					dest.ConservativeRaster=mapping(src.ConservativeRaster);
					dest.CullMode=mapping(src.CullMode);
					dest.DepthBias=src.DepthBias;
					dest.DepthBiasClamp=src.DepthBiasClamp;
					dest.DepthClipEnable=src.DepthClipEnable;
					dest.FillMode=mapping(src.FillMode);
					dest.ForcedSampleCount=src.ForcedSampleCount;
					dest.FrontCounterClockwise=src.FrontCounterClockwise;
					dest.MultisampleEnable=src.MultisampleEnable;
					dest.ScissorEnable=src.ScissorEnable;
					dest.SlopeScaledDepthBias=src.SlopeScaledDepthBias;
					return dest;
				}
				static D3D11_STENCIL_OP mapping(IGAEnum::EStencilOp op)
				{
					switch(op)
					{
					case IGAEnum::EStencilOp_DECR:
						return D3D11_STENCIL_OP_DECR;
					case IGAEnum::EStencilOp_DECR_SAT:
						return D3D11_STENCIL_OP_DECR_SAT;
					case IGAEnum::EStencilOp_INCR:
						return D3D11_STENCIL_OP_INCR;
					case IGAEnum::EStencilOp_INCR_SAT:
						return D3D11_STENCIL_OP_INCR_SAT;
					case IGAEnum::EStencilOp_INVERT:
						return D3D11_STENCIL_OP_INVERT;
					case IGAEnum::EStencilOp_KEEP:
						return D3D11_STENCIL_OP_KEEP;
					case IGAEnum::EStencilOp_REPLACE:
						return D3D11_STENCIL_OP_REPLACE;
					case IGAEnum::EStencilOp_ZERO:
						return D3D11_STENCIL_OP_ZERO;
					default:
						assert(0);
						return D3D11_STENCIL_OP_KEEP;
					}
				}
				static D3D11_COMPARISON_FUNC mapping(IGAEnum::EComparisonFunc func)
				{
					switch(func)
					{
					case IGAEnum::EComparisonFunc_ALWAYS:
						return D3D11_COMPARISON_ALWAYS;
					case IGAEnum::EComparisonFunc_EQUAL:
						return D3D11_COMPARISON_EQUAL;
					case IGAEnum::EComparisonFunc_GREATER:
						return D3D11_COMPARISON_GREATER;
					case IGAEnum::EComparisonFunc_GREATER_EQUAL:
						return D3D11_COMPARISON_GREATER_EQUAL;
					case IGAEnum::EComparisonFunc_LESS:
						return D3D11_COMPARISON_LESS;
					case IGAEnum::EComparisonFunc_LESS_EQUAL:
						return D3D11_COMPARISON_LESS_EQUAL;
					case IGAEnum::EComparisonFunc_NEVER:
						return D3D11_COMPARISON_NEVER;
					case IGAEnum::EComparisonFunc_NOT_EQUAL:
						return D3D11_COMPARISON_NOT_EQUAL;
					default:
						assert(0);
						return D3D11_COMPARISON_ALWAYS;
					}
				}
				static D3D11_DEPTH_WRITE_MASK mapping(IGAEnum::EDepthWriteMask mask)
				{
					switch(mask)
					{
					case IGAEnum::EDepthWriteMask_ALL:
						return D3D11_DEPTH_WRITE_MASK_ALL;
					case IGAEnum::EDepthWriteMask_ZERO:
						return D3D11_DEPTH_WRITE_MASK_ZERO;
					default:
						assert(0);
						return D3D11_DEPTH_WRITE_MASK_ALL;
					}
				}
				static CD3D11_DEPTH_STENCIL_DESC & mapping(const IGAStruct::SDepthStencilDesc & src,CD3D11_DEPTH_STENCIL_DESC & dest)
				{
					dest.BackFace.StencilDepthFailOp=mapping(src.BackFace.StencilDepthFailOp);
					dest.BackFace.StencilFailOp=mapping(src.BackFace.StencilFailOp);
					dest.BackFace.StencilFunc=mapping(src.BackFace.StencilFunc);
					dest.BackFace.StencilPassOp=mapping(src.BackFace.StencilPassOp);
					dest.DepthEnable=src.DepthEnable;
					dest.DepthFunc=mapping(src.DepthFunc);
					dest.DepthWriteMask=mapping(src.DepthWriteMask);
					dest.FrontFace.StencilDepthFailOp=mapping(src.FrontFace.StencilDepthFailOp);
					dest.FrontFace.StencilFailOp=mapping(src.FrontFace.StencilFailOp);
					dest.FrontFace.StencilFunc=mapping(src.FrontFace.StencilFunc);
					dest.FrontFace.StencilPassOp=mapping(src.FrontFace.StencilPassOp);
					dest.StencilEnable=src.StencilEnable;
					dest.StencilReadMask=src.StencilReadMask;
					dest.StencilWriteMask=src.StencilWriteMask;
					return dest;
				}
				static CD3D11_DEPTH_STENCIL_DESC mapping(const IGAStruct::SDepthStencilDesc & desc)
				{
					CD3D11_DEPTH_STENCIL_DESC ret;
					return mapping(desc,ret);
				}
				static D3D11_TEXTURE_ADDRESS_MODE mapping(IGAEnum::ETextureAddressMode mode)
				{
					switch(mode)
					{
					case IGAEnum::ETextureAddressMode_BORDER:
						return D3D11_TEXTURE_ADDRESS_BORDER;
					case IGAEnum::ETextureAddressMode_CLAMP:
						return D3D11_TEXTURE_ADDRESS_CLAMP;
					case IGAEnum::ETextureAddressMode_MIRROR:
						return D3D11_TEXTURE_ADDRESS_MIRROR;
					case IGAEnum::ETextureAddressMode_MIRROR_ONCE:
						return D3D11_TEXTURE_ADDRESS_MIRROR_ONCE;
					case IGAEnum::ETextureAddressMode_WRAP:
						return D3D11_TEXTURE_ADDRESS_WRAP;
					default:
						assert(0);
						return D3D11_TEXTURE_ADDRESS_WRAP;
					}
				}
				static D3D11_FILTER mapping(IGAEnum::EFilter filter)
				{
					switch(filter)
					{
					case IGAEnum::EFilter_MIN_LINEAR_MAG_MIP_POINT:
						return D3D11_FILTER_MIN_LINEAR_MAG_MIP_POINT;
					case IGAEnum::EFilter_MIN_LINEAR_MAG_POINT_MIP_LINEAR:
						return D3D11_FILTER_MIN_LINEAR_MAG_POINT_MIP_LINEAR;
					case IGAEnum::EFilter_MIN_MAG_LINEAR_MIP_POINT:
						return D3D11_FILTER_MIN_MAG_LINEAR_MIP_POINT;
					case IGAEnum::EFilter_MIN_MAG_MIP_LINEAR:
						return D3D11_FILTER_MIN_MAG_MIP_LINEAR;
					case IGAEnum::EFilter_MIN_MAG_MIP_POINT:
						return D3D11_FILTER_MIN_MAG_MIP_POINT;
					case IGAEnum::EFilter_MIN_MAG_POINT_MIP_LINEAR:
						return D3D11_FILTER_MIN_MAG_POINT_MIP_LINEAR;
					case IGAEnum::EFilter_MIN_POINT_MAG_LINEAR_MIP_POINT:
						return D3D11_FILTER_MIN_POINT_MAG_LINEAR_MIP_POINT;
					case IGAEnum::EFilter_MIN_POINT_MAG_MIP_LINEAR:
						return D3D11_FILTER_MIN_POINT_MAG_MIP_LINEAR;
					case IGAEnum::EFilter_ANISOTROPIC:
						return D3D11_FILTER_ANISOTROPIC;
					case IGAEnum::EFilter_COMPARISON_ANISOTROPIC:
						return D3D11_FILTER_COMPARISON_ANISOTROPIC;
					case IGAEnum::EFilter_COMPARISON_MIN_LINEAR_MAG_MIP_POINT:
						return D3D11_FILTER_COMPARISON_MIN_LINEAR_MAG_MIP_POINT;
					case IGAEnum::EFilter_COMPARISON_MIN_LINEAR_MAG_POINT_MIP_LINEAR:
						return D3D11_FILTER_COMPARISON_MIN_LINEAR_MAG_POINT_MIP_LINEAR;
					case IGAEnum::EFilter_COMPARISON_MIN_MAG_LINEAR_MIP_POINT:
						return D3D11_FILTER_COMPARISON_MIN_MAG_LINEAR_MIP_POINT;
					case IGAEnum::EFilter_COMPARISON_MIN_MAG_MIP_LINEAR:
						return D3D11_FILTER_COMPARISON_MIN_MAG_MIP_LINEAR;
					case IGAEnum::EFilter_COMPARISON_MIN_MAG_MIP_POINT:
						return D3D11_FILTER_COMPARISON_MIN_MAG_MIP_POINT;
					case IGAEnum::EFilter_COMPARISON_MIN_MAG_POINT_MIP_LINEAR:
						return D3D11_FILTER_COMPARISON_MIN_MAG_POINT_MIP_LINEAR;
					case IGAEnum::EFilter_COMPARISON_MIN_POINT_MAG_LINEAR_MIP_POINT:
						return D3D11_FILTER_COMPARISON_MIN_POINT_MAG_LINEAR_MIP_POINT;
					case IGAEnum::EFilter_COMPARISON_MIN_POINT_MAG_MIP_LINEAR:
						return D3D11_FILTER_COMPARISON_MIN_POINT_MAG_MIP_LINEAR;
					case IGAEnum::EFilter_MAXIMUM_ANISOTROPIC:
						return D3D11_FILTER_MAXIMUM_ANISOTROPIC;
					case IGAEnum::EFilter_MAXIMUM_MIN_LINEAR_MAG_MIP_POINT:
						return D3D11_FILTER_MAXIMUM_MIN_LINEAR_MAG_MIP_POINT;
					case IGAEnum::EFilter_MAXIMUM_MIN_LINEAR_MAG_POINT_MIP_LINEAR:
						return D3D11_FILTER_MAXIMUM_MIN_LINEAR_MAG_POINT_MIP_LINEAR;
					case IGAEnum::EFilter_MAXIMUM_MIN_MAG_LINEAR_MIP_POINT:
						return D3D11_FILTER_MAXIMUM_MIN_MAG_LINEAR_MIP_POINT;
					case IGAEnum::EFilter_MAXIMUM_MIN_MAG_MIP_LINEAR:
						return D3D11_FILTER_MAXIMUM_MIN_MAG_MIP_LINEAR;
					case IGAEnum::EFilter_MAXIMUM_MIN_MAG_MIP_POINT:
						return D3D11_FILTER_MAXIMUM_MIN_MAG_MIP_POINT;
					case IGAEnum::EFilter_MAXIMUM_MIN_MAG_POINT_MIP_LINEAR:
						return D3D11_FILTER_MAXIMUM_MIN_MAG_POINT_MIP_LINEAR;
					case IGAEnum::EFilter_MAXIMUM_MIN_POINT_MAG_LINEAR_MIP_POINT:
						return D3D11_FILTER_MAXIMUM_MIN_POINT_MAG_LINEAR_MIP_POINT;
					case IGAEnum::EFilter_MAXIMUM_MIN_POINT_MAG_MIP_LINEAR:
						return D3D11_FILTER_MAXIMUM_MIN_POINT_MAG_MIP_LINEAR;
					case IGAEnum::EFilter_MINIMUM_ANISOTROPIC:
						return D3D11_FILTER_MINIMUM_ANISOTROPIC;
					case IGAEnum::EFilter_MINIMUM_MIN_LINEAR_MAG_MIP_POINT:
						return D3D11_FILTER_MINIMUM_MIN_LINEAR_MAG_MIP_POINT;
					case IGAEnum::EFilter_MINIMUM_MIN_LINEAR_MAG_POINT_MIP_LINEAR:
						return D3D11_FILTER_MINIMUM_MIN_LINEAR_MAG_POINT_MIP_LINEAR;
					case IGAEnum::EFilter_MINIMUM_MIN_MAG_LINEAR_MIP_POINT:
						return D3D11_FILTER_MINIMUM_MIN_MAG_LINEAR_MIP_POINT;
					case IGAEnum::EFilter_MINIMUM_MIN_MAG_MIP_LINEAR:
						return D3D11_FILTER_MINIMUM_MIN_MAG_MIP_LINEAR;
					case IGAEnum::EFilter_MINIMUM_MIN_MAG_MIP_POINT:
						return D3D11_FILTER_MINIMUM_MIN_MAG_MIP_POINT;
					case IGAEnum::EFilter_MINIMUM_MIN_MAG_POINT_MIP_LINEAR:
						return D3D11_FILTER_MINIMUM_MIN_MAG_POINT_MIP_LINEAR;
					case IGAEnum::EFilter_MINIMUM_MIN_POINT_MAG_LINEAR_MIP_POINT:
						return D3D11_FILTER_MINIMUM_MIN_POINT_MAG_LINEAR_MIP_POINT;
					case IGAEnum::EFilter_MINIMUM_MIN_POINT_MAG_MIP_LINEAR:
						return D3D11_FILTER_MINIMUM_MIN_POINT_MAG_MIP_LINEAR;
					default:
						assert(0);
						return D3D11_FILTER_MIN_MAG_MIP_POINT;
					}
				}
				static CD3D11_SAMPLER_DESC & mapping(const IGAStruct::SSamplerDesc & src,CD3D11_SAMPLER_DESC & dest)
				{
					dest.AddressU=mapping(src.AddressU);
					dest.AddressV=mapping(src.AddressV);
					dest.AddressW=mapping(src.AddressW);
					for(int i=0;i<4;++i)
						dest.BorderColor[i]=src.BorderColor[i];
					dest.ComparisonFunc=mapping(src.ComparisonFunc);
					dest.Filter=mapping(src.Filter);
					dest.MaxAnisotropy=src.MaxAnisotropy;
					dest.MaxLOD=src.MaxLOD;
					dest.MinLOD=src.MinLOD;
					dest.MipLODBias=src.MipLODBias;
					return dest;
				}
				static CD3D11_SAMPLER_DESC mapping(const IGAStruct::SSamplerDesc & desc)
				{
					CD3D11_SAMPLER_DESC ret;
					return mapping(desc,ret);
				}
				static D3D11_INPUT_ELEMENT_DESC & mapping(const IGAStruct::SInputElementDesc & src,D3D11_INPUT_ELEMENT_DESC & dest)
				{
					dest.AlignedByteOffset=src.AlignedByteOffset;
					dest.Format=mapping(src.Format);
					dest.InputSlot=src.InputSlot;
					dest.InputSlotClass=(src.InstanceDataStepRate==0)?D3D11_INPUT_PER_VERTEX_DATA:D3D11_INPUT_PER_INSTANCE_DATA;
					dest.SemanticIndex=src.SemanticIndex;
					dest.SemanticName=src.SemanticName;
					return dest;
				}
				static D3D11_INPUT_ELEMENT_DESC mapping(const IGAStruct::SInputElementDesc & desc)
				{
					D3D11_INPUT_ELEMENT_DESC ret;
					return mapping(desc,ret);
				}
				static D3D11_CPU_ACCESS_FLAG mapping(IGAEnum::ECPUAccessFlag flag)
				{
					switch(flag)
					{
					case IGAEnum::ECPUAccessFlag_Read:
						return D3D11_CPU_ACCESS_READ;
					case IGAEnum::ECPUAccessFlag_Write:
						return D3D11_CPU_ACCESS_WRITE;
					default:
						assert(0);
						return (D3D11_CPU_ACCESS_FLAG)0;
					}
				}
				static UInt32 mappingCPUAccessFlags(UInt32 flags)
				{
					UInt32 ret=0;
					if(flags&IGAEnum::ECPUAccessFlag_Read)
						ret|=mapping(IGAEnum::ECPUAccessFlag_Read);
					if(flags&IGAEnum::ECPUAccessFlag_Write)
						ret|=mapping(IGAEnum::ECPUAccessFlag_Write);
					return ret;
				}
				static D3D11_BIND_FLAG mapping(IGAEnum::EBufferBindFlag flag)
				{
					switch(flag)
					{
					case IGAEnum::EBufferBindFlag_StreamOut:
						return D3D11_BIND_STREAM_OUTPUT;
					default:
						assert(0);
						return (D3D11_BIND_FLAG)0;
					}
				}
				static UInt32 mappingBufferBindFlags(UInt32 flags)
				{
					UInt32 ret=0;
					if(flags&IGAEnum::EBufferBindFlag_StreamOut)
						ret|=mapping(IGAEnum::EBufferBindFlag_StreamOut);
					return ret;
				}
				static D3D11_BIND_FLAG mapping(IGAEnum::ETextureBindFlag flag)
				{
					switch(flag)
					{
					case IGAEnum::ETextureBindFlag_DepthStencil:
						return D3D11_BIND_DEPTH_STENCIL;
					case IGAEnum::ETextureBindFlag_RenderTarget:
						return D3D11_BIND_RENDER_TARGET;
					case IGAEnum::ETextureBindFlag_ShaderResource:
						return D3D11_BIND_SHADER_RESOURCE;
					default:
						assert(0);
						return (D3D11_BIND_FLAG)0;
					}
				}
				static UInt32 mappingTextureBindFlags(UInt32 flags)
				{
					UInt32 ret=0;
					if(flags&IGAEnum::ETextureBindFlag_DepthStencil)
						ret|=mapping(IGAEnum::ETextureBindFlag_DepthStencil);
					if(flags&IGAEnum::ETextureBindFlag_RenderTarget)
						ret|=mapping(IGAEnum::ETextureBindFlag_RenderTarget);
					if(flags&IGAEnum::ETextureBindFlag_ShaderResource)
						ret|=mapping(IGAEnum::ETextureBindFlag_ShaderResource);
					return ret;
				}
				static UInt32 getComponentCount(IGAEnum::EGIFormat format)
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
				static UInt32 getComponentSize(IGAEnum::EGIFormat format)
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
						return sizeof(UInt8);
					case IGAEnum::EGIFormat_R16_UINT:
					case IGAEnum::EGIFormat_R16_SINT:
					case IGAEnum::EGIFormat_R16G16_UINT:
					case IGAEnum::EGIFormat_R16G16_SINT:
					case IGAEnum::EGIFormat_R16G16B16A16_UINT:
					case IGAEnum::EGIFormat_R16G16B16A16_SINT:
					case IGAEnum::EGIFormat_R16G16B16A16_FLOAT:
						return sizeof(UInt16);
					case IGAEnum::EGIFormat_R32G32_UINT:
					case IGAEnum::EGIFormat_R32G32_SINT:
					case IGAEnum::EGIFormat_R32G32B32_UINT:
					case IGAEnum::EGIFormat_R32G32B32_SINT:
					case IGAEnum::EGIFormat_R32G32B32A32_UINT:
					case IGAEnum::EGIFormat_R32G32B32A32_SINT:
					case IGAEnum::EGIFormat_R32G32B32_FLOAT:
					case IGAEnum::EGIFormat_R32G32B32A32_FLOAT:
						return sizeof(UInt32);
					default:
						assert(0);
						return 0;
					}
				}
				static IGAEnum::ERegisterComponentType mapping(D3D_REGISTER_COMPONENT_TYPE type)
				{
					switch(type)
					{
					case D3D_REGISTER_COMPONENT_UNKNOWN:
						return IGAEnum::ERegisterComponentType_UNKNOWN;
					case D3D_REGISTER_COMPONENT_FLOAT32:
						return IGAEnum::ERegisterComponentType_FLOAT32;
					case D3D_REGISTER_COMPONENT_SINT32:
						return IGAEnum::ERegisterComponentType_SINT32;
					case D3D_REGISTER_COMPONENT_UINT32:
						return IGAEnum::ERegisterComponentType_UINT32;
					default:
						assert(0);
						return IGAEnum::ERegisterComponentType_UNKNOWN;
					}
				}
				static IGAEnum::EShaderBufferType mapping(D3D_CBUFFER_TYPE type)
				{
					switch(type)
					{
					case D3D_CT_CBUFFER:
						return IGAEnum::EShaderBufferType_CBuffer;
					case D3D_CT_TBUFFER:
						return IGAEnum::EShaderBufferType_TBuffer;
					default:
						assert(0);
						return IGAEnum::EShaderBufferType_CBuffer;
					}
				}
				static IGAEnum::EShaderVariableClass mapping(D3D_SHADER_VARIABLE_CLASS cls)
				{
					switch(cls)
					{
					case D3D_SVC_SCALAR:
						return IGAEnum::EShaderVariableClass_SCALAR;
					case D3D_SVC_VECTOR:
						return IGAEnum::EShaderVariableClass_VECTOR;
					default:
						assert(0);
						return IGAEnum::EShaderVariableClass_VECTOR;
					}
				}
				static IGAEnum::EShaderVariableType mapping(D3D_SHADER_VARIABLE_TYPE type)
				{
					switch(type)
					{
					case D3D_SVT_BOOL:
						return IGAEnum::EShaderVariableType_BOOL;
					case D3D_SVT_BUFFER:
						return IGAEnum::EShaderVariableType_BUFFER;
					case D3D_SVT_FLOAT:
						return IGAEnum::EShaderVariableType_FLOAT;
					case D3D_SVT_INT:
						return IGAEnum::EShaderVariableType_UINT;
					case D3D_SVT_UINT8:
						return IGAEnum::EShaderVariableType_UINT8;
					default:
						assert(0);
						return IGAEnum::EShaderVariableType_VOID;
					}
				}
			};
		}
	}
}