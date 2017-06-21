#include "Precompiler.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		namespace NSD3D11
		{
			namespace NSInternal
			{
				template<class TInterface,class TDesc>
				TInterface * getState(const TDesc & desc,const TVector<TInterface*> & states)
				{
					TInterface * ret=nullptr;
					TDesc d;
					for(auto state:states)
					{
						state->GetDesc(&d);
						if(memcmp(&d,&desc,sizeof(TDesc))==0)
						{
							ret=state;
							break;
						}
					}
					return ret;
				}
				template<class TInterface,class TDesc>
				TInterface * getState1(const TDesc & desc,const TVector<TInterface*> & states)
				{
					TInterface * ret=nullptr;
					TDesc d;
					for(auto state:states)
					{
						state->GetDesc1(&d);
						if(memcmp(&d,&desc,sizeof(TDesc))==0)
						{
							ret=state;
							break;
						}
					}
					return ret;
				}
			}
		}
	}
}
using namespace NSDevilX;
using namespace NSRenderSystem;
using namespace NSD3D11;
ISystem * NSDevilX::NSRenderSystem::getSystem()
{
	if(!CSystemImp::getSingletonPtr())
		DEVILX_NEW CSystemImp;
	return ISystemImp::getSingletonPtr();
}

NSDevilX::NSRenderSystem::NSD3D11::CSystemImp::CSystemImp()
	:CConstantBufferContainer("cbSystem")
	,mRenderTaskThreadPool(nullptr)
	,mShaderCodeManager(nullptr)
	,mFactory(nullptr)
	,mConstantBufferDescriptionManager(nullptr)
	,mShaderModelType(CEnum::EShaderModelType_4_1)
	,mDefinitionShader5(nullptr)
	,mOverlayMaterialManager(nullptr)
{
	DEVILX_NEW ISystemImp();
	mRenderTaskThreadPool=DEVILX_NEW CThreadPool(4);
	mDefaultRasterizerStateDesc.AntialiasedLineEnable=FALSE;
	mDefaultRasterizerStateDesc.CullMode=D3D11_CULL_BACK;
	mDefaultRasterizerStateDesc.DepthBias=0;
	mDefaultRasterizerStateDesc.DepthBiasClamp=0.0f;
	mDefaultRasterizerStateDesc.DepthClipEnable=TRUE;
	mDefaultRasterizerStateDesc.FillMode=D3D11_FILL_SOLID;
	mDefaultRasterizerStateDesc.ForcedSampleCount=0;
	mDefaultRasterizerStateDesc.FrontCounterClockwise=FALSE;
	mDefaultRasterizerStateDesc.MultisampleEnable=FALSE;
	mDefaultRasterizerStateDesc.ScissorEnable=FALSE;
	mDefaultRasterizerStateDesc.SlopeScaledDepthBias=0.0f;
	mDefaultBlendStateDesc.AlphaToCoverageEnable=FALSE;
	mDefaultBlendStateDesc.IndependentBlendEnable=FALSE;
	for(int i=0;i<sizeof(mDefaultBlendStateDesc.RenderTarget)/sizeof(mDefaultBlendStateDesc.RenderTarget[0]);++i)
	{
		mDefaultBlendStateDesc.RenderTarget[i].BlendEnable=FALSE;
		mDefaultBlendStateDesc.RenderTarget[i].BlendOp=D3D11_BLEND_OP_ADD;
		mDefaultBlendStateDesc.RenderTarget[i].BlendOpAlpha=D3D11_BLEND_OP_ADD;
		mDefaultBlendStateDesc.RenderTarget[i].DestBlend=D3D11_BLEND_ZERO;
		mDefaultBlendStateDesc.RenderTarget[i].DestBlendAlpha=D3D11_BLEND_ZERO;
		mDefaultBlendStateDesc.RenderTarget[i].LogicOp=D3D11_LOGIC_OP_NOOP;
		mDefaultBlendStateDesc.RenderTarget[i].LogicOpEnable=FALSE;
		mDefaultBlendStateDesc.RenderTarget[i].RenderTargetWriteMask=D3D11_COLOR_WRITE_ENABLE_ALL;
		mDefaultBlendStateDesc.RenderTarget[i].SrcBlend=D3D11_BLEND_ONE;
		mDefaultBlendStateDesc.RenderTarget[i].SrcBlendAlpha=D3D11_BLEND_ONE;
	}
	mDefaultDepthStencilDesc.BackFace.StencilDepthFailOp=D3D11_STENCIL_OP_KEEP;
	mDefaultDepthStencilDesc.BackFace.StencilFailOp=D3D11_STENCIL_OP_KEEP;
	mDefaultDepthStencilDesc.BackFace.StencilFunc=D3D11_COMPARISON_ALWAYS;
	mDefaultDepthStencilDesc.BackFace.StencilPassOp=D3D11_STENCIL_OP_KEEP;
	mDefaultDepthStencilDesc.DepthEnable=TRUE;
	mDefaultDepthStencilDesc.DepthFunc=D3D11_COMPARISON_LESS;
	mDefaultDepthStencilDesc.DepthWriteMask=D3D11_DEPTH_WRITE_MASK_ALL;
	mDefaultDepthStencilDesc.FrontFace.StencilDepthFailOp=D3D11_STENCIL_OP_KEEP;
	mDefaultDepthStencilDesc.FrontFace.StencilFailOp=D3D11_STENCIL_OP_KEEP;
	mDefaultDepthStencilDesc.FrontFace.StencilFunc=D3D11_COMPARISON_ALWAYS;
	mDefaultDepthStencilDesc.FrontFace.StencilPassOp=D3D11_STENCIL_OP_KEEP;
	mDefaultDepthStencilDesc.StencilEnable=FALSE;
	mDefaultDepthStencilDesc.StencilReadMask=D3D11_DEFAULT_STENCIL_READ_MASK;
	mDefaultDepthStencilDesc.StencilWriteMask=D3D11_DEFAULT_STENCIL_WRITE_MASK;
	mDefaultSamplerDesc.AddressU=D3D11_TEXTURE_ADDRESS_CLAMP;
	mDefaultSamplerDesc.AddressV=D3D11_TEXTURE_ADDRESS_CLAMP;
	mDefaultSamplerDesc.AddressW=D3D11_TEXTURE_ADDRESS_CLAMP;
	for(int i=0;i<4;++i)
		mDefaultSamplerDesc.BorderColor[i]=0.0f;
	mDefaultSamplerDesc.ComparisonFunc=D3D11_COMPARISON_NEVER;
	mDefaultSamplerDesc.Filter=D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	mDefaultSamplerDesc.MaxAnisotropy=16;
	mDefaultSamplerDesc.MaxLOD=FLT_MAX;
	mDefaultSamplerDesc.MinLOD=-FLT_MAX;
	mDefaultSamplerDesc.MipLODBias=0.0f;
	CreateDXGIFactory1(__uuidof(IDXGIFactory1),reinterpret_cast<VoidPtr*>(&mFactory));
	UINT flag=0;
#ifdef DEVILX_DEBUG
	flag|=D3D11_CREATE_DEVICE_DEBUG;
#endif
	D3D_FEATURE_LEVEL feature_levels[]=
	{
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1
	};
	CComPtr<ID3D11Device> dev;
	CComPtr<ID3D11DeviceContext> context;
	D3D11CreateDevice(nullptr,D3D_DRIVER_TYPE_HARDWARE,nullptr,flag,feature_levels,sizeof(feature_levels)/sizeof(feature_levels[0]),D3D11_SDK_VERSION,&dev,&mSupport,&context);
	switch(mSupport)
	{
	case D3D_FEATURE_LEVEL_10_1:mShaderModelType=CEnum::EShaderModelType_4_1;mDefinitionShader4_1=DEVILX_NEW NSHLSL4_1::CDefinitionShader;break;
	case D3D_FEATURE_LEVEL_11_0:
	case D3D_FEATURE_LEVEL_11_1:mShaderModelType=CEnum::EShaderModelType_5;mDefinitionShader5=DEVILX_NEW NSHLSL5::CDefinitionShader;break;
	}
	dev->QueryInterface(__uuidof(ID3D11Device1),reinterpret_cast<VoidPtr*>(&mDevice));
	context->QueryInterface(__uuidof(ID3D11DeviceContext1),reinterpret_cast<VoidPtr*>(&mImmediateContext));
	mDevice->QueryInterface(__uuidof(ID3D11Debug),reinterpret_cast<VoidPtr*>(&mDebug));
	mShaderCodeManager=DEVILX_NEW CShaderCodeManager;
	mConstantBufferDescriptionManager=DEVILX_NEW CConstantBufferDescriptionManager;
	mClearViewportShader=DEVILX_NEW CClearViewportShader();
	mOverlayMaterialManager=DEVILX_NEW COverlayMaterialManager;
	ISystemImp::getSingleton().addListener(static_cast<TMessageReceiver<ISystemImp>*>(this),ISystemImp::EMessage_EndWindowCreate);
	ISystemImp::getSingleton().addListener(static_cast<TMessageReceiver<ISystemImp>*>(this),ISystemImp::EMessage_BeginWindowDestroy);
	ISystemImp::getSingleton().addListener(static_cast<TMessageReceiver<ISystemImp>*>(this),ISystemImp::EMessage_EndSceneCreate);
	ISystemImp::getSingleton().addListener(static_cast<TMessageReceiver<ISystemImp>*>(this),ISystemImp::EMessage_BeginSceneDestroy);
	ISystemImp::getSingleton().addListener(static_cast<TMessageReceiver<ISystemImp>*>(this),ISystemImp::EMessage_EndRenderableSurfaceCreate);
	ISystemImp::getSingleton().addListener(static_cast<TMessageReceiver<ISystemImp>*>(this),ISystemImp::EMessage_BeginRenderableSurfaceDestroy);
	ISystemImp::getSingleton().addListener(static_cast<TMessageReceiver<ISystemImp>*>(this),ISystemImp::EMessage_Update);
	ISystemImp::getSingleton().addListener(static_cast<TMessageReceiver<ISystemImp>*>(this),ISystemImp::EMessage_Destruction);
	static_cast<IResourceManagerImp*>(ISystemImp::getSingleton().queryInterface_IResourceManager())->addListener(static_cast<TMessageReceiver<IResourceManagerImp>*>(this),IResourceManagerImp::EMessage_EndGeometryCreate);
	static_cast<IResourceManagerImp*>(ISystemImp::getSingleton().queryInterface_IResourceManager())->addListener(static_cast<TMessageReceiver<IResourceManagerImp>*>(this),IResourceManagerImp::EMessage_BeginGeometryDestroy);
	static_cast<IResourceManagerImp*>(ISystemImp::getSingleton().queryInterface_IResourceManager())->addListener(static_cast<TMessageReceiver<IResourceManagerImp>*>(this),IResourceManagerImp::EMessage_EndTextureCreate);
	static_cast<IResourceManagerImp*>(ISystemImp::getSingleton().queryInterface_IResourceManager())->addListener(static_cast<TMessageReceiver<IResourceManagerImp>*>(this),IResourceManagerImp::EMessage_BeginTextureDestroy);
	static_cast<IResourceManagerImp*>(ISystemImp::getSingleton().queryInterface_IResourceManager())->addListener(static_cast<TMessageReceiver<IResourceManagerImp>*>(this),IResourceManagerImp::EMessage_VertexBufferCreate);
	static_cast<IResourceManagerImp*>(ISystemImp::getSingleton().queryInterface_IResourceManager())->addListener(static_cast<TMessageReceiver<IResourceManagerImp>*>(this),IResourceManagerImp::EMessage_VertexBufferDestroy);
	static_cast<IResourceManagerImp*>(ISystemImp::getSingleton().queryInterface_IResourceManager())->addListener(static_cast<TMessageReceiver<IResourceManagerImp>*>(this),IResourceManagerImp::EMessage_IndexBufferCreate);
	static_cast<IResourceManagerImp*>(ISystemImp::getSingleton().queryInterface_IResourceManager())->addListener(static_cast<TMessageReceiver<IResourceManagerImp>*>(this),IResourceManagerImp::EMessage_IndexBufferDestroy);
}

