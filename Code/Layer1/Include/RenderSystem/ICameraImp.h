#pragma once
#include "ISceneElementImp.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		class ISceneManagerImp;
		class ICameraImp;
		class CProjectionProperty
			:public NSDevilX::CDirtyFlagContainerMT
		{
		public:
			enum EDirtyFlag
			{
				EDirtyFlag_Matrix
			};
		protected:
			ICameraImp * const mCamera;
			CMatrix4F mProjectionMatrix;
		public:
			CProjectionProperty(ICameraImp * cam);
			virtual ~CProjectionProperty();
			const CMatrix4F & getPrjectionMatrixMT();
		protected:
			virtual Void _recalcProjectionMatrix()=0;
			virtual Boolean _process(UInt32 flagIndex,OUT Bool & needNextProcess) override;
			virtual Void _postProcessDirtyFlagAdd(UInt32 flagIndex) override;
		};
		class IPerspectivePropertyImp
			:public IPerspectiveProperty
			,public TBaseObject<IPerspectivePropertyImp>
			,public CProjectionProperty
			,public CMessageNotifier
		{
		public:
			enum EMessage
			{
				EMessage_BeginFovChange,
				EMessage_EndFovChange,
				EMessage_BeginAspectRatioChange,
				EMessage_EndAspectRatioChange
			};
		protected:
			CDegree mFovy;
			Float mAspectRatio;
		public:
			IPerspectivePropertyImp(ICameraImp * cam);
			~IPerspectivePropertyImp();
			virtual Void setFov(const CDegree & fov) override;

			virtual const CDegree & getFov() const override;

			virtual Void setAspectRatio(Float aspect) override;

			virtual Float getAspectRatio() const override;
		protected:
			virtual Void _recalcProjectionMatrix() override;
		};
		class IOrthoPropertyImp
			:public IOrthoProperty
			,public TBaseObject<IOrthoPropertyImp>
			,public CProjectionProperty
			,public CMessageNotifier
		{
			enum EMessage
			{
				EMessage_BeginWidthChange,
				EMessage_EndWidthChange,
				EMessage_BeginHeightChange,
				EMessage_EndHeightChange
			};
		protected:
			Float mWidth,mHeight;
		public:
			IOrthoPropertyImp(ICameraImp * cam);
			~IOrthoPropertyImp();
			virtual Void setWidth(Float width) override;

			virtual Float getWidth() const override;

			virtual Void setHeight(Float height) override;

			virtual Float getHeight() const override;
		protected:
			virtual Void _recalcProjectionMatrix() override;
		};
		class IViewportImp;
		class ICameraImp
			:public ICamera
			,public TBaseObject<ICameraImp>
			,public CMessageNotifier
			,public NSDevilX::CDirtyFlagContainerMT
			,public TMessageReceiver<ISceneElementImp>
		{
		public:
			enum EMessage
			{
				EMessage_BeginDestruction,
				EMessage_EndDestruction,
				EMessage_BeginNearClipPlaneChange,
				EMessage_EndNearClipPlaneChange,
				EMessage_BeginFarClipPlaneChange,
				EMessage_EndFarClipPlaneChange,
				EMessage_BeginProjectionTypeChange,
				EMessage_EndProjectionTypeChange,
				EMessage_BeginShadowReceiveDistanceChange,
				EMessage_EndShadowReceiveDistanceChange,
				EMessage_BeginShadowReceiveFadeOutStartDistanceChange,
				EMessage_EndShadowReceiveFadeOutStartDistanceChange,
				EMessage_BeginShadowReceiveEnableChange,
				EMessage_EndShadowReceiveEnableChange,
				EMessage_BeginShadowReceiveFadeOutEnableChange,
				EMessage_EndShadowReceiveFadeOutEnableChange,
				EMessage_Count
			};
			enum EDirtyFlag
			{
				EDirtyFlag_ViewMatrix,
				EDirtyFlag_Frustum,
				EDirtyFlag_PlaneBoundedVolume
			};
		protected:
			IViewportImp * mViewport;
			ISceneElementImp * mSceneElement;
			union
			{
				IPerspectivePropertyImp * mPerspectiveProperty;
				IOrthoPropertyImp * mOrthoProperty;
			};
			IEnum::EProjectionType mProjectionType;
			Float mNearClipPlane,mFarClipPlane;
			Float mShadowReceiveDistance;
			Float mShadowReceiveFadeOutStartDistance;
			CMatrix4F mViewMatrix;
			DirectX::BoundingFrustum mFrustum;
			CPlaneBoundedVolume mPlaneBoundedVolume;
			TVector<ILightImp*> mVisibleLights;
			TVector<ICameraImp*> mVisibleCameras;
			TVector<IRenderableObjectImp*> mVisibleRenderableObjects;
			TSharedReadData<UInt32> mVisibleObjectsFrameIndex;
		public:
			ICameraImp(const String & name,ISceneImp * scene);
			~ICameraImp();
			Void setViewport(IViewportImp * viewport)
			{
				mViewport=viewport;
			}
			IViewportImp * getViewport()const
			{
				return mViewport;
			}
			const CMatrix4F & getViewMatrixMT();
			const CMatrix4F & getPrjectionMatrixMT()const;
			Void findVisibleObjectsMT();
			const decltype(mVisibleRenderableObjects) & getVisibleRenderableObjects()const
			{
				return mVisibleRenderableObjects;
			}
			const decltype(mVisibleLights) & getVisibleLights()const
			{
				return mVisibleLights;
			}
			const decltype(mVisibleCameras) & getVisibleCameras()const
			{
				return mVisibleCameras;
			}
			virtual Void setProjectionType(IEnum::EProjectionType type) override;

			virtual IEnum::EProjectionType getProjectionType() const override;

			virtual Void setNearClipPlane(Float nearClipPlane) override;

			virtual Float getNearClipPlane() const override;

			virtual Void setFarClipPlane(Float farClipPlane) override;

			virtual Float getFarClipPlane() const override;

			virtual Void setShadowReceiveDistance(Float distance) override;

			virtual Float getShadowReceiveDistance() const override;

			virtual Void setShadowReceiveFadeOutStartDistance(Float distance) override;

			virtual Float getShadowReceiveFadeOutStartDistance() const override;

			virtual Void addClipPlane(const CPlane & plane) override;

			virtual UInt16 getClipPlaneCount() const override;

			virtual Void setClipPlane(UInt16 index,const CPlane & plane) override;

			virtual const CPlane & getClipPlane(UInt16 index) const override;

			virtual Void removeAllClipPlane() override;

			virtual IPerspectiveProperty * queryInterface_IPerspectiveProperty() const override;
			virtual IOrthoProperty * queryInterface_IOrthoProperty() const override;
			virtual ISceneElement * queryInterface_ISceneElement() const override;
		protected:
			Void _createProperty();
			Void _destroyProperty();
			const DirectX::BoundingFrustum & _getFrustom();
			const CPlaneBoundedVolume & _getPlaneBoundedVolume();
			CProjectionProperty * _getProjectionProperty()const;

			// Inherited via TMessageReceiver
			virtual Void onMessage(ISceneElementImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
			virtual Boolean _process(UInt32 flagIndex,OUT Bool & needNextProcess) override;
			virtual Void _postProcessDirtyFlagAdd(UInt32 flagIndex) override;
		};
	}
}