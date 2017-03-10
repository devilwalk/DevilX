#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSGUISystem;

NSDevilX::NSGUISystem::IStaticTextImp::IStaticTextImp(const String & name,IWindowImp * window)
	:mControl(nullptr)
{
	mControl=DEVILX_NEW IControlImp(name,window);
}

NSDevilX::NSGUISystem::IStaticTextImp::~IStaticTextImp()
{
	DEVILX_DELETE(mControl);
}

IControl * NSDevilX::NSGUISystem::IStaticTextImp::queryInterface_IControl() const
{
	return mControl;
}

Void NSDevilX::NSGUISystem::IStaticTextImp::setText(const WString & string,const CColour & colour)
{
	mText=string;
	mTextColour=colour;
}

Void NSDevilX::NSGUISystem::IStaticTextImp::_updateGraphicWindows()
{
	const auto word_width=1.0f/getText().length();
	TVector<CSInt2> pixel_starts;
	pixel_starts.resize(getText().length());
	TVector<CSInt2> pixel_ends;
	pixel_ends.resize(getText().length());
	for(size_t i=0;i<getText().length();++i)
	{
		auto Image=ISystemImp::getSingleton().getFontManager()->getImage(ISystemImp::getSingleton().getFontName(),getText()[i],&pixel_starts[i],&pixel_ends[i]);
		auto window=static_cast<ISceneImp*>(queryInterface_IControl()->getParentWindow()->getScene())->getGraphicScene()->createWindow(queryInterface_IControl()->queryInterface_IElement()->getName()+"/"+CStringConverter::toString(i));
		window->setColour(mTextColour);
		//window->setTexture(CApp::getSingleton().getGame()->getFontManager()->getRenderTexture(),pixel_starts[i],pixel_ends[i]);
		window->queryInterface_IElement()->setPosition(CFloat2(word_width,0.0f)*static_cast<Float>(i));
		window->queryInterface_IElement()->setSize(CFloat2(word_width,1.0f));
		mControl->attachGraphicWindow(window);
	}
}
