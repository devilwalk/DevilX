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

IInstance* NSDevilX::NSCore::NSGraphicsDriver::ISystemImp::createInstance(IEnum::EInstance* types,UInt32 count)
{
	if((nullptr==types)||(count==0))
	{
		TVector(IEnum::EInstance) default_types;
		default_types.reserve(32);
		for(Int32 i=IEnum::EInstance_Vulkan; i<=IEnum::EInstance_GLES2_0; i++)
		{
			default_types.push_back(static_cast<IEnum::EInstance>(i));
		}
		return createInstance(&default_types[0],static_cast<UInt32>(default_types.size()));
	}
	else
	{
		for(UInt32 i=0; i<count; i++)
		{
			IInstanceImp* inst=nullptr;
			switch(types[i])
			{
			case IEnum::EInstance_Vulkan:
				inst=DEVILX_NEW NSVulkan::IInstanceImp();
				break;
			case IEnum::EInstance_D3D12_0:
			case IEnum::EInstance_D3D11_3:
			case IEnum::EInstance_D3D11_2:
			case IEnum::EInstance_D3D11_1:
			case IEnum::EInstance_D3D11_0:
			case IEnum::EInstance_D3D10_1:
			case IEnum::EInstance_D3D10_0:
			case IEnum::EInstance_D3D9_3:
				inst=DEVILX_NEW NSDXGI::IInstanceImp(types[i]);
				break;
			}
			if(inst && inst->initialize())
			{
				return inst;
			}
			DEVILX_DELETE(inst);
		}
	}
	return nullptr;
}
