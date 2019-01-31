#pragma once
#include "ICoreGPUCommandQueue.h"
#include "ICoreGPUResource.h"
namespace NSDevilX
{
	namespace NSCore
	{
		class IGPUDevice
		{
		protected:
			virtual ~IGPUDevice(){ }
		public:
		};
		class IGPUDevice11
		{
		protected:
			virtual ~IGPUDevice11(){ }
		public:
			virtual IGPUDevice * queryInterface_IGPUDevice()=0;
			virtual IGPUBuffer * createBuffer(const IGPUStruct::SBufferDesc & desc,const IGPUStruct::SSubResourceData * initialData)=0;
		};
	}
}