#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;
using namespace NSGLES3;

NSDevilX::NSRenderSystem::NSGLES3::CCamera::CCamera(ICameraImp * interfaceImp)
	:TInterfaceObject<ICameraImp>(interfaceImp)
	,CConstantBufferContainer("cbCamera")
{
	CSystemImp::getSingleton().addListener(static_cast<TMessageReceiver<CSystemImp>*>(this),CSystemImp::EMessage_BeginFrame);
}

NSDevilX::NSRenderSystem::NSGLES3::CCamera::~CCamera()
{}

Void NSDevilX::NSRenderSystem::NSGLES3::CCamera::onMessage(ICameraImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
}

Void NSDevilX::NSRenderSystem::NSGLES3::CCamera::onMessage(CSystemImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case CSystemImp::EMessage_BeginFrame:
		needUpdate();
		break;
	}
}

Void NSDevilX::NSRenderSystem::NSGLES3::CCamera::_updateConstantBuffer(Byte * buffer)
{
	const auto & view_matrix=getInterfaceImp()->getViewMatrixMT();
	const auto & projection_matrix=getInterfaceImp()->getPrjectionMatrixMT();
	const auto & inv_view_matrix=DirectX::XMMatrixInverse(nullptr,view_matrix);
	const auto & inv_projection_matrix=DirectX::XMMatrixInverse(nullptr,projection_matrix);
	auto offset=mConstantBuffer->getDescription()->getConstantDesc("gViewMatrix").mOffsetInBytes;
	*reinterpret_cast<CMatrix4F*>(&buffer[offset])=view_matrix;
	offset=mConstantBuffer->getDescription()->getConstantDesc("gInverseViewMatrix").mOffsetInBytes;
	*reinterpret_cast<CMatrix4F*>(&buffer[offset])=inv_view_matrix;
	offset=mConstantBuffer->getDescription()->getConstantDesc("gProjectionMatrix").mOffsetInBytes;
	*reinterpret_cast<CMatrix4F*>(&buffer[offset])=projection_matrix;
	offset=mConstantBuffer->getDescription()->getConstantDesc("gInverseProjectionMatrix").mOffsetInBytes;
	*reinterpret_cast<CMatrix4F*>(&buffer[offset])=inv_projection_matrix;
	offset=mConstantBuffer->getDescription()->getConstantDesc("gViewProjectionMatrix").mOffsetInBytes;
	*reinterpret_cast<CMatrix4F*>(&buffer[offset])=DirectX::XMMatrixMultiply(view_matrix,projection_matrix);
	offset=mConstantBuffer->getDescription()->getConstantDesc("gInverseViewProjectionMatrix").mOffsetInBytes;
	*reinterpret_cast<CMatrix4F*>(&buffer[offset])=DirectX::XMMatrixMultiply(inv_projection_matrix,inv_view_matrix);
	offset=mConstantBuffer->getDescription()->getConstantDesc("gFarDistance").mOffsetInBytes;
	*reinterpret_cast<Float*>(&buffer[offset])=getInterfaceImp()->getFarClipPlane();
	offset=mConstantBuffer->getDescription()->getConstantDesc("gInverseFarDistance").mOffsetInBytes;
	*reinterpret_cast<Float*>(&buffer[offset])=1.0f/getInterfaceImp()->getFarClipPlane();
}
