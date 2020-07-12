#pragma once
namespace NSDevilX
{
	namespace NSCore
	{
		namespace NSGraphicsDriver
		{
			class IPhysicsDeviceGroupImp;
			class IPhysicsDeviceImp: public IPhysicsDevice
			{
			protected:
				IPhysicsDeviceGroupImp* mGroup;
			public:
				IPhysicsDeviceImp(IPhysicsDeviceGroupImp* group);
				virtual ~IPhysicsDeviceImp();

				// Í¨¹ý IPhysicsDeviceImp ¼Ì³Ð
				virtual IPhysicsDeviceGroup* getGroup() const override;
			};
			namespace NSDXGI
			{
#if DEVILX_WINDOW_SYSTEM==DEVILX_WINDOW_SYSTEM_WINDOWS
				class IPhysicsDeviceImp
					:public NSGraphicsDriver::IPhysicsDeviceImp
					,public TBaseObject<IPhysicsDeviceImp>
				{
				protected:
					UINT mInternal;
				public:
					IPhysicsDeviceImp(UINT node,IPhysicsDeviceGroupImp* group);
					virtual ~IPhysicsDeviceImp();
				};
#endif
			}
			namespace NSVulkan
			{
				class IPhysicsDeviceImp
					:public NSGraphicsDriver::IPhysicsDeviceImp
					,public TBaseObject<IPhysicsDeviceImp>
				{
				protected:
					VkPhysicalDevice mInternal;
				public:
					IPhysicsDeviceImp(VkPhysicalDevice dev,IPhysicsDeviceGroupImp* group);
					virtual ~IPhysicsDeviceImp();
				};
			}
		}
	}
}