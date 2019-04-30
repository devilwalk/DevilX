#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSCore;
using namespace NSOpenGL;

IGADeviceImp::IGADeviceImp(IGAEnum::EDeviceVersion version)
	:mVersion(version)
	,mEnvironment(nullptr)
{
}

Void NSDevilX::NSCore::NSOpenGL::IGADeviceImp::setEnvironment(CGAEnvironment* env)
{
	mEnvironment=env;
}

IGADeviceImp::~IGADeviceImp()
{
	mCommonObjects.destroyAll();
	mInputLayouts.destroyAll();
	mSamplerStates.destroyAll();
	mRenderTargetViews.destroyAll();
	mDepthStencilViews.destroyAll();
}

IGAEnum::EDeviceVersion NSDevilX::NSCore::NSOpenGL::IGADeviceImp::getVersion() const
{
	return mVersion;
}

IGADeviceContext * NSDevilX::NSCore::NSOpenGL::IGADeviceImp::getImmediateContext() const
{
	return const_cast<IGADeviceImp*>(this);
}

IGADeviceContext * NSDevilX::NSCore::NSOpenGL::IGADeviceImp::createDeferredContext()
{
	return nullptr;
}

IGAVertexBuffer* NSDevilX::NSCore::NSOpenGL::IGADeviceImp::createVertexBuffer(UInt32 sizeInByte,UInt32 cpuAccessFlags,IGAEnum::EUsage usage,UInt32 bindFlags,ConstVoidPtr initialData)
{
	auto ret=DEVILX_NEW IGABufferImp(GL_ARRAY_BUFFER,sizeInByte,CUtility::mapping(usage,cpuAccessFlags),initialData);
	mCommonObjects.insert(ret);
	return ret;
}

IGAIndexBuffer* NSDevilX::NSCore::NSOpenGL::IGADeviceImp::createIndexBuffer(UInt32 sizeInByte,UInt32 cpuAccessFlags,IGAEnum::EUsage usage,UInt32 bindFlags,ConstVoidPtr initialData)
{
	auto ret=DEVILX_NEW IGABufferImp(GL_ELEMENT_ARRAY_BUFFER,sizeInByte,CUtility::mapping(usage,cpuAccessFlags),initialData);
	mCommonObjects.insert(ret);
	return ret;
}

IGAConstantBuffer* NSDevilX::NSCore::NSOpenGL::IGADeviceImp::createConstantBuffer(UInt32 sizeInByte,UInt32 cpuAccessFlags,IGAEnum::EUsage usage,UInt32 bindFlags,ConstVoidPtr initialData)
{
	auto ret=DEVILX_NEW IGABufferImp(GL_UNIFORM_BUFFER,sizeInByte,CUtility::mapping(usage,cpuAccessFlags),initialData);
	mCommonObjects.insert(ret);
	return ret;
}

IGAUnorderedAccessBuffer* NSDevilX::NSCore::NSOpenGL::IGADeviceImp::createUnorderedAccessBuffer(UInt32 sizeInByte,UInt32 cpuAccessFlags,IGAEnum::EUsage usage,UInt32 bindFlags,ConstVoidPtr initialData)
{
	auto ret=DEVILX_NEW IGABufferImp(GL_SHADER_STORAGE_BUFFER,sizeInByte,CUtility::mapping(usage,cpuAccessFlags),initialData);
	mCommonObjects.insert(ret);
	return ret;
}

IGATexture1D* NSDevilX::NSCore::NSOpenGL::IGADeviceImp::createTexture1D(UInt32 length,IGAEnum::EUsage usage,IGAEnum::EGIFormat format,UInt32 cpuAccessFlags,UInt32 bindFlags,UInt32 mipLevelCount,UInt32 arrayCount,const IGAStruct::SSubResourceData* initialData)
{
	auto ret=DEVILX_NEW IGATextureImp(length,CUtility::getInternalFormat(format),mipLevelCount,arrayCount,initialData);
	mCommonObjects.insert(ret);
	return ret;
}

