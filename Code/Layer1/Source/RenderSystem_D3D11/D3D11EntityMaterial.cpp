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
	getSubEntity()->getInterfaceImp()->addListener(static_cast<TMessageReceiver<ISubEntityImp>*>(this),ISubEntityImp::EMessage_EndAlphaColourCreate);
	getSubEntity()->getInterfaceImp()->addListener(static_cast<TMessageReceiver<ISubEntityImp>*>(this),ISubEntityImp::EMessage_EndDiffuseColourCreate);
	getSubEntity()->getInterfaceImp()->addListener(static_cast<TMessageReceiver<ISubEntityImp>*>(this),ISubEntityImp::EMessage_EndSpecularColourCreate);
	getSubEntity()->getInterfaceImp()->addListener(static_cast<TMessageReceiver<ISubEntityImp>*>(this),ISubEntityImp::EMessage_EndEmissiveColourCreate);
	getSubEntity()->getInterfaceImp()->addListener(static_cast<TMessageReceiver<ISubEntityImp>*>(this),ISubEntityImp::EMessage_EndSpecularPowerValueCreate);
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
	case ISubEntityImp::EMessage_EndAlphaColourCreate:
		static_cast<const ISubEntityImp*>(notifier)->getAlphaColour()->addListener(static_cast<TMessageReceiver<IColourUnitStateImp>*>(this),IColourUnitStateImp::EMessage_EndValueChange);
		break;
	case ISubEntityImp::EMessage_EndDiffuseColourCreate:
		static_cast<const ISubEntityImp*>(notifier)->getDiffuseColour()->addListener(static_cast<TMessageReceiver<IColourUnitStateImp>*>(this),IColourUnitStateImp::EMessage_EndValueChange);
		break;
	case ISubEntityImp::EMessage_EndSpecularColourCreate:
		static_cast<const ISubEntityImp*>(notifier)->getSpecularColour()->addListener(static_cast<TMessageReceiver<IColourUnitStateImp>*>(this),IColourUnitStateImp::EMessage_EndValueChange);
		break;
	case ISubEntityImp::EMessage_EndEmissiveColourCreate:
		static_cast<const ISubEntityImp*>(notifier)->getEmissiveColour()->addListener(static_cast<TMessageReceiver<IColourUnitStateImp>*>(this),IColourUnitStateImp::EMessage_EndValueChange);
		break;
	case ISubEntityImp::EMessage_EndSpecularPowerValueCreate:
		static_cast<const ISubEntityImp*>(notifier)->getSpecularPowerValue()->addListener(static_cast<TMessageReceiver<IColourUnitStateImp>*>(this),IColourUnitStateImp::EMessage_EndValueChange);
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
	if(mSubEntity->getInterfaceImp()->getDiffuseColour())
	{
		*reinterpret_cast<CFloat3*>(&buffer[offset])=mSubEntity->getInterfaceImp()->getDiffuseColour()->getValue().rgb();
	}
	else
	{
		*reinterpret_cast<CFloat3*>(&buffer[offset])=CFloat3::sZero;
	}
	offset=mConstantBuffer->getDescription()->getConstantDesc("gAlpha").StartOffset;
	if(mSubEntity->getInterfaceImp()->getAlphaColour())
	{
		*reinterpret_cast<Float*>(&buffer[offset])=mSubEntity->getInterfaceImp()->getAlphaColour()->getValue().a();
	}
	else
	{
		*reinterpret_cast<Float*>(&buffer[offset])=1.0f;
	}
	offset=mConstantBuffer->getDescription()->getConstantDesc("gSpecularColour").StartOffset;
	if(mSubEntity->getInterfaceImp()->getSpecularColour())
	{
		*reinterpret_cast<CFloat3*>(&buffer[offset])=mSubEntity->getInterfaceImp()->getSpecularColour()->getValue().rgb();
	}
	else
	{
		*reinterpret_cast<CFloat3*>(&buffer[offset])=CFloat3::sZero;
	}
	offset=mConstantBuffer->getDescription()->getConstantDesc("gSpecularPower").StartOffset;
	if(mSubEntity->getInterfaceImp()->getSpecularPowerUnitState())
	{
		*reinterpret_cast<Float*>(&buffer[offset])=mSubEntity->getInterfaceImp()->getSpecularPowerUnitState()->getValue();
	}
	else
	{
		*reinterpret_cast<Float*>(&buffer[offset])=10.0f;
	}
	offset=mConstantBuffer->getDescription()->getConstantDesc("gEmissiveColour").StartOffset;
	if(mSubEntity->getInterfaceImp()->getEmissiveColour())
	{
		*reinterpret_cast<CFloat3*>(&buffer[offset])=mSubEntity->getInterfaceImp()->getEmissiveColour()->getValue().rgb();
	}
	else
	{
		*reinterpret_cast<CFloat3*>(&buffer[offset])=CFloat3::sZero;
	}
	offset=mConstantBuffer->getDescription()->getConstantDesc("gAlphaTestValue").StartOffset;
	*reinterpret_cast<Float*>(&buffer[offset])=getSubEntity()->getInterfaceImp()->getAlphaTestValue();
}
