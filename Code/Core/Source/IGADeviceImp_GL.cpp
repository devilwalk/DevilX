#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSCore;
using namespace NSOpenGL;

CGADeviceImp::CGADeviceImp(IGAEnum::EHighLevelDeviceVersion version)
	:mVersion(version)
	,mEnvironment(nullptr)
{
}

Void NSDevilX::NSCore::NSOpenGL::CGADeviceImp::setEnvironment(CGAEnvironment* env)
{
	mEnvironment=env;
}

CGADeviceImp::~CGADeviceImp()
{
	mCommonObjects.destroyAll();
	mInputLayouts.destroyAll();
	mSamplerStates.destroyAll();
	mRenderTargetViews.destroyAll();
	mDepthStencilViews.destroyAll();
}

IGAEnum::EHighLevelDeviceVersion NSDevilX::NSCore::NSOpenGL::CGADeviceImp::getVersion() const
{
	return mVersion;
}

IGADeviceContext * NSDevilX::NSCore::NSOpenGL::CGADeviceImp::getImmediateContext() const
{
	return const_cast<CGADeviceImp*>(static_cast<const CGADeviceImp*>(this));
}

IGADeviceContext * NSDevilX::NSCore::NSOpenGL::CGADeviceImp::createDeferredContext()
{
	return nullptr;
}

IGAVertexBuffer* NSDevilX::NSCore::NSOpenGL::CGADeviceImp::createVertexBuffer(UInt32 sizeInByte,UInt32 cpuAccessFlags,IGAEnum::EUsage usage,UInt32 bindFlags,ConstVoidPtr initialData)
{
	auto ret=DEVILX_NEW IGABufferImp(GL_ARRAY_BUFFER,sizeInByte,CUtility::mapping(usage,cpuAccessFlags),initialData);
	mCommonObjects.insert(ret);
	return ret;
}

IGAIndexBuffer* NSDevilX::NSCore::NSOpenGL::CGADeviceImp::createIndexBuffer(UInt32 sizeInByte,UInt32 cpuAccessFlags,IGAEnum::EUsage usage,UInt32 bindFlags,ConstVoidPtr initialData)
{
	auto ret=DEVILX_NEW IGABufferImp(GL_ELEMENT_ARRAY_BUFFER,sizeInByte,CUtility::mapping(usage,cpuAccessFlags),initialData);
	mCommonObjects.insert(ret);
	return ret;
}

IGAConstantBuffer* NSDevilX::NSCore::NSOpenGL::CGADeviceImp::createConstantBuffer(UInt32 sizeInByte,UInt32 cpuAccessFlags,IGAEnum::EUsage usage,UInt32 bindFlags,ConstVoidPtr initialData)
{
	auto ret=DEVILX_NEW IGABufferImp(GL_UNIFORM_BUFFER,sizeInByte,CUtility::mapping(usage,cpuAccessFlags),initialData);
	mCommonObjects.insert(ret);
	return ret;
}

IGAShaderResourceBuffer* NSDevilX::NSCore::NSOpenGL::CGADeviceImp::createShaderResourceBuffer(UInt32 sizeInByte,UInt32 cpuAccessFlags,UInt32 shaderResourceBufferFlags,UInt32 structureByteStride,IGAEnum::EUsage usage,UInt32 bindFlags,ConstVoidPtr initialData)
{
	auto ret=DEVILX_NEW IGABufferImp(GL_SHADER_STORAGE_BUFFER,sizeInByte,CUtility::mapping(usage,cpuAccessFlags),initialData);
	mCommonObjects.insert(ret);
	return ret;
}

IGAUnorderedAccessBuffer* NSDevilX::NSCore::NSOpenGL::CGADeviceImp::createUnorderedAccessBuffer(UInt32 sizeInByte,UInt32 cpuAccessFlags,IGAEnum::EUsage usage,UInt32 bindFlags,ConstVoidPtr initialData)
{
	auto ret=DEVILX_NEW IGABufferImp(GL_SHADER_STORAGE_BUFFER,sizeInByte,CUtility::mapping(usage,cpuAccessFlags),initialData);
	mCommonObjects.insert(ret);
	return ret;
}

