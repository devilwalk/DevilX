#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;
using namespace NSGL4;

NSDevilX::NSRenderSystem::NSGL4::CBufferImp::CBufferImp(IBufferImp * interfaceImp)
	:TInterfaceObject<IBufferImp>(interfaceImp)
	,CGLInternalObject(glDeleteBuffers)
	,mBuffer(nullptr)
{
	mBuffer=DEVILX_NEW CBufferUpdater();
	mBuffer->setDataSource(&getInterfaceImp()->getDatasRef());
	mBuffer->setDirtyRanges(&getInterfaceImp()->getDirties());
	CSystemImp::getSingleton().addListener(static_cast<TMessageReceiver<CSystemImp>*>(this),CSystemImp::EMessage_BeginFrame);
}

NSDevilX::NSRenderSystem::NSGL4::CBufferImp::~CBufferImp()
{
	DEVILX_DELETE(mBuffer);
}

Void NSDevilX::NSRenderSystem::NSGL4::CBufferImp::_update()
{
	if(getInterfaceImp()->hasDirtyFlag(IBufferImp::EDirtyFlag_Size))
	{
		mBuffer->setBuffer(0);
		GLuint buf=0;
		glCreateBuffers(1,&buf);
		CUtility::checkGLError();
		glNamedBufferStorage(buf,getInterfaceImp()->getSize(),nullptr,GL_DYNAMIC_STORAGE_BIT);
		CUtility::checkGLError();
		setInternal(buf);
		mBuffer->setBuffer(buf);
		getInterfaceImp()->removeDirtyFlag(IBufferImp::EDirtyFlag_Size);
		notify(EMessage_InternalCreate);
	}
	if(getInterfaceImp()->hasDirtyFlag(IBufferImp::EDirtyFlag_Datas))
	{
		mBuffer->update();
		getInterfaceImp()->removeDirtyFlag(IBufferImp::EDirtyFlag_Datas);
	}
}

Void NSDevilX::NSRenderSystem::NSGL4::CBufferImp::onMessage(IBufferImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{}

Void NSDevilX::NSRenderSystem::NSGL4::CBufferImp::onMessage(CSystemImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case CSystemImp::EMessage_BeginFrame:
		_update();
		break;
	}
}
