#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSCore;
using namespace NSDirectX;
using namespace NSVersion11;

NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceImp::IGADeviceImp()
	:mFeatureLevel(D3D_FEATURE_LEVEL_9_3)
{
	UINT flags=0;
#if DEVILX_DEBUG
	flags|=D3D11_CREATE_DEVICE_DEBUG;
#endif
	D3D_FEATURE_LEVEL levels[]={D3D_FEATURE_LEVEL_11_1,D3D_FEATURE_LEVEL_11_0,D3D_FEATURE_LEVEL_10_1,D3D_FEATURE_LEVEL_10_0,D3D_FEATURE_LEVEL_9_3};
	D3D11CreateDevice(NULL,D3D_DRIVER_TYPE_HARDWARE,NULL,flags,levels,_countof(levels),D3D11_SDK_VERSION,&mInternal,levels,nullptr);
	mFeatureLevel=levels[0];
	mContexts.push_back(DEVILX_NEW IGADeviceContextImp(mInternal,False));
}

NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceImp::~IGADeviceImp()
{
	mCommonResources.destroyAll();
	mContexts.destroyAll();
}

IGADeviceContext * NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceImp::getImmediateContext() const
{
	return mContexts[0];
}

IGADeviceContext * NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceImp::createDeferredContext()
{
	IGADeviceContextImp * ret=nullptr;
	D3D11_FEATURE_DATA_THREADING feature={0};
	mInternal->CheckFeatureSupport(D3D11_FEATURE_THREADING,&feature,sizeof(feature));
	if(feature.DriverCommandLists)
	{
		ret=DEVILX_NEW IGADeviceContextImp(mInternal,True);
		mContexts.push_back(ret);
	}
	return ret;
}

IGAVertexBuffer * NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceImp::createVertexBuffer(UInt32 sizeInByte,UInt32 cpuAccessFlags,IGAEnum::EUsage usage,UInt32 bindFlags,ConstVoidPtr initialData)
{
	D3D11_BUFFER_DESC d3d_desc={0};
	d3d_desc.BindFlags=D3D11_BIND_VERTEX_BUFFER|CUtility::mappingBufferBindFlags(bindFlags);
	d3d_desc.ByteWidth=sizeInByte;
	d3d_desc.CPUAccessFlags=CUtility::mappingCPUAccessFlags(cpuAccessFlags);
	d3d_desc.Usage=CUtility::mapping(usage);
	D3D11_SUBRESOURCE_DATA d3d_sub_data={0};
	if(initialData)
	{
		d3d_sub_data.pSysMem=initialData;
		d3d_sub_data.SysMemPitch=sizeInByte;
		d3d_sub_data.SysMemSlicePitch=sizeInByte;
	}
	auto ret=DEVILX_NEW IGABufferImp(mInternal,d3d_desc,initialData?(&d3d_sub_data):nullptr);
	mCommonResources.push_back(ret);
	return ret;
}

IGAIndexBuffer * NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceImp::createIndexBuffer(UInt32 sizeInByte,UInt32 cpuAccessFlags,IGAEnum::EUsage usage,UInt32 bindFlags,ConstVoidPtr initialData)
{
	D3D11_BUFFER_DESC d3d_desc={0};
	d3d_desc.BindFlags=D3D11_BIND_INDEX_BUFFER|CUtility::mappingBufferBindFlags(bindFlags);
	d3d_desc.ByteWidth=sizeInByte;
	d3d_desc.CPUAccessFlags=CUtility::mappingCPUAccessFlags(cpuAccessFlags);
	d3d_desc.Usage=CUtility::mapping(usage);
	D3D11_SUBRESOURCE_DATA d3d_sub_data={0};
	if(initialData)
	{
		d3d_sub_data.pSysMem=initialData;
		d3d_sub_data.SysMemPitch=sizeInByte;
		d3d_sub_data.SysMemSlicePitch=sizeInByte;
	}
	auto ret=DEVILX_NEW IGABufferImp(mInternal,d3d_desc,initialData?(&d3d_sub_data):nullptr);
	mCommonResources.push_back(ret);
	return ret;
}

