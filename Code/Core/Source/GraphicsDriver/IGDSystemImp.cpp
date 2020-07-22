#include "../Precompiler.h"
using namespace NSDevilX;
using namespace NSCore;
using namespace NSGraphicsDriver;

NSDevilX::NSCore::NSGraphicsDriver::ISystemImp::ISystemImp()
{
}

NSDevilX::NSCore::NSGraphicsDriver::ISystemImp::~ISystemImp()
{
}

IInstance* NSDevilX::NSCore::NSGraphicsDriver::ISystemImp::createInstance(IEnum::EInstanceMajorType majorType,Int32 minorType)
{
	IInstanceImp* inst=nullptr;
	switch(majorType)
	{
	case NSDevilX::NSCore::NSGraphicsDriver::IEnum::EInstanceMajorType_D3D:
		inst=DEVILX_NEW NSD3D::IInstanceImp(*reinterpret_cast<IEnum::EInstanceMinorType_D3D*>(&minorType));
		break;
	case NSDevilX::NSCore::NSGraphicsDriver::IEnum::EInstanceMajorType_Vulkan:
		inst=DEVILX_NEW NSVulkan::IInstanceImp();
		break;
	case NSDevilX::NSCore::NSGraphicsDriver::IEnum::EInstanceMajorType_GL:
		inst=DEVILX_NEW NSOpenGL::IInstanceImp(*reinterpret_cast<IEnum::EInstanceMinorType_GL*>(&minorType));
		break;
	}
	if(inst&&inst->initialize())
	{
		return inst;
	}
	DEVILX_DELETE(inst);
	return nullptr;
}
