#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;
using namespace NSD3D11;

NSDevilX::NSRenderSystem::NSD3D11::CTexture2D::CTexture2D(ITexture2DImp * interfaceImp)
	:TInterfaceObject<ITexture2DImp>(interfaceImp)
{
	getInterfaceImp()->addListener(static_cast<TMessageReceiver<ITexture2DImp>*>(this),ITexture2DImp::EMessage_EndArraySizeChange);
	getInterfaceImp()->addListener(static_cast<TMessageReceiver<ITexture2DImp>*>(this),ITexture2DImp::EMessage_EndFormatChange);
	getInterfaceImp()->addListener(static_cast<TMessageReceiver<ITexture2DImp>*>(this),ITexture2DImp::EMessage_EndMipmapChange);
	getInterfaceImp()->addListener(static_cast<TMessageReceiver<ITexture2DImp>*>(this),ITexture2DImp::EMessage_EndPixelsChange);
	getInterfaceImp()->addListener(static_cast<TMessageReceiver<ITexture2DImp>*>(this),ITexture2DImp::EMessage_EndSizeChange);
}

NSDevilX::NSRenderSystem::NSD3D11::CTexture2D::~CTexture2D()
{
}

Void NSDevilX::NSRenderSystem::NSD3D11::CTexture2D::onMessage(ITexture2DImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case ITexture2DImp::EMessage_EndArraySizeChange:
	case ITexture2DImp::EMessage_EndFormatChange:
	case ITexture2DImp::EMessage_EndMipmapChange:
	case ITexture2DImp::EMessage_EndSizeChange:
		addDirtyFlag(EDirtyFlag_Resource);
		_registerToSystemImp();
		break;
	case ITexture2DImp::EMessage_EndPixelsChange:
		addDirtyFlag(EDirtyFlag_Content);
		mDirtyContentSubTextureKeys.insert(*static_cast<UInt32*>(data));
		_registerToSystemImp();
		break;
	}
}

Void NSDevilX::NSRenderSystem::NSD3D11::CTexture2D::onMessage(CSystemImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case CSystemImp::EMessage_BeginFrame:
		_update();
		break;
	}
}

Void NSDevilX::NSRenderSystem::NSD3D11::CTexture2D::_update()
{
	if(hasDirtyFlag(EDirtyFlag_Resource)&&_recreateInternal())
	{
		removeDirtyFlag(EDirtyFlag_Resource);
	}
	if(hasDirtyFlag(EDirtyFlag_Content)&&_updatePixels())
	{
		removeDirtyFlag(EDirtyFlag_Content);
	}
}

Boolean NSDevilX::NSRenderSystem::NSD3D11::CTexture2D::_recreateInternal()
{
	TCOMInternalObject<ID3D11Texture2D>::setInternal(nullptr);
	CTexture::setInternal(nullptr);
	if(getInterfaceImp()->getWidth()>0&&getInterfaceImp()->getHeight()>0)
	{
		D3D11_TEXTURE2D_DESC desc;
		desc.ArraySize=1;
		desc.CPUAccessFlags=0;
		desc.Format=CUtility::getDXGIFormat(getInterfaceImp()->getFormat());
		desc.Height=getInterfaceImp()->getHeight();
		if(getInterfaceImp()->isAutoMipmap())
			desc.MipLevels=0;
		else
			desc.MipLevels=getInterfaceImp()->getMipmapCount()+1;
		desc.BindFlags=D3D11_BIND_SHADER_RESOURCE;
		desc.MiscFlags=0;
		if(0==desc.MipLevels)
		{
			desc.MiscFlags|=D3D11_RESOURCE_MISC_GENERATE_MIPS;
			desc.BindFlags|=D3D11_BIND_RENDER_TARGET;
		}
		desc.SampleDesc.Count=1;
		desc.SampleDesc.Quality=0;
		desc.Usage=D3D11_USAGE_DEFAULT;
		desc.Width=getInterfaceImp()->getWidth();
		ID3D11Texture2D * tex=nullptr;
		CSystemImp::getSingleton().getDevice()->CreateTexture2D(&desc,nullptr,&tex);
		TCOMInternalObject<ID3D11Texture2D>::setInternal(tex);
		ID3D11ShaderResourceView * srv=nullptr;
		CSystemImp::getSingleton().getDevice()->CreateShaderResourceView(TCOMInternalObject<ID3D11Texture2D>::getInternal(),nullptr,&srv);
		CTexture::setInternal(srv);
		return true;
	}
	else
	{
		return false;
	}
}

Boolean NSDevilX::NSRenderSystem::NSD3D11::CTexture2D::_updatePixels()
{
	if(nullptr==TCOMInternalObject<ID3D11Texture2D>::getInternal())
		return false;
	Boolean ret=true;
	for(auto iter=mDirtyContentSubTextureKeys.begin();mDirtyContentSubTextureKeys.end()!=iter;)
	{
		auto sub_tex_key=*iter;
		auto sub_tex=getInterfaceImp()->getSubTextures().get(sub_tex_key);
		if(sub_tex->mRenderTargetPixels)
		{
			_updateFromRenderableSources(sub_tex);
			ret=false;
			++iter;
		}
		else
		{
			_updateFromMemorySources(sub_tex);
			iter=mDirtyContentSubTextureKeys.erase(iter);
		}
	}
	return ret;
}

Void NSDevilX::NSRenderSystem::NSD3D11::CTexture2D::_updateFromMemorySources(ITexture2DImp::SSubTexture * subTexture)
{
	if(subTexture->mMemoryPixels)
	{
		const auto row_pitch=CUtility::getRowPitch(CUtility::getDXGIFormat(getInterfaceImp()->getFormat()),subTexture->mWidth);
		const auto depth_pitch=row_pitch*subTexture->mHeight;
		CSystemImp::getSingleton().getImmediateContext()->UpdateSubresource1(TCOMInternalObject<ID3D11Texture2D>::getInternal(),D3D11CalcSubresource(0,subTexture->mArrayIndex,subTexture->mMipmapLevel),nullptr,subTexture->mMemoryPixels,row_pitch,depth_pitch,0);
		if(getInterfaceImp()->isAutoMipmap())
			CSystemImp::getSingleton().getImmediateContext()->GenerateMips(TCOMInternalObject<ID3D11ShaderResourceView>::getInternal());
	}
}

Void NSDevilX::NSRenderSystem::NSD3D11::CTexture2D::_updateFromRenderableSources(ITexture2DImp::SSubTexture * subTexture)
{
	CSystemImp::getSingleton().getImmediateContext()->CopySubresourceRegion1(TCOMInternalObject<ID3D11Texture2D>::getInternal()
		,D3D11CalcSubresource(0,subTexture->mArrayIndex,subTexture->mMipmapLevel)
		,0
		,0
		,0
		,CSystemImp::getSingleton().getRenderTarget(subTexture->mRenderTargetPixels)->getRenderTargetResource()
		,0
		,nullptr,
		0);
}