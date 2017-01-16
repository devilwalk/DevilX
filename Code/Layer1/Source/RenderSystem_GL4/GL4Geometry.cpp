#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;
using namespace NSGL4;

NSDevilX::NSRenderSystem::NSGL4::CGeometry::CGeometry(IGeometryImp * interfaceImp)
	:TInterfaceObject<IGeometryImp>(interfaceImp)
	,mVertexBuffer(nullptr)
	,mIndexBuffer(nullptr)
{
	mVertexBuffer=static_cast<decltype(mVertexBuffer)>(CSystemImp::getSingleton().getVertexBuffer(static_cast<IVertexBufferImp*>(getInterfaceImp()->getVertexBuffer())));
	mIndexBuffer=static_cast<decltype(mIndexBuffer)>(CSystemImp::getSingleton().getIndexBuffer(static_cast<IIndexBufferImp*>(getInterfaceImp()->getIndexBuffer())));
	getInterfaceImp()->addListener(this,IGeometryImp::EMessage_EndVertexBufferChange);
	getInterfaceImp()->addListener(this,IGeometryImp::EMessage_EndIndexBufferChange);
}

NSDevilX::NSRenderSystem::NSGL4::CGeometry::~CGeometry()
{
}

Void NSDevilX::NSRenderSystem::NSGL4::CGeometry::onMessage(IGeometryImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case IGeometryImp::EMessage_EndIndexBufferChange:
		mIndexBuffer=static_cast<decltype(mIndexBuffer)>(CSystemImp::getSingleton().getIndexBuffer(static_cast<IIndexBufferImp*>(getInterfaceImp()->getIndexBuffer())));
		assert(mIndexBuffer);
		break;
	case IGeometryImp::EMessage_EndVertexBufferChange:
		mVertexBuffer=static_cast<decltype(mVertexBuffer)>(CSystemImp::getSingleton().getVertexBuffer(static_cast<IVertexBufferImp*>(getInterfaceImp()->getVertexBuffer())));
		assert(mVertexBuffer);
		break;
	}
}