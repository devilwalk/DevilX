#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;
NSDevilX::NSRenderSystem::IPerspectivePropertyImp::IPerspectivePropertyImp(ICameraImp * cam)
	:CProjectionProperty(cam)
	,mFovy(45.0f)
	,mAspectRatio(1)
{
	addDirtyFlag(CProjectionProperty::EDirtyFlag_Matrix);
}

NSDevilX::NSRenderSystem::IPerspectivePropertyImp::~IPerspectivePropertyImp()
{

}

Void NSDevilX::NSRenderSystem::IPerspectivePropertyImp::setFov(const CDegree & fov)
{
	if(fov!=getFov())
	{
		CMessageNotifier::notify(EMessage_BeginFovChange);
		mFovy=fov;
		addDirtyFlag(CProjectionProperty::EDirtyFlag_Matrix);
		CMessageNotifier::notify(EMessage_EndFovChange);
	}
}

const CDegree & NSDevilX::NSRenderSystem::IPerspectivePropertyImp::getFov() const
{
	return mFovy;
}

Void NSDevilX::NSRenderSystem::IPerspectivePropertyImp::setAspectRatio(Float aspect)
{
	if(aspect!=getAspectRatio())
	{
		CMessageNotifier::notify(EMessage_BeginAspectRatioChange);
		mAspectRatio=aspect;
		addDirtyFlag(CProjectionProperty::EDirtyFlag_Matrix);
		CMessageNotifier::notify(EMessage_EndAspectRatioChange);
	}
}

Float NSDevilX::NSRenderSystem::IPerspectivePropertyImp::getAspectRatio() const
{
	return mAspectRatio;
}

Void NSDevilX::NSRenderSystem::IPerspectivePropertyImp::_recalcProjectionMatrix()
{
	mProjectionMatrix=DirectX::XMMatrixPerspectiveFovLH(getFov().valueRadian(),getAspectRatio(),mCamera->getNearClipPlane(),mCamera->getFarClipPlane());
}

NSDevilX::NSRenderSystem::IOrthoPropertyImp::IOrthoPropertyImp(ICameraImp * cam)
	:CProjectionProperty(cam)
	,mWidth(1)
	,mHeight(1)
{
	addDirtyFlag(CProjectionProperty::EDirtyFlag_Matrix);
}

NSDevilX::NSRenderSystem::IOrthoPropertyImp::~IOrthoPropertyImp()
{

}

Void NSDevilX::NSRenderSystem::IOrthoPropertyImp::setWidth(Float width)
{
	if(width!=mWidth)
	{
		CMessageNotifier::notify(EMessage_BeginWidthChange);
		mWidth=width;
		addDirtyFlag(CProjectionProperty::EDirtyFlag_Matrix);
		CMessageNotifier::notify(EMessage_EndWidthChange);
	}
}

Float NSDevilX::NSRenderSystem::IOrthoPropertyImp::getWidth() const
{
	return mWidth;
}

Void NSDevilX::NSRenderSystem::IOrthoPropertyImp::setHeight(Float height)
{
	if(height!=mHeight)
	{
		CMessageNotifier::notify(EMessage_BeginHeightChange);
		mHeight=height;
		addDirtyFlag(CProjectionProperty::EDirtyFlag_Matrix);
		CMessageNotifier::notify(EMessage_EndHeightChange);
	}
}

Float NSDevilX::NSRenderSystem::IOrthoPropertyImp::getHeight() const
{
	return mHeight;
}

Void NSDevilX::NSRenderSystem::IOrthoPropertyImp::_recalcProjectionMatrix()
{
	mProjectionMatrix=DirectX::XMMatrixOrthographicLH(getWidth(),getHeight(),mCamera->getNearClipPlane(),mCamera->getFarClipPlane());
}

