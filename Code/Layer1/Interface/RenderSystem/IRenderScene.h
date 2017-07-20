#pragma once
#include "IRenderEnum.h"
#include "IRenderCamera.h"
#include "IRenderLight.h"
#include "IRenderEntity.h"
#include "IRenderVisibleArea.h"
#include "IRenderSky.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		class IScene
		{
		protected:
			virtual ~IScene(){ }
		public:
			virtual const String & getName()const=0;
			virtual IEnum::ESceneManagerAlgorithm getAlgorithm()const=0;
			virtual IVisibleArea * createVisibleArea(const String & name)=0;
			virtual IVisibleArea * getVisibleArea(const String & name)const=0;
			virtual Void destroyVisibleArea(IVisibleArea * area)=0;
			virtual ICamera * createCamera(const String & name)=0;
			virtual Void destroyCamera(ICamera * camera)=0;
			virtual ICamera * getCamera(const String & name)const=0;
			virtual ILight * createLight(const String & name,IEnum::ELightType type)=0;
			virtual Void destroyLight(ILight * light)=0;
			virtual ILight * getLight(const String & name)const=0;
			virtual IEntity * createEntity(const String & name)=0;
			virtual Void destroyEntity(IEntity * obj)=0;
			virtual IEntity * getEntity(const String & name)const=0;
			virtual ISky * createSky(const String & name)=0;
			virtual Void destroySky(ISky * sky)=0;
			virtual ISky * getSky(const String & name)const=0;
			virtual Void setAmbientColour(const CColour & colour)=0;
			virtual const CColour & getAmbientColour()const=0;
		};
	}
}