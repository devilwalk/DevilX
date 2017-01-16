#pragma once
#include "ICameraImp.h"
#include "ILightImp.h"
#include "IRenderableObjectImp.h"
#include "IVisibleAreaImp.h"
#include "SceneManager.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		class ISceneImp
			:public IScene
			,public TBaseObject<ISceneImp>
			,public CMessageNotifier
		{
		public:
			enum EMessage
			{
				EMessage_BeginCameraCreate,
				EMessage_EndCameraCreate,
				EMessage_BeginCameraDestroy,
				EMessage_EndCameraDestroy,
				EMessage_BeginLightCreate,
				EMessage_EndLightCreate,
				EMessage_BeginLightDestroy,
				EMessage_EndLightDestroy,
				EMessage_BeginRenderableObjectCreate,
				EMessage_EndRenderableObjectCreate,
				EMessage_BeginRenderableObjectDestroy,
				EMessage_EndRenderableObjectDestroy,
				EMessage_BeginVisibleAreaCreate,
				EMessage_EndVisibleAreaCreate,
				EMessage_BeginVisibleAreaDestroy,
				EMessage_EndVisibleAreaDestroy,
				EMessage_BeginAmbientColourChange,
				EMessage_EndAmbientColourChange
			};
		protected:
			const String mName;
			CSceneManager * mManager;
			CColour mAmbientColour;
			TNamedResourcePtrContainer<ICameraImp> mCameras;
			TNamedResourcePtrContainer<ILightImp> mLights;
			TNamedResourcePtrContainer<IRenderableObjectImp> mRenderableObjects;
			TNamedResourcePtrContainer<IVisibleAreaImp> mVisibleAreas;
		public:
			ISceneImp(const String & name,IEnum::ESceneManagerAlgorithm algorithm);
			~ISceneImp();
			CSceneManager * getManager()const
			{
				return mManager;
			}
			decltype(mLights) const & getLights()const
			{
				return mLights;
			}
			decltype(mRenderableObjects) const & getRenderableObjects()const
			{
				return mRenderableObjects;
			}
			// Inherited via IScene
			virtual const String & getName() const override;
			virtual IEnum::ESceneManagerAlgorithm getAlgorithm() const override;
			virtual ICamera * createCamera(const String & name) override;
			virtual Void destroyCamera(ICamera * camera) override;
			virtual ICamera * getCamera(const String & name) const override;
			virtual ILight * createLight(const String & name,IEnum::ELightType type) override;
			virtual Void destroyLight(ILight * light) override;
			virtual ILight * getLight(const String & name) const override;
			virtual IRenderableObject * createRenderableObject(const String & name) override;
			virtual Void destroyRenderableObject(IRenderableObject * obj) override;
			virtual IRenderableObject * getRenderableObject(const String & name) const override;
			virtual IVisibleArea * createVisibleArea(const String & name) override;
			virtual IVisibleArea * getVisibleArea(const String & name) const override;
			virtual Void destroyVisibleArea(IVisibleArea * area) override;
			virtual Void setAmbientColour(const CColour & colour) override;
			virtual const CColour & getAmbientColour() const override;
		};
	}
}