#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSCore;
using namespace NSOpenGL;

IGADeviceImp::IGADeviceImp()
	:mContext(0)
	,mFrameBufferObject(0)
{
	if(glCreateFramebuffers)
	{
		glCreateFramebuffers(1,&mFrameBufferObject);
	}
	else
	{
		glGenFramebuffers(1,&mFrameBufferObject);
	}
}

IGADeviceImp::~IGADeviceImp()
{
	mCommonObjects.destroyAll();
	mInputLayouts.destroyAll();
	mSamplerStates.destroyAll();
	mRenderTargetViews.destroyAll();
	mDepthStencilViews.destroyAll();
	glDeleteFramebuffers(1,&mFrameBufferObject);
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
	return nullptr;
}

IGARenderTargetView* NSDevilX::NSCore::NSOpenGL::IGADeviceImp::createRenderTargetView(IGATexture2D* resource,UInt32 mipSlice,UInt32 firstArraySlice)
{
	return nullptr;
}

IGARenderTargetView* NSDevilX::NSCore::NSOpenGL::IGADeviceImp::createRenderTargetView(IGATexture3D* resource,UInt32 mipSlice,UInt32 firstDepthSlice)
{
	return nullptr;
}

IGADepthStencilView* NSDevilX::NSCore::NSOpenGL::IGADeviceImp::createDepthStencilView(IGATexture1D* resource,UInt32 mipSlice,UInt32 firstArraySlice)
{
	return nullptr;
}

IGADepthStencilView* NSDevilX::NSCore::NSOpenGL::IGADeviceImp::createDepthStencilView(IGATexture2D* resource,UInt32 mipSlice,UInt32 firstArraySlice)
{
	return nullptr;
}

IGAShaderResourceView* NSDevilX::NSCore::NSOpenGL::IGADeviceImp::createShaderResourceView(IGATexture1D* resource,UInt32 mostDetailedMip,UInt32 numMipLevels,UInt32 firstArraySlice,UInt32 arrayCount)
{
	return nullptr;
}

IGAShaderResourceView* NSDevilX::NSCore::NSOpenGL::IGADeviceImp::createShaderResourceView(IGATexture2D* resource,UInt32 mostDetailedMip,UInt32 numMipLevels,UInt32 firstArraySlice,UInt32 arrayCount)
{
	return nullptr;
}

IGAShaderResourceView* NSDevilX::NSCore::NSOpenGL::IGADeviceImp::createShaderResourceView(IGATexture3D* resource,UInt32 mostDetailedMip,UInt32 numMipLevels)
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

IGAProgram* NSDevilX::NSCore::NSOpenGL::IGADeviceImp::createProgram(IGAComputeShader* computeShader)
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
