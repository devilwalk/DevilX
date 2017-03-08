#pragma once
#include "UIManager.h"
namespace NSDevilX
{
	namespace NSFightChess
	{
		class CUIScript
			:public TBaseObject<CUIScript>
		{
		public:
			CUIScript();
			~CUIScript();
			TVector<CUIControl*> process(const String & scriptFile);
		protected:
			Void _processElement(TiXmlElement * element,TVector<CUIControl*> & ret,CUIControl * parent=nullptr);
			CAny _getAttribute(const String & name,TiXmlElement * element)const;
			Boolean _processAttribute(TiXmlAttribute * attribute,CAny & ret)const;
			Boolean _processAttribute(const String & name,const String & value,CAny & ret)const;
		};
	}
}