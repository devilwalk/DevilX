#pragma once
#include "IEventWindowImp.h"
namespace NSDevilX
{
	namespace NSUISystem
	{
		class CEventManager
			:public TBaseObject<CEventManager>
		{
		protected:
			TList<IEventWindowImp*> mEventWindows;
		public:
			CEventManager();
			~CEventManager();
			Void addEventWindow(IEventWindowImp * window);
			Void removeEventWindow(IEventWindowImp * window);
			Void routeEvent(IEvent * e);
		};
	}
}