NSDevilX::NSRenderSystem::NSD3D11::CSystemImp::~CSystemImp()
{
	DEVILX_DELETE(mRenderTaskThreadPool);
	switch(mSupport)
	{
	case D3D_FEATURE_LEVEL_10_1:mShaderModelType=CEnum::EShaderModelType_4_1;DEVILX_DELETE(mDefinitionShader4_1);break;
	case D3D_FEATURE_LEVEL_11_0:
	case D3D_FEATURE_LEVEL_11_1:mShaderModelType=CEnum::EShaderModelType_5;DEVILX_DELETE(mDefinitionShader5);break;
	}
	DEVILX_DELETE(mShaderCodeManager);
	DEVILX_DELETE(mConstantBufferDescriptionManager);
	DEVILX_DELETE(mClearViewportShader);
	DEVILX_DELETE(mOverlayMaterialManager);
	mRasterizerStates.destroyAll();
	mBlendStates.destroyAll();
	mDepthStencilStates.destroyAll();
	mSamplerStates.destroyAll();
	mInputLayouts.destroyAll();
	mDepthStencils.clear();
	mShaders.destroyAll();
	mWindows.destroyAll();
	mScenes.destroyAll();
	mGeometrys.destroyAll();
	mVertexBuffers.destroyAll();
	mIndexBuffers.destroyAll();
	mTexture2Ds.destroyAll();
	mTransformers.destroyAll();
	DEVILX_DELETE(mConstantBuffer);
	mConstantBuffer=nullptr;
#ifdef DEVILX_DEBUG
	getDebug()->ReportLiveDeviceObjects(D3D11_RLDO_DETAIL);
	getDebug()->Release();
#endif
	auto ref_count=mImmediateContext->Release();
	assert(0==ref_count);
	ref_count=mFactory->Release();
	assert(0==ref_count);
	ref_count=mDevice->Release();
	assert(0==ref_count);
	mInstanceByInternals.clear();
	mInstanceByCOMInternals.clear();
}

