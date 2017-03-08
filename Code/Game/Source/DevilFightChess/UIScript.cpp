#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSFightChess;

NSDevilX::NSFightChess::CUIScript::CUIScript()
{
}

NSDevilX::NSFightChess::CUIScript::~CUIScript()
{}

TVector<CUIControl*> NSDevilX::NSFightChess::CUIScript::process(const String & scriptFile)
{
	TVector<CUIControl*> ret;
	TiXmlDocument doc;
	doc.LoadFile(scriptFile.c_str());
	auto element=doc.FirstChildElement();
	_processElement(element,ret);
	return ret;
}

Void NSDevilX::NSFightChess::CUIScript::_processElement(TiXmlElement * element,TVector<CUIControl*> & ret,CUIControl * parent)
{
	CUIControl * control=nullptr;
	if(String("Control")==element->Value())
	{
		auto window=CApp::getSingleton().getGame()->getUIManager()->getGraphicScene()->createWindow(_getAttribute("Name",element).get<String>());
		window->queryInterface_IElement()->setPosition(CFloat2::sZero);
		window->queryInterface_IElement()->setSize(CFloat2::sOne);
		control=CApp::getSingleton().getGame()->getUIManager()->createControl(_getAttribute("Name",element).get<String>(),_getAttribute("Position",element).get<CFloat2>(),_getAttribute("Size",element).get<CFloat2>(),parent);
		control->addGraphicWindow(window);
		ret.push_back(control);
	}
	else if(String("StaticText")==element->Value())
	{
		control=CApp::getSingleton().getGame()->getUIManager()->createStaticText(_getAttribute("Name",element).get<String>(),_getAttribute("Text",element).get<WString>(),_getAttribute("Position",element).get<CFloat2>(),_getAttribute("Size",element).get<CFloat2>(),_getAttribute("Colour",element).get<CColour>(),parent);
		ret.push_back(control);
	}
	else if(String("EditText")==element->Value())
	{
	}
	else if(String("Button")==element->Value())
	{

	}
	else
	{
		assert(0);
	}
	auto child=element->FirstChildElement();
	while(child)
	{
		_processElement(child,ret,control);
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
		ret=CAny(CStringConverter::UTF8ToWString(value));
	}
	else
	{
		assert(0);
		return false;
	}
	return true;
}
