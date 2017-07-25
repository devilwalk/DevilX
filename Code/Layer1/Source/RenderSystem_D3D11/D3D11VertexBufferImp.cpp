#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;
using namespace NSD3D11;

NSDevilX::NSRenderSystem::NSD3D11::CVertexBufferImp::CVertexBufferImp(IVertexBufferImp * interfaceImp)
	:TInterfaceObject<IVertexBufferImp>(interfaceImp)
{
	mBuffers.resize(IVertexBufferImp::EBufferType_Count);
	getInterfaceImp()->addListener(this,IVertexBufferImp::EMessage_EndDiffuseEnableChange);
	getInterfaceImp()->addListener(this,IVertexBufferImp::EMessage_EndNormalEnableChange);
	getInterfaceImp()->addListener(this,IVertexBufferImp::EMessage_EndTangentEnableChange);
	getInterfaceImp()->addListener(this,IVertexBufferImp::EMessage_EndTextureCoord0EnableChange);
	getInterfaceImp()->addListener(this,IVertexBufferImp::EMessage_EndTextureCoord1EnableChange);
	getInterfaceImp()->addListener(this,IVertexBufferImp::EMessage_EndPositionEnableChange);
	getInterfaceImp()->addListener(this,IVertexBufferImp::EMessage_EndBlendIndexEnableChange);
	getInterfaceImp()->addListener(this,IVertexBufferImp::EMessage_EndBlendWeightEnableChange);
}

NSDevilX::NSRenderSystem::NSD3D11::CVertexBufferImp::~CVertexBufferImp()
{
}

Void NSDevilX::NSRenderSystem::NSD3D11::CVertexBufferImp::onMessage(IVertexBufferImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	UInt32 index=-1;
	switch(message)
	{
	case IVertexBufferImp::EMessage_EndDiffuseEnableChange:
		index=IVertexBufferImp::EBufferType_Diffuse;
		break;
	case IVertexBufferImp::EMessage_EndNormalEnableChange:
		index=IVertexBufferImp::EBufferType_Normal;
		break;
	case IVertexBufferImp::EMessage_EndTangentEnableChange:
		index=IVertexBufferImp::EBufferType_Tangent;
		break;
	case IVertexBufferImp::EMessage_EndTextureCoord0EnableChange:
		index=IVertexBufferImp::EBufferType_TextureCoord0;
		break;
	case IVertexBufferImp::EMessage_EndTextureCoord1EnableChange:
		index=IVertexBufferImp::EBufferType_TextureCoord1;
		break;
	case IVertexBufferImp::EMessage_EndPositionEnableChange:
		index=IVertexBufferImp::EBufferType_Position;
		break;
	case IVertexBufferImp::EMessage_EndBlendIndexEnableChange:
		index=IVertexBufferImp::EBufferType_BlendIndex;
		break;
	case IVertexBufferImp::EMessage_EndBlendWeightEnableChange:
		index=IVertexBufferImp::EBufferType_BlendWeight;
		break;
	}
	if(getInterfaceImp()->getBuffer(index))
	{
		mBuffers[index]=CSystemImp::getSingleton().getBuffer(getInterfaceImp()->getBuffer(index));
		mBuffers[index]->addRef();
	}
	else
	{
		mBuffers[index]->release();
		mBuffers[index]=nullptr;
	}
}