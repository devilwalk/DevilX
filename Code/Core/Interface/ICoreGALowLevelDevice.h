#pragma once
#include "ICoreGACommandQueue.h"
namespace NSDevilX
{
	namespace NSCore
	{
		class IGALowLevelDevice
		{
		protected:
			virtual ~IGALowLevelDevice()
			{
			}
		public:
			virtual IGADevice* queryInterface_IGADevice()const=0;
			virtual IGAEnum::ELowLevelDeviceVersion getVersion()const=0;
			virtual IGAHeap* createHeap(const IGAStruct::SHeapDesc& desc)=0;
			virtual IGACommandQueue_3D* createCommandQueue_3D()=0;
			virtual IGACommandQueue_Compute* createCommandQueue_Compute()=0;
			virtual IGACommandQueue_Copy* createCommandQueue_Copy()=0;
		};
	}
}