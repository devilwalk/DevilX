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
	const D3D_FEATURE_LEVEL levels[]={D3D_FEATURE_LEVEL_11_1,D3D_FEATURE_LEVEL_11_0,D3D_FEATURE_LEVEL_10_1,D3D_FEATURE_LEVEL_10_0,D3D_FEATURE_LEVEL_9_3};
	D3D11CreateDevice(NULL,D3D_DRIVER_TYPE_HARDWARE,NULL,flags,levels,_countof(levels),D3D11_SDK_VERSION,&mInternal,&mFeatureLevel,nullptr);
	mContexts.push_back(DEVILX_NEW IGADeviceContextImp(mInternal,False));

	CComPtr<IDXGIDevice1> dxgi_dev;
	mInternal->QueryInterface(&dxgi_dev);
}

NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceImp::~IGADeviceImp()
{
	mCommonObjects.destroyAll();
	mInputLayouts.destroyAll();
	mRasterizerStates.destroyAll();
	mDepthStencilStates.destroyAll();
	mBlendStates.destroyAll();
	mSamplerStates.destroyAll();
	mRenderTargetViews.destroyAll();
	mDepthStencilViews.destroyAll();
	mShaderResourceViews.destroyAll();
	mContexts.destroyAll();
}

IGAEnum::EHighLevelDeviceVersion NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceImp::getVersion() const
{
	return IGAEnum::EHighLevelDeviceVersion_DirectX11;
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
	d3d_desc.CPUAccessFlags=CUtility::mappingT<IGAEnum::ECPUAccessFlag>(cpuAccessFlags);
	d3d_desc.Usage=CUtility::mapping(usage);
	D3D11_SUBRESOURCE_DATA d3d_sub_data={0};
	if(initialData)
	{
		d3d_sub_data.pSysMem=initialData;
		d3d_sub_data.SysMemPitch=sizeInByte;
		d3d_sub_data.SysMemSlicePitch=sizeInByte;
	}
	auto ret=DEVILX_NEW IGABufferImp(mInternal,d3d_desc,initialData?(&d3d_sub_data):nullptr);
	mCommonObjects.insert(ret);
	return ret;
}

IGAIndexBuffer * NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceImp::createIndexBuffer(UInt32 sizeInByte,UInt32 cpuAccessFlags,IGAEnum::EUsage usage,UInt32 bindFlags,ConstVoidPtr initialData)
{
	D3D11_BUFFER_DESC d3d_desc={0};
	d3d_desc.BindFlags=D3D11_BIND_INDEX_BUFFER|CUtility::mappingBufferBindFlags(bindFlags);
	d3d_desc.ByteWidth=sizeInByte;
	d3d_desc.CPUAccessFlags=CUtility::mappingT<IGAEnum::ECPUAccessFlag>(cpuAccessFlags);
	d3d_desc.Usage=CUtility::mapping(usage);
	D3D11_SUBRESOURCE_DATA d3d_sub_data={0};
	if(initialData)
	{
		d3d_sub_data.pSysMem=initialData;
		d3d_sub_data.SysMemPitch=sizeInByte;
		d3d_sub_data.SysMemSlicePitch=sizeInByte;
	}
	auto ret=DEVILX_NEW IGABufferImp(mInternal,d3d_desc,initialData?(&d3d_sub_data):nullptr);
	mCommonObjects.insert(ret);
	return ret;
}

IGAConstantBuffer * NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceImp::createConstantBuffer(UInt32 sizeInByte,UInt32 cpuAccessFlags,IGAEnum::EUsage usage,UInt32 bindFlags,ConstVoidPtr initialData)
{
	D3D11_BUFFER_DESC d3d_desc={0};
	d3d_desc.BindFlags=D3D11_BIND_CONSTANT_BUFFER|CUtility::mappingBufferBindFlags(bindFlags);
	d3d_desc.ByteWidth=sizeInByte;
	d3d_desc.CPUAccessFlags=CUtility::mappingT<IGAEnum::ECPUAccessFlag>(cpuAccessFlags);
	d3d_desc.Usage=CUtility::mapping(usage);
	D3D11_SUBRESOURCE_DATA d3d_sub_data={0};
	if(initialData)
	{
		d3d_sub_data.pSysMem=initialData;
		d3d_sub_data.SysMemPitch=sizeInByte;
		d3d_sub_data.SysMemSlicePitch=sizeInByte;
	}
	auto ret=DEVILX_NEW IGABufferImp(mInternal,d3d_desc,initialData?(&d3d_sub_data):nullptr);
	mCommonObjects.insert(ret);
	return ret;
}

