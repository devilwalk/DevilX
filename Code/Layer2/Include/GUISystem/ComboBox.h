#pragma once
#include "EditBox.h"
#include "DropList.h"
namespace NSDevilX
{
	namespace NSGUISystem
	{
		class ISystemImp;
		class CComboBox
			:public CControl
			,public TBaseObject<CComboBox>
			,public CDefaultWindowEventListener
			,public CMessageNotifier
			,public TMessageReceiver<ISystemImp>
		{
		public:
			enum EMessage
			{
				EMessage_SetFocus,
				EMessage_BeginTextChange,
				EMessage_EndTextChange
			};
		protected:
			CEditBox * mEditBox;
			CDropList * mDropList;
		public:
			CComboBox(const String & name,CControl * coordParent,CControl * orderParent);
			~CComboBox();
			CEditBox * getEditControl()const
			{
				return mEditBox;
			}
			CDropList * getDropList()const
			{
				return mDropList;
			}
		};
	}
}