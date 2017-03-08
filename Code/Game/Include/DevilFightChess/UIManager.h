#pragma once
namespace NSDevilX
{
	namespace NSFightChess
	{
		class CUIControl
		{
		protected:
			const String mName;
			NSUISystem::IElement * mLayer;
			TVector<NSUISystem::IGraphicWindow*> mUIGraphicWindows;
		public:
			CUIControl(const String & name,const CFloat2 & position,const CFloat2 & size,CUIControl * parent=nullptr);
			~CUIControl();
			const String & getName()const
			{
				return mName;
			}
			NSUISystem::IElement * getLayer()const
			{
				return mLayer;
			}
			Void addGraphicWindow(NSUISystem::IGraphicWindow * window);
			NSUISystem::IGraphicWindow * getGraphicWindow(UInt32 index=0)const
			{
				return mUIGraphicWindows[index];
			}
		};
		class CUIManager
			:public TBaseObject<CUIManager>
		{
		protected:
			NSUISystem::IGraphicScene * mGraphicScene;
			TNamedResourcePtrMap<CUIControl> mControls;
		public:
			CUIManager();
			~CUIManager();
			NSUISystem::IGraphicScene * getGraphicScene()const
			{
				return mGraphicScene;
			}
			CUIControl * createControl(const String & name,const CFloat2 & position,const CFloat2 & size,CUIControl * parent=nullptr);
			Void destroyControl(CUIControl * control);
			CUIControl * createStaticText(const String & name,const WString & text,const CFloat2 & position,const CFloat2 & size,const CColour & colour=CFloatRGBA::sBlack,CUIControl * parent=nullptr);
		};
	}
}