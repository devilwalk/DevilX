#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;
using namespace NSD3D11;

NSDevilX::NSRenderSystem::NSD3D11::CTexture2D::CTexture2D(ITexture2DImp * interfaceImp)
	:TInterfaceObject<ITexture2DImp>(interfaceImp)
{
	CSystemImp::getSingleton().addListener(static_cast<TMessageReceiver<CSystemImp>*>(this),CSystemImp::EMessage_BeginFrame);
}

NSDevilX::NSRenderSystem::NSD3D11::CTexture2D::~CTexture2D()
{
}

Void NSDevilX::NSRenderSystem::NSD3D11::CTexture2D::onMessage(ITexture2DImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
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
	if((getInterfaceImp()->hasDirtyFlag(ITexture2DImp::EDirtyFlag_ArraySize)
		||getInterfaceImp()->hasDirtyFlag(ITexture2DImp::EDirtyFlag_Format)
		||getInterfaceImp()->hasDirtyFlag(ITexture2DImp::EDirtyFlag_Mipmap)
		||getInterfaceImp()->hasDirtyFlag(ITexture2DImp::EDirtyFlag_Size)
		)&&_recreateInternal()
		)
	{
		getInterfaceImp()->removeDirtyFlag(ITexture2DImp::EDirtyFlag_ArraySize);
		getInterfaceImp()->removeDirtyFlag(ITexture2DImp::EDirtyFlag_Format);
		getInterfaceImp()->removeDirtyFlag(ITexture2DImp::EDirtyFlag_Mipmap);
		getInterfaceImp()->removeDirtyFlag(ITexture2DImp::EDirtyFlag_Size);
	}
	if(getInterfaceImp()->hasDirtyFlag(ITexture2DImp::EDirtyFlag_Pixels)
		&&_updatePixels()
		)
	{
		getInterfaceImp()->removeDirtyFlag(ITexture2DImp::EDirtyFlag_Pixels);
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
		desc.BindFlags=D3D11_BIND_SHADER_RESOURCE;
		desc.CPUAccessFlags=0;
		desc.Format=CUtility::getDXGIFormat(getInterfaceImp()->getFormat());
		desc.Height=getInterfaceImp()->getHeight();
		switch(getInterfaceImp()->getMipmapCount())
		{
		case 0xffffffff:
			desc.MipLevels=0;
		default:
			desc.MipLevels=getInterfaceImp()->getMipmapCount()+1;
		}
		desc.MiscFlags=0;
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
	if(TCOMInternalObject<ID3D11Texture2D>::getInternal())
	{
		const auto row_pitch=CUtility::getRowPitch(CUtility::getDXGIFormat(getInterfaceImp()->getFormat()),getInterfaceImp()->getWidth());
		const auto depth_pitch=row_pitch*getInterfaceImp()->getHeight();
		auto pixels=getInterfaceImp()->getPixels();
		switch(getInterfaceImp()->getFormat())
		{
		case IEnum::ETextureFormat_R8G8B8A8:
		{
			DWORD * abgr=static_cast<DWORD*>(DEVILX_ALLOC(depth_pitch));
			for(UInt32 i=0,count=getInterfaceImp()->getHeight()*getInterfaceImp()->getWidth();i<count;++i)
			{
				abgr[i]=((static_cast<const DWORD*>(pixels)[i]&0xff)<<24)|((static_cast<const DWORD*>(pixels)[i]&0xff00)<<8)|((static_cast<const DWORD*>(pixels)[i]&0xff0000)>>8)|((static_cast<const DWORD*>(pixels)[i]&0xff000000)>>24);
			}
			pixels=abgr;
		}
		break;
		}
		CSystemImp::getSingleton().getImmediateContext()->UpdateSubresource1(TCOMInternalObject<ID3D11Texture2D>::getInternal(),0,nullptr,pixels,row_pitch,depth_pitch,0);
		switch(getInterfaceImp()->getFormat())
		{
		case IEnum::ETextureFormat_R8G8B8A8:
			DEVILX_FREE(const_cast<VoidPtr>(pixels));
			break;
		}
		return true;
	}
	else
	{
		return false;
	}
}
