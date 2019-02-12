#pragma once
#include "ICoreGPUEnum.h"
#include "ICoreGPUResource.h"
namespace NSDevilX
{
	namespace NSCore
	{
		class IGPUStruct
		{
		public:
			struct SGISamplerDesc
			{
				UInt32 Count;
				UInt32 Quality;
			};
			struct SHeapProperties
			{
				IGPUEnum::EHeapType         Type;
				IGPUEnum::ECPUPageProperty CPUPageProperty;
				IGPUEnum::EMemoryPool       MemoryPoolPreference;
				UInt32                    CreationNodeMask;
				UInt32                    VisibleNodeMask;
			};
			struct SHeapDesc
			{
				UInt64                SizeInBytes;
				SHeapProperties Properties;
				UInt64                Alignment;
				IGPUEnum::EHeapFlag      Flags;
			};
			struct SResourceDesc
			{
				IGPUEnum::EResourceDimension Dimension;
				UInt64                   Alignment;
				UInt64                   Width;
				UInt32                     Height;
				UInt16                   DepthOrArraySize;
				UInt16                   MipLevels;
				IGPUEnum::EGIFormat              Format;
				SGISamplerDesc         SampleDesc;
				IGPUEnum::ETextureLayout     Layout;
				IGPUEnum::EResourceFlag     Flags;
			};
			struct SDepthStencilValue
			{
				Float Depth;
				UInt8 Stencil;
			};
			struct SClearValue
			{
				IGPUEnum::EGIFormat Format;
				union
				{
					Float                     Color[4];
					SDepthStencilValue DepthStencil;
				};
			};
			struct SBufferDesc
			{
				UInt32        ByteWidth;
				IGPUEnum::EUsage Usage;
				UInt32        BindFlags;
				UInt32        CPUAccessFlags;
				UInt32        MiscFlags;
				UInt32        StructureByteStride;
			};
			struct STexture1DDesc
			{
				UInt32        Width;
				UInt32        MipLevels;
				UInt32        ArraySize;
				IGPUEnum::EGIFormat Format;
				IGPUEnum::EUsage Usage;
				UInt32        BindFlags;
				UInt32        CPUAccessFlags;
				UInt32        MiscFlags;
			};
			struct STexture2DDesc
			{
				UInt32             Width;
				UInt32             Height;
				UInt32             MipLevels;
				UInt32             ArraySize;
				IGPUEnum::EGIFormat      Format;
				SGISamplerDesc SampleDesc;
				IGPUEnum::EUsage      Usage;
				UInt32             BindFlags;
				UInt32             CPUAccessFlags;
				UInt32             MiscFlags;
			};
			struct STexture3DDesc
			{
				UInt32        Width;
				UInt32        Height;
				UInt32        Depth;
				UInt32        MipLevels;
				IGPUEnum::EGIFormat Format;
				IGPUEnum::EUsage Usage;
				UInt32        BindFlags;
				UInt32        CPUAccessFlags;
				UInt32        MiscFlags;
			};
			struct SSubResourceData
			{
				ConstVoidPtr pSysMem;
				UInt32       SysMemPitch;
				UInt32       SysMemSlicePitch;
			};
			struct STex1DDSV
			{
				UInt32 MipSlice;
			};
			struct STex1DArrayDSV
			{
				UInt32 MipSlice;
				UInt32 FirstArraySlice;
				UInt32 ArraySize;
			};
			struct STex2DDsv
			{
				UInt32 MipSlice;
			};
			struct STex2DArrayDsv
			{
				UInt32 MipSlice;
				UInt32 FirstArraySlice;
				UInt32 ArraySize;
			};
			struct STex2DMSDsv
			{
				UInt32 UnusedField_NothingToDefine;
			};
			struct STex2DMSArrayDsv
			{
				UInt32 FirstArraySlice;
				UInt32 ArraySize;
			};
			struct SDepthStencilViewDesc
			{
				IGPUEnum::EGIFormat         Format;
				IGPUEnum::EDSVDimension ViewDimension;
				IGPUEnum::EDSVFlag     Flags;
				union
				{
					STex1DDSV         Texture1D;
					STex1DArrayDSV   Texture1DArray;
					STex2DDsv         Texture2D;
					STex2DArrayDsv   Texture2DArray;
					STex2DMSDsv       Texture2DMS;
					STex2DMSArrayDsv Texture2DMSArray;
				};
			};
			struct SIndexBufferView
			{
				UInt64 BufferLocation;
				UInt32                      SizeInBytes;
				IGPUEnum::EGIFormat               Format;
			};
			struct SVertexBufferView
			{
				UInt64 BufferLocation;
				UInt32                      SizeInBytes;
				UInt32                      StrideInBytes;
			};
			struct SViewport
			{
				Float TopLeftX;
				Float TopLeftY;
				Float Width;
				Float Height;
				Float MinDepth;
				Float MaxDepth;
			};
			struct SRenderTargetBlendDesc
			{
				Bool BlendEnable;
				Bool LogicOpEnable;
				IGPUEnum::EBlend SrcBlend;
				IGPUEnum::EBlend DestBlend;
				IGPUEnum::EBlendOp BlendOp;
				IGPUEnum::EBlend SrcBlendAlpha;
				IGPUEnum::EBlend DestBlendAlpha;
				IGPUEnum::EBlendOp BlendOpAlpha;
				IGPUEnum::ELogicOp LogicOp;
				UInt8 RenderTargetWriteMask;
			};
			struct SBlendDesc
			{
				Bool AlphaToCoverageEnable;
				Bool IndependentBlendEnable;
				SRenderTargetBlendDesc RenderTarget[8];
			};
			struct SShaderByteCode
			{
				ConstVoidPtr pShaderBytecode;
				SizeT     BytecodeLength;
			};
			struct SSoDeclarationEntry
			{
				UInt32 Stream;
				ConstCharPtr SemanticName;
				UInt32 SemanticIndex;
				Byte StartComponent;
				Byte ComponentCount;
				Byte OutputSlot;
			};
			struct SStreamOutputDesc
			{
				const SSoDeclarationEntry *pSODeclaration;
				UInt32 NumEntries;
				const UInt32 *pBufferStrides;
				UInt32 NumStrides;
				UInt32 RasterizedStream;
			};
			struct SRasterizerDesc
			{
				IGPUEnum::EFillMode                       FillMode;
				IGPUEnum::ECullMode                       CullMode;
				Bool                                  FrontCounterClockwise;
				Int32                                   DepthBias;
				Float                                 DepthBiasClamp;
				Float                                 SlopeScaledDepthBias;
				Bool                                  DepthClipEnable;
				Bool                                  MultisampleEnable;
				Bool                                  AntialiasedLineEnable;
				UInt32                                  ForcedSampleCount;
				IGPUEnum::EConservativeRasterizationMode ConservativeRaster;
			};
			struct SDepthStencilOpDesc
			{
				IGPUEnum::EStencilOp StencilFailOp;
				IGPUEnum::EStencilOp StencilDepthFailOp;
				IGPUEnum::EStencilOp StencilPassOp;
				IGPUEnum::EComparisonFunc StencilFunc;
			};
			struct SDepthStencilDesc
			{
				Bool                       DepthEnable;
				IGPUEnum::EDepthWriteMask     DepthWriteMask;
				IGPUEnum::EComparisonFunc      DepthFunc;
				Bool                       StencilEnable;
				UInt8                      StencilReadMask;
				UInt8                      StencilWriteMask;
				SDepthStencilOpDesc FrontFace;
				SDepthStencilOpDesc BackFace;
			};
			struct SInputElementDesc
			{
				ConstCharPtr SemanticName;
				UInt32 SemanticIndex;
				IGPUEnum::EGIFormat Format;
				UInt32 InputSlot;
				UInt32 AlignedByteOffset;
				IGPUEnum::EInputClassification InputSlotClass;
				UInt32 InstanceDataStepRate;
			};
			struct SInputLayoutDesc
			{
				const SInputElementDesc *pInputElementDescs;
				UInt32 NumElements;
			};
			struct SSamplerDesc
			{
				UInt32 Count;
				UInt32 Quality;
			};
			struct SCachedPipelineState
			{
				ConstVoidPtr pCachedBlob;
				SizeT CachedBlobSizeInBytes;
			};
		};
	}
}