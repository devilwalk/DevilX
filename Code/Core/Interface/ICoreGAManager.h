#pragma once
#include "ICoreGADevice.h"
#include "ICoreGASwapChain.h"
namespace NSDevilX
{
	namespace NSCore
	{
		class DLLAPI IGAManager
		{
		protected:
			~IGAManager();
		public:
			IGADevice * createDevice(IGAEnum::EDeviceVersion version);
			IGASwapChain * createSwapChain(IGADevice * dev,const IGAStruct::SGISwapChainDesc & desc);
		};
	}
}