IGATexture2D* NSDevilX::NSCore::NSOpenGL::IGADeviceImp::createTexture2D(UInt32 width,UInt32 height,IGAEnum::EUsage usage,IGAEnum::EGIFormat format,UInt32 cpuAccessFlags,UInt32 bindFlags,UInt32 mipLevelCount,UInt32 arrayCount,const IGAStruct::SSubResourceData* initialData)
{
	auto ret=DEVILX_NEW IGATextureImp(width,height,CUtility::getInternalFormat(format),mipLevelCount,arrayCount,False,initialData);
	mCommonObjects.insert(ret);
	return ret;
}

IGATexture3D* NSDevilX::NSCore::NSOpenGL::IGADeviceImp::createTexture3D(UInt32 width,UInt32 height,UInt32 depth,IGAEnum::EUsage usage,IGAEnum::EGIFormat format,UInt32 cpuAccessFlags,UInt32 bindFlags,UInt32 mipLevelCount,const IGAStruct::SSubResourceData* initialData)
{
	auto ret=DEVILX_NEW IGATextureImp(width,height,depth,CUtility::getInternalFormat(format),mipLevelCount,initialData);
	mCommonObjects.insert(ret);
	return ret;
}

IGATexture2D* NSDevilX::NSCore::NSOpenGL::IGADeviceImp::createTextureCube(UInt32 width,UInt32 height,IGAEnum::EUsage usage,IGAEnum::EGIFormat format,UInt32 cpuAccessFlags,UInt32 bindFlags,UInt32 mipLevelCount,UInt32 arrayCount,const IGAStruct::SSubResourceData* initialData)
{
	auto ret=DEVILX_NEW IGATextureImp(width,height,CUtility::getInternalFormat(format),mipLevelCount,arrayCount,True,initialData);
	mCommonObjects.insert(ret);
	return ret;
}

IGARenderTargetView* NSDevilX::NSCore::NSOpenGL::IGADeviceImp::createRenderTargetView(IGATexture1D* resource,UInt32 mipSlice,UInt32 firstArraySlice)
{
	return _createRenderTargetView(static_cast<IGATextureImp*>(resource),mipSlice,firstArraySlice);
}

IGARenderTargetView* NSDevilX::NSCore::NSOpenGL::IGADeviceImp::createRenderTargetView(IGATexture2D* resource,UInt32 mipSlice,UInt32 firstArraySlice)
{
	return _createRenderTargetView(static_cast<IGATextureImp*>(resource),mipSlice,firstArraySlice);
}

IGARenderTargetView* NSDevilX::NSCore::NSOpenGL::IGADeviceImp::createRenderTargetView(IGATexture3D* resource,UInt32 mipSlice,UInt32 firstDepthSlice)
{
	return _createRenderTargetView(static_cast<IGATextureImp*>(resource),mipSlice,firstDepthSlice);
}

IGADepthStencilView* NSDevilX::NSCore::NSOpenGL::IGADeviceImp::createDepthStencilView(IGATexture1D* resource,UInt32 mipSlice,UInt32 firstArraySlice)
{
	return _createDepthStencilView(static_cast<IGATextureImp*>(resource),mipSlice,firstArraySlice);
}

IGADepthStencilView* NSDevilX::NSCore::NSOpenGL::IGADeviceImp::createDepthStencilView(IGATexture2D* resource,UInt32 mipSlice,UInt32 firstArraySlice)
{
	return _createDepthStencilView(static_cast<IGATextureImp*>(resource),mipSlice,firstArraySlice);
}

IGATextureView* NSDevilX::NSCore::NSOpenGL::IGADeviceImp::createShaderResourceView(IGATexture1D* resource,UInt32 mostDetailedMip,UInt32 numMipLevels,UInt32 firstArraySlice,UInt32 arrayCount)
{
	return nullptr;
}

IGATextureView* NSDevilX::NSCore::NSOpenGL::IGADeviceImp::createShaderResourceView(IGATexture2D* resource,UInt32 mostDetailedMip,UInt32 numMipLevels,UInt32 firstArraySlice,UInt32 arrayCount)
{
	return nullptr;
}

IGATextureView* NSDevilX::NSCore::NSOpenGL::IGADeviceImp::createShaderResourceView(IGATexture3D* resource,UInt32 mostDetailedMip,UInt32 numMipLevels)
{
	return nullptr;
}

