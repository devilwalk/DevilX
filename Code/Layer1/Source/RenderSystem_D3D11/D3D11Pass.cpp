#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;
using namespace NSD3D11;

NSDevilX::NSRenderSystem::NSD3D11::CPass::CPass()
	:mVertexShader(nullptr)
	,mHullShader(nullptr)
	,mDomainShader(nullptr)
	,mPixelShader(nullptr)
	,mRasterizerState(nullptr)
	,mBlendState(nullptr)
	,mDepthState(nullptr)
{}

NSDevilX::NSRenderSystem::NSD3D11::CPass::~CPass()
{}