CDepthStencil * NSDevilX::NSRenderSystem::NSD3D11::CSystemImp::getFreeDepthStencil(UInt32 width,UInt32 height)
{
	auto key=(width<<16)|height;
	auto & depths=mDepthStencils[key];
	CDepthStencil * depth=nullptr;
	for(auto ds:depths)
	{
		if(!ds->getLocked())
		{
			depth=ds;
			break;
		}
	}
	if(!depth)
	{
		depth=DEVILX_NEW CDepthStencil(width,height);
		depths.push_back(depth);
	}
	return depth;
}

ID3D11InputLayout * NSDevilX::NSRenderSystem::NSD3D11::CSystemImp::getInputLayout(const D3D11_INPUT_ELEMENT_DESC * descs,UINT numElements)
{
	ID3D11InputLayout * ret=nullptr;
	for(auto layout:mInputLayouts)
	{
		if(static_cast<UINT>(layout->mDescs.size())==numElements)
		{
			ret=layout->mInternal;
			for(decltype(numElements) i=0;i<numElements;++i)
			{
				if(0!=memcmp(&layout->mDescs[i],&descs[i],sizeof(D3D11_INPUT_ELEMENT_DESC)))
				{
					ret=nullptr;
					break;
				}
			}
			if(ret)
				break;
		}
	}
	if(nullptr==ret)
	{
		String hlsl="void main(";
		for(decltype(numElements) i=0;i<numElements;++i)
		{
			switch(descs[i].Format)
			{
			case DXGI_FORMAT_R32G32B32A32_FLOAT:
			case DXGI_FORMAT_R8G8B8A8_UNORM:
				hlsl+="float4";
				break;
			case DXGI_FORMAT_R32G32B32_FLOAT:
				hlsl+="float3";
				break;
			case DXGI_FORMAT_R32G32_FLOAT:
				hlsl+="float2";
				break;
			case DXGI_FORMAT_R32_FLOAT:
				hlsl+="float";
				break;
			case DXGI_FORMAT_R32G32B32A32_UINT:
			case DXGI_FORMAT_R8G8B8A8_UINT:
				hlsl+="uint4";
				break;
			case DXGI_FORMAT_R32G32B32_UINT:
				hlsl+="uint3";
				break;
			case DXGI_FORMAT_R32G32_UINT:
				hlsl+="uint2";
				break;
			case DXGI_FORMAT_R32_UINT:
				hlsl+="uint";
				break;
			case DXGI_FORMAT_R32G32B32A32_SINT:
				hlsl+="int4";
				break;
			case DXGI_FORMAT_R32G32B32_SINT:
				hlsl+="int3";
				break;
			case DXGI_FORMAT_R32G32_SINT:
				hlsl+="int2";
				break;
			case DXGI_FORMAT_R32_SINT:
				hlsl+="int";
				break;
			default:
				assert(0);
			}
			hlsl+=" inputParameter"+CStringConverter::toString(i)+":"+descs[i].SemanticName+CStringConverter::toString(descs[i].SemanticIndex)+",";
		}
		hlsl+="out float4 outputParameter:SV_Position){outputParameter=1;}";
		CComPtr<ID3DBlob> code;
		CComPtr<ID3DBlob> error;
		D3DCompile(&hlsl[0],hlsl.size(),"temp",nullptr,nullptr,"main","vs_5_0",D3DCOMPILE_SKIP_VALIDATION|D3DCOMPILE_OPTIMIZATION_LEVEL3,0,&code,&error);
		if(error.p)
		{
			OutputDebugStringA(static_cast<LPCSTR>(error->GetBufferPointer()));
		}
		mDevice->CreateInputLayout(descs,numElements,code->GetBufferPointer(),code->GetBufferSize(),&ret);
		SInputLayout * layout=DEVILX_NEW SInputLayout;
		for(decltype(numElements) i=0;i<numElements;++i)
		{
			layout->mDescs.push_back(descs[i]);
		}
		layout->mInternal=ret;
		mInputLayouts.push_back(layout);
	}
	return ret;
}

