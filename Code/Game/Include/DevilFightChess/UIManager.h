#pragma once
namespace NSDevilX
{
	namespace NSFightChess
	{
		class CUIManager
			:public TBaseObject<CUIManager>
		{
		public:
			struct SStaticText
				:public TBaseObject<SStaticText>
			{
				TVector<NSUISystem::IGraphicWindow*> mUIGraphicWindows;
			};
		protected:
			NSUISystem::IGraphicScene * mGraphicScene;
			TNamedResourcePtrMap<SStaticText> mStaticTexts;
		public:
			CUIManager();
			~CUIManager();
			NSUISystem::IGraphicScene * getGraphicScene()const
			{
				return mGraphicScene;
			}
			Void createStaticText(const String & name,const WString & text,const CFloat2 & position,const CFloat2 & size,const CColour & colour=CFloatRGBA::sBlack);
		};
	}
}