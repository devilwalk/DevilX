#pragma once
#include "IGDEnum.h"
#include "IGDInstance.h"
namespace NSDevilX
{
	namespace NSCore
	{
		namespace NSGraphicsDriver
		{
			class ISystem
			{
			protected:
				virtual ~ISystem(){ }
			public:
				virtual IInstance* createInstance(IEnum::EInstanceMajorType majorType,Int32 minorType)=0;
			};
		}
	}
}