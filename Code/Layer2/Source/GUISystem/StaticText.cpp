#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSGUISystem;

NSDevilX::NSGUISystem::CStaticText::CStaticText(const String & name,CControl * parent)
	:CControl(name,parent)
	,mFontResource(nullptr)
{
}

NSDevilX::NSGUISystem::CStaticText::~CStaticText()
{
}

Void NSDevilX::NSGUISystem::CStaticText::setFontResource(NSResourceSystem::IResource * resource)
{
	if(getFontResource()!=resource)
	{
		mFontResource=resource;
		addDirtyFlag(EDirtyFlag_FontResource);
	}
}

NSResourceSystem::IResource * NSDevilX::NSGUISystem::CStaticText::getFontResource() const
{
	return mFontResource;
}

Void NSDevilX::NSGUISystem::CStaticText::setText(const CUTF8String & text)
{
	if(getText()!=text)
	{
		mText=text;
		addDirtyFlag(EDirtyFlag_Text);
	}
}

const CUTF8String & NSDevilX::NSGUISystem::CStaticText::getText() const
{
	// TODO: 在此处插入 return 语句
	return mText;
}

Void NSDevilX::NSGUISystem::CStaticText::setTextColour(const CColour & colour)
{
	if(getTextColour()!=colour)
	{
		mTextColour=colour;
		addDirtyFlag(EDirtyFlag_TextColour);
	}
}

const CColour & NSDevilX::NSGUISystem::CStaticText::getTextColour() const
{
	// TODO: 在此处插入 return 语句
	return mTextColour;
}

Boolean NSDevilX::NSGUISystem::CStaticText::getPosition(UInt32 charIndex,CFloat2 * position) const
{
	if((getText().size()<charIndex)
		||hasDirtyFlag(EDirtyFlag_Text))
		return false;
	else
	{
		if(position)
		{
			TVector<CFloat2> positions;
			Float last_char_right;
			_calculateTextParameters(&positions,&last_char_right);
			if(getText().size()==charIndex)
				*position=CFloat2(last_char_right,0.0f);
			else
				*position=positions[charIndex];
		}
		return true;
	}
}

Boolean NSDevilX::NSGUISystem::CStaticText::getPositions(TVector<CFloat2>* positions,Float * lastCharRight) const
{
	if(hasDirtyFlag(EDirtyFlag_Text))
		return false;
	_calculateTextParameters(positions,lastCharRight);
	return true;
}

Boolean NSDevilX::NSGUISystem::CStaticText::_updateGraphicWindows()
{
	_destroyGraphicWindows();
	if(!getFontResource())
		return false;
	getFontResource()->load(nullptr);
	if(!getFontResource()->isLoaded())
		return false;
	TVector<CFloat2> positions;
	auto loaded_resource=_calculateTextParameters(&positions);
	const auto word_width=1.0f/getText().size();
	for(size_t i=0;i<getText().size();++i)
	{
		auto char_info=NSResourceSystem::getSystem()->getChar(loaded_resource,getText()[i]);
		auto tex=NSResourceSystem::getSystem()->getRenderTexture(loaded_resource,getText()[i]);
		auto window=getGraphicScene()->createWindow(getLayer()->getName()+"/"+CStringConverter::toString(i));
		window->setColour(mTextColour);
		window->setTexture(tex,char_info.mPixelStart,char_info.mPixelEnd);
		window->queryInterface_IElement()->setPosition(positions[i]);
		window->queryInterface_IElement()->setSize(CFloat2(word_width,1.0f));
		_attachWindow(window);
	}
//#ifdef DEVILX_DEBUG
//	auto debug_window=getGraphicScene()->createWindow(getLayer()->getName()+"/debug");
//	debug_window->setColour(CFloatRGBA::sRed);
//	debug_window->queryInterface_IElement()->setPosition(CFloat2::sZero);
//	debug_window->queryInterface_IElement()->setSize(CFloat2::sOne);
//	_attachWindow(debug_window);
//#endif
	return true;
}

NSResourceSystem::ILoadedResource * NSDevilX::NSGUISystem::CStaticText::_calculateTextParameters(TVector<CFloat2> * positions,Float * lastCharRight)const
{
	struct SLoad
		:public NSResourceSystem::ILoadCallback
		,public TBaseObject<SLoad>
	{
		NSResourceSystem::ILoadedResource * mLoadedResource;
		virtual Void onLoaded(NSResourceSystem::ILoadedResource * resource) override
		{
			mLoadedResource=resource;
		}
	};
	SLoad load_call_back;
	getFontResource()->load(&load_call_back);
	if(positions||lastCharRight)
	{
		const auto & text=getText();
		Float base_line_in_pixel=0;
		for(size_t i=0;i<text.size();++i)
		{
			auto char_info=NSResourceSystem::getSystem()->getChar(load_call_back.mLoadedResource,text[i]);
			base_line_in_pixel=std::max<Float>(base_line_in_pixel,static_cast<Float>(char_info.mGlyphMetrics.height-char_info.mGlyphMetrics.horiBearingY)/char_info.mImage->getFontFace()->getFontPixelSize().y);
		}
		Float x_offset=0;
		for(size_t i=0;i<text.size();++i)
		{
			auto char_info=NSResourceSystem::getSystem()->getChar(load_call_back.mLoadedResource,text[i]);
			if(positions)
			{
				auto x=x_offset+static_cast<Float>(char_info.mGlyphMetrics.horiBearingX)/char_info.mImage->getFontFace()->getFontPixelSize().x/text.size();
				positions->push_back(CFloat2(x,-base_line_in_pixel+static_cast<Float>(char_info.mGlyphMetrics.height-char_info.mGlyphMetrics.horiBearingY)/char_info.mImage->getFontFace()->getFontPixelSize().y));
			}
			x_offset+=static_cast<Float>(char_info.mGlyphMetrics.horiAdvance)/char_info.mImage->getFontFace()->getFontPixelSize().x/text.size();
		}
		if(lastCharRight)
			*lastCharRight=x_offset;
	}
	return load_call_back.mLoadedResource;
}

Void NSDevilX::NSGUISystem::CStaticText::_preProcessDirtyFlagAdd(UInt32 flagIndex)
{
	if(!getDirtyFlag())
	{
		ISystemImp::getSingleton().addListener(this,ISystemImp::EMessage_Update);
	}
}

Void NSDevilX::NSGUISystem::CStaticText::_postProcessDirtyFlagRemove(UInt32 flagIndex)
{
	if(!getDirtyFlag())
	{
		ISystemImp::getSingleton().removeListener(this,ISystemImp::EMessage_Update);
	}
}

Void NSDevilX::NSGUISystem::CStaticText::onMessage(ISystemImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case ISystemImp::EMessage_Update:
		if(hasDirtyFlag(EDirtyFlag_FontResource)
			||hasDirtyFlag(EDirtyFlag_Text)
			)
		{
			if(_updateGraphicWindows())
			{
				removeDirtyFlag(EDirtyFlag_FontResource);
				removeDirtyFlag(EDirtyFlag_Text);
				removeDirtyFlag(EDirtyFlag_TextColour);
			}
		}
		else if(hasDirtyFlag(EDirtyFlag_TextColour))
		{
			for(auto window:mGraphicWindows)
				window->setColour(getTextColour());
			removeDirtyFlag(EDirtyFlag_TextColour);
		}
		break;
	}
}
