#pragma once
#include "ICubeBlockScene.h"
namespace NSDevilX
{
	namespace NSCubeBlockSystem
	{
		class ISystem
		{
		protected:
			virtual ~ISystem(){}
		public:
			virtual Void update()=0;
			virtual IBlock * createBlock(const String & name)=0;
			virtual IBlock * getBlock(const String & name)const=0;
			virtual IScene * createScene(NSRenderSystem::IScene * renderScene=nullptr)=0;
			virtual Void destroyScene(IScene * scene)=0;
			virtual IRenderMaterial * createRenderMaterial(const String & name)=0;
			virtual IRenderMaterial * getRenderMaterial(const String & name)const=0;
			virtual Void destroyRenderMaterial(IRenderMaterial * material)=0;
		};
		ISystem * getSystem();
	}
}