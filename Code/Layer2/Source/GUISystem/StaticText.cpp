#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSGUISystem;

NSDevilX::NSGUISystem::CStaticText::CStaticText(const String & name,CControl * coordParent)
	:CControl(name,coordParent,False)
	,mTextProperty(nullptr)
{
	mTextProperty=DEVILX_NEW CTextProperty;
	getTextProperty()->addListener(static_cast<TMessageReceiver<CTextProperty>*>(this),CTextProperty::EMessage_AddDirtyFlag);
}

NSDevilX::NSGUISystem::CStaticText::~CStaticText()
{
	DEVILX_DELETE(getTextProperty());
}

Void NSDevilX::NSGUISystem::CStaticText::setText(const CUTF8String & text)
{
	if(getText()!=text)
	{
		mText=text;
		if(!getText().empty())
			getTextProperty()->setFontSize(CFloat2(1.0f/getText().size(),1.0f));
		addDirtyFlag(EDirtyFlag_Text);
	}
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
			auto loaded_resource=_calculateTextParameters(&positions,&last_char_right);
			if(nullptr==loaded_resource)
				return false;
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
	auto loaded_resource=_calculateTextParameters(positions,lastCharRight);
	if(nullptr==loaded_resource)
		return false;
	return true;
}

Boolean NSDevilX::NSGUISystem::CStaticText::_updateGraphicWindows()
{
	_destroyGraphicWindows();
	TVector<CFloat2> positions;
	auto loaded_resource=_calculateTextParameters(&positions);
	if(nullptr==loaded_resource)
		return false;
	for(size_t i=0;i<getText().size();++i)
	{
		auto char_info=NSResourceSystem::getSystem()->getChar(loaded_resource,getText()[i]);
		auto tex=NSResourceSystem::getSystem()->getRenderTexture(loaded_resource,getText()[i]);
		auto window=getGraphicScene()->createWindow(getLayer()->getName()+"/"+CStringConverter::toString(i));
		window->setColour(getTextProperty()->getColour());
		window->setTexture(tex,char_info.mPixelStart,char_info.mPixelEnd);
		window->queryInterface_IElement()->setPosition(positions[i]);
		window->queryInterface_IElement()->setSize(getTextProperty()->getFontSize());
		_attachWindow(window);
	}
	return true;
}