IGAConstantBuffer * NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceImp::createConstantBuffer(UInt32 sizeInByte,UInt32 cpuAccessFlags,IGAEnum::EUsage usage,UInt32 bindFlags,ConstVoidPtr initialData)
{
	D3D11_BUFFER_DESC d3d_desc={0};
	d3d_desc.BindFlags=D3D11_BIND_CONSTANT_BUFFER|CUtility::mappingBufferBindFlags(bindFlags);
	d3d_desc.ByteWidth=sizeInByte;
	d3d_desc.CPUAccessFlags=CUtility::mappingCPUAccessFlags(cpuAccessFlags);
	d3d_desc.Usage=CUtility::mapping(usage);
	D3D11_SUBRESOURCE_DATA d3d_sub_data={0};
	if(initialData)
	{
		d3d_sub_data.pSysMem=initialData;
		d3d_sub_data.SysMemPitch=sizeInByte;
		d3d_sub_data.SysMemSlicePitch=sizeInByte;
	}
	auto ret=DEVILX_NEW IGABufferImp(mInternal,d3d_desc,initialData?(&d3d_sub_data):nullptr);
	mCommonResources.push_back(ret);
	return ret;
}

IGAUnorderedAccessBuffer * NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceImp::createUnorderedAccessBuffer(UInt32 sizeInByte,UInt32 cpuAccessFlags,IGAEnum::EUsage usage,UInt32 bindFlags,ConstVoidPtr initialData)
{
	D3D11_BUFFER_DESC d3d_desc={0};
	d3d_desc.BindFlags=D3D11_BIND_UNORDERED_ACCESS|CUtility::mappingBufferBindFlags(bindFlags);
	d3d_desc.ByteWidth=sizeInByte;
	d3d_desc.CPUAccessFlags=CUtility::mappingCPUAccessFlags(cpuAccessFlags);
	d3d_desc.Usage=CUtility::mapping(usage);
	D3D11_SUBRESOURCE_DATA d3d_sub_data={0};
	if(initialData)
	{
		d3d_sub_data.pSysMem=initialData;
		d3d_sub_data.SysMemPitch=sizeInByte;
		d3d_sub_data.SysMemSlicePitch=sizeInByte;
	}
	auto ret=DEVILX_NEW IGABufferImp(mInternal,d3d_desc,initialData?(&d3d_sub_data):nullptr);
	mCommonResources.push_back(ret);
	return ret;
}

IGATexture1D * NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceImp::createTexture1D(UInt32 length,IGAEnum::EUsage usage,IGAEnum::EGIFormat format,UInt32 cpuAccessFlags,UInt32 bindFlags,UInt32 mipLevelCount,UInt32 arrayCount,const IGAStruct::SSubResourceData * initialData)
{
	D3D11_TEXTURE1D_DESC d3d_desc={0};
	d3d_desc.ArraySize=arrayCount;
	d3d_desc.BindFlags=CUtility::mappingTextureBindFlags(bindFlags);
	d3d_desc.CPUAccessFlags=CUtility::mappingCPUAccessFlags(cpuAccessFlags);
	d3d_desc.Format=CUtility::mapping(format);
	d3d_desc.MipLevels=mipLevelCount;
	d3d_desc.Usage=CUtility::mapping(usage);
	d3d_desc.Width=length;
	D3D11_SUBRESOURCE_DATA d3d_sub_data={0};
	if(initialData)
	{
		d3d_sub_data.pSysMem=initialData;
		d3d_sub_data.SysMemPitch=length*CUtility::getComponentCount(format)*CUtility::getComponentSize(format);
		d3d_sub_data.SysMemSlicePitch=d3d_sub_data.SysMemPitch;
	}
	auto ret=DEVILX_NEW IGATexture1DImp(mInternal,d3d_desc,initialData?&d3d_sub_data:nullptr);
	mCommonResources.push_back(ret);
	return ret;
}

IGATexture2D * NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceImp::createTexture2D(UInt32 width,UInt32 height,IGAEnum::EUsage usage,IGAEnum::EGIFormat format,UInt32 cpuAccessFlags,UInt32 bindFlags,UInt32 mipLevelCount,UInt32 arrayCount,const IGAStruct::SSubResourceData * initialData)
{
	D3D11_TEXTURE2D_DESC d3d_desc={0};
	d3d_desc.ArraySize=arrayCount;
	d3d_desc.BindFlags=CUtility::mappingTextureBindFlags(bindFlags);
	d3d_desc.CPUAccessFlags=CUtility::mappingCPUAccessFlags(cpuAccessFlags);
	d3d_desc.Format=CUtility::mapping(format);
	d3d_desc.MipLevels=mipLevelCount;
	d3d_desc.Usage=CUtility::mapping(usage);
	d3d_desc.Width=width;
	d3d_desc.Height=height;
	d3d_desc.SampleDesc.Count=1;
	d3d_desc.SampleDesc.Quality=0;
	D3D11_SUBRESOURCE_DATA d3d_sub_data={0};
	if(initialData)
	{
		d3d_sub_data.pSysMem=initialData;
		d3d_sub_data.SysMemPitch=width*height*CUtility::getComponentCount(format)*CUtility::getComponentSize(format);
		d3d_sub_data.SysMemSlicePitch=d3d_sub_data.SysMemPitch;
	}
	auto ret=DEVILX_NEW IGATexture2DImp(mInternal,d3d_desc,initialData?&d3d_sub_data:nullptr);
	mCommonResources.push_back(ret);
	return ret;
}