IGAShaderResourceBuffer* NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceImp::createShaderResourceBuffer(UInt32 sizeInByte,UInt32 cpuAccessFlags,UInt32 shaderResourceBufferFlags,UInt32 structureByteStride,IGAEnum::EUsage usage,UInt32 bindFlags,ConstVoidPtr initialData)
{
	D3D11_BUFFER_DESC d3d_desc={0};
	d3d_desc.BindFlags=D3D11_BIND_SHADER_RESOURCE|CUtility::mappingBufferBindFlags(bindFlags);
	d3d_desc.ByteWidth=sizeInByte;
	d3d_desc.CPUAccessFlags=CUtility::mappingT<IGAEnum::ECPUAccessFlag>(cpuAccessFlags);
	d3d_desc.Usage=CUtility::mapping(usage);
	d3d_desc.MiscFlags=CUtility::mappingT<IGAEnum::EShaderResourceBufferFlag>(shaderResourceBufferFlags);
	if(structureByteStride)
	{
		d3d_desc.StructureByteStride=structureByteStride;
		d3d_desc.MiscFlags|=D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
		assert(d3d_desc.CPUAccessFlags==0);
	}
	D3D11_SUBRESOURCE_DATA d3d_sub_data={0};
	if(initialData)
	{
		d3d_sub_data.pSysMem=initialData;
		d3d_sub_data.SysMemPitch=sizeInByte;
		d3d_sub_data.SysMemSlicePitch=sizeInByte;
	}
	auto ret=DEVILX_NEW IGABufferImp(mInternal,d3d_desc,initialData?(&d3d_sub_data):nullptr);
	mCommonObjects.insert(ret);
	return ret;
}

IGAUnorderedAccessBuffer * NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceImp::createUnorderedAccessBuffer(UInt32 sizeInByte,UInt32 cpuAccessFlags,IGAEnum::EUsage usage,UInt32 bindFlags,ConstVoidPtr initialData)
{
	D3D11_BUFFER_DESC d3d_desc={0};
	d3d_desc.BindFlags=D3D11_BIND_UNORDERED_ACCESS|CUtility::mappingBufferBindFlags(bindFlags);
	d3d_desc.ByteWidth=sizeInByte;
	d3d_desc.CPUAccessFlags=CUtility::mappingT<IGAEnum::ECPUAccessFlag>(cpuAccessFlags);
	d3d_desc.Usage=CUtility::mapping(usage);
	D3D11_SUBRESOURCE_DATA d3d_sub_data={0};
	if(initialData)
	{
		d3d_sub_data.pSysMem=initialData;
		d3d_sub_data.SysMemPitch=sizeInByte;
		d3d_sub_data.SysMemSlicePitch=sizeInByte;
	}
	auto ret=DEVILX_NEW IGABufferImp(mInternal,d3d_desc,initialData?(&d3d_sub_data):nullptr);
	mCommonObjects.insert(ret);
	return ret;
}

IGATexture1D * NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceImp::createTexture1D(UInt32 length,IGAEnum::EUsage usage,IGAEnum::EGIFormat format,UInt32 cpuAccessFlags,UInt32 bindFlags,UInt32 mipLevelCount,UInt32 arrayCount,const IGAStruct::SSubResourceData * initialData)
{
	D3D11_TEXTURE1D_DESC d3d_desc={0};
	d3d_desc.ArraySize=arrayCount;
	d3d_desc.BindFlags=CUtility::mappingTextureBindFlags(bindFlags);
	d3d_desc.CPUAccessFlags=CUtility::mappingT<IGAEnum::ECPUAccessFlag>(cpuAccessFlags);
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
	mCommonObjects.insert(ret);
	return ret;
}

