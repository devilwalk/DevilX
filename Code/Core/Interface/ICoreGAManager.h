#pragma once
#include "ICoreGAHighLevelDevice.h"
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
			IGAHighLevelDevice* createDevice(IGAEnum::EHighLevelDeviceVersion version);
			IGASwapChain * createSwapChain(IGADevice * dev,const IGAStruct::SGISwapChainDesc & desc);
		};
	}
}