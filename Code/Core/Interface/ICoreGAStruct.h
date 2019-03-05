#pragma once
#include "ICoreGAEnum.h"
#include "ICoreGAResource.h"
namespace NSDevilX
{
	namespace NSCore
	{
		class IGAStruct
		{
		public:
			struct SGISamplerDesc
			{
				UInt32 Count;
				UInt32 Quality;
			};
			struct SHeapProperties
			{
				IGAEnum::EHeapType         Type;
				IGAEnum::ECPUPageProperty CPUPageProperty;
				IGAEnum::EMemoryPool       MemoryPoolPreference;
				UInt32                    CreationNodeMask;
				UInt32                    VisibleNodeMask;
			};
			struct SHeapDesc
			{
				UInt64                SizeInBytes;
				SHeapProperties Properties;
				UInt64                Alignment;
				IGAEnum::EHeapFlag      Flags;
			};
			struct SResourceDesc
			{
				IGAEnum::EResourceDimension Dimension;
				UInt64                   Alignment;
				UInt64                   Width;
				UInt32                     Height;
				UInt16                   DepthOrArraySize;
				UInt16                   MipLevels;
				IGAEnum::EGIFormat              Format;
				SGISamplerDesc         SampleDesc;
				IGAEnum::ETextureLayout     Layout;
				IGAEnum::EResourceFlag     Flags;
			};
			struct SDepthStencilValue
			{
				Float Depth;
				UInt8 Stencil;
			};
			struct SClearValue
			{
				IGAEnum::EGIFormat Format;
				union
				{
					Float                     Color[4];
					SDepthStencilValue DepthStencil;
				};
			};
			struct SBufferDesc
			{
				UInt32        ByteWidth;
				IGAEnum::EUsage Usage;
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
				IGAEnum::EGIFormat Format;
				IGAEnum::EUsage Usage;
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
				IGAEnum::EGIFormat      Format;
				SGISamplerDesc SampleDesc;
				IGAEnum::EUsage      Usage;
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
				IGAEnum::EGIFormat Format;
				IGAEnum::EUsage Usage;
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
				IGAEnum::EGIFormat         Format;
				IGAEnum::EDSVDimension ViewDimension;
				IGAEnum::EDSVFlag     Flags;
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
				IGAEnum::EGIFormat               Format;
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
				IGAEnum::EBlend SrcBlend;
				IGAEnum::EBlend DestBlend;
				IGAEnum::EBlendOp BlendOp;
				IGAEnum::EBlend SrcBlendAlpha;
				IGAEnum::EBlend DestBlendAlpha;
				IGAEnum::EBlendOp BlendOpAlpha;
				IGAEnum::ELogicOp LogicOp;
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
				IGAEnum::EFillMode                       FillMode;
				IGAEnum::ECullMode                       CullMode;
				Bool                                  FrontCounterClockwise;
				Int32                                   DepthBias;
				Float                                 DepthBiasClamp;
				Float                                 SlopeScaledDepthBias;
				Bool                                  DepthClipEnable;
				Bool                                  MultisampleEnable;
				Bool                                  AntialiasedLineEnable;
				UInt32                                  ForcedSampleCount;
				IGAEnum::EConservativeRasterizationMode ConservativeRaster;
			};
			struct SDepthStencilOpDesc
			{
				IGAEnum::EStencilOp StencilFailOp;
				IGAEnum::EStencilOp StencilDepthFailOp;
				IGAEnum::EStencilOp StencilPassOp;
				IGAEnum::EComparisonFunc StencilFunc;
			};
			struct SDepthStencilDesc
			{
				Bool                       DepthEnable;
				IGAEnum::EDepthWriteMask     DepthWriteMask;
				IGAEnum::EComparisonFunc      DepthFunc;
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
				IGAEnum::EGIFormat Format;
				UInt32 InputSlot;
				UInt32 AlignedByteOffset;
				IGAEnum::EInputClassification InputSlotClass;
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
			struct SBufferSRV
			{
				UInt64 FirstElement;
				UInt32 NumElements;
				UInt32 StructureByteStride;
				IGAEnum::EBufferSRVFlag Flags;
			};
			struct STex1DSRV
			{
				UInt32 MostDetailedMip;
				UInt32 MipLevels;
				Float ResourceMinLODClamp;
			};
			struct STex1DArraySRV
			{
				UInt32 MostDetailedMip;
				UInt32 MipLevels;
				UInt32 FirstArraySlice;
				UInt32 ArraySize;
				Float ResourceMinLODClamp;
			};
			struct STex2DSRV
			{
				UInt32 MostDetailedMip;
				UInt32 MipLevels;
				UInt32 PlaneSlice;
				Float ResourceMinLODClamp;
			};
			struct STex2DArraySRV
			{
				UInt32 MostDetailedMip;
				UInt32 MipLevels;
				UInt32 FirstArraySlice;
				UInt32 ArraySize;
				UInt32 PlaneSlice;
				Float ResourceMinLODClamp;
			};
			struct STex2DMSSRV
			{
				UInt32 UnusedField_NothingToDefine;
			};
			struct STex2DMSArraySRV
			{
				UInt32 FirstArraySlice;
				UInt32 ArraySize;
			};
			struct STex3DSRV
			{
				UInt32 MostDetailedMip;
				UInt32 MipLevels;
				Float ResourceMinLODClamp;
			};
			struct STexCubeSRV
			{
				UInt32 MostDetailedMip;
				UInt32 MipLevels;
				Float ResourceMinLODClamp;
			};
			struct STexCubeArraySRV
			{
				UInt32 MostDetailedMip;
				UInt32 MipLevels;
				UInt32 First2DArrayFace;
				UInt32 NumCubes;
				Float ResourceMinLODClamp;
			};
			struct SRaytracingAccelerationStructureSRV
			{
				UInt64 Location;
			};
			struct SShaderResourceViewDesc
			{
				IGAEnum::EGIFormat         Format;
				IGAEnum::ESRVDimension ViewDimension;
				UInt32                Shader4ComponentMapping;
				union
				{
					SBufferSRV                            Buffer;
					STex1DSRV                             Texture1D;
					STex1DArraySRV                       Texture1DArray;
					STex2DSRV                             Texture2D;
					STex2DArraySRV                       Texture2DArray;
					STex2DMSSRV                           Texture2DMS;
					STex2DMSArraySRV                     Texture2DMSArray;
					STex3DSRV                             Texture3D;
					STexCubeSRV                           TextureCube;
					STexCubeArraySRV                     TextureCubeArray;
					SRaytracingAccelerationStructureSRV RaytracingAccelerationStructure;
				};
			};
		};
	}
}