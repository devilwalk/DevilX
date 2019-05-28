#pragma once
#include "ICoreGAEnum.h"
#include "ICoreGAHighLevelResource.h"
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
				EGLNativeWindowType             OutputWindow;
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
				IGAEnum::EBlend SrcBlend;
				IGAEnum::EBlend DestBlend;
				IGAEnum::EBlendOp BlendOp;
				IGAEnum::EBlend SrcBlendAlpha;
				IGAEnum::EBlend DestBlendAlpha;
				IGAEnum::EBlendOp BlendOpAlpha;
				UInt8 RenderTargetWriteMask;
			};
			struct SRenderTargetBlendDesc1
				:public SRenderTargetBlendDesc
			{
				Bool LogicOpEnable;
				IGAEnum::ELogicOp LogicOp;
			};
			struct SBlendDesc
			{
				Bool AlphaToCoverageEnable;
				Bool IndependentBlendEnable;
				SRenderTargetBlendDesc RenderTarget[8];
			};
			struct SBlendDesc1
			{
				Bool AlphaToCoverageEnable;
				Bool IndependentBlendEnable;
				SRenderTargetBlendDesc1 RenderTarget[8];
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
			};
			struct SRasterizerDesc1
				:public SRasterizerDesc
			{
				UInt32 ForcedSampleCount;
			};
			struct SRasterizerDesc2
				:public SRasterizerDesc1
			{
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
			class IGAVertexBuffer;
			struct SVAOElementDesc
				:public SInputElementDesc
			{
				IGAVertexBuffer* mVertexBuffer;
				UInt32 mVertexBufferOffsetInBytes;
			};
			struct SDrawParameter_GL
			{
				UInt32 mVertexCount;
				UInt32 mInstanceCount;
				UInt32 mFirstVertex;
				UInt32 mBaseInstances;
			};
			struct SDrawIndexedParameter_GL
			{
				UInt32 mIndexCount;
				UInt32 mInstanceCount;
				UInt32 mFirstIndex;
				UInt32 mBaseVertex;
				UInt32 mBaseInstances;
			};
			struct SHeapDesc
			{
				UInt64 SizeInBytes;
				IGAEnum::EHeapType Properties;
				UInt64 Alignment;
				IGAEnum::EHeapFlags Flags;
			};
		};
	}
}