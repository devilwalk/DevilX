#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;
using namespace NSGLES3;

NSDevilX::NSRenderSystem::NSGLES3::CTransformerImp::CTransformerImp(ITransformerImp * interfaceImp)
	:TInterfaceObject<ITransformerImp>(interfaceImp)
	,CConstantBufferContainer("cbObjectTransform")
{
	getInterfaceImp()->addListener(this,ITransformerImp::EMessage_BeginDestruction);
	getInterfaceImp()->addListener(this,ITransformerImp::EMessage_EndPositionChange);
	getInterfaceImp()->addListener(this,ITransformerImp::EMessage_EndOrientationChange);
	getInterfaceImp()->addListener(this,ITransformerImp::EMessage_EndScaleChange);
}

NSDevilX::NSRenderSystem::NSGLES3::CTransformerImp::~CTransformerImp()
{}

Void NSDevilX::NSRenderSystem::NSGLES3::CTransformerImp::onMessage(ITransformerImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
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

Void NSDevilX::NSRenderSystem::NSGLES3::CTransformerImp::_updateConstantBuffer(Byte * buffer)
{
	auto offset=mConstantBuffer->getDescription()->getConstantDesc("gWorldMatrix").mOffsetInBytes;
	*reinterpret_cast<CFloat4*>(&buffer[offset])=getInterfaceImp()->getTransformMT().colume(0);
	*reinterpret_cast<CFloat4*>(&buffer[offset+sizeof(CFloat4)])=getInterfaceImp()->getTransformMT().colume(1);
	*reinterpret_cast<CFloat4*>(&buffer[offset+sizeof(CFloat4)*2])=getInterfaceImp()->getTransformMT().colume(2);
}