NSDevilX::NSRenderSystem::ICameraImp::ICameraImp(const String & name,ISceneImp * scene)
	:mSceneElement(0)
	,mProjectionType(IEnum::EProjectionType_Perspective)
	,mPerspectiveProperty(0)
	,mShadowReceiveDistance(0)
	,mShadowReceiveFadeOutStartDistance(0)
	,mNearClipPlane(1.0f)
	,mFarClipPlane(1000.0f)
	,mVisibleObjectsFrameIndex(0)
{
	mSceneElement=DEVILX_NEW ISceneElementImp(name,scene,this,ISceneElementImp::EContainerObjectType_Camera);
	mPerspectiveProperty=DEVILX_NEW IPerspectivePropertyImp(this);
	addDirtyFlag(EDirtyFlag_Frustum);
	addDirtyFlag(EDirtyFlag_ViewMatrix);
	addDirtyFlag(EDirtyFlag_PlaneBoundedVolume);
	mSceneElement->CMessageNotifier::addListener(static_cast<TMessageReceiver<ISceneElementImp>*>(this),ISceneElementImp::EMessage_OrientationChange);
	mSceneElement->CMessageNotifier::addListener(static_cast<TMessageReceiver<ISceneElementImp>*>(this),ISceneElementImp::EMessage_PositionChange);
}

NSDevilX::NSRenderSystem::ICameraImp::~ICameraImp()
{
	if(ISystemImp::getSingleton().isExit())
	{
		DEVILX_DELETE(mSceneElement);
		_destroyProperty();
	}
	else
	{
		CMessageNotifier::notify(EMessage_BeginDestruction);
		DEVILX_DELETE(mSceneElement);
		_destroyProperty();
		CMessageNotifier::notify(EMessage_EndDestruction);
	}
}

const CMatrix4F & NSDevilX::NSRenderSystem::ICameraImp::getViewMatrixMT()
{
	// TODO: insert return statement here
	processSingle(EDirtyFlag_ViewMatrix);
	return mViewMatrix;
}

const CMatrix4F & NSDevilX::NSRenderSystem::ICameraImp::getPrjectionMatrixMT() const
{
	// TODO: insert return statement here
	const CMatrix4F * projection_matrix=nullptr;
	switch(getProjectionType())
	{
	case IEnum::EProjectionType_Perspective:
		projection_matrix=&static_cast<IPerspectivePropertyImp*>(queryInterface_IPerspectiveProperty())->getPrjectionMatrixMT();
		break;
	case IEnum::EProjectionType_Ortho:
		projection_matrix=&static_cast<IOrthoPropertyImp*>(queryInterface_IOrthoProperty())->getPrjectionMatrixMT();
		break;
	}
	return *projection_matrix;
}

const DirectX::BoundingFrustum & NSDevilX::NSRenderSystem::ICameraImp::_getFrustom()
{
	// TODO: insert return statement here
	if(hasDirtyFlag(EDirtyFlag_Frustum))
	{
		DirectX::BoundingFrustum init_frustum;
		DirectX::BoundingFrustum::CreateFromMatrix(init_frustum,getPrjectionMatrixMT());
		init_frustum.Transform(mFrustum,static_cast<ITransformerImp*>(queryInterface_ISceneElement()->getTransformer())->getTransformMT());
		removeDirtyFlag(EDirtyFlag_Frustum);
	}
	return mFrustum;
}

const CPlaneBoundedVolume & NSDevilX::NSRenderSystem::ICameraImp::_getPlaneBoundedVolume()
{
	// TODO: insert return statement here
	if(hasDirtyFlag(EDirtyFlag_PlaneBoundedVolume))
	{
		mPlaneBoundedVolume.mPlaneList.clear();
		DirectX::XMVECTOR planes[6];
		_getFrustom().GetPlanes(&planes[0],&planes[1],&planes[2],&planes[3],&planes[4],&planes[5]);
		mPlaneBoundedVolume.mPlaneList.resize(6);
		for(int i=0;i<6;++i)
		{
			mPlaneBoundedVolume.mPlaneList[i]=planes[i]*(-1.0f);
		}
		removeDirtyFlag(EDirtyFlag_PlaneBoundedVolume);
	}
	return mPlaneBoundedVolume;
}