IGATexture2D * NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceImp::createTexture2D(UInt32 width,UInt32 height,IGAEnum::EUsage usage,IGAEnum::EGIFormat format,UInt32 cpuAccessFlags,UInt32 bindFlags,UInt32 mipLevelCount,UInt32 arrayCount,const IGAStruct::SSubResourceData * initialData)
{
	D3D11_TEXTURE2D_DESC d3d_desc={0};
	d3d_desc.ArraySize=arrayCount;
	d3d_desc.BindFlags=CUtility::mappingTextureBindFlags(bindFlags);
	d3d_desc.CPUAccessFlags=CUtility::mappingT<IGAEnum::ECPUAccessFlag>(cpuAccessFlags);
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
	mCommonObjects.insert(ret);
	return ret;
}

IGATexture3D * NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceImp::createTexture3D(UInt32 width,UInt32 height,UInt32 depth,IGAEnum::EUsage usage,IGAEnum::EGIFormat format,UInt32 cpuAccessFlags,UInt32 bindFlags,UInt32 mipLevelCount,const IGAStruct::SSubResourceData * initialData)
{
	D3D11_TEXTURE3D_DESC d3d_desc={0};
	d3d_desc.BindFlags=CUtility::mappingTextureBindFlags(bindFlags);
	d3d_desc.CPUAccessFlags=CUtility::mappingT<IGAEnum::ECPUAccessFlag>(cpuAccessFlags);
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
	mCommonObjects.insert(ret);
	return ret;
}

