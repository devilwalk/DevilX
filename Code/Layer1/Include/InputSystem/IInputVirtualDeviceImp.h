#pragma once
namespace NSDevilX
{
	namespace NSInputSystem
	{
		class IPhysicalDeviceImp;
		class IVirtualDeviceImp
			:public IVirtualDevice
		{
		protected:
			const String & mName;
			IPhysicalDeviceImp * const mPhysicalDevice;
		public:
			IVirtualDeviceImp(const String & name,IPhysicalDeviceImp * physicalDevice);
			virtual ~IVirtualDeviceImp();

			// Inherited via IVirtualDevice
			virtual IMouse * queryInterface_IMouse() const override;
			virtual IKeyboard * queryInterface_IKeyboard() const override;
			virtual const String & getName() const override;
			virtual IPhysicalDevice * getPhysicalDevice() const override;
		};
	}
}