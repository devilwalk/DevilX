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
				TResourcePtrVector(CGADeviceImp) mDevices;
				TResourcePtrVector(IGASwapChainImp) mSwapChains;
			public:
				CGAManager();
				~CGAManager();

				CGADeviceImp* createDevice(IGAEnum::EHighLevelDeviceVersion version);
				IGASwapChainImp* createSwapChain(CGADeviceImp* device,const IGAStruct::SGISwapChainDesc& desc);
			};
		}
	}
}