Void NSDevilX::NSRenderSystem::ICameraImp::findVisibleObjectsMT()
{
	if(ISystemImp::getSingleton().getFrameIndex()==mVisibleObjectsFrameIndex)
		return;
	auto & frame_index=mVisibleObjectsFrameIndex.beginWrite();
	if(ISystemImp::getSingleton().getFrameIndex()!=frame_index)
	{
		mVisibleCameras.clear();
		mVisibleLights.clear();
		mVisibleRenderableObjects.clear();
		TVector<ISceneElementImp*> temp;
		const CPlaneBoundedVolume & volume=_getPlaneBoundedVolume();
		static_cast<ISceneImp*>(mSceneElement->getScene())->getManager()->findVisibleObjects(volume,temp);
		for(auto object:temp)
		{
			switch(object->getContainerObjectType())
			{
			case ISceneElementImp::EContainerObjectType_Camera:
				mVisibleCameras.push_back(object->getContainerObject<ICameraImp>());
				break;
			case ISceneElementImp::EContainerObjectType_Light:
				mVisibleLights.push_back(object->getContainerObject<ILightImp>());
				break;
			case ISceneElementImp::EContainerObjectType_RenderableObject:
				mVisibleRenderableObjects.push_back(object->getContainerObject<IRenderableObjectImp>());
				break;
			}
		}
		frame_index=ISystemImp::getSingleton().getFrameIndex();
	}
	mVisibleObjectsFrameIndex.endWrite();
}

Void NSDevilX::NSRenderSystem::ICameraImp::setProjectionType(IEnum::EProjectionType type)
{
	if(type!=mProjectionType)
	{
		CMessageNotifier::notify(EMessage_BeginProjectionTypeChange);
		_destroyProperty();
		mProjectionType=type;
		_createProperty();
		CMessageNotifier::notify(EMessage_EndProjectionTypeChange);
	}
}

IEnum::EProjectionType NSDevilX::NSRenderSystem::ICameraImp::getProjectionType() const
{
	return mProjectionType;
}

Void NSDevilX::NSRenderSystem::ICameraImp::setNearClipPlane(Float nearClipPlane)
{
	if(nearClipPlane!=mNearClipPlane)
	{
		CMessageNotifier::notify(EMessage_BeginNearClipPlaneChange);
		mNearClipPlane=nearClipPlane;
		_getProjectionProperty()->addDirtyFlag(CProjectionProperty::EDirtyFlag_Matrix);
		CMessageNotifier::notify(EMessage_EndNearClipPlaneChange);
	}
}

Float NSDevilX::NSRenderSystem::ICameraImp::getNearClipPlane() const
{
	return mNearClipPlane;
}

Void NSDevilX::NSRenderSystem::ICameraImp::setFarClipPlane(Float farClipPlane)
{
	if(farClipPlane!=mFarClipPlane)
	{
		CMessageNotifier::notify(EMessage_BeginFarClipPlaneChange);
		mFarClipPlane=farClipPlane;
		_getProjectionProperty()->addDirtyFlag(CProjectionProperty::EDirtyFlag_Matrix);
		CMessageNotifier::notify(EMessage_EndFarClipPlaneChange);
	}
}

Float NSDevilX::NSRenderSystem::ICameraImp::getFarClipPlane() const
{
	return mFarClipPlane;
}

