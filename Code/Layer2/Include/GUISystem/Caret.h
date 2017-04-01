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
			Bool mEnable;
			CTimer mTimer;
		public:
			CCaret(const String & name,CControl * parent);
			~CCaret();
			Void setEnable(Bool enable);
			// Í¨¹ý TMessageReceiver ¼Ì³Ð
			virtual Void onMessage(ISystemImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
		protected:
			Boolean _isShow()const;
			Void _show(Bool enable);
		};
	}
}