ID3D11RasterizerState1 * NSDevilX::NSRenderSystem::NSD3D11::CSystemImp::getRasterizerState(const D3D11_RASTERIZER_DESC1 & desc)
{
	if(0==memcmp(&getDefaultRasterizerStateDescription(),&desc,sizeof(D3D11_RASTERIZER_DESC1)))
		return nullptr;
	ID3D11RasterizerState1 * ret=NSInternal::getState1(desc,mRasterizerStates);
	if(nullptr==ret)
	{
		getDevice()->CreateRasterizerState1(&desc,&ret);
		mRasterizerStates.push_back(ret);
	}
	return ret;
}

ID3D11BlendState1 * NSDevilX::NSRenderSystem::NSD3D11::CSystemImp::getBlendState(const D3D11_BLEND_DESC1 & desc)
{
	if(0==memcmp(&getDefaultBlendStateDescription(),&desc,sizeof(D3D11_BLEND_DESC1)))
		return nullptr;
	ID3D11BlendState1 * ret=NSInternal::getState1(desc,mBlendStates);
	if(nullptr==ret)
	{
		getDevice()->CreateBlendState1(&desc,&ret);
		mBlendStates.push_back(ret);
	}
	return ret;
}

ID3D11DepthStencilState * NSDevilX::NSRenderSystem::NSD3D11::CSystemImp::getDepthStencilState(const D3D11_DEPTH_STENCIL_DESC & desc)
{
	if(0==memcmp(&getDefaultDepthStencilDescription(),&desc,sizeof(D3D11_DEPTH_STENCIL_DESC)))
		return nullptr;
	ID3D11DepthStencilState * ret=NSInternal::getState(desc,mDepthStencilStates);
	if(nullptr==ret)
	{
		getDevice()->CreateDepthStencilState(&desc,&ret);
		mDepthStencilStates.push_back(ret);
	}
	return ret;
}

