#pragma once
namespace NSDevilX
{
	namespace NSGUISystem
	{
		class IWindowImp;
		class IStaticTextImp
			:public IStaticText
			,public TBaseObject<IStaticTextImp>
		{
		protected:
			IControlImp * mControl;
			WString mText;
			CFloatRGBA mTextColour;
		public:
			IStaticTextImp(const String & name,IWindowImp * window);
			~IStaticTextImp();

			// Í¨¹ý IStaticText ¼Ì³Ð
			virtual IControl * queryInterface_IControl() const override;
			virtual Void setText(const WString & string,const CColour & colour) override;
			virtual const WString & getText() const override;
			virtual const CColour & getTextColour() const override;
		protected:
			Void _updateGraphicWindows();
		};
	}
}