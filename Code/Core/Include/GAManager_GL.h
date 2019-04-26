#include "IGADeviceImp_GL.h"
#include "IGASwapChainImp_GL.h"
#include "GAEnvironment_GL.h"
namespace NSDevilX
{
	namespace NSCore
	{
		namespace NSOpenGL
		{
			class CGAManager
				:public TBaseObject<CGAManager>
				,public TSingleton<CGAManager>
			{
			protected:
				TResourcePtrVector(IGADeviceImp) mDevices;
				TResourcePtrVector(IGASwapChainImp) mSwapChains;
			public:
				CGAManager();
				~CGAManager();

				IGADeviceImp* createDevice(IGAEnum::EDeviceVersion version);
				IGASwapChainImp* createSwapChain(IGADeviceImp* device,const IGAStruct::SGISwapChainDesc& desc);
			};
		}
	}
}