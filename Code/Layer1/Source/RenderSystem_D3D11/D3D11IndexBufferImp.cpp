#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;
using namespace NSD3D11;

NSDevilX::NSRenderSystem::NSD3D11::CIndexBufferImp::CIndexBufferImp(IIndexBufferImp * interfaceImp)
	:TInterfaceObject<IIndexBufferImp>(interfaceImp)
	,mBuffer(nullptr)
{
	mBuffer=CSystemImp::getSingleton().getBuffer(getInterfaceImp()->getBuffer());
	mBuffer->addRef();
}

NSDevilX::NSRenderSystem::NSD3D11::CIndexBufferImp::~CIndexBufferImp()
{
	mBuffer->release();
}

Void NSDevilX::NSRenderSystem::NSD3D11::CIndexBufferImp::onMessage(IIndexBufferImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	return Void();
}