IGATexture1D* NSDevilX::NSCore::NSOpenGL::CGADeviceImp::createTexture1D(UInt32 length,IGAEnum::EUsage usage,IGAEnum::EGIFormat format,UInt32 cpuAccessFlags,UInt32 bindFlags,UInt32 mipLevelCount,UInt32 arrayCount,const IGAStruct::SSubResourceData* initialData)
{
	auto ret=DEVILX_NEW IGATextureImp(length,CUtility::mappingInternalFormat(format),mipLevelCount,arrayCount,initialData);
	mCommonObjects.insert(ret);
	return ret;
}

IGATexture2D* NSDevilX::NSCore::NSOpenGL::CGADeviceImp::createTexture2D(UInt32 width,UInt32 height,IGAEnum::EUsage usage,IGAEnum::EGIFormat format,UInt32 cpuAccessFlags,UInt32 bindFlags,UInt32 mipLevelCount,UInt32 arrayCount,const IGAStruct::SSubResourceData* initialData)
{
	auto ret=DEVILX_NEW IGATextureImp(width,height,CUtility::mappingInternalFormat(format),mipLevelCount,arrayCount,False,initialData);
	mCommonObjects.insert(ret);
	return ret;
}

IGATexture3D* NSDevilX::NSCore::NSOpenGL::CGADeviceImp::createTexture3D(UInt32 width,UInt32 height,UInt32 depth,IGAEnum::EUsage usage,IGAEnum::EGIFormat format,UInt32 cpuAccessFlags,UInt32 bindFlags,UInt32 mipLevelCount,const IGAStruct::SSubResourceData* initialData)
{
	auto ret=DEVILX_NEW IGATextureImp(width,height,depth,CUtility::mappingInternalFormat(format),mipLevelCount,initialData);
	mCommonObjects.insert(ret);
	return ret;
}

IGATexture2D* NSDevilX::NSCore::NSOpenGL::CGADeviceImp::createTextureCube(UInt32 width,UInt32 height,IGAEnum::EUsage usage,IGAEnum::EGIFormat format,UInt32 cpuAccessFlags,UInt32 bindFlags,UInt32 mipLevelCount,UInt32 arrayCount,const IGAStruct::SSubResourceData* initialData)
{
	auto ret=DEVILX_NEW IGATextureImp(width,height,CUtility::mappingInternalFormat(format),mipLevelCount,arrayCount,True,initialData);
	mCommonObjects.insert(ret);
	return ret;
}

IGARenderTargetView* NSDevilX::NSCore::NSOpenGL::CGADeviceImp::createRenderTargetView(IGATexture1D* resource,UInt32 mipSlice,UInt32 firstArraySlice)
{
	return _createRenderTargetView(static_cast<IGATextureImp*>(resource),mipSlice,firstArraySlice);
}

IGARenderTargetView* NSDevilX::NSCore::NSOpenGL::CGADeviceImp::createRenderTargetView(IGATexture2D* resource,UInt32 mipSlice,UInt32 firstArraySlice)
{
	return _createRenderTargetView(static_cast<IGATextureImp*>(resource),mipSlice,firstArraySlice);
}

IGARenderTargetView* NSDevilX::NSCore::NSOpenGL::CGADeviceImp::createRenderTargetView(IGATexture3D* resource,UInt32 mipSlice,UInt32 firstDepthSlice)
{
	return _createRenderTargetView(static_cast<IGATextureImp*>(resource),mipSlice,firstDepthSlice);
}

IGADepthStencilView* NSDevilX::NSCore::NSOpenGL::CGADeviceImp::createDepthStencilView(IGATexture1D* resource,UInt32 mipSlice,UInt32 firstArraySlice)
{
	return _createDepthStencilView(static_cast<IGATextureImp*>(resource),mipSlice,firstArraySlice);
}

