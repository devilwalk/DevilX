#pragma once
#include "IPhysicalResourceManager.h"
#include "IPhysicalScene.h"
namespace NSDevilX
{
	namespace NSPhysicalSystem
	{
		class ISystem
		{
		protected:
			virtual ~ISystem(){}
		public:
			virtual IResourceManager * queryInterface_IResourceManager()const=0;
			virtual Void shutdown()=0;
			virtual Void update()=0;
			virtual IScene * createScene(const String & name)=0;
			virtual Void destroyScene(IScene * scene)=0;
			virtual IScene * getScene(const String & name)const=0;
		};
		ISystem * getSystem();
	}
}