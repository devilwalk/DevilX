#pragma once
#include "Control.h"
namespace NSDevilX
{
	namespace NSGUISystem
	{
		class ISystemImp;
		class CCaret
			:public CControl
			,public TBaseObject<CCaret>
			,public TMessageReceiver<ISystemImp>
		{
		protected:
			CTimer mTimer;
			Bool mShow;
		public:
			CCaret(const String & name,CControl * parent);
			~CCaret();

			// Í¨¹ý TMessageReceiver ¼Ì³Ð
			virtual Void onMessage(ISystemImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
		};
	}
}