IGADepthStencilView* NSDevilX::NSCore::NSOpenGL::CGADeviceImp::createDepthStencilView(IGATexture2D* resource,UInt32 mipSlice,UInt32 firstArraySlice)
{
	return _createDepthStencilView(static_cast<IGATextureImp*>(resource),mipSlice,firstArraySlice);
}

IGATextureView* NSDevilX::NSCore::NSOpenGL::CGADeviceImp::createShaderResourceView(IGATexture1D* resource,UInt32 mostDetailedMip,UInt32 numMipLevels,UInt32 firstArraySlice,UInt32 arrayCount)
{
	return nullptr;
}

IGATextureView* NSDevilX::NSCore::NSOpenGL::CGADeviceImp::createShaderResourceView(IGATexture2D* resource,UInt32 mostDetailedMip,UInt32 numMipLevels,UInt32 firstArraySlice,UInt32 arrayCount)
{
	return nullptr;
}

IGATextureView* NSDevilX::NSCore::NSOpenGL::CGADeviceImp::createShaderResourceView(IGATexture3D* resource,UInt32 mostDetailedMip,UInt32 numMipLevels)
{
	return nullptr;
}

IGAUnorderedAccessView* NSDevilX::NSCore::NSOpenGL::CGADeviceImp::createUnorderedAccessView(IGATexture1D* resource,UInt32 mipSlice,UInt32 firstArraySlice,UInt32 arrayCount)
{
	return nullptr;
}

IGAUnorderedAccessView* NSDevilX::NSCore::NSOpenGL::CGADeviceImp::createUnorderedAccessView(IGATexture2D* resource,UInt32 mipSlice,UInt32 firstArraySlice,UInt32 arrayCount)
{
	return nullptr;
}

IGAUnorderedAccessView* NSDevilX::NSCore::NSOpenGL::CGADeviceImp::createUnorderedAccessView(IGATexture3D* resource,UInt32 mipSlice,UInt32 firstDepthSlice,UInt32 depthCount)
{
	return nullptr;
}

IGAInputLayout* NSDevilX::NSCore::NSOpenGL::CGADeviceImp::createInputLayout(const TVector<IGAStruct::SInputElementDesc>& inputElements)
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

IGAVertexShader* NSDevilX::NSCore::NSOpenGL::CGADeviceImp::createVertexShader(const std::string& code)
{
	auto ret=DEVILX_NEW IGAShaderImp(code.c_str(),IGAEnum::EShaderType_Vertex);
	mCommonObjects.insert(ret);
	return ret;
}

IGAPixelShader* NSDevilX::NSCore::NSOpenGL::CGADeviceImp::createPixelShader(const std::string& code)
{
	auto ret=DEVILX_NEW IGAShaderImp(code.c_str(),IGAEnum::EShaderType_Pixel);
	mCommonObjects.insert(ret);
	return ret;
}

IGAGeometryShader* NSDevilX::NSCore::NSOpenGL::CGADeviceImp::createGeometryShader(const std::string& code)
{
	auto ret=DEVILX_NEW IGAShaderImp(code.c_str(),IGAEnum::EShaderType_Geometry);
	mCommonObjects.insert(ret);
	return ret;
}

IGAHullShader* NSDevilX::NSCore::NSOpenGL::CGADeviceImp::createHullShader(const std::string& code)
{
	auto ret=DEVILX_NEW IGAShaderImp(code.c_str(),IGAEnum::EShaderType_Hull);
	mCommonObjects.insert(ret);
	return ret;
}

IGADomainShader* NSDevilX::NSCore::NSOpenGL::CGADeviceImp::createDomainShader(const std::string& code)
{
	auto ret=DEVILX_NEW IGAShaderImp(code.c_str(),IGAEnum::EShaderType_Domain);
	mCommonObjects.insert(ret);
	return ret;
}

IGAComputeShader* NSDevilX::NSCore::NSOpenGL::CGADeviceImp::createComputeShader(const std::string& code)
{
	auto ret=DEVILX_NEW IGAShaderImp(code.c_str(),IGAEnum::EShaderType_Compute);
	mCommonObjects.insert(ret);
	return ret;
}

