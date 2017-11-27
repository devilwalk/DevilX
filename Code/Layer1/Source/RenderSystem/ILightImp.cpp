#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;

NSDevilX::NSRenderSystem::CLightProperty::CLightProperty(ILightImp * light)
	:mLight(light)
{
	mLight->addListener(this,ILightImp::EMessage_EndDestruction);
}

NSDevilX::NSRenderSystem::CLightProperty::~CLightProperty()
{}

void NSDevilX::NSRenderSystem::CLightProperty::onMessage(ILightImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case ILightImp::EMessage_EndDestruction:
		DEVILX_DELETE(this);
		break;
	}
}

NSDevilX::NSRenderSystem::IDirectionLightPropertyImp::IDirectionLightPropertyImp(ILightImp * light)
	:CLightProperty(light)
	,mDirection(CFloat3::sUnitZ)
{
	static_cast<ISceneElementImp*>(getLight()->queryInterface_ISceneElement())->addListener(static_cast<TMessageReceiver<ISceneElementImp>*>(this),ISceneElementImp::EMessage_OrientationChange);
}

NSDevilX::NSRenderSystem::IDirectionLightPropertyImp::~IDirectionLightPropertyImp()
{}

const CFloat3 & NSDevilX::NSRenderSystem::IDirectionLightPropertyImp::getDirectionMT()
{
	// TODO: insert return statement here
	processSingle(EDirtyFlag_Direction);
	return mDirection;
}

const CFloat3 & NSDevilX::NSRenderSystem::IDirectionLightPropertyImp::getDirection() const
{
	// TODO: insert return statement here
	assert(False==mDirtyFlag[EDirtyFlag_Direction]);
	return mDirection;
}

Void NSDevilX::NSRenderSystem::IDirectionLightPropertyImp::onMessage(ISceneElementImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case ISceneElementImp::EMessage_OrientationChange:
		addDirtyFlag(EDirtyFlag_Direction);
		break;
	}
}

Boolean NSDevilX::NSRenderSystem::IDirectionLightPropertyImp::_process(UInt32 flagIndex,OUT Bool & needNextProcess)
{
	switch(flagIndex)
	{
	case EDirtyFlag_Direction:
		mDirection=DirectX::XMVector3TransformNormal(CFloat3::sUnitZ,DirectX::XMMatrixRotationQuaternion(getLight()->queryInterface_ISceneElement()->getTransformer()->getOrientation()));
		return true;
	}
	return false;
}

NSDevilX::NSRenderSystem::IPointLightPropertyImp::IPointLightPropertyImp(ILightImp * light)
	:CLightProperty(light)
{
	addDirtyFlag(EDirtyFlag_Bound);
	static_cast<ISceneElementImp*>(getLight()->queryInterface_ISceneElement())->addListener(static_cast<TMessageReceiver<ISceneElementImp>*>(this),ISceneElementImp::EMessage_PositionChange);
	static_cast<ISceneElementImp*>(getLight()->queryInterface_ISceneElement())->addListener(static_cast<TMessageReceiver<ISceneElementImp>*>(this),ISceneElementImp::EMessage_ScaleChange);
}

NSDevilX::NSRenderSystem::IPointLightPropertyImp::~IPointLightPropertyImp()
{}

const DirectX::BoundingSphere & NSDevilX::NSRenderSystem::IPointLightPropertyImp::getBoundMT()
{
	// TODO: insert return statement here
	processSingle(EDirtyFlag_Bound);
	return mBound;
}

Float NSDevilX::NSRenderSystem::IPointLightPropertyImp::getRange() const
{
	return getLight()->queryInterface_ISceneElement()->getTransformer()->getScale().x;
}

Boolean NSDevilX::NSRenderSystem::IPointLightPropertyImp::_process(UInt32 flagIndex,OUT Bool & needNextProcess)
{
	switch(flagIndex)
	{
	case EDirtyFlag_Bound:
		mBound.Radius=getRange();
		mBound.Center=getLight()->queryInterface_ISceneElement()->getTransformer()->getPosition();
		return true;
	}
	return false;
}

Void NSDevilX::NSRenderSystem::IPointLightPropertyImp::onMessage(ISceneElementImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case ISceneElementImp::EMessage_PositionChange:
		addDirtyFlag(EDirtyFlag_Bound);
		break;
	case ISceneElementImp::EMessage_ScaleChange:
		addDirtyFlag(EDirtyFlag_Bound);
		notify(EMessage_RangeChange);
		break;
	}
}