IGATexture2D * NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceImp::createTextureCube(UInt32 width,UInt32 height,IGAEnum::EUsage usage,IGAEnum::EGIFormat format,UInt32 cpuAccessFlags,UInt32 bindFlags,UInt32 mipLevelCount,UInt32 arrayCount,const IGAStruct::SSubResourceData * initialData)
{
	D3D11_TEXTURE2D_DESC d3d_desc={0};
	d3d_desc.ArraySize=arrayCount*6;
	d3d_desc.BindFlags=CUtility::mappingTextureBindFlags(bindFlags);
	d3d_desc.CPUAccessFlags=CUtility::mappingT<IGAEnum::ECPUAccessFlag>(cpuAccessFlags);
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
	mCommonObjects.insert(ret);
	return ret;
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
		auto & descs=il->getInputElementDescs();
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
	auto d3d_desc=CUtility::mappingT<IGAStruct::SBlendDesc,CD3D11_BLEND_DESC>(desc);
	auto iter=std::find_if(mBlendStates.begin(),mBlendStates.end(),[&d3d_desc](IGABlendStateImp * state)
	{
		D3D11_BLEND_DESC test_desc;
		state->getInternal()->GetDesc(reinterpret_cast<D3D11_BLEND_DESC*>(&test_desc));
		return memcmp(&test_desc,&d3d_desc,sizeof(D3D11_BLEND_DESC));
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
	auto d3d_desc=CUtility::mappingT<IGAStruct::SRasterizerDesc,CD3D11_RASTERIZER_DESC>(desc);
	auto iter=std::find_if(mRasterizerStates.begin(),mRasterizerStates.end(),[&d3d_desc](IGARasterizerStateImp*state)
		{
			D3D11_RASTERIZER_DESC test_desc;
			static_cast<ID3D11RasterizerState *>(state->getInternal())->GetDesc(&test_desc);
			return memcmp(&test_desc,&d3d_desc,sizeof(D3D11_RASTERIZER_DESC));
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
	auto ret=DEVILX_NEW IGAVertexShaderImp(mInternal,code.c_str());
	mCommonObjects.insert(ret);
	return ret;
}

IGAPixelShader * NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceImp::createPixelShader(const std::string & code)
{
	auto ret=DEVILX_NEW IGAPixelShaderImp(mInternal,code.c_str());
	mCommonObjects.insert(ret);
	return ret;
}

IGAGeometryShader * NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceImp::createGeometryShader(const std::string & code)
{
	auto ret=DEVILX_NEW IGAGeometryShaderImp(mInternal,code.c_str());
	mCommonObjects.insert(ret);
	return ret;
}

IGAHullShader * NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceImp::createHullShader(const std::string & code)
{
	auto ret=DEVILX_NEW IGAHullShaderImp(mInternal,code.c_str());
	mCommonObjects.insert(ret);
	return ret;
}

IGADomainShader * NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceImp::createDomainShader(const std::string & code)
{
	auto ret=DEVILX_NEW IGADomainShaderImp(mInternal,code.c_str());
	mCommonObjects.insert(ret);
	return ret;
}

IGAComputeShader * NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceImp::createComputeShader(const std::string & code)
{
	auto ret=DEVILX_NEW IGAComputeShaderImp(mInternal,code.c_str());
	mCommonObjects.insert(ret);
	return ret;
}

IGAProgram * NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceImp::createProgram(IGAVertexShader * vertexShader,IGAPixelShader * pixelShader,IGAGeometryShader * geometryShader,IGAHullShader * hullShader,IGADomainShader * domainShader)
{
	auto ret=DEVILX_NEW IGAProgramImp(static_cast<IGAVertexShaderImp*>(vertexShader),static_cast<IGAPixelShaderImp*>(pixelShader),static_cast<IGAGeometryShaderImp*>(geometryShader),static_cast<IGAHullShaderImp*>(hullShader),static_cast<IGADomainShaderImp*>(domainShader));
	mCommonObjects.insert(ret);
	return ret;
}

IGAProgramReflection * NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceImp::createReflection(IGAProgram * program)
{
	std::array<ID3DBlob*,5> blobs={nullptr};
	for(SizeT i=0;i<5;++i)
	{
		auto shader=static_cast<IGAProgramImp*>(program)->getShaders()[i];
		if(shader)
		{
			blobs[i]=shader->getInternal();
		}
	}
	auto ret=DEVILX_NEW IGAProgramReflectionImp(&blobs[0],5);
	mCommonObjects.insert(ret);
	return ret;
}

Void NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceImp::destroyReflection(IGAProgramReflection * reflection)
{
	mCommonObjects.destroy(static_cast<IGAProgramReflectionImp*>(reflection));
}

IGAProgramParameter* NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceImp::createProgramParameter()
{
	auto ret=DEVILX_NEW IGAProgramParameterImp();
	mCommonObjects.insert(ret);
	return ret;
}

Void NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceImp::destroyProgramParameter(IGAProgramParameter* parameter)
{
	mCommonObjects.destroy(static_cast<IGAProgramParameterImp*>(parameter));
}

IGAShaderParameter* NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceImp::createShaderParameter()
{
	return nullptr;
}

IGAComputeShaderParameter* NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceImp::createComputeShaderParameter()
{
	return nullptr;
}

Void NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceImp::destroyShaderParameter(IGAShaderParameter* parameter)
{
	return Void();
}

IGARenderTargetView * NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceImp::createRenderTargetView(IGATexture1D * resource,UInt32 mipSlice,UInt32 firstArraySlice)
{
	D3D11_RENDER_TARGET_VIEW_DESC * desc_ptr=nullptr;
	D3D11_RENDER_TARGET_VIEW_DESC desc;
	if((mipSlice>0)
		||(firstArraySlice>0)
		)
	{
		desc.Format=DXGI_FORMAT_UNKNOWN;
		desc.ViewDimension=firstArraySlice>0?D3D11_RTV_DIMENSION_TEXTURE1DARRAY:D3D11_RTV_DIMENSION_TEXTURE1D;
		desc.Texture1DArray.MipSlice=mipSlice;
		desc.Texture1DArray.FirstArraySlice=firstArraySlice;
		desc.Texture1DArray.ArraySize=1;
		desc_ptr=&desc;
	}
	auto iter=std::find_if(mRenderTargetViews.begin(),mRenderTargetViews.end(),[&desc,this](IGARenderTargetViewImp*view)
		{
			D3D11_RENDER_TARGET_VIEW_DESC test_desc;
			view->getInternal()->GetDesc(&test_desc);
			return memcmp(&test_desc,&desc,sizeof(D3D11_RENDER_TARGET_VIEW_DESC));
		});
	IGARenderTargetViewImp * ret=nullptr;
	if(mRenderTargetViews.end()==iter)
	{
		ret=_create(static_cast<IGATexture1DImp *>(resource)->getInternal(),desc_ptr);
	}
	else
	{
		ret=*iter;
	}
	return ret;
}

IGARenderTargetView * NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceImp::createRenderTargetView(IGATexture2D * resource,UInt32 mipSlice,UInt32 firstArraySlice)
{
	D3D11_RENDER_TARGET_VIEW_DESC * desc_ptr=nullptr;
	D3D11_RENDER_TARGET_VIEW_DESC desc;
	if((mipSlice>0)
		||(firstArraySlice>0)
		)
	{
		desc.Format=DXGI_FORMAT_UNKNOWN;
		desc.ViewDimension=firstArraySlice>0?D3D11_RTV_DIMENSION_TEXTURE2DARRAY:D3D11_RTV_DIMENSION_TEXTURE2D;
		desc.Texture2DArray.MipSlice=mipSlice;
		desc.Texture2DArray.FirstArraySlice=firstArraySlice;
		desc.Texture2DArray.ArraySize=1;
		desc_ptr=&desc;
	}
	auto iter=std::find_if(mRenderTargetViews.begin(),mRenderTargetViews.end(),[&desc,this](IGARenderTargetViewImp*view)
		{
			D3D11_RENDER_TARGET_VIEW_DESC test_desc;
			view->getInternal()->GetDesc(&test_desc);
			return memcmp(&test_desc,&desc,sizeof(D3D11_RENDER_TARGET_VIEW_DESC));
		});
	IGARenderTargetViewImp * ret=nullptr;
	if(mRenderTargetViews.end()==iter)
	{
		ret=_create(static_cast<IGATexture2DImp*>(resource)->getInternal(),desc_ptr);
	}
	else
	{
		ret=*iter;
	}
	return ret;
}

IGARenderTargetView* NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceImp::createRenderTargetView(IGATexture3D* resource,UInt32 mipSlice,UInt32 firstDepthSlice)
{
	D3D11_RENDER_TARGET_VIEW_DESC * desc_ptr=nullptr;
	D3D11_RENDER_TARGET_VIEW_DESC desc;
	if((mipSlice>0)
		||(firstDepthSlice>0)
		)
	{
		desc.Format=DXGI_FORMAT_UNKNOWN;
		desc.ViewDimension=D3D11_RTV_DIMENSION_TEXTURE3D;
		desc.Texture3D.MipSlice=mipSlice;
		desc.Texture3D.FirstWSlice=firstDepthSlice;
		desc.Texture3D.WSize=1;
		desc_ptr=&desc;
	}
	auto iter=std::find_if(mRenderTargetViews.begin(),mRenderTargetViews.end(),[&desc,this](IGARenderTargetViewImp*view)
		{
			D3D11_RENDER_TARGET_VIEW_DESC test_desc;
			view->getInternal()->GetDesc(&test_desc);
			return memcmp(&test_desc,&desc,sizeof(D3D11_RENDER_TARGET_VIEW_DESC));
		});
	IGARenderTargetViewImp * ret=nullptr;
	if(mRenderTargetViews.end()==iter)
	{
		ret=_create(static_cast<IGATexture3DImp *>(resource)->getInternal(),desc_ptr);
	}
	else
	{
		ret=*iter;
	}
	return ret;
}

IGADepthStencilView* NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceImp::createDepthStencilView(IGATexture1D* resource,UInt32 mipSlice,UInt32 firstArraySlice)
{
	D3D11_DEPTH_STENCIL_VIEW_DESC * desc_ptr=nullptr;
	D3D11_DEPTH_STENCIL_VIEW_DESC desc;
	if((mipSlice>0)
		||(firstArraySlice>0)
		)
	{
		desc.Format=DXGI_FORMAT_UNKNOWN;
		desc.ViewDimension=firstArraySlice>0?D3D11_DSV_DIMENSION_TEXTURE1DARRAY:D3D11_DSV_DIMENSION_TEXTURE1D;
		desc.Texture1DArray.MipSlice=mipSlice;
		desc.Texture1DArray.FirstArraySlice=firstArraySlice;
		desc.Texture1DArray.ArraySize=1;
		desc_ptr=&desc;
	}
	auto iter=std::find_if(mDepthStencilViews.begin(),mDepthStencilViews.end(),[&desc,this](IGADepthStencilViewImp*view)
		{
			D3D11_DEPTH_STENCIL_VIEW_DESC test_desc;
			view->getInternal()->GetDesc(&test_desc);
			return memcmp(&test_desc,&desc,sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));
		});
	IGADepthStencilViewImp * ret=nullptr;
	if(mDepthStencilViews.end()==iter)
	{
		ret=_create(static_cast<IGATexture1DImp *>(resource)->getInternal(),desc_ptr);
	}
	else
	{
		ret=*iter;
	}
	return ret;
}

IGADepthStencilView* NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceImp::createDepthStencilView(IGATexture2D* resource,UInt32 mipSlice,UInt32 firstArraySlice)
{
	D3D11_DEPTH_STENCIL_VIEW_DESC * desc_ptr=nullptr;
	D3D11_DEPTH_STENCIL_VIEW_DESC desc;
	if((mipSlice>0)
		||(firstArraySlice>0)
		)
	{
		desc.Format=DXGI_FORMAT_UNKNOWN;
		desc.ViewDimension=firstArraySlice>0?D3D11_DSV_DIMENSION_TEXTURE2DARRAY:D3D11_DSV_DIMENSION_TEXTURE2D;
		desc.Texture2DArray.MipSlice=mipSlice;
		desc.Texture2DArray.FirstArraySlice=firstArraySlice;
		desc.Texture2DArray.ArraySize=1;
		desc_ptr=&desc;
	}
	auto iter=std::find_if(mDepthStencilViews.begin(),mDepthStencilViews.end(),[&desc,this](IGADepthStencilViewImp*view)
		{
			D3D11_DEPTH_STENCIL_VIEW_DESC test_desc;
			view->getInternal()->GetDesc(&test_desc);
			return memcmp(&test_desc,&desc,sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));
		});
	IGADepthStencilViewImp * ret=nullptr;
	if(mDepthStencilViews.end()==iter)
	{
		ret=_create(static_cast<IGATexture2DImp *>(resource)->getInternal(),desc_ptr);
	}
	else
	{
		ret=*iter;
	}
	return ret;
}

IGATextureView* NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceImp::createShaderResourceView(IGATexture1D * resource,UInt32 mostDetailedMip,UInt32 numMipLevels,UInt32 firstArraySlice,UInt32 arrayCount)
{
	D3D11_SHADER_RESOURCE_VIEW_DESC * desc_ptr=nullptr;
	D3D11_SHADER_RESOURCE_VIEW_DESC desc;
	if((mostDetailedMip>0)
		||(static_cast<UInt32>(-1)!=numMipLevels)
		||(firstArraySlice>0)
		||(arrayCount>0)
		)
	{
		desc.Format=DXGI_FORMAT_UNKNOWN;
		desc.ViewDimension=arrayCount>1?D3D11_SRV_DIMENSION_TEXTURE1DARRAY:D3D11_SRV_DIMENSION_TEXTURE1D;
		desc.Texture1DArray.MostDetailedMip=mostDetailedMip;
		desc.Texture1DArray.MipLevels=numMipLevels;
		desc.Texture1DArray.FirstArraySlice=firstArraySlice;
		desc.Texture1DArray.ArraySize=arrayCount;
		desc_ptr=&desc;
	}
	auto iter=std::find_if(mShaderResourceViews.begin(),mShaderResourceViews.end(),[&desc,resource](IGAShaderResourceViewImp*view)
		{
			D3D11_SHADER_RESOURCE_VIEW_DESC test_desc;
			view->getInternal()->GetDesc(&test_desc);
			CComPtr<ID3D11Resource> test_res;
			view->getInternal()->GetResource(&test_res);
			return memcmp(&test_desc,&desc,sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC))&&(static_cast<IGATexture1DImp*>(resource)->getInternal()==test_res);
		});
	IGAShaderResourceViewImp * ret=nullptr;
	if(mShaderResourceViews.end()==iter)
	{
		ret=_create(static_cast<IGATexture1DImp *>(resource)->getInternal(),desc_ptr);
	}
	else
	{
		ret=*iter;
	}
	return ret;
}

IGATextureView* NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceImp::createShaderResourceView(IGATexture2D* resource,UInt32 mostDetailedMip,UInt32 numMipLevels,UInt32 firstArraySlice,UInt32 arrayCount)
{
	D3D11_SHADER_RESOURCE_VIEW_DESC * desc_ptr=nullptr;
	D3D11_SHADER_RESOURCE_VIEW_DESC desc;
	if((mostDetailedMip>0)
		||(static_cast<UInt32>(-1)!=numMipLevels)
		||(firstArraySlice>0)
		||(arrayCount>0)
		)
	{
		desc.Format=DXGI_FORMAT_UNKNOWN;
		desc.ViewDimension=arrayCount>1?D3D11_SRV_DIMENSION_TEXTURE2DARRAY:D3D11_SRV_DIMENSION_TEXTURE2D;
		desc.Texture2DArray.MostDetailedMip=mostDetailedMip;
		desc.Texture2DArray.MipLevels=numMipLevels;
		desc.Texture2DArray.FirstArraySlice=firstArraySlice;
		desc.Texture2DArray.ArraySize=arrayCount;
		desc_ptr=&desc;
	}
	auto iter=std::find_if(mShaderResourceViews.begin(),mShaderResourceViews.end(),[&desc,resource](IGAShaderResourceViewImp*view)
		{
			D3D11_SHADER_RESOURCE_VIEW_DESC test_desc;
			view->getInternal()->GetDesc(&test_desc);
			CComPtr<ID3D11Resource> test_res;
			view->getInternal()->GetResource(&test_res);
			return memcmp(&test_desc,&desc,sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC))&&(static_cast<IGATexture2DImp*>(resource)->getInternal()==test_res);
		});
	IGAShaderResourceViewImp * ret=nullptr;
	if(mShaderResourceViews.end()==iter)
	{
		ret=_create(static_cast<IGATexture2DImp *>(resource)->getInternal(),desc_ptr);
	}
	else
	{
		ret=*iter;
	}
	return ret;
}

