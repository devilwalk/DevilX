#pragma once
#include "IGAViewImp.h"
namespace NSDevilX
{
	namespace NSCore
	{
		namespace NSDirectX
		{
			namespace NSVersion11
			{
				template<class TInterface,class TInternal>
				class TGAD3DViewImp
					:public TGAViewImp<TInterface>
					,public TD3DObjectContainer<TInternal>
				{
				public:
					TGAD3DViewImp(TInternal * obj=0)
						:TD3DObjectContainer<TInternal>(obj)
					{
					}
					virtual ~TGAD3DViewImp()
					{
					}
				};
				class IGARenderTargetViewImp
					:public TGAD3DViewImp<IGARenderTargetView,ID3D11RenderTargetView>
					,public TBaseObject<IGARenderTargetViewImp>
				{
				protected:
				public:
					IGARenderTargetViewImp(ID3D11Device * device,ID3D11Resource * resource,const D3D11_RENDER_TARGET_VIEW_DESC * desc=nullptr);
					IGARenderTargetViewImp(ID3D11Device3 * device,ID3D11Resource * resource,const D3D11_RENDER_TARGET_VIEW_DESC1 * desc=nullptr);
					~IGARenderTargetViewImp();
				};
				class IGADepthStencilViewImp
					:public TGAD3DViewImp<IGADepthStencilView,ID3D11DepthStencilView>
					,public TBaseObject<IGADepthStencilViewImp>
				{
				protected:
				public:
					IGADepthStencilViewImp(ID3D11Device * device,ID3D11Resource * resource,const D3D11_DEPTH_STENCIL_VIEW_DESC * desc=nullptr);
					~IGADepthStencilViewImp();
				};
				class IGAShaderResourceViewImp
					:public TGAD3DViewImp<IGATextureView,ID3D11ShaderResourceView>
					,public TGAViewImp<IGATextureBufferView>
					,public TBaseObject<IGAShaderResourceViewImp>
				{
				protected:
				public:
					IGAShaderResourceViewImp(ID3D11Device * device,ID3D11Resource * resource,const D3D11_SHADER_RESOURCE_VIEW_DESC * desc=nullptr);
					IGAShaderResourceViewImp(ID3D11Device3 * device,ID3D11Resource * resource,const D3D11_SHADER_RESOURCE_VIEW_DESC1 * desc=nullptr);
					~IGAShaderResourceViewImp();
				};
				class IGAUnorderedAccessViewImp
					:public TGAD3DViewImp<IGAUnorderedAccessView,ID3D11UnorderedAccessView>
					,public TBaseObject<IGAUnorderedAccessViewImp>
				{
				public:
					IGAUnorderedAccessViewImp(ID3D11Device* device,ID3D11Resource* resource,const D3D11_UNORDERED_ACCESS_VIEW_DESC * desc=nullptr);
					~IGAUnorderedAccessViewImp();
				};
			}
		}
	}
}