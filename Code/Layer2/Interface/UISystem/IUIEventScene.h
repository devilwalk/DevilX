#pragma once
#include "IUIEvent.h"
#include "IUIEventWindow.h"
namespace NSDevilX
{
	namespace NSUISystem
	{
		class IEventScene
		{
		protected:
			virtual ~IEventScene(){}
		public:
			virtual const String & getName()const=0;
			virtual IEventWindow * createWindow(const String & name)=0;
			virtual IEventWindow * getWindow(const String & name)const=0;
			virtual Void destroyWindow(IEventWindow * window)=0;
			virtual Void route(IEvent * eve)=0;
		};
	}
}