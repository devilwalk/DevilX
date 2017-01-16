#pragma once
#include "PhysicalDeviceManager.h"
#include "VirtualDeviceManager.h"
namespace NSDevilX
{
	namespace NSInputSystem
	{
		namespace NSDirectX
		{
			class CSystem
				:public TBaseObject<CSystem>
				,public TSingleton<CSystem>
				,public TMessageReceiver<ISystemImp>
			{
			protected:
				CPhysicalDeviceManager * mPhysicalDeviceManager;
				CVirtualDeviceManager * mVirtualDeviceManager;
				IDirectInput8 * mDirectInput;
			public:
				CSystem();
				~CSystem();
				IDirectInput8 * getDirectInput()const
				{
					return mDirectInput;
				}
				CPhysicalDeviceManager * getPhysicalDeviceManager()const
				{
					return mPhysicalDeviceManager;
				}
				CVirtualDeviceManager * getVirtualDeviceManager()const
				{
					return mVirtualDeviceManager;
				}

				// Inherited via TMessageReceiver
				virtual void onMessage(ISystemImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
			};
		}
	}
}