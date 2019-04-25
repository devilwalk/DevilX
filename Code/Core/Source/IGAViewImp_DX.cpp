#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSCore;
using namespace NSDirectX;
using namespace NSVersion11;

NSDevilX::NSCore::NSDirectX::NSVersion11::IGARenderTargetViewImp::IGARenderTargetViewImp(ID3D11Device * device,ID3D11Resource * resource,const D3D11_RENDER_TARGET_VIEW_DESC * desc)
{
	device->CreateRenderTargetView(resource,desc,&mInternal);
}

NSDevilX::NSCore::NSDirectX::NSVersion11::IGARenderTargetViewImp::IGARenderTargetViewImp(ID3D11Device3 * device,ID3D11Resource * resource,const D3D11_RENDER_TARGET_VIEW_DESC1 * desc)
{
	device->CreateRenderTargetView1(resource,desc,reinterpret_cast<ID3D11RenderTargetView1**>(&mInternal));
}

NSDevilX::NSCore::NSDirectX::NSVersion11::IGARenderTargetViewImp::~IGARenderTargetViewImp()
{
}

NSDevilX::NSCore::NSDirectX::NSVersion11::IGADepthStencilViewImp::IGADepthStencilViewImp(ID3D11Device * device,ID3D11Resource * resource,const D3D11_DEPTH_STENCIL_VIEW_DESC * desc)
{
	device->CreateDepthStencilView(resource,desc,&mInternal);
}

NSDevilX::NSCore::NSDirectX::NSVersion11::IGADepthStencilViewImp::~IGADepthStencilViewImp()
{
}

NSDevilX::NSCore::NSDirectX::NSVersion11::IGAShaderResourceViewImp::IGAShaderResourceViewImp(ID3D11Device * device,ID3D11Resource * resource,const D3D11_SHADER_RESOURCE_VIEW_DESC * desc)
{
	device->CreateShaderResourceView(resource,desc,&mInternal);
}

NSDevilX::NSCore::NSDirectX::NSVersion11::IGAShaderResourceViewImp::IGAShaderResourceViewImp(ID3D11Device3 * device,ID3D11Resource * resource,const D3D11_SHADER_RESOURCE_VIEW_DESC1 * desc)
{
	device->CreateShaderResourceView1(resource,desc,reinterpret_cast<ID3D11ShaderResourceView1**>(&mInternal));
}

NSDevilX::NSCore::NSDirectX::NSVersion11::IGAShaderResourceViewImp::~IGAShaderResourceViewImp()
{
}
