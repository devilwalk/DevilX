#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;
using namespace NSD3D11;

NSDevilX::NSRenderSystem::NSD3D11::CIndexBufferImp::CIndexBufferImp(IIndexBufferImp * interfaceImp)
	:TInterfaceObject<IIndexBufferImp>(interfaceImp)
	,mBuffer(0)
{
	_update();
	CSystemImp::getSingleton().addListener(static_cast<TMessageReceiver<CSystemImp>*>(this),CSystemImp::EMessage_BeginFrame);
}

NSDevilX::NSRenderSystem::NSD3D11::CIndexBufferImp::~CIndexBufferImp()
{
	if(getBuffer())
		mBuffer->Release();
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
		if(getBuffer())
		{
			getBuffer()->Release();
			mBuffer=nullptr;
		}
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
				D3D11_SUBRESOURCE_DATA sub_data;
				sub_data.pSysMem=getInterfaceImp()->getIndices();
				sub_data.SysMemPitch=desc.ByteWidth;
				sub_data.SysMemSlicePitch=desc.ByteWidth;
				CSystemImp::getSingleton().getDevice()->CreateBuffer(&desc,&sub_data,&buf);
				mBuffer=buf;
			}
			else
			{
				CSystemImp::getSingleton().getImmediateContext()->UpdateSubresource(getBuffer(),0,nullptr,getInterfaceImp()->getIndices(),getInterfaceImp()->getCount()*sizeof(UInt32),getInterfaceImp()->getCount()*sizeof(UInt32));
			}
			getInterfaceImp()->removeDirtyFlag(IIndexBufferImp::EDirtyFlag_Index);
		}
	}
}