IGATexture3D * NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceImp::createTexture3D(UInt32 width,UInt32 height,UInt32 depth,IGAEnum::EUsage usage,IGAEnum::EGIFormat format,UInt32 cpuAccessFlags,UInt32 bindFlags,UInt32 mipLevelCount,const IGAStruct::SSubResourceData * initialData)
{
	D3D11_TEXTURE3D_DESC d3d_desc={0};
	d3d_desc.BindFlags=CUtility::mappingTextureBindFlags(bindFlags);
	d3d_desc.CPUAccessFlags=CUtility::mappingCPUAccessFlags(cpuAccessFlags);
	d3d_desc.Format=CUtility::mapping(format);
	d3d_desc.MipLevels=mipLevelCount;
	d3d_desc.Usage=CUtility::mapping(usage);
	d3d_desc.Width=width;
	d3d_desc.Height=height;
	d3d_desc.Depth=depth;
	D3D11_SUBRESOURCE_DATA d3d_sub_data={0};
	if(initialData)
	{
		d3d_sub_data.pSysMem=initialData;
		d3d_sub_data.SysMemPitch=width*height*CUtility::getComponentCount(format)*CUtility::getComponentSize(format);
		d3d_sub_data.SysMemSlicePitch=d3d_sub_data.SysMemPitch;
	}
	auto ret=DEVILX_NEW IGATexture3DImp(mInternal,d3d_desc,initialData?&d3d_sub_data:nullptr);
	mCommonResources.push_back(ret);
	return ret;
}

IGATexture2D * NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceImp::createTextureCube(UInt32 width,UInt32 height,IGAEnum::EUsage usage,IGAEnum::EGIFormat format,UInt32 cpuAccessFlags,UInt32 bindFlags,UInt32 mipLevelCount,UInt32 arrayCount,const IGAStruct::SSubResourceData * initialData)
{
	D3D11_TEXTURE2D_DESC d3d_desc={0};
	d3d_desc.ArraySize=arrayCount*6;
	d3d_desc.BindFlags=CUtility::mappingTextureBindFlags(bindFlags);
	d3d_desc.CPUAccessFlags=CUtility::mappingCPUAccessFlags(cpuAccessFlags);
	d3d_desc.Format=CUtility::mapping(format);
	d3d_desc.MipLevels=mipLevelCount;
	d3d_desc.Usage=CUtility::mapping(usage);
	d3d_desc.Width=width;
	d3d_desc.Height=height;
	d3d_desc.SampleDesc.Count=1;
	d3d_desc.SampleDesc.Quality=0;
	D3D11_SUBRESOURCE_DATA d3d_sub_data={0};
	if(initialData)
	{
		d3d_sub_data.pSysMem=initialData;
		d3d_sub_data.SysMemPitch=width*height*CUtility::getComponentCount(format)*CUtility::getComponentSize(format);
		d3d_sub_data.SysMemSlicePitch=d3d_sub_data.SysMemPitch;
	}
	auto ret=DEVILX_NEW IGATexture2DImp(mInternal,d3d_desc,initialData?&d3d_sub_data:nullptr);
	mCommonResources.push_back(ret);
	return ret;
}

IGAShaderResourceView * NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceImp::createShaderResourceView(IGAResource * resource,const IGAStruct::SShaderResourceViewDesc * desc)
{
	return nullptr;
}

