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
				CSystemImp::getSingleton().getDevice()->CreateBuffer(&desc,nullptr,&buf);
				mBuffer=buf;
			}
			if(getInterfaceImp()->getIndicesDirties().empty())
				CSystemImp::getSingleton().getImmediateContext()->UpdateSubresource(getBuffer(),0,nullptr,getInterfaceImp()->getIndices(),getInterfaceImp()->getCount()*sizeof(UInt32),getInterfaceImp()->getCount()*sizeof(UInt32));
			else
			{
				for(auto const & dirty:getInterfaceImp()->getIndicesDirties())
				{
					D3D11_BOX dst_box={0};
					dst_box.left=dirty.getMin()*sizeof(UInt32);
					dst_box.right=(dirty.getMax()+1)*sizeof(UInt32);
					dst_box.bottom=1;
					dst_box.back=1;
					ConstVoidPtr src_ptr=reinterpret_cast<ConstVoidPtr>(reinterpret_cast<SizeT>(getInterfaceImp()->getIndices())+dst_box.left);
					CSystemImp::getSingleton().getImmediateContext()->UpdateSubresource(getBuffer(),0,&dst_box,src_ptr,dst_box.right-dst_box.left+1,dst_box.right-dst_box.left+1);
				}
			}
			getInterfaceImp()->removeDirtyFlag(IIndexBufferImp::EDirtyFlag_Index);
		}
	}
}