Void NSDevilX::NSRenderSystem::ICameraImp::setShadowReceiveDistance(Float distance)
{
	if(distance!=mShadowReceiveDistance)
	{
		CMessageNotifier::notify(EMessage_BeginShadowReceiveDistanceChange);
		const bool new_enable=distance>0;
		const bool old_enable=mShadowReceiveDistance>0;
		const bool enable_change=new_enable!=old_enable;
		if(enable_change)
			CMessageNotifier::notify(EMessage_BeginShadowReceiveEnableChange);
		const bool new_fade_enable=mShadowReceiveFadeOutStartDistance<distance;
		const bool old_fade_enable=mShadowReceiveFadeOutStartDistance<mShadowReceiveDistance;
		const bool fade_enable_change=new_fade_enable!=old_fade_enable;
		if(fade_enable_change)
			CMessageNotifier::notify(EMessage_BeginShadowReceiveFadeOutEnableChange);
		mShadowReceiveDistance=distance;
		if(fade_enable_change)
			CMessageNotifier::notify(EMessage_EndShadowReceiveFadeOutEnableChange);
		if(enable_change)
			CMessageNotifier::notify(EMessage_EndShadowReceiveEnableChange);
		CMessageNotifier::notify(EMessage_EndShadowReceiveDistanceChange);
	}
}

Float NSDevilX::NSRenderSystem::ICameraImp::getShadowReceiveDistance() const
{
	return mShadowReceiveDistance;
}

Void NSDevilX::NSRenderSystem::ICameraImp::setShadowReceiveFadeOutStartDistance(Float distance)
{
	if(distance!=mShadowReceiveFadeOutStartDistance)
	{
		CMessageNotifier::notify(EMessage_BeginShadowReceiveFadeOutStartDistanceChange);
		const bool new_enable=distance<mShadowReceiveDistance;
		const bool old_enable=mShadowReceiveFadeOutStartDistance<mShadowReceiveDistance;
		const bool enable_change=new_enable!=old_enable;
		if(enable_change)
			CMessageNotifier::notify(EMessage_BeginShadowReceiveFadeOutEnableChange);
		mShadowReceiveFadeOutStartDistance=distance;
		if(enable_change)
			CMessageNotifier::notify(EMessage_EndShadowReceiveFadeOutEnableChange);
		CMessageNotifier::notify(EMessage_EndShadowReceiveFadeOutStartDistanceChange);
	}
}

Float NSDevilX::NSRenderSystem::ICameraImp::getShadowReceiveFadeOutStartDistance() const
{
	return mShadowReceiveFadeOutStartDistance;
}

Void NSDevilX::NSRenderSystem::ICameraImp::addClipPlane(const CPlane & plane)
{
	throw std::logic_error("The method or operation is not implemented.");
}

UInt16 NSDevilX::NSRenderSystem::ICameraImp::getClipPlaneCount() const
{
	throw std::logic_error("The method or operation is not implemented.");
}

Void NSDevilX::NSRenderSystem::ICameraImp::setClipPlane(UInt16 index,const CPlane & plane)
{
	throw std::logic_error("The method or operation is not implemented.");
}

const CPlane & NSDevilX::NSRenderSystem::ICameraImp::getClipPlane(UInt16 index) const
{
	throw std::logic_error("The method or operation is not implemented.");
}

Void NSDevilX::NSRenderSystem::ICameraImp::removeAllClipPlane()
{
	throw std::logic_error("The method or operation is not implemented.");
}

IPerspectiveProperty * NSDevilX::NSRenderSystem::ICameraImp::queryInterface_IPerspectiveProperty() const
{
	IPerspectiveProperty * ret=0;
	if(IEnum::EProjectionType_Perspective==mProjectionType)
	{
		ret=mPerspectiveProperty;
	}
	return ret;
}

IOrthoProperty * NSDevilX::NSRenderSystem::ICameraImp::queryInterface_IOrthoProperty() const
{
	IOrthoProperty * ret=0;
	if(IEnum::EProjectionType_Ortho==mProjectionType)
	{
		ret=mOrthoProperty;
	}
	return ret;
}

ISceneElement * NSDevilX::NSRenderSystem::ICameraImp::queryInterface_ISceneElement() const
{
	return mSceneElement;
}

