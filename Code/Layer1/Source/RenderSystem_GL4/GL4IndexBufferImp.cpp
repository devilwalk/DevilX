#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;
using namespace NSGL4;

NSDevilX::NSRenderSystem::NSGL4::CIndexBufferImp::CIndexBufferImp(IIndexBufferImp * interfaceImp)
	:TInterfaceObject<IIndexBufferImp>(interfaceImp)
	,mBuffer(nullptr)
{
	mBuffer=CSystemImp::getSingleton().getBuffer(getInterfaceImp()->getBuffer());
	mBuffer->addRef();
}

NSDevilX::NSRenderSystem::NSGL4::CIndexBufferImp::~CIndexBufferImp()
{
	mBuffer->release();
}

Void NSDevilX::NSRenderSystem::NSGL4::CIndexBufferImp::onMessage(IIndexBufferImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	return Void();
}
