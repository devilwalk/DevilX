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
	if(static_cast<const WString &>(getText())!=static_cast<const WString &>(text))
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

Void NSDevilX::NSGUISystem::CStaticText::_updateGraphicWindows()
{
	_destroyGraphicWindows();
	if(!getFontResource())
		return;
	getFontResource()->load(nullptr);
	if(!getFontResource()->isLoaded())
		return;
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

	const WString text=getText();
	const auto word_width=1.0f/text.length();
	TVector<CUInt2> pixel_starts;
	pixel_starts.resize(text.length());
	TVector<CUInt2> pixel_ends;
	pixel_ends.resize(text.length());
	for(size_t i=0;i<text.length();++i)
	{
		auto tex=NSResourceSystem::getSystem()->getRenderTexture(load_call_back.mLoadedResource,text[i],&pixel_starts[i],&pixel_ends[i]);
		auto window=getGraphicScene()->createWindow(getLayer()->getName()+"/"+CStringConverter::toString(i));
		window->setColour(mTextColour);
		window->setTexture(tex,pixel_starts[i],pixel_ends[i]);
		window->queryInterface_IElement()->setPosition(CFloat2(word_width,0.0f)*static_cast<Float>(i));
		window->queryInterface_IElement()->setSize(CFloat2(word_width,1.0f));
		_attachGraphicWindow(window);
	}
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
			_updateGraphicWindows();
			removeDirtyFlag(EDirtyFlag_FontResource);
			removeDirtyFlag(EDirtyFlag_Text);
			removeDirtyFlag(EDirtyFlag_TextColour);
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
