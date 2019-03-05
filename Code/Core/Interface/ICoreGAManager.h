#pragma once
#include "ICoreGAAdapter.h"
#include "ICoreGADevice.h"
namespace NSDevilX
{
	namespace NSCore
	{
		class DLLAPI IGAManager
		{
		protected:
			~IGAManager();
		public:
			IGAAdapter * getAdapter(SizeT index=0);
			IGADevice * createDevice(IGAEnum::EDeviceVersion version,IGAAdapter * adapter=nullptr);
		};
	}
}