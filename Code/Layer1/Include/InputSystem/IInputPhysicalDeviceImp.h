#pragma once
namespace NSDevilX
{
	namespace NSInputSystem
	{
		class IPhysicalDeviceImp
			:public IPhysicalDevice
			,public TBaseObject<IPhysicalDeviceImp>
		{
		protected:
			const IEnum::EPhysicalDeviceType mType;
		public:
			IPhysicalDeviceImp(IEnum::EPhysicalDeviceType type);
			virtual ~IPhysicalDeviceImp();

			// Inherited via IPhysicalDevice
			virtual IEnum::EPhysicalDeviceType getType() const override;
		};
	}
}