IGABlendState* NSDevilX::NSCore::NSOpenGL::CGADeviceImp::createBlendState(const IGAStruct::SBlendDesc& desc)
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

IGARasterizerState* NSDevilX::NSCore::NSOpenGL::CGADeviceImp::createRasterizerState(const IGAStruct::SRasterizerDesc&desc)
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

IGADepthStencilState* NSDevilX::NSCore::NSOpenGL::CGADeviceImp::createDepthStencilState(const IGAStruct::SDepthStencilDesc& desc)
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

IGASamplerState* NSDevilX::NSCore::NSOpenGL::CGADeviceImp::createSamplerState(const IGAStruct::SSamplerDesc& desc)
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

IGAProgram* NSDevilX::NSCore::NSOpenGL::CGADeviceImp::createProgram(IGAVertexShader* vertexShader,IGAPixelShader* pixelShader,IGAGeometryShader* geometryShader,IGAHullShader* hullShader,IGADomainShader* domainShader)
{
	auto ret=DEVILX_NEW CGAProgramImp(vertexShader?static_cast<IGAShaderImp*>(vertexShader)->getInternal():0
		,pixelShader?static_cast<IGAShaderImp*>(pixelShader)->getInternal():0
		,geometryShader?static_cast<IGAShaderImp*>(geometryShader)->getInternal():0
		,hullShader?static_cast<IGAShaderImp*>(hullShader)->getInternal():0
		,domainShader?static_cast<IGAShaderImp*>(domainShader)->getInternal():0
	);
	mCommonObjects.insert(ret);
	return ret;
}

IGAProgramReflection* NSDevilX::NSCore::NSOpenGL::CGADeviceImp::createReflection(IGAProgram* program)
{
	return nullptr;
}

Void NSDevilX::NSCore::NSOpenGL::CGADeviceImp::destroyReflection(IGAProgramReflection* reflection)
{
	return Void();
}

IGAProgramParameter* NSDevilX::NSCore::NSOpenGL::CGADeviceImp::createProgramParameter()
{
	auto ret=DEVILX_NEW IGAProgramParameterImp;
	mCommonObjects.insert(ret);
	return ret;
}

Void NSDevilX::NSCore::NSOpenGL::CGADeviceImp::destroyProgramParameter(IGAProgramParameter* parameter)
{
	mCommonObjects.destroy(static_cast<IGAProgramParameterImp*>(parameter));
}

Void NSDevilX::NSCore::NSOpenGL::CGADeviceImp::clear(IGADepthStencilView* view,UInt32 flags,Float depth,UInt8 stencil)
{
	switch(flags)
	{
	case IGAEnum::EClearFlag_DEPTH:
		mEnvironment->active()->clear(static_cast<IGADepthStencilViewImp*>(view),depth);
		break;
	case IGAEnum::EClearFlag_STENCIL:
		mEnvironment->active()->clear(static_cast<IGADepthStencilViewImp*>(view),stencil);
		break;
	case IGAEnum::EClearFlag_DEPTH|IGAEnum::EClearFlag_STENCIL:
		mEnvironment->active()->clear(static_cast<IGADepthStencilViewImp*>(view),depth,stencil);
		break;
	}
}

Void NSDevilX::NSCore::NSOpenGL::CGADeviceImp::clear(IGARenderTargetView* view,const Float colourRGBA[4])
{
	mEnvironment->active()->clear(static_cast<IGARenderTargetViewImp*>(view),colourRGBA);
}

Void NSDevilX::NSCore::NSOpenGL::CGADeviceImp::clear(IGAUnorderedAccessView* view,const Float value[4])
{
	return Void();
}

Void NSDevilX::NSCore::NSOpenGL::CGADeviceImp::clear(IGAUnorderedAccessView* view,const UInt32 value[4])
{
	return Void();
}

Void NSDevilX::NSCore::NSOpenGL::CGADeviceImp::setRenderTargets(UInt32 numRenderTarget,IGARenderTargetView* const* renderTargetViews,IGADepthStencilView* depthStencilView)
{
	for(UInt32 i=0;i<numRenderTarget;++i)
	{
		mEnvironment->active()->setRenderTarget(i,reinterpret_cast<IGARenderTargetViewImp*>(renderTargetViews[i]));
	}
	mEnvironment->active()->setDepthStencil(static_cast<IGADepthStencilViewImp*>(depthStencilView));
}

