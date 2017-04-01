#pragma once
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
			Boolean process
			(const String & scriptFile,NSGUISystem::IWindow * guiWindow
				,NSGUISystem::IButtonEventCallback * buttonEventCallback=nullptr
				,NSGUISystem::IEditBoxEventCallback * editBoxEventCallback=nullptr
			);
		protected:
			Void _processElement
			(TiXmlElement * element
				,NSGUISystem::IWindow * guiWindow
				,NSGUISystem::IButtonEventCallback * buttonEventCallback=nullptr
				,NSGUISystem::IEditBoxEventCallback * editBoxEventCallback=nullptr
				,NSGUISystem::IControl * parent=nullptr
			);
			CAny _getAttribute(const String & name,TiXmlElement * element)const;
			Boolean _processAttribute(TiXmlAttribute * attribute,CAny & ret)const;
			Boolean _processAttribute(const String & name,const String & value,CAny & ret)const;
		};
	}
}