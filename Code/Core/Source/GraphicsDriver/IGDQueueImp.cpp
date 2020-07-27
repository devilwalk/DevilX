#include "../Precompiler.h"
using namespace NSDevilX;
using namespace NSCore;
using namespace NSGraphicsDriver;

NSDevilX::NSCore::NSGraphicsDriver::IQueueImp::IQueueImp(IDeviceImp* dev)
	:mDevice(dev)
{
}

NSDevilX::NSCore::NSGraphicsDriver::IQueueImp::~IQueueImp()
{
}

#if DEVILX_WINDOW_SYSTEM==DEVILX_WINDOW_SYSTEM_WINDOWS

NSDevilX::NSCore::NSGraphicsDriver::NSD3D12::IQueueImp::IQueueImp(IDeviceImp* dev,ID3D12CommandQueue* queue)
	:NSGraphicsDriver::IQueueImp(dev)
	,mInternal(queue)
{
}

NSDevilX::NSCore::NSGraphicsDriver::NSD3D12::IQueueImp::~IQueueImp()
{
}

#endif

NSDevilX::NSCore::NSGraphicsDriver::NSVulkan::IQueueImp::IQueueImp(IDeviceImp* dev,VkQueue queue)
	:NSGraphicsDriver::IQueueImp(dev)
	,mInternal(queue)
{
}

NSDevilX::NSCore::NSGraphicsDriver::NSVulkan::IQueueImp::~IQueueImp()
{
}
