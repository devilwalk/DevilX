#pragma once
#include "Control.h"
#include "TextProperty.h"
namespace NSDevilX
{
	namespace NSGUISystem
	{
		class ISystemImp;
		class CStaticText
			:public CControl
			,public TBaseObject<CStaticText>
			,public TMessageReceiver<ISystemImp>
			,public CDirtyFlagContainer
			,public TMessageReceiver<CTextProperty>
		{
		public:
			enum EDirtyFlag
			{
				EDirtyFlag_Property,
				EDirtyFlag_Text
			};
		protected:
			CTextProperty * mTextProperty;
			CUTF8String mText;
		public:
			CStaticText(const String & name,CControl * coordParent);
			~CStaticText();
			CTextProperty * getTextProperty()const
			{
				return mTextProperty;
			}
			Void setText(const CUTF8String & text);
			const CUTF8String & getText() const
			{
				return mText;
			}
			Boolean getPosition(UInt32 charIndex,CFloat2 * position)const;
			Boolean getPositions(TVector<CFloat2> * positions,Float * lastCharRight=nullptr)const;
		protected:
			NSResourceSystem::ILoadedResource * _load()const;
			CFloat2 _calcFontUnitSize()const;
			CFloat2 _calcMaxFontSize()const;
			UInt32 _calcLineCount()const;
			UInt32 _calcMaxCharPerLine()const;
			Boolean _updateGraphicWindows();
			NSResourceSystem::ILoadedResource * _calculateTextParameters(TVector<CFloat2> * positions,TVector<CFloat2> * sizes,Float * lastCharRight=nullptr)const;
			virtual Void _preProcessDirtyFlagAdd(UInt32 flagIndex) override;
			virtual Void _postProcessDirtyFlagRemove(UInt32 flagIndex) override;
			// Í¨¹ý TMessageReceiver ¼Ì³Ð
			virtual Void onMessage(ISystemImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
			virtual Void onMessage(CTextProperty * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
		};
	}
}