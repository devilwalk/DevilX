#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;
using namespace NSD3D11;

NSDevilX::NSRenderSystem::NSD3D11::CVertexBufferImp::CVertexBufferImp(IVertexBufferImp * interfaceImp)
	:TInterfaceObject<IVertexBufferImp>(interfaceImp)
{
	mBuffers.resize(CEnum::EVertexBufferType_Count);
	_update();
	CSystemImp::getSingleton().addListener(static_cast<TMessageReceiver<CSystemImp>*>(this),CSystemImp::EMessage_BeginFrame);
}

NSDevilX::NSRenderSystem::NSD3D11::CVertexBufferImp::~CVertexBufferImp()
{
}

Void NSDevilX::NSRenderSystem::NSD3D11::CVertexBufferImp::onMessage(IVertexBufferImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	return Void();
}

Void NSDevilX::NSRenderSystem::NSD3D11::CVertexBufferImp::onMessage(CSystemImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case CSystemImp::EMessage_BeginFrame:
		_update();
		break;
	}
}

Void NSDevilX::NSRenderSystem::NSD3D11::CVertexBufferImp::_update()
{
	if(getInterfaceImp()->hasDirtyFlag(IVertexBufferImp::EDirtyFlag_Count))
	{
		for(auto & vb:mBuffers)
		{
			if(vb)
			{
				vb->setBuffer(nullptr);
			}
		}
		getInterfaceImp()->removeDirtyFlag(IVertexBufferImp::EDirtyFlag_Count);
	}
	if(getInterfaceImp()->hasDirtyFlag(IVertexBufferImp::EDirtyFlag_Position)&&_update(CEnum::EVertexBufferType_Position))
	{
		getInterfaceImp()->removeDirtyFlag(IVertexBufferImp::EDirtyFlag_Position);
	}
	if(getInterfaceImp()->hasDirtyFlag(IVertexBufferImp::EDirtyFlag_Normal)&&_update(CEnum::EVertexBufferType_Normal))
	{
		getInterfaceImp()->removeDirtyFlag(IVertexBufferImp::EDirtyFlag_Normal);
	}
	if(getInterfaceImp()->hasDirtyFlag(IVertexBufferImp::EDirtyFlag_Tangent)&&_update(CEnum::EVertexBufferType_Tangent))
	{
		getInterfaceImp()->removeDirtyFlag(IVertexBufferImp::EDirtyFlag_Tangent);
	}
	if(getInterfaceImp()->hasDirtyFlag(IVertexBufferImp::EDirtyFlag_TextureCoord0)&&_update(CEnum::EVertexBufferType_TextureCoord0))
	{
		getInterfaceImp()->removeDirtyFlag(IVertexBufferImp::EDirtyFlag_TextureCoord0);
	}
	if(getInterfaceImp()->hasDirtyFlag(IVertexBufferImp::EDirtyFlag_TextureCoord1)&&_update(CEnum::EVertexBufferType_TextureCoord1))
	{
		getInterfaceImp()->removeDirtyFlag(IVertexBufferImp::EDirtyFlag_TextureCoord1);
	}
	if(getInterfaceImp()->hasDirtyFlag(IVertexBufferImp::EDirtyFlag_BlendWeight)&&_update(CEnum::EVertexBufferType_BlendWeight))
	{
		getInterfaceImp()->removeDirtyFlag(IVertexBufferImp::EDirtyFlag_BlendWeight);
	}
	if(getInterfaceImp()->hasDirtyFlag(IVertexBufferImp::EDirtyFlag_BlendIndex)&&_update(CEnum::EVertexBufferType_BlendIndex))
	{
		getInterfaceImp()->removeDirtyFlag(IVertexBufferImp::EDirtyFlag_BlendIndex);
	}
	if(getInterfaceImp()->hasDirtyFlag(IVertexBufferImp::EDirtyFlag_Diffuse)&&_update(CEnum::EVertexBufferType_Diffuse))
	{
		getInterfaceImp()->removeDirtyFlag(IVertexBufferImp::EDirtyFlag_Diffuse);
	}
}

Bool NSDevilX::NSRenderSystem::NSD3D11::CVertexBufferImp::_update(CEnum::EVertexBufferType type)
{
	ConstVoidPtr data_ptr=nullptr;
	const IVertexBufferImp::SDirties * dirties=nullptr;
	switch(type)
	{
	case CEnum::EVertexBufferType_Position:
		data_ptr=&getInterfaceImp()->getPositionsRef();
		dirties=&getInterfaceImp()->getPositionsDirties();
		break;
	case CEnum::EVertexBufferType_Normal:
		data_ptr=&getInterfaceImp()->getNormalsRef();
		dirties=&getInterfaceImp()->getNormalsDirties();
		break;
	case CEnum::EVertexBufferType_Tangent:
		data_ptr=&getInterfaceImp()->getTangentsRef();
		dirties=&getInterfaceImp()->getTangentsDirties();
		break;
	case CEnum::EVertexBufferType_TextureCoord0:
		data_ptr=&getInterfaceImp()->getTextureCoordsRef(IEnum::ETextureCoord_0);
		dirties=&getInterfaceImp()->getTextureCoordsDities(IEnum::ETextureCoord_0);
		break;
	case CEnum::EVertexBufferType_TextureCoord1:
		data_ptr=&getInterfaceImp()->getTextureCoordsRef(IEnum::ETextureCoord_1);
		dirties=&getInterfaceImp()->getTextureCoordsDities(IEnum::ETextureCoord_1);
		break;
	case CEnum::EVertexBufferType_BlendWeight:
		data_ptr=&getInterfaceImp()->getBlendWeightsRef();
		dirties=&getInterfaceImp()->getBlendWeightsDirties();
		break;
	case CEnum::EVertexBufferType_BlendIndex:
		data_ptr=&getInterfaceImp()->getBlendIndicesRef();
		dirties=&getInterfaceImp()->getBlendIndicesDirties();
		break;
	case CEnum::EVertexBufferType_Diffuse:
		data_ptr=&getInterfaceImp()->getDiffusesRef();
		dirties=&getInterfaceImp()->getDiffusesDirties();
		break;
	default:
		assert(0);
	}
	if(nullptr==data_ptr)
		return False;
	if(!getBuffers()[type])
	{
		mBuffers[type]=DEVILX_NEW CBufferUpdater(CUtility::getStride(type));
		mBuffers[type]->setDataSource(static_cast<const ConstVoidPtr*>(data_ptr));
		mBuffers[type]->setDirtyRanges(dirties);
	}
	if(!getBuffers()[type]->get())
	{
		ID3D11Buffer * buf=nullptr;
		D3D11_BUFFER_DESC desc;
		desc.BindFlags=D3D11_BIND_VERTEX_BUFFER;
		desc.CPUAccessFlags=0;
		desc.MiscFlags=0;
		desc.StructureByteStride=CUtility::getStride(type);
		desc.ByteWidth=getInterfaceImp()->getCount()*desc.StructureByteStride;
		desc.Usage=D3D11_USAGE_DEFAULT;
		CSystemImp::getSingleton().getDevice()->CreateBuffer(&desc,nullptr,&buf);
		mBuffers[type]->setBuffer(buf);
	}
	mBuffers[type]->update();
	return True;
}