IGATextureView* NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceImp::createShaderResourceView(IGATexture3D* resource,UInt32 mostDetailedMip,UInt32 numMipLevels)
{
	D3D11_SHADER_RESOURCE_VIEW_DESC * desc_ptr=nullptr;
	D3D11_SHADER_RESOURCE_VIEW_DESC desc;
	if((mostDetailedMip>0)
		||(static_cast<UInt32>(-1)!=numMipLevels)
		)
	{
		desc.Format=DXGI_FORMAT_UNKNOWN;
		desc.ViewDimension=D3D11_SRV_DIMENSION_TEXTURE3D;
		desc.Texture3D.MostDetailedMip=mostDetailedMip;
		desc.Texture3D.MipLevels=numMipLevels;
		desc_ptr=&desc;
	}
	auto iter=std::find_if(mShaderResourceViews.begin(),mShaderResourceViews.end(),[&desc,resource](IGAShaderResourceViewImp*view)
		{
			D3D11_SHADER_RESOURCE_VIEW_DESC test_desc;
			view->getInternal()->GetDesc(&test_desc);
			CComPtr<ID3D11Resource> test_res;
			view->getInternal()->GetResource(&test_res);
			return memcmp(&test_desc,&desc,sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC))&&(static_cast<IGATexture3DImp*>(resource)->getInternal()==test_res);
		});
	IGAShaderResourceViewImp * ret=nullptr;
	if(mShaderResourceViews.end()==iter)
	{
		ret=_create(static_cast<IGATexture3DImp *>(resource)->getInternal(),desc_ptr);
	}
	else
	{
		ret=*iter;
	}
	return ret;
}

