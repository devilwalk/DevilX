#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;
using namespace NSGLES3;

NSDevilX::NSRenderSystem::NSGLES3::CResource::CResource()
	:mRegisterCounter(0)
{}

NSDevilX::NSRenderSystem::NSGLES3::CResource::~CResource()
{}

Void NSDevilX::NSRenderSystem::NSGLES3::CResource::_registerToSystemImp()
{
	if(0==mRegisterCounter)
	{
		CSystemImp::getSingleton().addListener(this,CSystemImp::EMessage_BeginFrame);
	}
	mRegisterCounter+=60;
	mRegisterCounter=std::min<UInt32>(mRegisterCounter,600000000);
}

Void NSDevilX::NSRenderSystem::NSGLES3::CResource::_unregisterToSystemImp()
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