IGAInputLayout * NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceImp::createInputLayout(const TVector<IGAStruct::SInputElementDesc> & inputElements)
{
	TVector(D3D11_INPUT_ELEMENT_DESC) d3d_descs;
	d3d_descs.reserve(inputElements.size());
	for(const auto & desc:inputElements)
	{
		d3d_descs.push_back(CUtility::mapping(desc));
	}
	auto iter=std::find_if(mInputLayouts.begin(),mInputLayouts.end(),[&d3d_descs](IGAInputLayoutImp * il)
	{
		auto & descs=il->getInputelementDescs();
		if(descs.size()!=d3d_descs.size())
			return false;
		for(SizeT i=0,count=descs.size();i<count;++i)
		{
			if((descs[i].AlignedByteOffset!=d3d_descs[i].AlignedByteOffset)
				||(descs[i].Format!=d3d_descs[i].Format)
				||(descs[i].InputSlot!=d3d_descs[i].InputSlot)
				||(descs[i].InstanceDataStepRate!=d3d_descs[i].InstanceDataStepRate)
				||(descs[i].SemanticIndex!=d3d_descs[i].SemanticIndex)
				||strcmp(descs[i].SemanticName,d3d_descs[i].SemanticName)
				)
			{
				return false;
			}
		}
		return true;
	});
	if(mInputLayouts.end()==iter)
	{
		auto ret=DEVILX_NEW IGAInputLayoutImp(mInternal,d3d_descs);
		mInputLayouts.push_back(ret);
		return ret;
	}
	else
	{
		return *iter;
	}
}

IGABlendState * NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceImp::createBlendState(const IGAStruct::SBlendDesc & desc)
{
	CComPtr<ID3D11Device1> dev;
	mInternal->QueryInterface(__uuidof(dev),reinterpret_cast<VoidPtr*>(&dev));
	auto d3d_desc=CUtility::mapping(desc);
	auto iter=std::find_if(mBlendStates.begin(),mBlendStates.end(),[&d3d_desc,&dev](IGABlendStateImp * state)
	{
		if(dev.p)
		{
			D3D11_BLEND_DESC1 test_desc;
			static_cast<ID3D11BlendState1*>(state->getInternal())->GetDesc1(&test_desc);
			return memcmp(&test_desc,&d3d_desc,sizeof(D3D11_BLEND_DESC1));
		}
		else
		{
			D3D11_BLEND_DESC test_desc;
			state->getInternal()->GetDesc(reinterpret_cast<D3D11_BLEND_DESC*>(&test_desc));
			return memcmp(&test_desc,&d3d_desc,sizeof(D3D11_BLEND_DESC));
		}
	});
	if(mBlendStates.end()==iter)
	{
		auto ret=DEVILX_NEW IGABlendStateImp(mInternal,d3d_desc);
		mBlendStates.push_back(ret);
		return ret;
	}
	else
	{
		auto ret=*iter;
		ret->addRef();
		return ret;
	}
}

IGARasterizerState * NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceImp::createRasterizerState(const IGAStruct::SRasterizerDesc & desc)
{
	CComPtr<ID3D11Device2> dev2;
	mInternal->QueryInterface(__uuidof(dev2),reinterpret_cast<VoidPtr*>(&dev2));
	CComPtr<ID3D11Device2> dev1;
	mInternal->QueryInterface(__uuidof(dev1),reinterpret_cast<VoidPtr*>(&dev1));
	auto d3d_desc=CUtility::mapping(desc);
	auto iter=std::find_if(mRasterizerStates.begin(),mRasterizerStates.end(),[&d3d_desc,&dev1,&dev2](IGARasterizerStateImp * state)
	{
		if(dev2.p)
		{
			D3D11_RASTERIZER_DESC2 test_desc;
			static_cast<ID3D11RasterizerState2*>(state->getInternal())->GetDesc2(&test_desc);
			return memcmp(&test_desc,&d3d_desc,sizeof(D3D11_RASTERIZER_DESC2));
		}
		else if(dev1.p)
		{
			D3D11_RASTERIZER_DESC1 test_desc;
			static_cast<ID3D11RasterizerState1*>(state->getInternal())->GetDesc1(&test_desc);
			return memcmp(&test_desc,&d3d_desc,sizeof(D3D11_RASTERIZER_DESC1));
		}
		else
		{
			D3D11_RASTERIZER_DESC test_desc;
			static_cast<ID3D11RasterizerState*>(state->getInternal())->GetDesc(&test_desc);
			return memcmp(&test_desc,&d3d_desc,sizeof(D3D11_RASTERIZER_DESC));
		}
	});
	if(mRasterizerStates.end()==iter)
	{
		auto ret=DEVILX_NEW IGARasterizerStateImp(mInternal,d3d_desc);
		mRasterizerStates.push_back(ret);
		return ret;
	}
	else
	{
		auto ret=*iter;
		ret->addRef();
		return ret;
	}
}

