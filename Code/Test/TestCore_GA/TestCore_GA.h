#pragma once

#include "resource.h"

class CGATester
	:public NSDevilX::TSingletonEx<CGATester>
{
protected:
	NSDevilX::NSCore::IGADevice* mGADevice;
	NSDevilX::NSCore::IGASwapChain* mGASwapChain;
	NSDevilX::NSCore::IGAProgram* mProgram;
	NSDevilX::NSCore::IGAProgramParameter* mProgramParameter;
	NSDevilX::NSCore::IGAStruct::SViewport mViewport;
public:
	CGATester()
	{
	}
	~CGATester()
	{
		NSDevilX::NSCore::getSystem()->shutdown();
	}

	NSDevilX::Void initialize(HWND wnd)
	{
		RECT rc;
		GetClientRect(wnd,&rc);
		mViewport.Height=static_cast<NSDevilX::Float>(rc.bottom-rc.top);
		mViewport.MaxDepth=1;
		mViewport.MinDepth=0;
		mViewport.TopLeftX=0;
		mViewport.TopLeftY=0;
		mViewport.Width=static_cast<NSDevilX::Float>(rc.right-rc.left);
		mGADevice=NSDevilX::NSCore::getSystem()->getGAManager()->createDevice(NSDevilX::NSCore::IGAEnum::EDeviceVersion_DirectX11);
		NSDevilX::NSCore::IGAStruct::SGISwapChainDesc swap_chain_desc={0};
		swap_chain_desc.BufferDesc.Format=NSDevilX::NSCore::IGAEnum::EGIFormat_R8G8B8A8_UNORM_SRGB;
		swap_chain_desc.BufferUsage=NSDevilX::NSCore::IGAEnum::EGIUsage_BackBuffer|NSDevilX::NSCore::IGAEnum::EGIUsage_RenderTargetOutput;
		swap_chain_desc.OutputWindow=wnd;
		swap_chain_desc.SampleDesc.Count=1;
		swap_chain_desc.SampleDesc.Quality=0;
		mGASwapChain=NSDevilX::NSCore::getSystem()->getGAManager()->createSwapChain(mGADevice,swap_chain_desc);

		auto vertex_buffer=mGADevice->createShaderResourceBuffer(sizeof(NSDevilX::CFloat4)*3,0,0,16);
		NSDevilX::CFloat4 pos[]={NSDevilX::CFloat4(1,-1,0.5,0),NSDevilX::CFloat4(-1,-1,0.5,0),NSDevilX::CFloat4(0,1,0.5,0)};
		mGADevice->getImmediateContext()->update(vertex_buffer->queryInterface_IGABuffer(),pos);
		auto index_buffer=mGADevice->createShaderResourceBuffer(sizeof(NSDevilX::CUInt4),0,0,16);
		NSDevilX::UInt32 index[]={0,1,2,0};
		mGADevice->getImmediateContext()->update(index_buffer->queryInterface_IGABuffer(),index);
		struct SObjectBuffer
		{
			NSDevilX::CMatrix4F mWorldViewProjMatrix;
		};
		auto object_buffer=mGADevice->createShaderResourceBuffer(sizeof(SObjectBuffer)*1000,0,0,sizeof(SObjectBuffer));
		SObjectBuffer obj[1000];
		srand(GetTickCount());
		for(int i=0;i<1000;++i)
		{
			auto scale=DirectX::XMMatrixScaling(abs(rand())*0.00001f,abs(rand())*0.00001f,1);
			auto trans=DirectX::XMMatrixTranslation(rand()*0.0001f,rand()*0.0001f,0);
			obj[i].mWorldViewProjMatrix=scale*trans;
		}
		mGADevice->getImmediateContext()->update(object_buffer->queryInterface_IGABuffer(),obj);
		auto instance_buffer=mGADevice->createConstantBuffer(sizeof(NSDevilX::CUInt4)*4096,NSDevilX::NSCore::IGAEnum::ECPUAccessFlag_Write,NSDevilX::NSCore::IGAEnum::EUsage_DYNAMIC);
		struct SInstanceBuffer
		{
			NSDevilX::UInt32 mIndexStart0;
			NSDevilX::UInt32 mIndexCount0;
			NSDevilX::UInt32 mIndexStart1;
			NSDevilX::UInt32 mIndexCount1;
		};
		SInstanceBuffer instance[4096]={0};
		for(int i=0;i<500;++i)
		{
			instance[i].mIndexStart0=0;
			instance[i].mIndexCount0=3;
			instance[i].mIndexStart1=0;
			instance[i].mIndexCount1=3;
		}
		mGADevice->getImmediateContext()->update(instance_buffer->queryInterface_IGABuffer(),instance);

		NSDevilX::String code;
		{
			NSDevilX::CFileStream fs("D:\\develop\\DevilX\\Code\\Test\\TestCore_GA\\PreDepthVS.hlsl");
			auto reader=fs.createReader();
			code.resize(fs.getSize());
			reader->process(fs.getSize(),&code[0]);
		}
		auto vertex_shader=mGADevice->createVertexShader(code);
		{
			NSDevilX::CFileStream fs("D:\\develop\\DevilX\\Code\\Test\\TestCore_GA\\PreDepthPS.hlsl");
			auto reader=fs.createReader();
			code.resize(fs.getSize());
			reader->process(fs.getSize(),&code[0]);
		}
		auto pixel_shader=mGADevice->createPixelShader(code);
		{
			NSDevilX::CFileStream fs("D:\\develop\\DevilX\\Code\\Test\\TestCore_GA\\PreDepthGS.hlsl");
			auto reader=fs.createReader();
			code.resize(fs.getSize());
			reader->process(fs.getSize(),&code[0]);
		}
		auto geometry_shader=mGADevice->createGeometryShader(code);
		mProgram=mGADevice->createProgram(vertex_shader,pixel_shader);

		auto reflection=mGADevice->createReflection(mProgram);

		mProgramParameter=mGADevice->createProgramParameter();

		auto vertex_buffer_view=mGADevice->createShaderResourceView(vertex_buffer,0,3);
		auto index_buffer_view=mGADevice->createShaderResourceView(index_buffer,0,1);
		auto object_buffer_view=mGADevice->createShaderResourceView(object_buffer,0,1000);
		mProgramParameter->setResource(0,vertex_buffer_view);
		mProgramParameter->setResource(1,index_buffer_view);
		mProgramParameter->setResource(2,object_buffer_view);
		mProgramParameter->setResource(0,instance_buffer);
	}

	NSDevilX::Void update()
	{
		NSDevilX::Float clear_rgba[]={1.0f,0,0,1.0f};
		mGADevice->getImmediateContext()->clear(mGASwapChain->getRenderTargetView(),clear_rgba);
		mGADevice->getImmediateContext()->clear(mGASwapChain->getDepthStencilView(),NSDevilX::NSCore::IGAEnum::EClearFlag_DEPTH|NSDevilX::NSCore::IGAEnum::EClearFlag_STENCIL,1.0f,0);
		auto rtv=mGASwapChain->getRenderTargetView();
		mGADevice->getImmediateContext()->setRenderTargets(1,&rtv,mGASwapChain->getDepthStencilView());
		mGADevice->getImmediateContext()->setViewports(1,&mViewport);
		mGADevice->getImmediateContext()->setPrimitiveTopology(NSDevilX::NSCore::IGAEnum::EPrimitiveTopology_TRIANGLELIST);
		mGADevice->getImmediateContext()->setProgram(mProgram,mProgramParameter);
		mGADevice->getImmediateContext()->draw(1000*3,0,1000);
		mGASwapChain->present();
	}
};