NSDevilX::NSRenderSystem::ISpotLightPropertyImp::ISpotLightPropertyImp(ILightImp * light)
	:CLightProperty(light)
	,mDirection(CFloat3::sUnitZ)
{
	static_cast<ISceneElementImp*>(getLight()->queryInterface_ISceneElement())->addListener(static_cast<TMessageReceiver<ISceneElementImp>*>(this),ISceneElementImp::EMessage_PositionChange);
	static_cast<ISceneElementImp*>(getLight()->queryInterface_ISceneElement())->addListener(static_cast<TMessageReceiver<ISceneElementImp>*>(this),ISceneElementImp::EMessage_OrientationChange);
	static_cast<ISceneElementImp*>(getLight()->queryInterface_ISceneElement())->addListener(static_cast<TMessageReceiver<ISceneElementImp>*>(this),ISceneElementImp::EMessage_ScaleChange);
}

NSDevilX::NSRenderSystem::ISpotLightPropertyImp::~ISpotLightPropertyImp()
{}

CPlaneBoundedVolume const & NSDevilX::NSRenderSystem::ISpotLightPropertyImp::getBoundMT()
{
	// TODO: insert return statement here
	processSingle(EDirtyFlag_Bound);
	return mBound;
}

const CFloat3 & NSDevilX::NSRenderSystem::ISpotLightPropertyImp::getDirectionMT()
{
	// TODO: insert return statement here
	processSingle(EDirtyFlag_Direction);
	return mDirection;
}

const CFloat3 & NSDevilX::NSRenderSystem::ISpotLightPropertyImp::getDirection() const
{
	// TODO: insert return statement here
	return mDirection;
}

Float NSDevilX::NSRenderSystem::ISpotLightPropertyImp::getRange() const
{
	return getLight()->queryInterface_ISceneElement()->getTransformer()->getScale().x;
}

void NSDevilX::NSRenderSystem::ISpotLightPropertyImp::setAngle(const CDegree & angle)
{
	if(angle!=mAngle)
	{
		notify(EMessage_BeginAngleChange);
		mAngle=angle;
		addDirtyFlag(EDirtyFlag_Bound);
		notify(EMessage_EndAngleChange);
	}
}

const CDegree & NSDevilX::NSRenderSystem::ISpotLightPropertyImp::getAngle() const
{
	// TODO: insert return statement here
	return mAngle;
}

Boolean NSDevilX::NSRenderSystem::ISpotLightPropertyImp::_process(UInt32 flagIndex,OUT Bool & needNextProcess)
{
	switch(flagIndex)
	{
	case EDirtyFlag_Bound:
	{
		auto proj_matrix=DirectX::XMMatrixPerspectiveFovLH(getAngle().valueRadian(),1.0f,0.0000000000001f,getRange());
		DirectX::BoundingFrustum init_frustum;
		DirectX::BoundingFrustum::CreateFromMatrix(init_frustum,proj_matrix);
		init_frustum.Transform(init_frustum,static_cast<ITransformerImp*>(getLight()->queryInterface_ISceneElement()->getTransformer())->getTransformMT());
		mBound.mPlaneList.clear();
		DirectX::XMVECTOR planes[6];
		init_frustum.GetPlanes(&planes[0],&planes[1],&planes[2],&planes[3],&planes[4],&planes[5]);
		mBound.mPlaneList.resize(6);
		for(int i=0;i<6;++i)
		{
			mBound.mPlaneList[i]=planes[i]*(-1.0f);
		}
	}
	return true;
	case EDirtyFlag_Direction:
		mDirection=DirectX::XMVector3TransformNormal(CFloat3::sUnitZ,DirectX::XMMatrixRotationQuaternion(getLight()->queryInterface_ISceneElement()->getTransformer()->getOrientation()));
		return true;
	}
	return false;
}

Void NSDevilX::NSRenderSystem::ISpotLightPropertyImp::onMessage(ISceneElementImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case ISceneElementImp::EMessage_PositionChange:
		addDirtyFlag(EDirtyFlag_Bound);
		break;
	case ISceneElementImp::EMessage_OrientationChange:
		addDirtyFlag(EDirtyFlag_Bound);
		notify(EMessage_DirectionChange);
		break;
	case ISceneElementImp::EMessage_ScaleChange:
		addDirtyFlag(EDirtyFlag_Bound);
		notify(EMessage_RangeChange);
		break;
	}
}

NSDevilX::NSRenderSystem::ILightImp::ILightImp(const String & name,IEnum::ELightType type,ISceneImp * scene)
	:mType(type)
	,mSceneElement(0)
	,mDirectionLightProperty(0)
	,mShadowEnable(False)
	,mLightRenderModel(IEnum::ELightRenderModel_Basic)
	,mVisibleElementsFrameIndex(0)
{
	mSceneElement=DEVILX_NEW ISceneElementImp(name,scene,this,ISceneElementImp::EContainerObjectType_Light);
	switch(mType)
	{
	case IEnum::ELightType_Directional:
		mDirectionLightProperty=DEVILX_NEW IDirectionLightPropertyImp(this);
		break;
	case IEnum::ELightType_Point:
		mPointLightProperty=DEVILX_NEW IPointLightPropertyImp(this);
		break;
	case IEnum::ELightType_Spot:
		mSpotLightProperty=DEVILX_NEW ISpotLightPropertyImp(this);
		break;
	}
}