IGAUnorderedAccessView* NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceImp::createUnorderedAccessView(IGATexture1D* resource,UInt32 mipSlice,UInt32 firstArraySlice,UInt32 arrayCount)
{
	return nullptr;
}

IGAUnorderedAccessView* NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceImp::createUnorderedAccessView(IGATexture2D* resource,UInt32 mipSlice,UInt32 firstArraySlice,UInt32 arrayCount)
{
	return nullptr;
}

IGAUnorderedAccessView* NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceImp::createUnorderedAccessView(IGATexture3D* resource,UInt32 mipSlice,UInt32 firstDepthSlice,UInt32 depthCount)
{
	return nullptr;
}

IGARenderTargetViewImp * NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceImp::_create(ID3D11Resource * resource,const D3D11_RENDER_TARGET_VIEW_DESC * desc)
{
	IGARenderTargetViewImp * ret=DEVILX_NEW IGARenderTargetViewImp(mInternal,resource,desc);
	mRenderTargetViews.push_back(ret);
	return ret;
}

IGADepthStencilViewImp * NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceImp::_create(ID3D11Resource * resource,const D3D11_DEPTH_STENCIL_VIEW_DESC * desc)
{
	IGADepthStencilViewImp * ret=DEVILX_NEW IGADepthStencilViewImp(mInternal,resource,desc);
	mDepthStencilViews.push_back(ret);
	return ret;
}

