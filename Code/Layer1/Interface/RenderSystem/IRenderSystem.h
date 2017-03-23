#include "IRenderEnum.h"
#include "IRenderResourceManager.h"
#include "IRenderWindow.h"
#include "IRenderableSurface.h"
#include "IRenderScene.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		class ISystem
		{
		protected:
			virtual ~ISystem(){ }
		public:
			virtual Void shutdown()=0;
			virtual IResourceManager * queryInterface_IResourceManager()const=0;
			virtual Void update()=0;
			virtual IWindow * createWindow(CWindow * window)=0;
			virtual Void destroyWindow(IWindow * window)=0;
			virtual IWindow * getWindow(CWindow * window)const=0;
			virtual IRenderableSurface * createRenderableSurface(const String & name)=0;
			virtual Void destroyRenderableSurface(IRenderableSurface * surface)=0;
			virtual IRenderableSurface * getRenderableSurface(const String & name)const=0;
			virtual IScene * createScene(const String & name,IEnum::ESceneManagerAlgorithm algorithm)=0;
			virtual Void destroyScene(IScene * scene)=0;
			virtual IScene * getScene(const String & name)const=0;
		};
		ISystem * getSystem();
	}
}