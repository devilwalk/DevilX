#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;
using namespace NSD3D11;

NSDevilX::NSRenderSystem::NSD3D11::CIndexBufferImp::CIndexBufferImp(IIndexBufferImp * interfaceImp)
	:TInterfaceObject<IIndexBufferImp>(interfaceImp)
	,mBuffer(nullptr)
{
	mBuffer=DEVILX_NEW CBufferUpdater(sizeof(UInt32));
	mBuffer->setDataSource(reinterpret_cast<const ConstVoidPtr*>(&getInterfaceImp()->getIndicesRef()));
	mBuffer->setDirtyRanges(&getInterfaceImp()->getIndicesDirties());
	_update();
	CSystemImp::getSingleton().addListener(static_cast<TMessageReceiver<CSystemImp>*>(this),CSystemImp::EMessage_BeginFrame);
}

NSDevilX::NSRenderSystem::NSD3D11::CIndexBufferImp::~CIndexBufferImp()
{
	DEVILX_DELETE(mBuffer);
}

Void NSDevilX::NSRenderSystem::NSD3D11::CIndexBufferImp::onMessage(IIndexBufferImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	return Void();
}

Void NSDevilX::NSRenderSystem::NSD3D11::CIndexBufferImp::onMessage(CSystemImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case CSystemImp::EMessage_BeginFrame:
		_update();
		break;
	}
}

Void NSDevilX::NSRenderSystem::NSD3D11::CIndexBufferImp::_update()
{
	if(getInterfaceImp()->hasDirtyFlag(IIndexBufferImp::EDirtyFlag_Count))
	{
		mBuffer->setBuffer(nullptr);
		getInterfaceImp()->removeDirtyFlag(IIndexBufferImp::EDirtyFlag_Count);
	}
	if(getInterfaceImp()->hasDirtyFlag(IIndexBufferImp::EDirtyFlag_Index))
	{
		if(getInterfaceImp()->getIndices())
		{
			if(!getBuffer())
			{
				ID3D11Buffer * buf=nullptr;
				D3D11_BUFFER_DESC desc;
				desc.BindFlags=D3D11_BIND_INDEX_BUFFER;
				desc.CPUAccessFlags=0;
				desc.MiscFlags=0;
				desc.StructureByteStride=sizeof(UInt32);
				desc.ByteWidth=getInterfaceImp()->getCount()*desc.StructureByteStride;
				desc.Usage=D3D11_USAGE_DEFAULT;
				CSystemImp::getSingleton().getDevice()->CreateBuffer(&desc,nullptr,&buf);
				mBuffer->setBuffer(buf);
			}
			mBuffer->update();
			getInterfaceImp()->removeDirtyFlag(IIndexBufferImp::EDirtyFlag_Index);
		}
	}
}
