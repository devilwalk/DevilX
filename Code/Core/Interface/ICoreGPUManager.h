#pragma once
#include "ICoreGPUDevice.h"
namespace NSDevilX
{
	namespace NSCore
	{
		class DLLAPI IGPUManager
		{
		protected:
			~IGPUManager();
		public:
			IGPUDevice * createDevice(IGPUEnum::EDeviceVersion version);
		};
	}
}