NSResourceSystem::ILoadedResource * NSDevilX::NSGUISystem::CStaticText::_calculateTextParameters(TVector<CFloat2> * positions,Float * lastCharRight)const
{
	if(!getTextProperty()->getFontResource())
		return nullptr;
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
	getTextProperty()->getFontResource()->load(&load_call_back,True);
	if(positions||lastCharRight)
	{
		const auto & text=getText();
		const UInt32 max_row_count=static_cast<UInt32>(1.0f/getTextProperty()->getFontSize().y);
		TVector<TVector<UInt32> > text_indices;
		TVector<Float> row_widths;
		TVector<UInt32> row_indices;
		Float row_width=0;
		for(size_t i=0;i<text.size();++i)
		{
			const auto char_info=NSResourceSystem::getSystem()->getChar(load_call_back.mLoadedResource,text[i]);
			const Float char_width=getTextProperty()->getFontSize().x*static_cast<Float>(char_info.mGlyphMetrics.horiAdvance)/char_info.mImage->getFontFace()->getFontPixelSize().x;
			const Float new_row_width=row_width+char_width;
			if(new_row_width>1.0f)
			{
				row_widths.push_back(row_width);
				text_indices.push_back(row_indices);
				row_indices.clear();
				row_indices.push_back(static_cast<UInt32>(i));
				row_width=char_width;
			}
			else
			{
				row_indices.push_back(static_cast<UInt32>(i));
				row_width=new_row_width;
			}
		}
		if(!row_indices.empty())
		{
			row_widths.push_back(row_width);
			text_indices.push_back(row_indices);
		}
		text_indices.resize(std::min<SizeT>(text_indices.size(),max_row_count));
		CFloat2 offset=CFloat2::sZero;
		for(size_t row=0;row<text_indices.size();++row)
		{
			const auto & indices=text_indices[row];
			switch(getTextProperty()->getRowAlignMode())
			{
			case IEnum::ETextRowAlignMode_Center:
				offset.x=(1.0f-row_widths[row])*0.5f;
				break;
			case IEnum::ETextRowAlignMode_Left:
				offset.x=0.0f;
				break;
			case IEnum::ETextRowAlignMode_Right:
			{
				auto char_info=NSResourceSystem::getSystem()->getChar(load_call_back.mLoadedResource,text[indices[0]]);
				offset.x=1.0f-static_cast<Float>(char_info.mGlyphMetrics.horiAdvance)/char_info.mImage->getFontFace()->getFontPixelSize().x/indices.size();
			}
			break;
			}
			switch(getTextProperty()->getColumeAlignMode())
			{
			case IEnum::ETextColumeAlignMode_Bottom:
				offset.y=1.0f-(text_indices.size()-row)*getTextProperty()->getFontSize().y;
				break;
			case IEnum::ETextColumeAlignMode_Center:
				offset.y=(1.0f-text_indices.size()*getTextProperty()->getFontSize().y)*0.5f;
				break;
			case IEnum::ETextColumeAlignMode_Top:
				offset.y=row*getTextProperty()->getFontSize().y;
				break;
			}
			Float base_line_in_pixel=0;
			for(auto index:indices)
			{
				auto char_info=NSResourceSystem::getSystem()->getChar(load_call_back.mLoadedResource,text[index]);
				base_line_in_pixel=std::max<Float>(base_line_in_pixel,static_cast<Float>(char_info.mGlyphMetrics.height-char_info.mGlyphMetrics.horiBearingY)/char_info.mImage->getFontFace()->getFontPixelSize().y);
			}
			base_line_in_pixel+=offset.y;
			for(auto index:indices)
			{
				auto char_info=NSResourceSystem::getSystem()->getChar(load_call_back.mLoadedResource,text[index]);
				if(positions)
				{
					auto x=offset.x+static_cast<Float>(char_info.mGlyphMetrics.horiBearingX)/char_info.mImage->getFontFace()->getFontPixelSize().x*getTextProperty()->getFontSize().x;
					positions->push_back(CFloat2(x,-base_line_in_pixel+static_cast<Float>(char_info.mGlyphMetrics.height-char_info.mGlyphMetrics.horiBearingY)/char_info.mImage->getFontFace()->getFontPixelSize().y));
				}
				offset.x+=static_cast<Float>(char_info.mGlyphMetrics.horiAdvance)/char_info.mImage->getFontFace()->getFontPixelSize().x*getTextProperty()->getFontSize().x;
			}
		}
		if(lastCharRight)
			*lastCharRight=offset.x;
	}
	return load_call_back.mLoadedResource;
}

Void NSDevilX::NSGUISystem::CStaticText::_preProcessDirtyFlagAdd(UInt32 flagIndex)
{
	if(!getDirtyFlag())
	{
		ISystemImp::getSingleton().addListener(static_cast<TMessageReceiver<ISystemImp>*>(this),ISystemImp::EMessage_Update);
	}
}

Void NSDevilX::NSGUISystem::CStaticText::_postProcessDirtyFlagRemove(UInt32 flagIndex)
{
	if(!getDirtyFlag())
	{
		ISystemImp::getSingleton().removeListener(static_cast<TMessageReceiver<ISystemImp>*>(this),ISystemImp::EMessage_Update);
	}
}

Void NSDevilX::NSGUISystem::CStaticText::onMessage(ISystemImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case ISystemImp::EMessage_Update:
		if(getTextProperty()->hasDirtyFlag(CTextProperty::EDirtyFlag_Font)
			||hasDirtyFlag(EDirtyFlag_Text)
			)
		{
			if(_updateGraphicWindows())
			{
				removeDirtyFlag(EDirtyFlag_Text);
				getTextProperty()->removeDirtyFlag(CTextProperty::EDirtyFlag_Font);
				getTextProperty()->removeDirtyFlag(CTextProperty::EDirtyFlag_Colour);
			}
		}
		else if(getTextProperty()->hasDirtyFlag(CTextProperty::EDirtyFlag_Colour))
		{
			for(auto window:mGraphicWindows)
				window->setColour(getTextProperty()->getColour());
			getTextProperty()->removeDirtyFlag(CTextProperty::EDirtyFlag_Colour);
		}
		if(0==getTextProperty()->getDirtyFlag())
			removeDirtyFlag(EDirtyFlag_Property);
		break;
	}
}

Void NSDevilX::NSGUISystem::CStaticText::onMessage(CTextProperty * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case CTextProperty::EMessage_AddDirtyFlag:
		addDirtyFlag(EDirtyFlag_Property);
		break;
	}
}
