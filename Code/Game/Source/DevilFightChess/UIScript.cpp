#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSFightChess;

NSDevilX::NSFightChess::CUIScript::CUIScript()
{
}

NSDevilX::NSFightChess::CUIScript::~CUIScript()
{}

Boolean NSDevilX::NSFightChess::CUIScript::process(const String & scriptFile,NSGUISystem::IWindow * guiWindow)
{
	TiXmlDocument doc;
	doc.LoadFile(scriptFile.c_str());
	auto element=doc.FirstChildElement();
	_processElement(element,guiWindow);
	return true;
}

Void NSDevilX::NSFightChess::CUIScript::_processElement(TiXmlElement * element,NSGUISystem::IWindow * guiWindow,NSGUISystem::IControl * parent)
{
	NSGUISystem::IControl * control=parent;
	if(String("Window")==element->Value())
	{
		guiWindow->queryInterface_IControl()->setPosition(_getAttribute("Position",element).get<CFloat2>());
		guiWindow->queryInterface_IControl()->setSize(_getAttribute("Size",element).get<CFloat2>());
	}
	else if(String("ImageBox")==element->Value())
	{
		auto ctl=guiWindow->createImageBox(_getAttribute("Name",element).get<String>());
		if(element->Attribute("Background"))
			ctl->setBackground(NSResourceSystem::getSystem()->createResource(_getAttribute("Background",element).get<String>(),_getAttribute("Background",element).get<String>()));
		ctl->queryInterface_IControl()->setPosition(_getAttribute("Position",element).get<CFloat2>());
		ctl->queryInterface_IControl()->setSize(_getAttribute("Size",element).get<CFloat2>());
		control=ctl->queryInterface_IControl();
	}
	else if(String("StaticText")==element->Value())
	{
		auto ctl=guiWindow->createStaticText(_getAttribute("Name",element).get<String>());
		ctl->getTextProperty()->setFontResource(CApp::getSingleton().getGame()->getFontManager()->getFontResource());
		ctl->setText(_getAttribute("Text",element).get<CUTF8String>());
		ctl->getTextProperty()->setColour(_getAttribute("Colour",element).get<CColour>());
		ctl->queryInterface_IControl()->setPosition(_getAttribute("Position",element).get<CFloat2>());
		ctl->queryInterface_IControl()->setSize(_getAttribute("Size",element).get<CFloat2>());
		control=ctl->queryInterface_IControl();
	}
	else if(String("EditBox")==element->Value())
	{
		auto ctl=guiWindow->createEditBox(_getAttribute("Name",element).get<String>());
		ctl->getTextProperty()->setFontResource(CApp::getSingleton().getGame()->getFontManager()->getFontResource());
		if(element->Attribute("Text"))
			ctl->setText(_getAttribute("Text",element).get<CUTF8String>());
		ctl->getTextProperty()->setColour(_getAttribute("Colour",element).get<CColour>());
		if(element->Attribute("Background"))
			ctl->setBackground(NSResourceSystem::getSystem()->createResource(_getAttribute("Background",element).get<String>(),_getAttribute("Background",element).get<String>()));
		ctl->queryInterface_IControl()->setPosition(_getAttribute("Position",element).get<CFloat2>());
		ctl->queryInterface_IControl()->setSize(_getAttribute("Size",element).get<CFloat2>());
		control=ctl->queryInterface_IControl();
	}
	else if(String("Button")==element->Value())
	{
		auto ctl=guiWindow->createButton(_getAttribute("Name",element).get<String>());
		ctl->getTextProperty()->setFontResource(CApp::getSingleton().getGame()->getFontManager()->getFontResource());
		if(element->Attribute("Text"))
			ctl->setText(_getAttribute("Text",element).get<CUTF8String>());
		if(element->Attribute("Colour"))
			ctl->getTextProperty()->setColour(_getAttribute("Colour",element).get<CColour>());
		if(element->Attribute("Background"))
			ctl->setBackground(NSResourceSystem::getSystem()->createResource(_getAttribute("Background",element).get<String>(),_getAttribute("Background",element).get<String>()));
		ctl->queryInterface_IControl()->setPosition(_getAttribute("Position",element).get<CFloat2>());
		ctl->queryInterface_IControl()->setSize(_getAttribute("Size",element).get<CFloat2>());
		control=ctl->queryInterface_IControl();
	}
	else
	{
		assert(0);
	}
	if(parent)
		control->setParent(parent);
	auto child=element->FirstChildElement();
	while(child)
	{
		_processElement(child,guiWindow,control);
		child=child->NextSiblingElement();
	}
}

CAny NSDevilX::NSFightChess::CUIScript::_getAttribute(const String & name,TiXmlElement * element) const
{
	if(element->Attribute(name.c_str()))
	{
		CAny ret;
		_processAttribute(name,element->Attribute(name.c_str()),ret);
		return ret;
	}
	else
	{
		if(name==String("Name"))
		{
			return CAny(String("Unname"));
		}
		else if((name==String("Position"))
			||(name==String("Size")))
		{
			return CAny(CFloat2::sZero);
		}
		else if(name==String("Order"))
		{
			return CAny(0);
		}
		else if(name==String("Colour"))
		{
			return CFloatRGBA::sWhite;
		}
		else
		{
			assert(0);
		}
	}
	return CAny();
}

Boolean NSDevilX::NSFightChess::CUIScript::_processAttribute(TiXmlAttribute * attribute,CAny & ret) const
{
	return _processAttribute(attribute->Name(),attribute->Value(),ret);
}

Boolean NSDevilX::NSFightChess::CUIScript::_processAttribute(const String & name,const String & value,CAny & ret) const
{
	if(name==String("Name"))
	{
		ret=CAny(value);
	}
	else if((name==String("Position"))
		||(name==String("Size")))
	{
		ret=CAny(CStringConverter::toFloat2(value));
	}
	else if(name==String("Order"))
	{
		ret=CAny(CStringConverter::toValue<Int32>(value));
	}
	else if(name==String("Colour"))
	{
		ret=CAny(CFloatRGBA(CStringConverter::toFloat4(value)));
	}
	else if(name==String("Text"))
	{
		ret=CAny(CUTF8String(reinterpret_cast<ConstBytePtr>(&value[0]),value.size()));
	}
	else
	{
		assert(0);
		return false;
	}
	return true;
}
