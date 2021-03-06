#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;
using namespace NSD3D11;

NSDevilX::NSRenderSystem::NSD3D11::CResource::CResource()
	:mRegisterCounter(0)
{}

NSDevilX::NSRenderSystem::NSD3D11::CResource::~CResource()
{}

Void NSDevilX::NSRenderSystem::NSD3D11::CResource::_registerToSystemImp()
{
	if(0==mRegisterCounter)
	{
		CSystemImp::getSingleton().addListener(this,CSystemImp::EMessage_BeginFrame);
	}
	mRegisterCounter+=60;
	mRegisterCounter=std::min<UInt32>(mRegisterCounter,600000000);
}

Void NSDevilX::NSRenderSystem::NSD3D11::CResource::_unregisterToSystemImp()
{
	if(mRegisterCounter)
	{
		mRegisterCounter-=1;
		if(0==mRegisterCounter)
		{
			CSystemImp::getSingleton().removeListener(this,CSystemImp::EMessage_BeginFrame);
		}
	}
}
