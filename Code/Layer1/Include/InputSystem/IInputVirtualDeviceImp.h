#pragma once
namespace NSDevilX
{
	namespace NSInputSystem
	{
		class IPhysicalDeviceImp;
		class IVirtualDeviceImp
			:public IVirtualDevice
			,public CMessageNotifier
		{
		public:
			enum EMessage
			{
				EMessage_UpdateData,
			};
		protected:
			const String & mName;
			IPhysicalDeviceImp * const mPhysicalDevice;
			CWindow * const mWindow;
		public:
			IVirtualDeviceImp(const String & name,IPhysicalDeviceImp * physicalDevice,CWindow * window);
			virtual ~IVirtualDeviceImp();
			virtual Void update();
			// Inherited via IVirtualDevice
			virtual const String & getName() const override;
			virtual IPhysicalDevice * getPhysicalDevice() const override;
			virtual CWindow * getWindow() const override;
		};
	}
}