IGAUnorderedAccessView* NSDevilX::NSCore::NSOpenGL::IGADeviceImp::createUnorderedAccessView(IGATexture1D* resource,UInt32 mipSlice,UInt32 firstArraySlice,UInt32 arrayCount)
{
	return nullptr;
}

IGAUnorderedAccessView* NSDevilX::NSCore::NSOpenGL::IGADeviceImp::createUnorderedAccessView(IGATexture2D* resource,UInt32 mipSlice,UInt32 firstArraySlice,UInt32 arrayCount)
{
	return nullptr;
}

IGAUnorderedAccessView* NSDevilX::NSCore::NSOpenGL::IGADeviceImp::createUnorderedAccessView(IGATexture3D* resource,UInt32 mipSlice,UInt32 firstDepthSlice,UInt32 depthCount)
{
	return nullptr;
}

IGAInputLayout* NSDevilX::NSCore::NSOpenGL::IGADeviceImp::createInputLayout(const TVector<IGAStruct::SInputElementDesc>& inputElements)
{
	auto iter=std::find_if(mInputLayouts.begin(),mInputLayouts.end(),[&inputElements](IGAInputLayoutImp*il)
		{
			auto& descs=il->getInputElementDescs();
			if(descs.size()!=inputElements.size())
				return false;
			for(SizeT i=0,count=descs.size();i<count;++i)
			{
				if((descs[i].AlignedByteOffset!=inputElements[i].AlignedByteOffset)
					||(descs[i].Format!=inputElements[i].Format)
					||(descs[i].InputSlot!=inputElements[i].InputSlot)
					||(descs[i].InstanceDataStepRate!=inputElements[i].InstanceDataStepRate)
					||(descs[i].SemanticIndex!=inputElements[i].SemanticIndex)
					||strcmp(descs[i].SemanticName,inputElements[i].SemanticName)
					)
				{
					return false;
				}
			}
			return true;
		});
	if(mInputLayouts.end()==iter)
	{
		auto ret=DEVILX_NEW IGAInputLayoutImp(inputElements);
		mInputLayouts.push_back(ret);
		return ret;
	}
	else
	{
		return *iter;
	}
}

IGAVertexShader* NSDevilX::NSCore::NSOpenGL::IGADeviceImp::createVertexShader(const std::string& code)
{
	auto ret=DEVILX_NEW IGAShaderImp(code,IGAEnum::EShaderType_Vertex);
	mCommonObjects.insert(ret);
	return ret;
}

IGAPixelShader* NSDevilX::NSCore::NSOpenGL::IGADeviceImp::createPixelShader(const std::string& code)
{
	auto ret=DEVILX_NEW IGAShaderImp(code,IGAEnum::EShaderType_Pixel);
	mCommonObjects.insert(ret);
	return ret;
}

IGAGeometryShader* NSDevilX::NSCore::NSOpenGL::IGADeviceImp::createGeometryShader(const std::string& code)
{
	auto ret=DEVILX_NEW IGAShaderImp(code,IGAEnum::EShaderType_Geometry);
	mCommonObjects.insert(ret);
	return ret;
}

IGAHullShader* NSDevilX::NSCore::NSOpenGL::IGADeviceImp::createHullShader(const std::string& code)
{
	auto ret=DEVILX_NEW IGAShaderImp(code,IGAEnum::EShaderType_Hull);
	mCommonObjects.insert(ret);
	return ret;
}

IGADomainShader* NSDevilX::NSCore::NSOpenGL::IGADeviceImp::createDomainShader(const std::string& code)
{
	auto ret=DEVILX_NEW IGAShaderImp(code,IGAEnum::EShaderType_Domain);
	mCommonObjects.insert(ret);
	return ret;
}

IGAComputeShader* NSDevilX::NSCore::NSOpenGL::IGADeviceImp::createComputeShader(const std::string& code)
{
	auto ret=DEVILX_NEW IGAShaderImp(code,IGAEnum::EShaderType_Compute);
	mCommonObjects.insert(ret);
	return ret;
}