Void NSDevilX::NSRenderSystem::ICameraImp::_createProperty()
{
	switch(mProjectionType)
	{
	case NSDevilX::NSRenderSystem::IEnum::EProjectionType_Perspective:
		mPerspectiveProperty=DEVILX_NEW IPerspectivePropertyImp(this);
		break;
	case NSDevilX::NSRenderSystem::IEnum::EProjectionType_Ortho:
		mOrthoProperty=DEVILX_NEW IOrthoPropertyImp(this);
		break;
	}
}

Void NSDevilX::NSRenderSystem::ICameraImp::_destroyProperty()
{
	switch(mProjectionType)
	{
	case NSDevilX::NSRenderSystem::IEnum::EProjectionType_Perspective:
		DEVILX_DELETE(mPerspectiveProperty);
		break;
	case NSDevilX::NSRenderSystem::IEnum::EProjectionType_Ortho:
		DEVILX_DELETE(mOrthoProperty);
		break;
	}
}

CProjectionProperty * NSDevilX::NSRenderSystem::ICameraImp::_getProjectionProperty() const
{
	switch(getProjectionType())
	{
	case IEnum::EProjectionType_Perspective:
		return mPerspectiveProperty;
	case IEnum::EProjectionType_Ortho:
		return mOrthoProperty;
	default:
		return nullptr;
	}
}

Void NSDevilX::NSRenderSystem::ICameraImp::onMessage(ISceneElementImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case ISceneElementImp::EMessage_PositionChange:
	case ISceneElementImp::EMessage_OrientationChange:
		addDirtyFlag(ICameraImp::EDirtyFlag_ViewMatrix);
		addDirtyFlag(ICameraImp::EDirtyFlag_Frustum);
		break;
	}
}

Boolean NSDevilX::NSRenderSystem::ICameraImp::_process(UInt32 flagIndex,OUT Bool & needNextProcess)
{
	switch(flagIndex)
	{
	case EDirtyFlag_ViewMatrix:
	{
		DirectX::FXMMATRIX trans=DirectX::XMMatrixRotationQuaternion(queryInterface_ISceneElement()->getTransformer()->getOrientation());
		mViewMatrix=DirectX::XMMatrixLookToLH(queryInterface_ISceneElement()->getTransformer()->getPosition(),trans.r[2],trans.r[1]);
	}
	return true;
	}
	return false;
}

Void NSDevilX::NSRenderSystem::ICameraImp::_postProcessDirtyFlagAdd(UInt32 flagIndex)
{
	switch(flagIndex)
	{
	case EDirtyFlag_ViewMatrix:
		addDirtyFlag(EDirtyFlag_Frustum);
		break;
	case EDirtyFlag_Frustum:
		addDirtyFlag(EDirtyFlag_PlaneBoundedVolume);
		break;
	}
}

NSDevilX::NSRenderSystem::CProjectionProperty::CProjectionProperty(ICameraImp * cam)
	:mCamera(cam)
{
	addDirtyFlag(EDirtyFlag_Matrix);
}

NSDevilX::NSRenderSystem::CProjectionProperty::~CProjectionProperty()
{}

const CMatrix4F & NSDevilX::NSRenderSystem::CProjectionProperty::getPrjectionMatrixMT()
{
	// TODO: insert return statement here
	processSingle(EDirtyFlag_Matrix);
	return mProjectionMatrix;
}

Boolean NSDevilX::NSRenderSystem::CProjectionProperty::_process(UInt32 flagIndex,OUT Bool & needNextProcess)
{
	switch(flagIndex)
	{
	case EDirtyFlag_Matrix:
		_recalcProjectionMatrix();
		return true;
	}
	return false;
}

Void NSDevilX::NSRenderSystem::CProjectionProperty::_postProcessDirtyFlagAdd(UInt32 flagIndex)
{
	switch(flagIndex)
	{
	case EDirtyFlag_Matrix:
		mCamera->addDirtyFlag(ICameraImp::EDirtyFlag_Frustum);
		break;
	}
}