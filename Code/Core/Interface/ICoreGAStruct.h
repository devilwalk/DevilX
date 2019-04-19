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
			struct SGIModeDesc
			{
				UInt32 Width;
				UInt32 Height;
				UInt32 RefreshRate;
				IGAEnum::EGIFormat Format;
			};
			struct SGISamplerDesc
			{
				UInt32 Count;
				UInt32 Quality;
			};
			struct SGISwapChainDesc
			{
				SGIModeDesc   BufferDesc;
				SGISamplerDesc SampleDesc;
				UInt32       BufferUsage;
				VoidPtr             OutputWindow;
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
			struct SSubResourceData
			{
				ConstVoidPtr pSysMem;
				UInt32       SysMemPitch;
				UInt32       SysMemSlicePitch;
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
				IGAEnum::EFillMode FillMode;
				IGAEnum::ECullMode CullMode;
				Bool FrontCounterClockwise;
				Int32 DepthBias;
				Float DepthBiasClamp;
				Float SlopeScaledDepthBias;
				Bool DepthClipEnable;
				Bool ScissorEnable;
				Bool MultisampleEnable;
				Bool AntialiasedLineEnable;
				UInt32 ForcedSampleCount;
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
			struct SSamplerDesc
			{
				IGAEnum::EFilter Filter;
				IGAEnum::ETextureAddressMode AddressU;
				IGAEnum::ETextureAddressMode AddressV;
				IGAEnum::ETextureAddressMode AddressW;
				Float MipLODBias;
				UInt32 MaxAnisotropy;
				IGAEnum::EComparisonFunc ComparisonFunc;
				Float BorderColor[4];
				Float MinLOD;
				Float MaxLOD;
			};
			struct SInputElementDesc
			{
				ConstCharPtr SemanticName;
				UInt32 SemanticIndex;
				IGAEnum::EGIFormat Format;
				UInt32 InputSlot;
				UInt32 AlignedByteOffset;
				UInt32 InstanceDataStepRate;
			};
			struct SInputLayoutDesc
			{
				const SInputElementDesc *pInputElementDescs;
				UInt32 NumElements;
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
			struct SShaderDesc
			{
				UInt32                             ConstantBuffers;
				UInt32                             BoundResources;
				UInt32                             InputParameters;
				UInt32                             OutputParameters;
			};
			struct SShaderSignatureParameterDesc
			{
				LPCSTR                      SemanticName;
				UInt32                        SemanticIndex;
				UInt32                        Register;
				IGAEnum::ERegisterComponentType ComponentType;
				UInt32                        Stream;
			};
			struct SShaderBufferDesc
			{
				LPCSTR           Name;
				IGAEnum::EShaderBufferType Type;
				UInt32             Variables;
				UInt32             Size;
			};
			struct SShaderVariableDesc
			{
				LPCSTR Name;
				UInt32   StartOffset;
				UInt32   Size;
				UInt32   StartTexture;
				UInt32   TextureSize;
				UInt32   StartSampler;
				UInt32   SamplerSize;
				IGAEnum::EShaderVariableClass Class;
				IGAEnum::EShaderVariableType Type;
			};
		};
	}
}