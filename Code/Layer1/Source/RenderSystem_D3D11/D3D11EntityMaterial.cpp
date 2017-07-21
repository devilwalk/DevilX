#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;
using namespace NSD3D11;

NSDevilX::NSRenderSystem::NSD3D11::CEntityMaterial::CEntityMaterial(CSubEntityImp * subEntity)
	:CConstantBufferContainer("cbObjectMaterial")
	,mSubEntity(subEntity)
{
	SecureZeroMemory(&mTechniques[0],mTechniques.size()*sizeof(mTechniques[0]));
	_refreshTechnique();
	getSubEntity()->getInterfaceImp()->addListener(static_cast<TMessageReceiver<ISubEntityImp>*>(this),ISubEntityImp::EMessage_EndAlphaTestValueChange);
	getSubEntity()->getInterfaceImp()->addListener(static_cast<TMessageReceiver<ISubEntityImp>*>(this),ISubEntityImp::EMessage_EndColourUnitStateCreate);
	getSubEntity()->getInterfaceImp()->addListener(static_cast<TMessageReceiver<ISubEntityImp>*>(this),ISubEntityImp::EMessage_EndRenderableChange);
	getSubEntity()->getInterfaceImp()->addListener(static_cast<TMessageReceiver<ISubEntityImp>*>(this),ISubEntityImp::EMessage_EndQueriableChange);
}

NSDevilX::NSRenderSystem::NSD3D11::CEntityMaterial::~CEntityMaterial()
{
	for(auto technique:mTechniques)
		DEVILX_DELETE(technique);
}

Void NSDevilX::NSRenderSystem::NSD3D11::CEntityMaterial::onMessage(ISubEntityImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case ISubEntityImp::EMessage_EndAlphaTestValueChange:
		needUpdate();
		break;
	case ISubEntityImp::EMessage_EndColourUnitStateCreate:
		static_cast<const ISubEntityImp*>(notifier)->getColourUnitState(*static_cast<IEnum::EEntityColourUnitStateType*>(data))->addListener(static_cast<TMessageReceiver<IColourUnitStateImp>*>(this),IColourUnitStateImp::EMessage_EndValueChange);
		break;
	case ISubEntityImp::EMessage_EndRenderableChange:
	case ISubEntityImp::EMessage_EndQueriableChange:
		_refreshTechnique();
		break;
	}
}

Void NSDevilX::NSRenderSystem::NSD3D11::CEntityMaterial::_refreshTechnique()
{
	if(getSubEntity()->getInterfaceImp()->isRenderable())
	{
		if(!mTechniques[CEnum::ETechniqueType_Forward])
			mTechniques[CEnum::ETechniqueType_Forward]=DEVILX_NEW CEntityForwardTechnique(this);
	}
	else
	{
		DEVILX_DELETE(mTechniques[CEnum::ETechniqueType_Forward]);
		mTechniques[CEnum::ETechniqueType_Forward]=nullptr;
	}
	if(getSubEntity()->getInterfaceImp()->isQueriable())
	{
		if(!mTechniques[CEnum::ETechniqueType_Query])
			mTechniques[CEnum::ETechniqueType_Query]=DEVILX_NEW CEntityQueryTechnique(this);
	}
	else
	{
		DEVILX_DELETE(mTechniques[CEnum::ETechniqueType_Query]);
		mTechniques[CEnum::ETechniqueType_Query]=nullptr;
	}
}

Void NSDevilX::NSRenderSystem::NSD3D11::CEntityMaterial::onMessage(IColourUnitStateImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case IColourUnitStateImp::EMessage_EndValueChange:
		needUpdate();
		break;
	}
}

Void NSDevilX::NSRenderSystem::NSD3D11::CEntityMaterial::_updateConstantBuffer(Byte * buffer)
{
	auto offset=mConstantBuffer->getDescription()->getConstantDesc("gMainColour").StartOffset;
	if(static_cast<const ISubEntityImp*>(getSubEntity()->getInterfaceImp())->getColourUnitState(IEnum::EEntityColourUnitStateType_Diffuse))
	{
		*reinterpret_cast<CFloat3*>(&buffer[offset])=getSubEntity()->getInterfaceImp()->getColourUnitState(IEnum::EEntityColourUnitStateType_Diffuse)->getValue().rgb();
	}
	else
	{
		*reinterpret_cast<CFloat3*>(&buffer[offset])=CFloat3::sZero;
	}
	offset=mConstantBuffer->getDescription()->getConstantDesc("gAlpha").StartOffset;
	*reinterpret_cast<Float*>(&buffer[offset])=1.0f;
	offset=mConstantBuffer->getDescription()->getConstantDesc("gSpecularColour").StartOffset;
	if(static_cast<const ISubEntityImp*>(getSubEntity()->getInterfaceImp())->getColourUnitState(IEnum::EEntityColourUnitStateType_Specular))
	{
		*reinterpret_cast<CFloat3*>(&buffer[offset])=getSubEntity()->getInterfaceImp()->getColourUnitState(IEnum::EEntityColourUnitStateType_Specular)->getValue().rgb();
	}
	else
	{
		*reinterpret_cast<CFloat3*>(&buffer[offset])=CFloat3::sZero;
	}
	offset=mConstantBuffer->getDescription()->getConstantDesc("gSpecularPower").StartOffset;
	*reinterpret_cast<Float*>(&buffer[offset])=10.0f;
	offset=mConstantBuffer->getDescription()->getConstantDesc("gEmissiveColour").StartOffset;
	if(static_cast<const ISubEntityImp*>(getSubEntity()->getInterfaceImp())->getColourUnitState(IEnum::EEntityColourUnitStateType_Emissive))
	{
		*reinterpret_cast<CFloat3*>(&buffer[offset])=getSubEntity()->getInterfaceImp()->getColourUnitState(IEnum::EEntityColourUnitStateType_Emissive)->getValue().rgb();
	}
	else
	{
		*reinterpret_cast<CFloat3*>(&buffer[offset])=CFloat3::sZero;
	}
	offset=mConstantBuffer->getDescription()->getConstantDesc("gAlphaTestValue").StartOffset;
	*reinterpret_cast<Float*>(&buffer[offset])=getSubEntity()->getInterfaceImp()->getAlphaTestValue();
}
