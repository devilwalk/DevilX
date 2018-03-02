#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSGUISystem;

NSDevilX::NSGUISystem::CStaticText::CStaticText(const String & name,CControl * coordParent)
	:CControl(name,coordParent,False)
	,mTextProperty(nullptr)
{
	mTextProperty=DEVILX_NEW CTextProperty;
	mTextProperty->addListener(static_cast<TMessageReceiver<CTextProperty>*>(this),CTextProperty::EMessage_AddDirtyFlag);
	ISystemImp::getSingleton().getWindow()->registerEventListener(this);
}

NSDevilX::NSGUISystem::CStaticText::~CStaticText()
{
	DEVILX_DELETE(mTextProperty);
	ISystemImp::getSingleton().getWindow()->unregisterEventListener(this);
}

Void NSDevilX::NSGUISystem::CStaticText::setText(const CUTF8String & text)
{
	if(mText!=text)
	{
		mText=text;
		addDirtyFlag(EDirtyFlag_Text);
	}
}

Boolean NSDevilX::NSGUISystem::CStaticText::getPosition(UInt32 charIndex,CFloat2 * position) const
{
	if((mText.size()<charIndex)
		||hasDirtyFlag(EDirtyFlag_Text))
		return false;
	else
	{
		if(position)
		{
			_load();
			if(nullptr==mTextProperty->getFontResource())
				return false;
			TVector<CFloat2> positions;
			Float last_char_right;
			_calculateTextParameters(&positions,nullptr,&last_char_right);
			if(mText.size()==charIndex)
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
	_load();
	if(nullptr==mTextProperty->getFontResource())
		return false;
	_calculateTextParameters(positions,nullptr,lastCharRight);
	return true;
}

Void NSDevilX::NSGUISystem::CStaticText::_load() const
{
	if(!mTextProperty->getFontResource())
		return;
	getTextProperty()->getFontResource()->load(nullptr,True);
}

CFloat2 NSDevilX::NSGUISystem::CStaticText::_calcFontUnitSize() const
{
	_load();
	auto font_face=NSResourceSystem::getSystem()->getFontFace(mTextProperty->getFontResource());
	if(mText.empty())
		return CFloat2::sZero;
	else
		return _calcValidateSize()/CUInt2(_calcMaxCharPerLine(),_calcLineCount())/CUInt2(font_face->getBBox().xMax-font_face->getBBox().xMin,font_face->getBBox().yMax-font_face->getBBox().yMin);
}

CFloat2 NSDevilX::NSGUISystem::CStaticText::_calcValidateSize() const
{
	_load();
	auto font_face=NSResourceSystem::getSystem()->getFontFace(mTextProperty->getFontResource());
	if(mText.empty())
		return CFloat2::sZero;
	else
	{
		const auto max_char_per_line=_calcMaxCharPerLine();
		const auto line_count=_calcLineCount();
		const auto size_in_pixel=getSizeInPixel();
		const auto scalar_best=(static_cast<Float>(font_face->getBBox().xMax-font_face->getBBox().xMin)*max_char_per_line)/((font_face->getBBox().yMax-font_face->getBBox().yMin)*line_count);
		const auto scalar_current=static_cast<Float>(size_in_pixel.x)/size_in_pixel.y;
		CFloat2 ret;
		if(scalar_best>=scalar_current)
		{
			ret=CFloat2(1.0f,static_cast<Float>(size_in_pixel.x)/size_in_pixel.y/scalar_best);
		}
		else
		{
			ret=CFloat2(scalar_best*size_in_pixel.y/size_in_pixel.x,1.0f);
		}
		return ret;
	}
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
	_load();
	if(nullptr==mTextProperty->getFontResource())
		return false;
	TVector<CFloat2> positions;
	TVector<CFloat2> sizes;
	_calculateTextParameters(&positions,&sizes);
	for(size_t i=0;i<getText().size();++i)
	{
		auto char_info=NSResourceSystem::getSystem()->getChar(mTextProperty->getFontResource(),getText()[i]);
		auto tex=NSResourceSystem::getSystem()->getRenderTexture(mTextProperty->getFontResource(),getText()[i]);
		auto window=getGraphicScene()->createWindow(getLayer()->getName()+"/"+CStringConverter::toString(i));
		window->setColour(mTextProperty->getColour());
		window->setTexture(tex,char_info.mPixelStart,char_info.mPixelEnd);
		window->queryInterface_IElement()->setPosition(positions[i]);
		window->queryInterface_IElement()->setSize(sizes[i]);
		_attachWindow(window);
	}
	return true;
}

Void NSDevilX::NSGUISystem::CStaticText::_calculateTextParameters(TVector<CFloat2> * positions,TVector<CFloat2> * sizes,Float * lastCharRight)const
{
	_load();
	if(!mTextProperty->getFontResource())
		return;
	auto font_face=NSResourceSystem::getSystem()->getFontFace(mTextProperty->getFontResource());
	if(positions||sizes||lastCharRight)
	{
		const auto font_unit_size=_calcFontUnitSize();
		const auto max_char_per_line=_calcMaxCharPerLine();
		const auto max_line_width=max_char_per_line*(font_face->getBBox().xMax-font_face->getBBox().xMin);
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
		{
			row_widths.push_back(font_face->getTotalAdvanceWidth(line_text));
			text_indices.push_back(text_index);
		}
		const auto validate_size=_calcValidateSize();
		CFloat2 fixed_offset=CFloat2::sZero;
		switch(mTextProperty->getRowAlignMode())
		{
		case IEnum::ETextRowAlignMode_Center:
			fixed_offset.x=(1.0f-validate_size.x)/2;
			break;
		case IEnum::ETextRowAlignMode_Left:
			fixed_offset.x=0;
			break;
		case IEnum::ETextRowAlignMode_Right:
			fixed_offset.x=1.0f-validate_size.x;
			break;
		}
		switch(mTextProperty->getColumeAlignMode())
		{
		case IEnum::ETextRowAlignMode_Center:
			fixed_offset.y=(1.0f-validate_size.y)/2;
			break;
		case IEnum::ETextColumeAlignMode_Top:
			fixed_offset.y=0;
			break;
		case IEnum::ETextColumeAlignMode_Bottom:
			fixed_offset.y=1.0f-validate_size.y;
			break;
		}
		CUInt2 offset=CUInt2::sZero;
		for(size_t row=0;row<row_widths.size();++row)
		{
			switch(getTextProperty()->getRowAlignMode())
			{
			case IEnum::ETextRowAlignMode_Center:
				offset.x=(max_line_width-row_widths[row])/2;
				break;
			case IEnum::ETextRowAlignMode_Left:
				offset.x=0;
				break;
			case IEnum::ETextRowAlignMode_Right:
				offset.x=max_line_width-row_widths[row];
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
					(*positions)[index]=fixed_offset+CUInt2(offset.x+sum_width+metrics.horiBearingX,offset.y+(font_face->getBBox().yMax-metrics.horiBearingY))*font_unit_size;
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
		if(lastCharRight)
		{
			UInt32 sum_width=0;
			if(!text_indices.empty())
			{
				for(auto index:text_indices[row_widths.size()-1])
				{
					auto const & metrics=font_face->getGlyphMetrics(mText[index]);
					sum_width+=metrics.horiAdvance;
				}
			}
			*lastCharRight=fixed_offset.x+sum_width*font_unit_size.x;
		}
	}
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
		if(mTextProperty->hasDirtyFlag(CTextProperty::EDirtyFlag_Font)
			||hasDirtyFlag(EDirtyFlag_Text)
			)
		{
			if(_updateGraphicWindows())
			{
				removeDirtyFlag(EDirtyFlag_Text);
				mTextProperty->removeDirtyFlag(CTextProperty::EDirtyFlag_Font);
				mTextProperty->removeDirtyFlag(CTextProperty::EDirtyFlag_Colour);
			}
		}
		else if(mTextProperty->hasDirtyFlag(CTextProperty::EDirtyFlag_Colour))
		{
			for(auto window:mGraphicWindows)
				window->setColour(getTextProperty()->getColour());
			mTextProperty->removeDirtyFlag(CTextProperty::EDirtyFlag_Colour);
		}
		if(0==mTextProperty->getDirtyFlag())
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

Void NSDevilX::NSGUISystem::CStaticText::onResize(CWindow * window)
{
	_updateGraphicWindows();
}
