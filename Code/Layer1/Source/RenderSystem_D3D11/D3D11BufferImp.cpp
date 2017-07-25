#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;
using namespace NSD3D11;

NSDevilX::NSRenderSystem::NSD3D11::CBufferImp::CBufferImp(IBufferImp * interfaceImp)
	:TInterfaceObject<IBufferImp>(interfaceImp)
	,mBuffer(nullptr)
{
	mBuffer=DEVILX_NEW CBufferUpdater();
	mBuffer->setDataSource(&getInterfaceImp()->getDatasRef());
	mBuffer->setDirtyRanges(&getInterfaceImp()->getDirties());
	CSystemImp::getSingleton().addListener(static_cast<TMessageReceiver<CSystemImp>*>(this),CSystemImp::EMessage_BeginFrame);
}

NSDevilX::NSRenderSystem::NSD3D11::CBufferImp::~CBufferImp()
{
	DEVILX_DELETE(mBuffer);
}

Void NSDevilX::NSRenderSystem::NSD3D11::CBufferImp::_update()
{
	if(getInterfaceImp()->hasDirtyFlag(IBufferImp::EDirtyFlag_Size))
	{
		mBuffer->setBuffer(nullptr);
		ID3D11Buffer * buf=nullptr;
		D3D11_BUFFER_DESC desc;
		desc.BindFlags=(getInterfaceImp()->getType()==IBufferImp::EType_VertexBuffer)?D3D11_BIND_VERTEX_BUFFER:D3D11_BIND_INDEX_BUFFER;
		desc.CPUAccessFlags=0;
		desc.MiscFlags=0;
		desc.StructureByteStride=0;
		desc.ByteWidth=getInterfaceImp()->getSize();
		desc.Usage=D3D11_USAGE_DEFAULT;
		CSystemImp::getSingleton().getDevice()->CreateBuffer(&desc,nullptr,&buf);
		setInternal(buf);
		mBuffer->setBuffer(buf);
		getInterfaceImp()->removeDirtyFlag(IBufferImp::EDirtyFlag_Size);
	}
	if(getInterfaceImp()->hasDirtyFlag(IBufferImp::EDirtyFlag_Datas))
	{
		mBuffer->update();
		getInterfaceImp()->removeDirtyFlag(IBufferImp::EDirtyFlag_Datas);
	}
}

Void NSDevilX::NSRenderSystem::NSD3D11::CBufferImp::onMessage(IBufferImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
}

Void NSDevilX::NSRenderSystem::NSD3D11::CBufferImp::onMessage(CSystemImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case CSystemImp::EMessage_BeginFrame:
		_update();
		break;
	}
}
