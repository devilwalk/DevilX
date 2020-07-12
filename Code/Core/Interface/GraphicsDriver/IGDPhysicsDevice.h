#pragma once
namespace NSDevilX
{
	namespace NSCore
	{
		namespace NSGraphicsDriver
		{
			class IPhysicsDeviceGroup;
			class IPhysicsDevice
			{
			protected:
				virtual ~IPhysicsDevice(){ }
			public:
				virtual IPhysicsDeviceGroup* getGroup()const=0;
			};

			class IPhysicsDeviceGroup
			{
			protected:
				virtual ~IPhysicsDeviceGroup(){ }
			public:
				virtual UInt32 getDeviceCount()const=0;
				virtual IPhysicsDevice* getDevice(UInt32 index)const=0;
			};
		}
	}
}