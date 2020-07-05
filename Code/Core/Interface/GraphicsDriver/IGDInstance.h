#pragma once
#include "IGDPhysicsDevice.h"
namespace NSDevilX
{
	namespace NSCore
	{
		namespace NSGraphicsDriver
		{
			class IInstance
			{
			protected:
				virtual ~IInstance(){ }
			public:
				virtual UInt32 enumPhysicsDevices(IPhysicsDevice** outDevices=nullptr)=0;
			};
		}
	}
}