IGAShaderResourceViewImp* NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceImp::_create(ID3D11Resource* resource,const D3D11_SHADER_RESOURCE_VIEW_DESC* desc)
{
	IGAShaderResourceViewImp* ret=DEVILX_NEW IGAShaderResourceViewImp(mInternal,resource,desc);
	mShaderResourceViews.push_back(ret);
	return ret;
}

IGAShaderResourceBufferView* NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceImp::createShaderResourceView(IGAShaderResourceBuffer* resource,IGAEnum::EGIFormat format,UInt32 elementOffset,UInt32 numElements)
{
	D3D11_SHADER_RESOURCE_VIEW_DESC desc;
	desc.Format=CUtility::mapping(format);
	desc.ViewDimension=D3D11_SRV_DIMENSION_BUFFER;
	desc.Buffer.ElementOffset=elementOffset;
	if(static_cast<UInt32>(-1)==numElements)
	{
		D3D11_BUFFER_DESC buffer_desc;
		static_cast<IGABufferImp*>(resource)->getInternal()->GetDesc(&buffer_desc);
		auto struct_size=1;
		if(buffer_desc.StructureByteStride)
		{
			struct_size=buffer_desc.StructureByteStride;
		}
		else if(IGAEnum::EGIFormat_UNKNOWN!=format)
		{
			struct_size=CUtility::getComponentSize(format)*CUtility::getComponentCount(format);
		}
		desc.Buffer.NumElements=buffer_desc.ByteWidth/struct_size;
	}
	else
		desc.Buffer.NumElements=numElements;
	auto iter=std::find_if(mShaderResourceViews.begin(),mShaderResourceViews.end(),[&desc,resource](IGAShaderResourceViewImp*view)
		{
			D3D11_SHADER_RESOURCE_VIEW_DESC test_desc;
			view->getInternal()->GetDesc(&test_desc);
			CComPtr<ID3D11Resource> test_res;
			view->getInternal()->GetResource(&test_res);
			return memcmp(&test_desc,&desc,sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC))&&(test_res==static_cast<IGABufferImp*>(resource)->getInternal());
		});
	IGAShaderResourceViewImp* ret=nullptr;
	if(mShaderResourceViews.end()==iter)
	{
		ret=_create(static_cast<IGABufferImp*>(resource)->getInternal(),&desc);
	}
	else
	{
		ret=*iter;
	}
	return ret;
}