ID3D11SamplerState * NSDevilX::NSRenderSystem::NSD3D11::CSystemImp::getSamplerState(const D3D11_SAMPLER_DESC & desc)
{
	if(0==memcmp(&getDefaultSamplerStateDescription(),&desc,sizeof(D3D11_SAMPLER_DESC)))
		return nullptr;
	ID3D11SamplerState * ret=NSInternal::getState(desc,mSamplerStates);
	if(nullptr==ret)
	{
		getDevice()->CreateSamplerState(&desc,&ret);
		mSamplerStates.push_back(ret);
	}
	return ret;
}

CVertexShader * NSDevilX::NSRenderSystem::NSD3D11::CSystemImp::getVertexShader(ID3DBlob * code)
{
	auto * ret=mShaders[code];
	if(nullptr==ret)
	{
		ret=DEVILX_NEW CVertexShader(code);
		mShaders[code]=ret;
	}
	return dynamic_cast<CVertexShader*>(ret);
}

CHullShader * NSDevilX::NSRenderSystem::NSD3D11::CSystemImp::getHullShader(ID3DBlob * code)
{
	auto * ret=mShaders[code];
	if(nullptr==ret)
	{
		ret=DEVILX_NEW CHullShader(code);
		mShaders[code]=ret;
	}
	return dynamic_cast<CHullShader*>(ret);
}