Void NSDevilX::NSCore::NSOpenGL::CGADeviceImp::setInputLayout(IGAInputLayout* layout)
{
	glBindVertexArray(static_cast<IGAInputLayoutImp*>(layout)->getInternal());
	CUtility::checkGLError();
}

Void NSDevilX::NSCore::NSOpenGL::CGADeviceImp::setVertexBuffer(UInt32 startSlot,UInt32 numBuffers,IGAVertexBuffer* const* buffers,const UInt32* strides,const UInt32* offsets)
{
}

Void NSDevilX::NSCore::NSOpenGL::CGADeviceImp::setProgram(IGAProgram* program,IGAProgramParameter* parameter)
{
	return Void();
}

Void NSDevilX::NSCore::NSOpenGL::CGADeviceImp::setRasterizerState(IGARasterizerState* state)
{
	return Void();
}

Void NSDevilX::NSCore::NSOpenGL::CGADeviceImp::setDepthStencilState(IGADepthStencilState* state,UInt32 stencilRef)
{
	return Void();
}

Void NSDevilX::NSCore::NSOpenGL::CGADeviceImp::setBlendState(IGABlendState* state,const Float factor[4],UInt32 samplerMask)
{
	return Void();
}

Void NSDevilX::NSCore::NSOpenGL::CGADeviceImp::setScissorRects(UInt32 numRects,const CRect* rects)
{
	return Void();
}

Void NSDevilX::NSCore::NSOpenGL::CGADeviceImp::setViewports(UInt32 numViewports,const IGAStruct::SViewport* viewports)
{
	return Void();
}

IGARenderTargetViewImp* NSDevilX::NSCore::NSOpenGL::CGADeviceImp::_createRenderTargetView(IGATextureImp* texture,UInt32 mipLevel,UInt32 arrayIndex)
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

IGADepthStencilViewImp* NSDevilX::NSCore::NSOpenGL::CGADeviceImp::_createDepthStencilView(IGATextureImp* texture,UInt32 mipLevel,UInt32 arrayIndex)
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

IGAShaderParameter* NSDevilX::NSCore::NSOpenGL::CGADeviceImp::createShaderParameter()
{
	return nullptr;
}

IGAComputeShaderParameter* NSDevilX::NSCore::NSOpenGL::CGADeviceImp::createComputeShaderParameter()
{
	return nullptr;
}

Void NSDevilX::NSCore::NSOpenGL::CGADeviceImp::destroyShaderParameter(IGAShaderParameter* parameter)
{
	return Void();
}

IGAShaderReflection* NSDevilX::NSCore::NSOpenGL::CGADeviceImp::createReflection(IGAShader* shader)
{
	return nullptr;
}

Void NSDevilX::NSCore::NSOpenGL::CGADeviceImp::destroyReflection(IGAShaderReflection* reflection)
{
	return Void();
}

Void NSDevilX::NSCore::NSOpenGL::CGADeviceImp::setVertexShader(IGAVertexShader* shader,IGAShaderParameter* parameter)
{
	return Void();
}

Void NSDevilX::NSCore::NSOpenGL::CGADeviceImp::setPixelShader(IGAPixelShader* shader,IGAShaderParameter* parameter)
{
	return Void();
}

Void NSDevilX::NSCore::NSOpenGL::CGADeviceImp::setGeometryShader(IGAGeometryShader* shader,IGAShaderParameter* parameter)
{
	return Void();
}

Void NSDevilX::NSCore::NSOpenGL::CGADeviceImp::setHullShader(IGAHullShader* shader,IGAShaderParameter* parameter)
{
	return Void();
}

Void NSDevilX::NSCore::NSOpenGL::CGADeviceImp::setDomainShader(IGADomainShader* shader,IGAShaderParameter* parameter)
{
	return Void();
}

