#pragma once
#include "PageBarItem.h"
namespace NSDevilX
{
	namespace NSGUISystem
	{
		class CPageBar
			:public CControl
			,public TBaseObject<CPageBar>
			,public CMessageNotifier
		{
		protected:
			NSResourceSystem::IResource * mFontResource;
			TResourcePtrList<CPageBarItem> mItems;
			UInt32 mNextItemName;
			CPageBarItem * mFocus;
		public:
			CPageBar(const String & name,CControl * parent);
			~CPageBar();
			Void setFontResource(NSResourceSystem::IResource * resource);
			NSResourceSystem::IResource * getFontResource() const;
			Void setFocus(CPageBarItem * item);
			Void addItem(const CUTF8String & text);
			const CUTF8String & getItem(UInt32 index)const;
			Void removeItem(UInt32 index);
		protected:
			Void _updateItems();
		};
	}
}