NSDevilX::NSRenderSystem::ILightImp::~ILightImp()
{
	if(ISystemImp::getSingleton().isExit())
	{
		DEVILX_DELETE(mSceneElement);
		switch(mType)
		{
		case IEnum::ELightType_Directional:
			DEVILX_DELETE(mDirectionLightProperty);
			break;
		case IEnum::ELightType_Point:
			DEVILX_DELETE(mPointLightProperty);
			break;
		case IEnum::ELightType_Spot:
			DEVILX_DELETE(mSpotLightProperty);
			break;
		}
	}
	else
	{
		notify(EMessage_BeginDestruction);
		DEVILX_DELETE(mSceneElement);
		switch(mType)
		{
		case IEnum::ELightType_Directional:
			DEVILX_DELETE(mDirectionLightProperty);
			break;
		case IEnum::ELightType_Point:
			DEVILX_DELETE(mPointLightProperty);
			break;
		case IEnum::ELightType_Spot:
			DEVILX_DELETE(mSpotLightProperty);
			break;
		}
		notify(EMessage_EndDestruction);
	}
}

Void NSDevilX::NSRenderSystem::ILightImp::findVisibleObjectsMT()
{
	if((IEnum::ELightType_Directional==getType())
		||(ISystemImp::getSingleton().getFrameIndex()==mVisibleElementsFrameIndex))
		return;
	auto & frame_index=mVisibleElementsFrameIndex.beginWrite();
	if(ISystemImp::getSingleton().getFrameIndex()!=frame_index)
	{
		TVector<ISceneElementImp*> temp;
		switch(getType())
		{
		case IEnum::ELightType_Point:
			static_cast<ISceneImp*>(mSceneElement->getScene())->getManager()->findVisibleObjects(mPointLightProperty->getBoundMT(),temp);
			break;
		case IEnum::ELightType_Spot:
			static_cast<ISceneImp*>(mSceneElement->getScene())->getManager()->findVisibleObjects(mSpotLightProperty->getBoundMT(),temp);
			break;
		}
		mVisibleEntities.clear();
		for(auto object:temp)
		{
			switch(object->getContainerObjectType())
			{
			case ISceneElementImp::EContainerObjectType_Entity:
				mVisibleEntities.push_back(object->getContainerObject<IEntityImp>());
				break;
			}
		}
		frame_index=ISystemImp::getSingleton().getFrameIndex();
	}
	mVisibleElementsFrameIndex.endWrite();
}

ISceneElement * NSDevilX::NSRenderSystem::ILightImp::queryInterface_ISceneElement() const
{
	return mSceneElement;
}

IDirectionLightProperty * NSDevilX::NSRenderSystem::ILightImp::queryInterface_IDirectionLightProperty() const
{
	return IEnum::ELightType_Directional==mType?mDirectionLightProperty:0;
}

IPointLightProperty * NSDevilX::NSRenderSystem::ILightImp::queryInterface_IPointLightProperty() const
{
	return IEnum::ELightType_Point==mType?mPointLightProperty:0;
}

ISpotLightProperty * NSDevilX::NSRenderSystem::ILightImp::queryInterface_ISpotLightProperty() const
{
	return IEnum::ELightType_Spot==mType?mSpotLightProperty:0;
}

IEnum::ELightType NSDevilX::NSRenderSystem::ILightImp::getType() const
{
	return mType;
}

IColourUnitState * NSDevilX::NSRenderSystem::ILightImp::getColourUnitState(IEnum::ELightColourUnitStateType type)
{
	if(static_cast<decltype(type)>(mColourUnitStates.size())<=type)
		mColourUnitStates.resize(type+1);
	if(!mColourUnitStates[type])
	{
		notify(EMessage_BeginColourUnitStateCreate);
		mColourUnitStates[type]=DEVILX_NEW IColourUnitStateImp();
		notify(EMessage_EndColourUnitStateCreate,&type);
	}
	return mColourUnitStates[type];
}

Void NSDevilX::NSRenderSystem::ILightImp::setShadowEnable(Bool enable)
{
	if(enable!=mShadowEnable)
	{
		notify(EMessage_BeginShadowEnableChange);
		mShadowEnable=enable;
		notify(EMessage_EndShadowEnableChange);
	}
}

Bool NSDevilX::NSRenderSystem::ILightImp::getShadowEnable() const
{
	return mShadowEnable;
}

Void NSDevilX::NSRenderSystem::ILightImp::setRenderModel(IEnum::ELightRenderModel model)
{
	if(model!=mLightRenderModel)
	{
		notify(EMessage_BeginLightRenderModelChange);
		mLightRenderModel=model;
		notify(EMessage_EndLightRenderModelChange);
	}
}

IEnum::ELightRenderModel NSDevilX::NSRenderSystem::ILightImp::getRenderModel() const
{
	return mLightRenderModel;
}
