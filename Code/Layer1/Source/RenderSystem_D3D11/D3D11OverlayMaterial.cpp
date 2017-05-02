#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;
using namespace NSD3D11;

NSDevilX::NSRenderSystem::NSD3D11::COverlayMaterial::COverlayMaterial(CTexture * texture)
{
	if(texture)
		mPSTextures.push_back(texture);
	_updateShader();
	_updateRasterizerState();
	_updateBlendState();
	_updateDepthStencilState();
	_updateSamplerState();
}

NSDevilX::NSRenderSystem::NSD3D11::COverlayMaterial::~COverlayMaterial()
{}

Void NSDevilX::NSRenderSystem::NSD3D11::COverlayMaterial::_updateShader()
{
	String code_key="Overlay_VertexShader";
	ID3DBlob * blob=CSystemImp::getSingleton().getShaderCodeManager()->getCode(code_key);
	if(nullptr==blob)
	{
		String code;
		switch(CSystemImp::getSingleton().getShaderModelType())
		{
		case CEnum::EShaderModelType_4_1:
			code=CSystemImp::getSingleton().getDefinitionShader4_1()->OverlayShader;
			break;
		case CEnum::EShaderModelType_5:
			code=CSystemImp::getSingleton().getDefinitionShader5()->OverlayShader;
			break;
		}
		blob=CSystemImp::getSingleton().getShaderCodeManager()->registerShader(code_key,code,CEnum::EShaderType_VertexShader,CSystemImp::getSingleton().getShaderModelType(),nullptr);
	}
	mVertexShader=CSystemImp::getSingleton().getVertexShader(blob);

	/*code_key="Overlay_HullShader";
	blob=CSystemImp::getSingleton().getShaderCodeManager()->getCode(code_key);
	if(nullptr==blob)
	{
		String code;
		switch(CSystemImp::getSingleton().getShaderModelType())
		{
		case CEnum::EShaderModelType_4_1:
			code=CSystemImp::getSingleton().getDefinitionShader4_1()->OverlayShader;
			break;
		case CEnum::EShaderModelType_5:
			code=CSystemImp::getSingleton().getDefinitionShader5()->OverlayShader;
			break;
		}
		blob=CSystemImp::getSingleton().getShaderCodeManager()->registerShader(code_key,code,CEnum::EShaderType_HullShader,CSystemImp::getSingleton().getShaderModelType(),nullptr);
	}
	mHullShader=CSystemImp::getSingleton().getHullShader(blob);

	code_key="Overlay_DomainShader";
	blob=CSystemImp::getSingleton().getShaderCodeManager()->getCode(code_key);
	if(nullptr==blob)
	{
		String code;
		switch(CSystemImp::getSingleton().getShaderModelType())
		{
		case CEnum::EShaderModelType_4_1:
			code=CSystemImp::getSingleton().getDefinitionShader4_1()->OverlayShader;
			break;
		case CEnum::EShaderModelType_5:
			code=CSystemImp::getSingleton().getDefinitionShader5()->OverlayShader;
			break;
		}
		blob=CSystemImp::getSingleton().getShaderCodeManager()->registerShader(code_key,code,CEnum::EShaderType_DomainShader,CSystemImp::getSingleton().getShaderModelType(),nullptr);
	}
	mDomainShader=CSystemImp::getSingleton().getDomainShader(blob);*/

	code_key="Overlay_PixelShader_"+CStringConverter::toString(mPSTextures.empty()?0:1);
	blob=CSystemImp::getSingleton().getShaderCodeManager()->getCode(code_key);
	if(nullptr==blob)
	{
		TVector<D3D_SHADER_MACRO> macro_list;
		class CMacro
			:public D3D_SHADER_MACRO
		{
		public:
			CMacro()
			{
				Name=nullptr;
				Definition=nullptr;
			}
			Void set(decltype(Name) name)
			{
				Name=name;
				Definition="1";
			}
		};
		CMacro def;
		if(!mPSTextures.empty())
		{
			def.set("USE_DIFFUSE_TEXTURE");
			macro_list.push_back(def);
		}
		macro_list.push_back(CMacro());
		String code;
		switch(CSystemImp::getSingleton().getShaderModelType())
		{
		case CEnum::EShaderModelType_4_1:
			code=CSystemImp::getSingleton().getDefinitionShader4_1()->OverlayShader;
			break;
		case CEnum::EShaderModelType_5:
			code=CSystemImp::getSingleton().getDefinitionShader5()->OverlayShader;
			break;
		}
		blob=CSystemImp::getSingleton().getShaderCodeManager()->registerShader(code_key,code,CEnum::EShaderType_PixelShader,CSystemImp::getSingleton().getShaderModelType(),&macro_list[0]);
	}
	mPixelShader=CSystemImp::getSingleton().getPixelShader(blob);
}

Void NSDevilX::NSRenderSystem::NSD3D11::COverlayMaterial::_updateRasterizerState()
{
	D3D11_RASTERIZER_DESC1 desc=CSystemImp::getSingleton().getDefaultRasterizerStateDescription();
	desc.CullMode=D3D11_CULL_NONE;
	desc.ScissorEnable=TRUE;
	mRasterizerState=CSystemImp::getSingleton().getRasterizerState(desc);
}

Void NSDevilX::NSRenderSystem::NSD3D11::COverlayMaterial::_updateBlendState()
{
	D3D11_BLEND_DESC1 desc=CSystemImp::getSingleton().getDefaultBlendStateDescription();
	desc.RenderTarget[0].BlendEnable=TRUE;
	desc.RenderTarget[0].DestBlend=D3D11_BLEND_INV_SRC_ALPHA;
	desc.RenderTarget[0].SrcBlend=D3D11_BLEND_SRC_ALPHA;
	mBlendState=CSystemImp::getSingleton().getBlendState(desc);
}

Void NSDevilX::NSRenderSystem::NSD3D11::COverlayMaterial::_updateDepthStencilState()
{
	D3D11_DEPTH_STENCIL_DESC desc=CSystemImp::getSingleton().getDefaultDepthStencilDescription();
	desc.DepthWriteMask=D3D11_DEPTH_WRITE_MASK_ZERO;
	desc.DepthFunc=D3D11_COMPARISON_ALWAYS;
	mDepthState=CSystemImp::getSingleton().getDepthStencilState(desc);
}

Void NSDevilX::NSRenderSystem::NSD3D11::COverlayMaterial::_updateSamplerState()
{
	mPSSamplerStates.clear();
	D3D11_SAMPLER_DESC desc=CSystemImp::getSingleton().getDefaultSamplerStateDescription();
	desc.MaxLOD=0;
	desc.MinLOD=0;
	desc.AddressU=D3D11_TEXTURE_ADDRESS_CLAMP;
	desc.AddressV=D3D11_TEXTURE_ADDRESS_CLAMP;
	desc.Filter=D3D11_FILTER_MIN_MAG_LINEAR_MIP_POINT;
	mPSSamplerStates.push_back(CSystemImp::getSingleton().getSamplerState(desc));
}
