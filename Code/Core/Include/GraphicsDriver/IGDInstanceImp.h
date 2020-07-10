#pragma once
#include "IGDPhysicsDeviceImp.h"
namespace NSDevilX
{
	namespace NSCore
	{
		namespace NSGraphicsDriver
		{
			class IInstanceImp: public IInstance
			{
			protected:
				IEnum::EInstance mType;
				TResourcePtrVector(IPhysicsDeviceImp) mPhysicsDevices;
			public:
				IInstanceImp(IEnum::EInstance type);
				virtual ~IInstanceImp();

				virtual Boolean initialize()=0;
			};
			namespace NSDXGI
			{
#if DEVILX_WINDOW_SYSTEM==DEVILX_WINDOW_SYSTEM_WINDOWS
				class IInstanceImp
					:public NSGraphicsDriver::IInstanceImp
					,public TBaseObject<IInstanceImp>
				{
				protected:
					CComPtr<IDXGIFactory> mInternal;
				public:
					IInstanceImp(IEnum::EInstance type);
					virtual ~IInstanceImp();

					// ͨ�� IInstance �̳�
					virtual UInt32 enumPhysicsDevices(IPhysicsDevice** outDevices=nullptr) override;

					// ͨ�� IInstanceImp �̳�
					virtual Boolean initialize() override;
				};
#endif
			}
			namespace NSVulkan
			{
				class IInstanceImp
					:public NSGraphicsDriver::IInstanceImp
					,public TBaseObject<IInstanceImp>
				{
				protected:
					VkInstance mInternal;
				public:
					IInstanceImp();
					virtual ~IInstanceImp();

					// ͨ�� IInstance �̳�
					virtual UInt32 enumPhysicsDevices(IPhysicsDevice** outDevices=nullptr) override;

					// ͨ�� IInstanceImp �̳�
					virtual Boolean initialize() override;
				};
			}
		}
	}
}