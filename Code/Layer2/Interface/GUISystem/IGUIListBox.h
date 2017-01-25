#pragma once
#include "IGUIControl.h"
namespace NSDevilX
{
	namespace NSGUISystem
	{
		class IListBox
		{
		protected:
			virtual ~IListBox(){}
		public:
			virtual IControl * queryInterface_IControl()const=0;
			virtual Void addString(const String & text)=0;
			virtual UInt32 getIndex(const String & text)const=0;
			virtual Void setString(UInt32 index,const String & text)=0;
			virtual Void removeString(const String & text)=0;
			virtual const String & getString(UInt32 index)const=0;
			virtual Void setCurrentSelect(UInt32 index)=0;
			virtual UInt32 getCurrentSelect()const=0;
			virtual Void sort()=0;
		};
	}
}