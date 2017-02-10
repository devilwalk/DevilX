#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;
using namespace NSD3D11;

NSDevilX::NSRenderSystem::NSD3D11::CRenderableSurfaceImp::CRenderableSurfaceImp(IRenderableSurfaceImp * interfaceImp)
	:TInterfaceObject<IRenderableSurfaceImp>(interfaceImp)
	,CRenderTargetImp(nullptr)
{
	getInterfaceImp()->addListener(this,IRenderableSurfaceImp::EMessage_EndFormatChange);
	getInterfaceImp()->addListener(this,IRenderableSurfaceImp::EMessage_EndSizeChange);
}

NSDevilX::NSRenderSystem::NSD3D11::CRenderableSurfaceImp::~CRenderableSurfaceImp()
{}

Void NSDevilX::NSRenderSystem::NSD3D11::CRenderableSurfaceImp::onMessage(IRenderableSurfaceImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case IRenderableSurfaceImp::EMessage_EndFormatChange:
	case IRenderableSurfaceImp::EMessage_EndSizeChange:
		addDirtyFlag(EDirtyFlag_Texture);
		break;
	}
}

Boolean NSDevilX::NSRenderSystem::NSD3D11::CRenderableSurfaceImp::_process(UInt32 flagIndex,OUT Bool & needNextProcess)
{
	switch(flagIndex)
	{
	case EDirtyFlag_Texture:
		if(mRenderTargetResource)
		{
			mRenderTargetResource->Release();
			mRenderTargetResource=nullptr;
		}
		if((getInterfaceImp()->getWidth()>0)&&(getInterfaceImp()->getHeight()>0))
		{
			D3D11_TEXTURE2D_DESC desc={0};
			desc.ArraySize=1;
			desc.BindFlags=D3D11_BIND_RENDER_TARGET;
			desc.Format=CUtility::getDXGIFormat(getInterfaceImp()->getFormat());
			desc.Height=getInterfaceImp()->getHeight();
			desc.MipLevels=1;
			desc.SampleDesc.Count=1;
			desc.Usage=D3D11_USAGE_DEFAULT;
			desc.Width=getInterfaceImp()->getWidth();
			CSystemImp::getSingleton().getDevice()->CreateTexture2D(&desc,nullptr,&mRenderTargetResource);
		}
		return true;
	}
	return false;
}
