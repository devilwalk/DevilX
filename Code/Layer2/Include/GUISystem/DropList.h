#pragma once
#include "CommonControl.h"
namespace NSDevilX
{
	namespace NSGUISystem
	{
		class CDropList
			:public CControl
			,public TBaseObject<CDropList>
			,public CDefaultWindowEventListener
			,public CMessageNotifier
			,public TMessageReceiver<ISystemImp>
		{
		protected:
			TVector<CCommonControl*> mControls;
		public:
			CDropList(const String & name,CControl * coordParent,CControl * orderParent);
			~CDropList();
			Void setSize(UInt32 size);
			UInt32 getSize()const
			{
				return static_cast<UInt32>(mControls.size());
			}
		};
	}
}