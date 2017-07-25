#pragma once
#include "ICameraImp.h"
#include "ILightImp.h"
#include "IEntityImp.h"
#include "IVisibleAreaImp.h"
#include "ISkyImp.h"
#include "SceneManager.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		class ISceneImp
			:public IScene
			,public TBaseObject<ISceneImp>
			,public CMessageNotifier
			,public CReferenceObject
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
				EMessage_BeginEntityCreate,
				EMessage_EndEntityCreate,
				EMessage_BeginEntityDestroy,
				EMessage_EndEntityDestroy,
				EMessage_BeginVisibleAreaCreate,
				EMessage_EndVisibleAreaCreate,
				EMessage_BeginVisibleAreaDestroy,
				EMessage_EndVisibleAreaDestroy,
				EMessage_BeginSkyCreate,
				EMessage_EndSkyCreate,
				EMessage_BeginSkyDestroy,
				EMessage_EndSkyDestroy,
				EMessage_BeginAmbientColourChange,
				EMessage_EndAmbientColourChange
			};
		protected:
			const String mName;
			CSceneManager * mManager;
			CFloatRGBA mAmbientColour;
			TNamedRefResourcePtrMap<ICameraImp> mCameras;
			TNamedRefResourcePtrMap<ILightImp> mLights;
			TNamedRefResourcePtrMap<IEntityImp> mEntities;
			TNamedResourcePtrMap<IVisibleAreaImp> mVisibleAreas;
			TNamedRefResourcePtrMap<ISkyImp> mSkys;
		public:
			ISceneImp(const String & name,IEnum::ESceneManagerAlgorithm algorithm);
			CSceneManager * getManager()const
			{
				return mManager;
			}
			decltype(mLights) const & getLights()const
			{
				return mLights;
			}
			decltype(mEntities) const & getEntities()const
			{
				return mEntities;
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
			virtual IEntity * createEntity(const String & name) override;
			virtual Void destroyEntity(IEntity * obj) override;
			virtual IEntity * getEntity(const String & name) const override;
			virtual IVisibleArea * createVisibleArea(const String & name) override;
			virtual IVisibleArea * getVisibleArea(const String & name) const override;
			virtual Void destroyVisibleArea(IVisibleArea * area) override;
			virtual ISky * createSky(const String & name) override;
			virtual ISky * getSky(const String & name) const override;
			virtual Void destroySky(ISky * sky) override;
			virtual Void setAmbientColour(const CColour & colour) override;
			virtual const CColour & getAmbientColour() const override;
		protected:
			~ISceneImp();
		};
	}
}