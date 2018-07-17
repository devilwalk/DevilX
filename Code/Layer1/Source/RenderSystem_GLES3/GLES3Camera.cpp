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
	const CMatrix4F inv_view_matrix=DirectX::XMMatrixInverse(nullptr,view_matrix);
	const CMatrix4F inv_projection_matrix=DirectX::XMMatrixInverse(nullptr,projection_matrix);
	const CMatrix4F view_projection_matrix=DirectX::XMMatrixMultiply(view_matrix,projection_matrix);
	const CMatrix4F inv_view_projection_matrix=DirectX::XMMatrixInverse(nullptr,view_projection_matrix);
	auto offset=mConstantBuffer->getDescription()->getConstantDesc("gViewMatrix").mOffsetInBytes;
	*reinterpret_cast<CFloat4*>(&buffer[offset])=view_matrix.colume(0);
	*reinterpret_cast<CFloat4*>(&buffer[offset+sizeof(CFloat4)])=view_matrix.colume(1);
	*reinterpret_cast<CFloat4*>(&buffer[offset+sizeof(CFloat4)*2])=view_matrix.colume(2);
	offset=mConstantBuffer->getDescription()->getConstantDesc("gInverseViewMatrix").mOffsetInBytes;
	*reinterpret_cast<CFloat4*>(&buffer[offset])=inv_view_matrix.colume(0);
	*reinterpret_cast<CFloat4*>(&buffer[offset+sizeof(CFloat4)])=inv_view_matrix.colume(1);
	*reinterpret_cast<CFloat4*>(&buffer[offset+sizeof(CFloat4)*2])=inv_view_matrix.colume(2);
	*reinterpret_cast<CFloat4*>(&buffer[offset+sizeof(CFloat4)*3])=inv_view_matrix.colume(3);
	offset=mConstantBuffer->getDescription()->getConstantDesc("gProjectionMatrix").mOffsetInBytes;
	*reinterpret_cast<CFloat4*>(&buffer[offset])=projection_matrix.colume(0);
	*reinterpret_cast<CFloat4*>(&buffer[offset+sizeof(CFloat4)])=projection_matrix.colume(1);
	*reinterpret_cast<CFloat4*>(&buffer[offset+sizeof(CFloat4)*2])=projection_matrix.colume(2);
	*reinterpret_cast<CFloat4*>(&buffer[offset+sizeof(CFloat4)*3])=projection_matrix.colume(3);
	offset=mConstantBuffer->getDescription()->getConstantDesc("gInverseProjectionMatrix").mOffsetInBytes;
	*reinterpret_cast<CFloat4*>(&buffer[offset])=inv_projection_matrix.colume(0);
	*reinterpret_cast<CFloat4*>(&buffer[offset+sizeof(CFloat4)])=inv_projection_matrix.colume(1);
	*reinterpret_cast<CFloat4*>(&buffer[offset+sizeof(CFloat4)*2])=inv_projection_matrix.colume(2);
	*reinterpret_cast<CFloat4*>(&buffer[offset+sizeof(CFloat4)*3])=inv_projection_matrix.colume(3);
	offset=mConstantBuffer->getDescription()->getConstantDesc("gViewProjectionMatrix").mOffsetInBytes;
	*reinterpret_cast<CFloat4*>(&buffer[offset])=view_projection_matrix.colume(0);
	*reinterpret_cast<CFloat4*>(&buffer[offset+sizeof(CFloat4)])=view_projection_matrix.colume(1);
	*reinterpret_cast<CFloat4*>(&buffer[offset+sizeof(CFloat4)*2])=view_projection_matrix.colume(2);
	*reinterpret_cast<CFloat4*>(&buffer[offset+sizeof(CFloat4)*3])=view_projection_matrix.colume(3);
	offset=mConstantBuffer->getDescription()->getConstantDesc("gInverseViewProjectionMatrix").mOffsetInBytes;
	*reinterpret_cast<CFloat4*>(&buffer[offset])=inv_view_projection_matrix.colume(0);
	*reinterpret_cast<CFloat4*>(&buffer[offset+sizeof(CFloat4)])=inv_view_projection_matrix.colume(1);
	*reinterpret_cast<CFloat4*>(&buffer[offset+sizeof(CFloat4)*2])=inv_view_projection_matrix.colume(2);
	*reinterpret_cast<CFloat4*>(&buffer[offset+sizeof(CFloat4)*3])=inv_view_projection_matrix.colume(3);
	offset=mConstantBuffer->getDescription()->getConstantDesc("gFarDistance").mOffsetInBytes;
	*reinterpret_cast<Float*>(&buffer[offset])=getInterfaceImp()->getFarClipPlane();
	offset=mConstantBuffer->getDescription()->getConstantDesc("gInverseFarDistance").mOffsetInBytes;
	*reinterpret_cast<Float*>(&buffer[offset])=1.0f/getInterfaceImp()->getFarClipPlane();
}