IGABlendState* NSDevilX::NSCore::NSOpenGL::IGADeviceImp::createBlendState(const IGAStruct::SBlendDesc& desc)
{
	auto iter=std::find_if(mBlendStates.begin(),mBlendStates.end(),[&desc](IGABlendStateImp*state)
		{
			return 0==memcmp(&state->getDesc(),&desc,sizeof(desc));
		});
	if(mBlendStates.end()==iter)
	{
		auto ret=DEVILX_NEW IGABlendStateImp(desc);
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

IGARasterizerState* NSDevilX::NSCore::NSOpenGL::IGADeviceImp::createRasterizerState(const IGAStruct::SRasterizerDesc&desc)
{
	auto iter=std::find_if(mRasterizerStates.begin(),mRasterizerStates.end(),[&desc](IGARasterizerStateImp*state)
		{
			return 0==memcmp(&state->getDesc(),&desc,sizeof(desc));
		});
	if(mRasterizerStates.end()==iter)
	{
		auto ret=DEVILX_NEW IGARasterizerStateImp(desc);
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

IGADepthStencilState* NSDevilX::NSCore::NSOpenGL::IGADeviceImp::createDepthStencilState(const IGAStruct::SDepthStencilDesc& desc)
{
	auto iter=std::find_if(mDepthStencilStates.begin(),mDepthStencilStates.end(),[&desc](IGADepthStencilStateImp*state)
		{
			return 0==memcmp(&state->getDesc(),&desc,sizeof(desc));
		});
	if(mDepthStencilStates.end()==iter)
	{
		auto ret=DEVILX_NEW IGADepthStencilStateImp(desc);
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

IGASamplerState* NSDevilX::NSCore::NSOpenGL::IGADeviceImp::createSamplerState(const IGAStruct::SSamplerDesc& desc)
{
	auto iter=std::find_if(mSamplerStates.begin(),mSamplerStates.end(),[&desc](IGASamplerStateImp*state)
		{
			return 0==memcmp(&state->getDesc(),&desc,sizeof(desc));
		});
	if(mSamplerStates.end()==iter)
	{
		auto ret=DEVILX_NEW IGASamplerStateImp(desc);
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

IGAProgram* NSDevilX::NSCore::NSOpenGL::IGADeviceImp::createProgram(IGAVertexShader* vertexShader,IGAPixelShader* pixelShader,IGAGeometryShader* geometryShader,IGAHullShader* hullShader,IGADomainShader* domainShader)
{
	return nullptr;
}

IGAProgramReflection* NSDevilX::NSCore::NSOpenGL::IGADeviceImp::createReflection(IGAProgram* program)
{
	return nullptr;
}

Void NSDevilX::NSCore::NSOpenGL::IGADeviceImp::destroyReflection(IGAProgramReflection* reflection)
{
	return Void();
}

IGAProgramParameter* NSDevilX::NSCore::NSOpenGL::IGADeviceImp::createProgramParameter()
{
	return nullptr;
}

Void NSDevilX::NSCore::NSOpenGL::IGADeviceImp::destroyProgramParameter(IGAProgramParameter* parameter)
{
	return Void();
}

Void NSDevilX::NSCore::NSOpenGL::IGADeviceImp::clear(IGADepthStencilView* view,UInt32 flags,Float depth,UInt8 stencil)
{
	switch(flags)
	{
	case IGAEnum::EClearFlag_DEPTH:
		mEnvironment->clear(static_cast<IGADepthStencilViewImp*>(view),depth);
		break;
	case IGAEnum::EClearFlag_STENCIL:
		mEnvironment->clear(static_cast<IGADepthStencilViewImp*>(view),stencil);
		break;
	case IGAEnum::EClearFlag_DEPTH|IGAEnum::EClearFlag_STENCIL:
		mEnvironment->clear(static_cast<IGADepthStencilViewImp*>(view),depth,stencil);
		break;
	}
}

Void NSDevilX::NSCore::NSOpenGL::IGADeviceImp::clear(IGARenderTargetView* view,const Float colourRGBA[4])
{
	mEnvironment->clear(static_cast<IGARenderTargetViewImp*>(view),colourRGBA);
}

Void NSDevilX::NSCore::NSOpenGL::IGADeviceImp::clear(IGAUnorderedAccessView* view,const Float value[4])
{
	return Void();
}

Void NSDevilX::NSCore::NSOpenGL::IGADeviceImp::clear(IGAUnorderedAccessView* view,const UInt32 value[4])
{
	return Void();
}

Void NSDevilX::NSCore::NSOpenGL::IGADeviceImp::setRenderTargets(UInt32 numRenderTarget,IGARenderTargetView* const* renderTargetViews,IGADepthStencilView* depthStencilView)
{
	for(UInt32 i=0;i<numRenderTarget;++i)
	{
		mEnvironment->setRenderTarget(i,reinterpret_cast<IGARenderTargetViewImp*>(renderTargetViews[i]));
	}
	mEnvironment->setDepthStencil(static_cast<IGADepthStencilViewImp*>(depthStencilView));
}

Void NSDevilX::NSCore::NSOpenGL::IGADeviceImp::setInputLayout(IGAInputLayout* layout)
{
	mEnvironment->setInputLayout(static_cast<IGAInputLayoutImp*>(layout));
}

Void NSDevilX::NSCore::NSOpenGL::IGADeviceImp::setVertexBuffer(UInt32 startSlot,UInt32 numBuffers,IGAVertexBuffer* const* buffers,const UInt32* strides,const UInt32* offsets)
{
	return Void();
}

Void NSDevilX::NSCore::NSOpenGL::IGADeviceImp::setIndexBuffer(IGAIndexBuffer* buffer,IGAEnum::EGIFormat format,UInt32 offset)
{
	return Void();
}

Void NSDevilX::NSCore::NSOpenGL::IGADeviceImp::setProgram(IGAProgram* program,IGAProgramParameter* parameter)
{
	return Void();
}

Void NSDevilX::NSCore::NSOpenGL::IGADeviceImp::setPrimitiveTopology(IGAEnum::EPrimitiveTopology primitiveTopology)
{
	return Void();
}

Void NSDevilX::NSCore::NSOpenGL::IGADeviceImp::setRasterizerState(IGARasterizerState* state)
{
	return Void();
}

Void NSDevilX::NSCore::NSOpenGL::IGADeviceImp::setDepthStencilState(IGADepthStencilState* state,UInt32 stencilRef)
{
	return Void();
}

Void NSDevilX::NSCore::NSOpenGL::IGADeviceImp::setBlendState(IGABlendState* state,const Float factor[4],UInt32 samplerMask)
{
	return Void();
}

Void NSDevilX::NSCore::NSOpenGL::IGADeviceImp::setScissorRects(UInt32 numRects,const CRect* rects)
{
	return Void();
}

Void NSDevilX::NSCore::NSOpenGL::IGADeviceImp::setViewports(UInt32 numViewports,const IGAStruct::SViewport* viewports)
{
	return Void();
}

Void NSDevilX::NSCore::NSOpenGL::IGADeviceImp::draw(UInt32 vertexCountPerInstance,UInt32 startVertexLocation,UInt32 instanceCount,UInt32 startInstanceLocation)
{
	return Void();
}

Void NSDevilX::NSCore::NSOpenGL::IGADeviceImp::draw(UInt32 indexCountPerInstance,UInt32 startIndexLocation,Int32 baseVertexLocation,UInt32 instanceCount,UInt32 startInstanceLocation)
{
	return Void();
}

IGARenderTargetViewImp* NSDevilX::NSCore::NSOpenGL::IGADeviceImp::_createRenderTargetView(IGATextureImp* texture,UInt32 mipLevel,UInt32 arrayIndex)
{
	auto iter=std::find_if(mRenderTargetViews.begin(),mRenderTargetViews.end(),[texture,mipLevel,arrayIndex](IGARenderTargetViewImp*rtv)
		{
			return (rtv->getTexture()==texture->getInternal())&&(rtv->getMipLevel()==mipLevel)&&(rtv->getArrayIndex()==arrayIndex);
		});
	IGARenderTargetViewImp*ret=nullptr;
	if(mRenderTargetViews.end()==iter)
	{
		ret=DEVILX_NEW IGARenderTargetViewImp(texture->getInternal(),mipLevel,arrayIndex);
		mRenderTargetViews.push_back(ret);
	}
	else
	{
		ret=*iter;
	}
	return ret;
}

IGADepthStencilViewImp* NSDevilX::NSCore::NSOpenGL::IGADeviceImp::_createDepthStencilView(IGATextureImp* texture,UInt32 mipLevel,UInt32 arrayIndex)
{
	auto iter=std::find_if(mDepthStencilViews.begin(),mDepthStencilViews.end(),[texture,mipLevel,arrayIndex](IGADepthStencilViewImp*dsv)
		{
			return (dsv->getTexture()==texture->getInternal())&&(dsv->getMipLevel()==mipLevel)&&(dsv->getArrayIndex()==arrayIndex);
		});
	IGADepthStencilViewImp*ret=nullptr;
	if(mDepthStencilViews.end()==iter)
	{
		ret=DEVILX_NEW IGADepthStencilViewImp(texture->getInternal(),mipLevel,arrayIndex);
		mDepthStencilViews.push_back(ret);
	}
	else
	{
		ret=*iter;
	}
	return ret;
}

IGADevice1* NSDevilX::NSCore::NSOpenGL::IGADeviceImp::queryInterface_IGADevice1() const
{
	if(GLEW_VERSION_4_5)
		return const_cast<IGADeviceImp*>(this);
	else
		return nullptr;
}

IGADevice* NSDevilX::NSCore::NSOpenGL::IGADeviceImp::queryInterface_IGADevice() const
{
	return const_cast<IGADeviceImp*>(this);
}

IGAShaderParameter* NSDevilX::NSCore::NSOpenGL::IGADeviceImp::createShaderParameter()
{
	return nullptr;
}

IGAComputeShaderParameter* NSDevilX::NSCore::NSOpenGL::IGADeviceImp::createComputeShaderParameter()
{
	return nullptr;
}

Void NSDevilX::NSCore::NSOpenGL::IGADeviceImp::destroyShaderParameter(IGAShaderParameter* parameter)
{
	return Void();
}

IGAShaderReflection* NSDevilX::NSCore::NSOpenGL::IGADeviceImp::createReflection(IGAShader* shader)
{
	return nullptr;
}

Void NSDevilX::NSCore::NSOpenGL::IGADeviceImp::destroyReflection(IGAShaderReflection* reflection)
{
	return Void();
}

IGADeviceContext1* NSDevilX::NSCore::NSOpenGL::IGADeviceImp::queryInterface_IGADeviceContext1() const
{
	if(GLEW_VERSION_4_5)
		return const_cast<IGADeviceImp*>(this);
	else
		return nullptr;
}

IGADeviceContext* NSDevilX::NSCore::NSOpenGL::IGADeviceImp::queryInterface_IGADeviceContext() const
{
	return const_cast<IGADeviceImp*>(this);
}

Void NSDevilX::NSCore::NSOpenGL::IGADeviceImp::setVertexShader(IGAVertexShader* shader,IGAShaderParameter* parameter)
{
	return Void();
}

Void NSDevilX::NSCore::NSOpenGL::IGADeviceImp::setPixelShader(IGAPixelShader* shader,IGAShaderParameter* parameter)
{
	return Void();
}

Void NSDevilX::NSCore::NSOpenGL::IGADeviceImp::setGeometryShader(IGAGeometryShader* shader,IGAShaderParameter* parameter)
{
	return Void();
}

Void NSDevilX::NSCore::NSOpenGL::IGADeviceImp::setHullShader(IGAHullShader* shader,IGAShaderParameter* parameter)
{
	return Void();
}

Void NSDevilX::NSCore::NSOpenGL::IGADeviceImp::setDomainShader(IGADomainShader* shader,IGAShaderParameter* parameter)
{
	return Void();
}

Void NSDevilX::NSCore::NSOpenGL::IGADeviceImp::dispatch(IGAComputeShader* shader,IGAShaderParameter* parameter,UInt32 threadGroupCountX,UInt32 threadGroupCountY,UInt32 threadGroupCountZ)
{
	return Void();
}