#pragma once
namespace NSDevilX
{
	namespace NSCore
	{
		namespace NSGraphicsDriver
		{
			class IPhysicsDeviceGroupImp
				:public IPhysicsDeviceGroup
			{
			protected:
				TResourcePtrVector(IPhysicsDeviceImp) mDevices;
			public:
				IPhysicsDeviceGroupImp();
				virtual ~IPhysicsDeviceGroupImp();

				void addDevice(IPhysicsDeviceImp* device)
				{
					mDevices.push_back(device);
				}

				// Í¨¹ý IPhysicsDeviceGroup ¼Ì³Ð
				virtual UInt32 getDeviceCount() const override;
				virtual IPhysicsDevice* getDevice(UInt32 index) const override;
			};
			namespace NSDXGI
			{
#if DEVILX_WINDOW_SYSTEM==DEVILX_WINDOW_SYSTEM_WINDOWS
				class IPhysicsDeviceGroupImp
					:public NSGraphicsDriver::IPhysicsDeviceGroupImp
					,public TBaseObject<IPhysicsDeviceGroupImp>
				{
				protected:
					CComPtr<IDXGIAdapter> mInternal;
				public:
					IPhysicsDeviceGroupImp(IDXGIAdapter* adapter);
					~IPhysicsDeviceGroupImp();
				};
#endif
			}
			namespace NSVulkan
			{
				class IPhysicsDeviceGroupImp
					:public NSGraphicsDriver::IPhysicsDeviceGroupImp
					,public TBaseObject<IPhysicsDeviceGroupImp>
				{
				protected:
					UInt32 mInternal;
				public:
					IPhysicsDeviceGroupImp(UInt32 group);
					~IPhysicsDeviceGroupImp();
				};
			}
		}
	}
}