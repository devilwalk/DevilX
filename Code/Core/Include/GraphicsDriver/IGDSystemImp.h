#pragma once
#include "IGDInstanceImp.h"
namespace NSDevilX
{
	namespace NSCore
	{
		namespace NSGraphicsDriver
		{
			class ISystemImp
				:public ISystem
				,public TMemoryAllocatorObject<ISystemImp>
				,public TSingleton<ISystemImp>
			{
			protected:
			public:
				ISystemImp();
				virtual ~ISystemImp();
				// ͨ�� ISystem �̳�
				virtual IInstance* createInstance(IEnum::EInstanceMajorType majorType,Int32 minorType) override;
			};
		}
	}
}