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
			CStaticText(const String & name,CControl * parent);
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
			Boolean _updateGraphicWindows();
			NSResourceSystem::ILoadedResource * _calculateTextParameters(TVector<CFloat2> * positions,Float * lastCharRight=nullptr)const;
			virtual Void _preProcessDirtyFlagAdd(UInt32 flagIndex) override;
			virtual Void _postProcessDirtyFlagRemove(UInt32 flagIndex) override;
			// ͨ�� TMessageReceiver �̳�
			virtual Void onMessage(ISystemImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
			virtual Void onMessage(CTextProperty * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
		};
	}
}