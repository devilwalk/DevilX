#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;
using namespace NSD3D11;

NSDevilX::NSRenderSystem::NSD3D11::CTransformer::CTransformer(ITransformerImp * interfaceImp)
	:TInterfaceObject<ITransformerImp>(interfaceImp)
	,CConstantBufferContainer("cbObjectTransform")
{
	getInterfaceImp()->addListener(this,ITransformerImp::EMessage_BeginDestruction);
	getInterfaceImp()->addListener(this,ITransformerImp::EMessage_EndPositionChange);
	getInterfaceImp()->addListener(this,ITransformerImp::EMessage_EndOrientationChange);
	getInterfaceImp()->addListener(this,ITransformerImp::EMessage_EndScaleChange);
}

NSDevilX::NSRenderSystem::NSD3D11::CTransformer::~CTransformer()
{}

Void NSDevilX::NSRenderSystem::NSD3D11::CTransformer::onMessage(ITransformerImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case ITransformerImp::EMessage_EndPositionChange:
	case ITransformerImp::EMessage_EndOrientationChange:
	case ITransformerImp::EMessage_EndScaleChange:
		needUpdate();
		break;
	case ITransformerImp::EMessage_BeginDestruction:
		CSystemImp::getSingleton().destroyTransformer(getInterfaceImp());
		break;
	}
}

Void NSDevilX::NSRenderSystem::NSD3D11::CTransformer::_updateConstantBuffer(Byte * buffer)
{
	auto offset=mConstantBuffer->getDescription()->getConstantDesc("gWorldMatrix").StartOffset;
	memcpy(&buffer[offset],&getInterfaceImp()->getTransformMT(),sizeof(CMatrix4F));
}
