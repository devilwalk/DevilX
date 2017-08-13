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

NSResourceSystem::ILoadedResource * NSDevilX::NSGUISystem::CStaticText::_load() const
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
	return load_call_back.mLoadedResource;
}

CFloat2 NSDevilX::NSGUISystem::CStaticText::_calcFontUnitSize() const
{
	auto res=_load();
	auto font_face=NSResourceSystem::getSystem()->getFontFace(res);
	auto ret=_calcMaxFontSize()/CUInt2(font_face->getBBox().xMax-font_face->getBBox().xMin,font_face->getBBox().yMax-font_face->getBBox().yMin);
	return ret;
}

CFloat2 NSDevilX::NSGUISystem::CStaticText::_calcMaxFontSize() const
{
	Float size_y=1.0f/_calcLineCount();
	Float size_x=1.0f/_calcMaxCharPerLine();
	return CFloat2(size_x,size_y);
}

UInt32 NSDevilX::NSGUISystem::CStaticText::_calcLineCount() const
{
	UInt32 line_count=1;
	for(auto const & c:mText)
	{
		if(c=='\n')
		{
			line_count++;
		}
	}
	return line_count;
}

UInt32 NSDevilX::NSGUISystem::CStaticText::_calcMaxCharPerLine() const
{
	UInt32 max_char_per_line=0;
	UInt32 char_per_line=0;
	for(auto const & c:mText)
	{
		if(c=='\n')
		{
			max_char_per_line=std::max<>(max_char_per_line,char_per_line);
			char_per_line=0;
		}
		++char_per_line;
	}
	max_char_per_line=std::max<>(max_char_per_line,char_per_line);
	return max_char_per_line;
}

Boolean NSDevilX::NSGUISystem::CStaticText::_updateGraphicWindows()
{
	_destroyGraphicWindows();
	TVector<CFloat2> positions;
	auto loaded_resource=_calculateTextParameters(&positions);
	if(nullptr==loaded_resource)
		return false;
	auto font_face=NSResourceSystem::getSystem()->getFontFace(loaded_resource);
	const auto max_font_size=_calcMaxFontSize();
	for(size_t i=0;i<getText().size();++i)
	{
		auto char_info=NSResourceSystem::getSystem()->getChar(loaded_resource,getText()[i]);
		auto tex=NSResourceSystem::getSystem()->getRenderTexture(loaded_resource,getText()[i]);
		auto window=getGraphicScene()->createWindow(getLayer()->getName()+"/"+CStringConverter::toString(i));
		window->setColour(getTextProperty()->getColour());
		window->setTexture(tex,char_info.mPixelStart,char_info.mPixelEnd);
		window->queryInterface_IElement()->setPosition(positions[i]);
		window->queryInterface_IElement()->setSize(CFloat2(max_font_size.x*char_info.mGlyphMetrics.horiAdvance/font_face->getBBox().xMax,max_font_size.y));
		_attachWindow(window);
	}
	return true;
}

NSResourceSystem::ILoadedResource * NSDevilX::NSGUISystem::CStaticText::_calculateTextParameters(TVector<CFloat2> * positions,TVector<CFloat2> * sizes,Float * lastCharRight)const
{
	auto res=_load();
	if(!res)
		return nullptr;
	auto font_face=NSResourceSystem::getSystem()->getFontFace(res);
	if(positions||sizes||lastCharRight)
	{
		const auto font_unit_size=_calcFontUnitSize();
		const auto max_font_size=_calcMaxFontSize();
		TVector<TVector<UInt32> > text_indices;
		TVector<UInt32> text_index;
		TVector<UInt32> row_widths;
		CUTF8String line_text;
		for(UInt32 i=0;i<mText.size();++i)
		{
			auto const & c=mText[i];
			if(c=='\r')
				continue;
			if(c=='\n')
			{
				row_widths.push_back(font_face->getTotalAdvanceWidth(line_text));
				line_text.clear();
				text_indices.push_back(text_index);
				text_index.clear();
			}
			else
			{
				line_text.push_back(c);
				text_index.push_back(i);
			}
		}
		if(!line_text.empty())
			row_widths.push_back(font_face->getTotalAdvanceWidth(line_text));
		CUInt2 offset=CUInt2::sZero;
		for(size_t row=0;row<row_widths.size();++row)
		{
			switch(getTextProperty()->getRowAlignMode())
			{
			case IEnum::ETextRowAlignMode_Center:
				offset.x=(font_face->getBBox().xMax-row_widths[row])/2;
				break;
			case IEnum::ETextRowAlignMode_Left:
				offset.x=0;
				break;
			case IEnum::ETextRowAlignMode_Right:
				offset.x=font_face->getBBox().xMax-row_widths[row];
				break;
			}
			offset.y=row*(font_face->getBBox().yMax-font_face->getBBox().yMin);
			if(positions)
			{
				positions->resize(mText.size());
				memset(&((*positions)[0]),0,sizeof(CFloat2));
				UInt32 sum_width=0;
				for(auto index:text_indices[row])
				{
					auto const & metrics=font_face->getGlyphMetrics(mText[index]);
					(*positions)[index]=CUInt2(offset.x+sum_width+metrics.horiBearingX,offset.y+(font_face->getBBox().yMax-metrics.horiBearingY))*font_unit_size;
					sum_width+=metrics.horiAdvance;
				}
			}
			if(sizes)
			{
				sizes->resize(mText.size());
				memset(&((*sizes)[0]),0,sizeof(CFloat2));
				for(auto index:text_indices[row])
				{
					auto const box=font_face->getBBox(mText[index]);
					(*sizes)[index]=CUInt2(box.xMax-box.xMin,box.yMax-box.yMin)*font_unit_size;
				}
			}
		}
	}
	return res;
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