IGAVertexArrayObject* NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceImp::createVertexArrayObject(const TVector<IGAStruct::SVAOElementDesc>& inputElements)
{
	return nullptr;
}

IGAHighLevelDeviceFeature_SeparateVAO* NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceImp::queryFeature_SeparateVAO() const
{
	return const_cast<IGADeviceImp*>(this);
}

IGAHighLevelDeviceFeature_ComputeShader* NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceImp::queryFeature_ComputeShader() const
{
	return const_cast<IGADeviceImp*>(this);
}

IGAHighLevelDeviceFeature_SeparateProgram* NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceImp::queryFeature_SeparateProgram() const
{
	return const_cast<IGADeviceImp*>(this);
}

IGADevice* NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceImp::queryInterface_IGADevice() const
{
	return const_cast<IGADeviceImp*>(this);
}

IGAShaderReflection* NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceImp::createReflection(IGAShader* shader)
{
	auto ret=DEVILX_NEW IGAShaderReflectionImp(static_cast<TGAD3DResourceImp<IGAShader,ID3DBlob>*>(shader)->getInternal());
	mCommonObjects.insert(ret);
	return ret;
}

Void NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceImp::destroyReflection(IGAShaderReflection* reflection)
{
	mCommonObjects.destroy(static_cast<IGAShaderReflectionImp*>(reflection));
}