CDomainShader * NSDevilX::NSRenderSystem::NSD3D11::CSystemImp::getDomainShader(ID3DBlob * code)
{
	auto * ret=mShaders[code];
	if(nullptr==ret)
	{
		ret=DEVILX_NEW CDomainShader(code);
		mShaders[code]=ret;
	}
	return dynamic_cast<CDomainShader*>(ret);
}

CPixelShader * NSDevilX::NSRenderSystem::NSD3D11::CSystemImp::getPixelShader(ID3DBlob * code)
{
	auto * ret=mShaders[code];
	if(nullptr==ret)
	{
		ret=DEVILX_NEW CPixelShader(code);
		mShaders[code]=ret;
	}
	return dynamic_cast<CPixelShader*>(ret);
}

CTransformerImp * NSDevilX::NSRenderSystem::NSD3D11::CSystemImp::createTransformer(ITransformerImp * interfaceImp)
{
	if(getTransformer(interfaceImp))
		return nullptr;
	auto ret=DEVILX_NEW CTransformerImp(interfaceImp);
	mTransformers[interfaceImp]=ret;
	return ret;
}

Void NSDevilX::NSRenderSystem::NSD3D11::CSystemImp::onMessage(ISystemImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case ISystemImp::EMessage_Update:
		notify(EMessage_BeginFrame);
		needUpdate();
		for(auto const & window_pair:mWindows)
		{
			auto window=window_pair.second;
			window->prepare();
		}
		for(auto const & window_pair:mWindows)
		{
			auto window=window_pair.second;
			window->render();
		}
		notify(EMessage_EndFrame);
		break;
	case ISystemImp::EMessage_EndWindowCreate:
	{
		CWindowImp * window=DEVILX_NEW CWindowImp(static_cast<IWindowImp*>(data));
		mWindows[static_cast<IWindowImp*>(data)]=window;
	}
	break;
	case ISystemImp::EMessage_BeginWindowDestroy:
	{
		mWindows.destroy(static_cast<IWindowImp*>(data));
	}
	break;
	case ISystemImp::EMessage_EndSceneCreate:
	{
		auto * scene=DEVILX_NEW CScene(static_cast<ISceneImp*>(data));
		mScenes[static_cast<ISceneImp*>(data)]=scene;
	}
	break;
	case ISystemImp::EMessage_BeginSceneDestroy:
	{
		mScenes.destroy(static_cast<ISceneImp*>(data));
	}
	break;
	case ISystemImp::EMessage_EndRenderableSurfaceCreate:
	{
		CRenderableSurfaceImp * renderable_surface=DEVILX_NEW CRenderableSurfaceImp(static_cast<IRenderableSurfaceImp*>(data));
		mRenderableSurfaces[static_cast<IRenderableSurfaceImp*>(data)]=renderable_surface;
	}
	break;
	case ISystemImp::EMessage_BeginRenderableSurfaceDestroy:
		mRenderableSurfaces.destroy(static_cast<IRenderableSurfaceImp*>(data));
		break;
	case ISystemImp::EMessage_Destruction:
		DEVILX_DELETE(this);
		break;
	}
}

