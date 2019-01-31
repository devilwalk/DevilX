#pragma once
namespace NSDevilX
{
	namespace NSCore
	{
		class IGPUEnum
		{
		public:
			enum EGIFormat
			{
				EGIFormat_UNKNOWN,
				EGIFormat_R32G32B32A32_TYPELESS,
				EGIFormat_R32G32B32A32_FLOAT,
				EGIFormat_R32G32B32A32_UINT,
				EGIFormat_R32G32B32A32_SINT,
				EGIFormat_R32G32B32_TYPELESS,
				EGIFormat_R32G32B32_FLOAT,
				EGIFormat_R32G32B32_UINT,
				EGIFormat_R32G32B32_SINT,
				EGIFormat_R16G16B16A16_TYPELESS,
				EGIFormat_R16G16B16A16_FLOAT,
				EGIFormat_R16G16B16A16_UNORM,
				EGIFormat_R16G16B16A16_UINT,
				EGIFormat_R16G16B16A16_SNORM,
				EGIFormat_R16G16B16A16_SINT,
				EGIFormat_R32G32_TYPELESS,
				EGIFormat_R32G32_FLOAT,
				EGIFormat_R32G32_UINT,
				EGIFormat_R32G32_SINT,
				EGIFormat_R32G8X24_TYPELESS,
				EGIFormat_D32_FLOAT_S8X24_UINT,
				EGIFormat_R32_FLOAT_X8X24_TYPELESS,
				EGIFormat_X32_TYPELESS_G8X24_UINT,
				EGIFormat_R10G10B10A2_TYPELESS,
				EGIFormat_R10G10B10A2_UNORM,
				EGIFormat_R10G10B10A2_UINT,
				EGIFormat_R11G11B10_FLOAT,
				EGIFormat_R8G8B8A8_TYPELESS,
				EGIFormat_R8G8B8A8_UNORM,
				EGIFormat_R8G8B8A8_UNORM_SRGB,
				EGIFormat_R8G8B8A8_UINT,
				EGIFormat_R8G8B8A8_SNORM,
				EGIFormat_R8G8B8A8_SINT,
				EGIFormat_R16G16_TYPELESS,
				EGIFormat_R16G16_FLOAT,
				EGIFormat_R16G16_UNORM,
				EGIFormat_R16G16_UINT,
				EGIFormat_R16G16_SNORM,
				EGIFormat_R16G16_SINT,
				EGIFormat_R32_TYPELESS,
				EGIFormat_D32_FLOAT,
				EGIFormat_R32_FLOAT,
				EGIFormat_R32_UINT,
				EGIFormat_R32_SINT,
				EGIFormat_R24G8_TYPELESS,
				EGIFormat_D24_UNORM_S8_UINT,
				EGIFormat_R24_UNORM_X8_TYPELESS,
				EGIFormat_X24_TYPELESS_G8_UINT,
				EGIFormat_R8G8_TYPELESS,
				EGIFormat_R8G8_UNORM,
				EGIFormat_R8G8_UINT,
				EGIFormat_R8G8_SNORM,
				EGIFormat_R8G8_SINT,
				EGIFormat_R16_TYPELESS,
				EGIFormat_R16_FLOAT,
				EGIFormat_D16_UNORM,
				EGIFormat_R16_UNORM,
				EGIFormat_R16_UINT,
				EGIFormat_R16_SNORM,
				EGIFormat_R16_SINT,
				EGIFormat_R8_TYPELESS,
				EGIFormat_R8_UNORM,
				EGIFormat_R8_UINT,
				EGIFormat_R8_SNORM,
				EGIFormat_R8_SINT,
				EGIFormat_A8_UNORM,
				EGIFormat_R1_UNORM,
				EGIFormat_R9G9B9E5_SHAREDEXP,
				EGIFormat_R8G8_B8G8_UNORM,
				EGIFormat_G8R8_G8B8_UNORM,
				EGIFormat_BC1_TYPELESS,
				EGIFormat_BC1_UNORM,
				EGIFormat_BC1_UNORM_SRGB,
				EGIFormat_BC2_TYPELESS,
				EGIFormat_BC2_UNORM,
				EGIFormat_BC2_UNORM_SRGB,
				EGIFormat_BC3_TYPELESS,
				EGIFormat_BC3_UNORM,
				EGIFormat_BC3_UNORM_SRGB,
				EGIFormat_BC4_TYPELESS,
				EGIFormat_BC4_UNORM,
				EGIFormat_BC4_SNORM,
				EGIFormat_BC5_TYPELESS,
				EGIFormat_BC5_UNORM,
				EGIFormat_BC5_SNORM,
				EGIFormat_B5G6R5_UNORM,
				EGIFormat_B5G5R5A1_UNORM,
				EGIFormat_B8G8R8A8_UNORM,
				EGIFormat_B8G8R8X8_UNORM,
				EGIFormat_R10G10B10_XR_BIAS_A2_UNORM,
				EGIFormat_B8G8R8A8_TYPELESS,
				EGIFormat_B8G8R8A8_UNORM_SRGB,
				EGIFormat_B8G8R8X8_TYPELESS,
				EGIFormat_B8G8R8X8_UNORM_SRGB,
				EGIFormat_BC6H_TYPELESS,
				EGIFormat_BC6H_UF16,
				EGIFormat_BC6H_SF16,
				EGIFormat_BC7_TYPELESS,
				EGIFormat_BC7_UNORM,
				EGIFormat_BC7_UNORM_SRGB,
				EGIFormat_AYUV,
				EGIFormat_Y410,
				EGIFormat_Y416,
				EGIFormat_NV12,
				EGIFormat_P010,
				EGIFormat_P016,
				EGIFormat_420_OPAQUE,
				EGIFormat_YUY2,
				EGIFormat_Y210,
				EGIFormat_Y216,
				EGIFormat_NV11,
				EGIFormat_AI44,
				EGIFormat_IA44,
				EGIFormat_P8,
				EGIFormat_A8P8,
				EGIFormat_B4G4R4A4_UNORM,
				EGIFormat_P208,
				EGIFormat_V208,
				EGIFormat_V408,
				EGIFormat_FORCE_UINT
			};
			enum EPrimitiveTopology
			{
				EPrimitiveTopology_UNDEFINED,
				EPrimitiveTopology_POINTLIST,
				EPrimitiveTopology_LINELIST,
				EPrimitiveTopology_LINESTRIP,
				EPrimitiveTopology_TRIANGLELIST,
				EPrimitiveTopology_TRIANGLESTRIP,
				EPrimitiveTopology_LINELIST_ADJ,
				EPrimitiveTopology_LINESTRIP_ADJ,
				EPrimitiveTopology_TRIANGLELIST_ADJ,
				EPrimitiveTopology_TRIANGLESTRIP_ADJ,
				EPrimitiveTopology_1_CONTROL_POINT_PATCHLIST,
				EPrimitiveTopology_2_CONTROL_POINT_PATCHLIST,
				EPrimitiveTopology_3_CONTROL_POINT_PATCHLIST,
				EPrimitiveTopology_4_CONTROL_POINT_PATCHLIST,
				EPrimitiveTopology_5_CONTROL_POINT_PATCHLIST,
				EPrimitiveTopology_6_CONTROL_POINT_PATCHLIST,
				EPrimitiveTopology_7_CONTROL_POINT_PATCHLIST,
				EPrimitiveTopology_8_CONTROL_POINT_PATCHLIST,
				EPrimitiveTopology_9_CONTROL_POINT_PATCHLIST,
				EPrimitiveTopology_10_CONTROL_POINT_PATCHLIST,
				EPrimitiveTopology_11_CONTROL_POINT_PATCHLIST,
				EPrimitiveTopology_12_CONTROL_POINT_PATCHLIST,
				EPrimitiveTopology_13_CONTROL_POINT_PATCHLIST,
				EPrimitiveTopology_14_CONTROL_POINT_PATCHLIST,
				EPrimitiveTopology_15_CONTROL_POINT_PATCHLIST,
				EPrimitiveTopology_16_CONTROL_POINT_PATCHLIST,
				EPrimitiveTopology_17_CONTROL_POINT_PATCHLIST,
				EPrimitiveTopology_18_CONTROL_POINT_PATCHLIST,
				EPrimitiveTopology_19_CONTROL_POINT_PATCHLIST,
				EPrimitiveTopology_20_CONTROL_POINT_PATCHLIST,
				EPrimitiveTopology_21_CONTROL_POINT_PATCHLIST,
				EPrimitiveTopology_22_CONTROL_POINT_PATCHLIST,
				EPrimitiveTopology_23_CONTROL_POINT_PATCHLIST,
				EPrimitiveTopology_24_CONTROL_POINT_PATCHLIST,
				EPrimitiveTopology_25_CONTROL_POINT_PATCHLIST,
				EPrimitiveTopology_26_CONTROL_POINT_PATCHLIST,
				EPrimitiveTopology_27_CONTROL_POINT_PATCHLIST,
				EPrimitiveTopology_28_CONTROL_POINT_PATCHLIST,
				EPrimitiveTopology_29_CONTROL_POINT_PATCHLIST,
				EPrimitiveTopology_30_CONTROL_POINT_PATCHLIST,
				EPrimitiveTopology_31_CONTROL_POINT_PATCHLIST,
				EPrimitiveTopology_32_CONTROL_POINT_PATCHLIST
			};
			enum EUsage
			{
				EUsage_DEFAULT,
				EUsage_IMMUTABLE,
				EUsage_DYNAMIC,
				EUsage_STAGING
			};
			enum EDSVDimension
			{
				EDSVDimension_UNKNOWN,
				EDSVDimension_TEXTURE1D,
				EDSVDimension_TEXTURE1DARRAY,
				EDSVDimension_TEXTURE2D,
				EDSVDimension_TEXTURE2DARRAY,
				EDSVDimension_TEXTURE2DMS,
				EDSVDimension_TEXTURE2DMSARRAY
			};
			enum EDSVFlag
			{
				EDSVFlag_NONE,
				EDSVFlag_READ_ONLY_DEPTH,
				EDSVFlag_READ_ONLY_STENCIL
			};
			enum EClearFlag
			{
				EClearFlag_DEPTH,
				EClearFlag_STENCIL
			};
			enum ECommandListType
			{
				ECommandListType_DIRECT,
				ECommandListType_BUNDLE,
				ECommandListType_COMPUTE,
				ECommandListType_COPY,
				ECommandListType_VIDEO_DECODE,
				ECommandListType_VIDEO_PROCESS
			};
			enum EHeapType
			{
				EHeapType_DEFAULT,
				EHeapType_UPLOAD,
				EHeapType_READBACK,
				EHeapType_CUSTOM
			};
			enum ECPUPageProperty
			{
				ECPUPageProperty_UNKNOWN,
				ECPUPageProperty_NOT_AVAILABLE,
				ECPUPageProperty_WRITE_COMBINE,
				ECPUPageProperty_WRITE_BACK
			};
			enum EMemoryPool
			{
				EMemoryPool_UNKNOWN,
				EMemoryPool_L0,
				EMemoryPool_L1
			};
			enum EBlend
			{
				EBlend_ZERO=1,
				EBlend_ONE=2,
				EBlend_SRC_COLOR=3,
				EBlend_INV_SRC_COLOR=4,
				EBlend_SRC_ALPHA=5,
				EBlend_INV_SRC_ALPHA=6,
				EBlend_DEST_ALPHA=7,
				EBlend_INV_DEST_ALPHA=8,
				EBlend_DEST_COLOR=9,
				EBlend_INV_DEST_COLOR=10,
				EBlend_SRC_ALPHA_SAT=11,
				EBlend_BLEND_FACTOR=14,
				EBlend_INV_BLEND_FACTOR=15,
				EBlend_SRC1_COLOR=16,
				EBlend_INV_SRC1_COLOR=17,
				EBlend_SRC1_ALPHA=18,
				EBlend_INV_SRC1_ALPHA=19
			};
			enum EBlendOp
			{
				EBlendOp_ADD=1,
				EBlendOp_SUBTRACT=2,
				EBlendOp_REV_SUBTRACT=3,
				EBlendOp_MIN=4,
				EBlendOp_MAX=5
			};
			enum ELogicOp
			{
				ELogicOp_CLEAR=0,
				ELogicOp_SET=(ELogicOp_CLEAR+1),
				ELogicOp_COPY=(ELogicOp_SET+1),
				ELogicOp_COPY_INVERTED=(ELogicOp_COPY+1),
				ELogicOp_NOOP=(ELogicOp_COPY_INVERTED+1),
				ELogicOp_INVERT=(ELogicOp_NOOP+1),
				ELogicOp_AND=(ELogicOp_INVERT+1),
				ELogicOp_NAND=(ELogicOp_AND+1),
				ELogicOp_OR=(ELogicOp_NAND+1),
				ELogicOp_NOR=(ELogicOp_OR+1),
				ELogicOp_XOR=(ELogicOp_NOR+1),
				ELogicOp_EQUIV=(ELogicOp_XOR+1),
				ELogicOp_AND_REVERSE=(ELogicOp_EQUIV+1),
				ELogicOp_AND_INVERTED=(ELogicOp_AND_REVERSE+1),
				ELogicOp_OR_REVERSE=(ELogicOp_AND_INVERTED+1),
				ELogicOp_OR_INVERTED=(ELogicOp_OR_REVERSE+1)
			};
			enum EFillMode
			{
				EFillMode_WIREFRAME=2,
				EFillMode_SOLID=3
			};
			enum ECullMode
			{
				ECullMode_NONE=1,
				ECullMode_FRONT=2,
				ECullMode_BACK=3
			};
			enum EConservativeRasterizationMode
			{
				EConservativeRasterizationMode_OFF=0,
				EConservativeRasterizationMode_ON=1
			};
			enum EDepthWriteMask
			{
				EDepthWriteMask_ZERO=0,
				EDepthWriteMask_ALL=1
			};
			enum EComparisonFunc
			{
				EComparisonFunc_NEVER=1,
				EComparisonFunc_LESS=2,
				EComparisonFunc_EQUAL=3,
				EComparisonFunc_LESS_EQUAL=4,
				EComparisonFunc_GREATER=5,
				EComparisonFunc_NOT_EQUAL=6,
				EComparisonFunc_GREATER_EQUAL=7,
				EComparisonFunc_ALWAYS=8
			};
			enum EStencilOp
			{
				EStencilOp_KEEP=1,
				EStencilOp_ZERO=2,
				EStencilOp_REPLACE=3,
				EStencilOp_INCR_SAT=4,
				EStencilOp_DECR_SAT=5,
				EStencilOp_INVERT=6,
				EStencilOp_INCR=7,
				EStencilOp_DECR=8
			};
			enum EInputClassification
			{
				EInputClassification_PER_VERTEX_DATA=0,
				EInputClassification_PER_INSTANCE_DATA=1
			};
			enum EIndexBufferStripCutValue
			{
				EIndexBufferStripCutValue_DISABLED=0,
				EIndexBufferStripCutValue_0xFFFF=1,
				EIndexBufferStripCutValue_0xFFFFFFFF=2
			};
			enum EPrimitiveTopologyType
			{
				EPrimitiveTopologyType_UNDEFINED=0,
				EPrimitiveTopologyType_POINT=1,
				EPrimitiveTopologyType_LINE=2,
				EPrimitiveTopologyType_TRIANGLE=3,
				EPrimitiveTopologyType_PATCH=4
			};
			enum EPipelineStateFlag
			{
				EPipelineStateFlag_NONE=0,
				EPipelineStateFlag_TOOL_DEBUG=0x1
			};
		};
	}
}