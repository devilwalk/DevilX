#pragma once
#include "Control.h"
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
		{
		public:
			enum EDirtyFlag
			{
				EDirtyFlag_FontResource,
				EDirtyFlag_Text,
				EDirtyFlag_TextColour
			};
		protected:
			NSResourceSystem::IResource * mFontResource;
			CUTF8String mText;
			CFloatRGBA mTextColour;
		public:
			CStaticText(const String & name,CControl * parent);
			~CStaticText();
			Void setFontResource(NSResourceSystem::IResource * resource);
			NSResourceSystem::IResource * getFontResource() const;
			Void setText(const CUTF8String & text);
			const CUTF8String & getText() const;
			Void setTextColour(const CColour & colour);
			const CColour & getTextColour() const;
		protected:
			Void _updateGraphicWindows();
			virtual Void _preProcessDirtyFlagAdd(UInt32 flagIndex) override;
			virtual Void _postProcessDirtyFlagRemove(UInt32 flagIndex) override;
			// Í¨¹ý TMessageReceiver ¼Ì³Ð
			virtual Void onMessage(ISystemImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
		};
	}
}