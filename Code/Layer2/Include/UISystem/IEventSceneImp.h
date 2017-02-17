#pragma once
#include "IEventWindowImp.h"
#include "EventManager.h"
namespace NSDevilX
{
	namespace NSUISystem
	{
		class IEventSceneImp
			:public IEventScene
			,public TBaseObject<IEventSceneImp>
		{
		protected:
			const String mName;
			CEventManager * mManager;
			TNamedResourcePtrMap<IEventWindowImp> mWindows;
		public:
			IEventSceneImp(const String & name);
			~IEventSceneImp();

			// Í¨¹ý IEventScene ¼Ì³Ð
			virtual const String & getName() const override;
			virtual IEventWindow * createWindow(const String & name) override;
			virtual IEventWindow * getWindow(const String & name) const override;
			virtual Void destroyWindow(IEventWindow * window) override;
			virtual Void route(IEvent * eve) override;
		};
	}
}