IGADepthStencilState * NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceImp::createDepthStencilState(const IGAStruct::SDepthStencilDesc & desc)
{
	auto d3d_desc=CUtility::mapping(desc);
	auto iter=std::find_if(mDepthStencilStates.begin(),mDepthStencilStates.end(),[&d3d_desc,this](IGADepthStencilStateImp * state)
	{
		D3D11_DEPTH_STENCIL_DESC test_desc;
		state->getInternal()->GetDesc(&test_desc);
		return memcmp(&test_desc,&d3d_desc,sizeof(D3D11_DEPTH_STENCIL_DESC));
	});
	if(mDepthStencilStates.end()==iter)
	{
		auto ret=DEVILX_NEW IGADepthStencilStateImp(mInternal,d3d_desc);
		mDepthStencilStates.push_back(ret);
		return ret;
	}
	else
	{
		auto ret=*iter;
		ret->addRef();
		return ret;
	}
}

IGASamplerState * NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceImp::createSamplerState(const IGAStruct::SSamplerDesc & desc)
{
	auto d3d_desc=CUtility::mapping(desc);
	auto iter=std::find_if(mSamplerStates.begin(),mSamplerStates.end(),[&d3d_desc,this](IGASamplerStateImp * state)
	{
		D3D11_SAMPLER_DESC test_desc;
		state->getInternal()->GetDesc(&test_desc);
		return memcmp(&test_desc,&d3d_desc,sizeof(D3D11_SAMPLER_DESC));
	});
	if(mSamplerStates.end()==iter)
	{
		auto ret=DEVILX_NEW IGASamplerStateImp(mInternal,d3d_desc);
		mSamplerStates.push_back(ret);
		return ret;
	}
	else
	{
		auto ret=*iter;
		ret->addRef();
		return ret;
	}
}

IGAVertexShader * NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceImp::createVertexShader(const std::string & code)
{
	auto ret=DEVILX_NEW IGAVertexShaderImp(mInternal,code);
	mCommonResources.push_back(ret);
	return ret;
}

IGAPixelShader * NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceImp::createPixelShader(const std::string & code)
{
	auto ret=DEVILX_NEW IGAPixelShaderImp(mInternal,code);
	mCommonResources.push_back(ret);
	return ret;
}

IGAGeometryShader * NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceImp::createGeometryShader(const std::string & code)
{
	auto ret=DEVILX_NEW IGAGeometryShaderImp(mInternal,code);
	mCommonResources.push_back(ret);
	return ret;
}

IGAHullShader * NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceImp::createHullShader(const std::string & code)
{
	auto ret=DEVILX_NEW IGAHullShaderImp(mInternal,code);
	mCommonResources.push_back(ret);
	return ret;
}

IGADomainShader * NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceImp::createDomainShader(const std::string & code)
{
	auto ret=DEVILX_NEW IGADomainShaderImp(mInternal,code);
	mCommonResources.push_back(ret);
	return ret;
}

IGAComputeShader * NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceImp::createComputeShader(const std::string & code)
{
	auto ret=DEVILX_NEW IGAComputeShaderImp(mInternal,code);
	mCommonResources.push_back(ret);
	return ret;
}

IGAProgram * NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceImp::createProgram(IGAVertexShader * vertexShader,IGAPixelShader * pixelShader,IGAGeometryShader * geometryShader,IGAHullShader * hullShader,IGADomainShader * domainShader)
{
	UInt32 shader_count=0;
	if(vertexShader)
		++shader_count;
	if(pixelShader)
		++shader_count;
	if(geometryShader)
		++shader_count;
	if(hullShader)
		++shader_count;
	if(domainShader)
		++shader_count;
	if((shader_count==0)||(shader_count>1))
		return nullptr;
	else if(vertexShader)
		return static_cast<IGAVertexShaderImp*>(vertexShader);
	else if(pixelShader)
		return static_cast<IGAPixelShaderImp*>(pixelShader);
	else if(geometryShader)
		return static_cast<IGAGeometryShaderImp*>(geometryShader);
	else if(hullShader)
		return static_cast<IGAHullShaderImp*>(hullShader);
	else
		return static_cast<IGADomainShaderImp*>(domainShader);
}

IGAProgram * NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceImp::createProgram(IGAComputeShader * computeShader)
{
	return static_cast<IGAComputeShaderImp*>(computeShader);
}

IGAShaderReflection * NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceImp::createShaderReflection(IGAProgram * program)
{
	auto blob=static_cast<IGAShaderImp*>(program)->getInternal();
	auto ret=DEVILX_NEW IGAShaderReflectionImp(blob);
	mShaderReflections.insert(ret);
	return ret;
}

Void NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceImp::destroyShaderReflection(IGAShaderReflection * reflection)
{
	mShaderReflections.destroy(static_cast<IGAShaderReflectionImp*>(reflection));
}