Void NSDevilX::NSCore::NSOpenGL::CGADeviceImp::dispatch(IGAComputeShader* shader,IGAShaderParameter* parameter,UInt32 threadGroupCountX,UInt32 threadGroupCountY,UInt32 threadGroupCountZ)
{
	return Void();
}

Void NSDevilX::NSCore::NSOpenGL::CGADeviceImp::update(IGAHighLevelBuffer* buffer,ConstVoidPtr data,UInt32 updateOffsetInBytes,UInt32 updateSizeInBytes)
{
	mEnvironment->active()->update(static_cast<IGABufferImp*>(buffer),data,updateOffsetInBytes,updateSizeInBytes);
}

IGAShaderResourceBufferView* NSDevilX::NSCore::NSOpenGL::CGADeviceImp::createShaderResourceView(IGAShaderResourceBuffer* resource,IGAEnum::EGIFormat format,UInt32 elementOffset,UInt32 numElements)
{
	if((elementOffset==0)&&(static_cast<UInt32>(-1)==numElements))
	{
		return static_cast<IGABufferImp*>(resource);
	}
	else
	{
		assert(0);
		return nullptr;
	}
}

Void NSDevilX::NSCore::NSOpenGL::CGADeviceImp::draw(const TVector<IGAStruct::SDrawParameter_GL>& parameters)
{
	glMultiDrawArraysIndirect(mDrawMode,&parameters[0],static_cast<GLsizei>(parameters.size()),sizeof(parameters[0]));
	CUtility::checkGLError();
}

Void NSDevilX::NSCore::NSOpenGL::CGADeviceImp::draw(const TVector<IGAStruct::SDrawIndexedParameter_GL>& parameters)
{
	glMultiDrawElementsIndirect(mDrawMode,mIndexType,&parameters[0],static_cast<GLsizei>(parameters.size()),sizeof(parameters[0]));
	CUtility::checkGLError();
}

Void NSDevilX::NSCore::NSOpenGL::CGADeviceImp::setIndexBuffer(IGAIndexBuffer* buffer,IGAEnum::EIndexBufferFormat format,UInt32 offset)
{
	mIndexType=CUtility::mapping(format);
	mIndexOffset=offset;
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,static_cast<IGABufferImp*>(buffer)->getInternal());
	CUtility::checkGLError();
}

Void NSDevilX::NSCore::NSOpenGL::CGADeviceImp::setPrimitiveTopology(IGAEnum::EPrimitiveTopology primitiveTopology)
{
	mDrawMode=CUtility::mapping(primitiveTopology);
}

Void NSDevilX::NSCore::NSOpenGL::CGADeviceImp::draw(UInt32 vertexCountPerInstance,UInt32 startVertexLocation,UInt32 instanceCount,UInt32 startInstanceLocation)
{
	glDrawArraysInstancedBaseInstance(mDrawMode,startVertexLocation,vertexCountPerInstance,instanceCount,startInstanceLocation);
	CUtility::checkGLError();
}

Void NSDevilX::NSCore::NSOpenGL::CGADeviceImp::drawIndexed(UInt32 indexCountPerInstance,UInt32 startIndexLocation,Int32 baseVertexLocation,UInt32 instanceCount,UInt32 startInstanceLocation)
{
	glDrawElementsInstancedBaseVertexBaseInstance(mDrawMode,indexCountPerInstance,mIndexType,reinterpret_cast<ConstVoidPtr>(static_cast<SizeT>((startIndexLocation+mIndexOffset)*CUtility::getSizeInBytes(mIndexType))),instanceCount,baseVertexLocation,startInstanceLocation);
	CUtility::checkGLError();
}

IGAVertexArrayObject* NSDevilX::NSCore::NSOpenGL::CGADeviceImp::createVertexArrayObject(const TVector<IGAStruct::SVAOElementDesc>& inputElements)
{
	return nullptr;
}

Void NSDevilX::NSCore::NSOpenGL::CGADeviceImp::setVertexArrayObject(IGAVertexArrayObject* vao)
{
	return Void();
}