Void NSDevilX::NSRenderSystem::NSD3D11::CSystemImp::onMessage(IResourceManagerImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case IResourceManagerImp::EMessage_EndGeometryCreate:
		mGeometrys[static_cast<IGeometryImp*>(data)]=DEVILX_NEW CGeometry(static_cast<IGeometryImp*>(data));
		break;
	case IResourceManagerImp::EMessage_BeginGeometryDestroy:
		mGeometrys.destroy(static_cast<IGeometryImp*>(data));
		break;
	case IResourceManagerImp::EMessage_EndTextureCreate:
		switch(static_cast<ITextureImp*>(data)->getType())
		{
		case IEnum::ETextureType_2D:
			mTexture2Ds[static_cast<ITexture2DImp*>(static_cast<ITextureImp*>(data))]=DEVILX_NEW CTexture2D(static_cast<ITexture2DImp*>(static_cast<ITextureImp*>(data)));
			break;
		case IEnum::ETextureType_Cube:
			break;
		}
		break;
	case IResourceManagerImp::EMessage_BeginTextureDestroy:
		switch(static_cast<ITextureImp*>(data)->getType())
		{
		case IEnum::ETextureType_2D:
			mTexture2Ds.destroy(static_cast<ITexture2DImp*>(static_cast<ITextureImp*>(data)));
			break;
		case IEnum::ETextureType_Cube:
			break;
		}
		break;
	case IResourceManagerImp::EMessage_VertexBufferCreate:
		mVertexBuffers[static_cast<IVertexBufferImp*>(data)]=DEVILX_NEW CVertexBufferImp(static_cast<IVertexBufferImp*>(data));
		break;
	case IResourceManagerImp::EMessage_VertexBufferDestroy:
		mVertexBuffers.destroy(static_cast<IVertexBufferImp*>(data));
		break;
	case IResourceManagerImp::EMessage_IndexBufferCreate:
		mIndexBuffers[static_cast<IIndexBufferImp*>(data)]=DEVILX_NEW CIndexBufferImp(static_cast<IIndexBufferImp*>(data));
		break;
	case IResourceManagerImp::EMessage_IndexBufferDestroy:
		mIndexBuffers.destroy(static_cast<IIndexBufferImp*>(data));
		break;
	}
}

Void NSDevilX::NSRenderSystem::NSD3D11::CSystemImp::_updateConstantBuffer(Byte * buffer)
{
	auto offset=mConstantBuffer->getDescription()->getConstantDesc("gFrameTimeInSeconds").StartOffset;
	*reinterpret_cast<Float*>(&buffer[offset])=ISystemImp::getSingleton().getFrameTimeInSecond();
	offset=mConstantBuffer->getDescription()->getConstantDesc("gInverseFrameTimeInSeconds").StartOffset;
	*reinterpret_cast<Float*>(&buffer[offset])=1.0f/ISystemImp::getSingleton().getFrameTimeInSecond();

}
