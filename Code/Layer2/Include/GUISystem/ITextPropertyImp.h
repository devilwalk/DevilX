#pragma once
#include "TextProperty.h"
namespace NSDevilX
{
	namespace NSGUISystem
	{
		class ITextPropertyImp
			:public ITextProperty
			,public TBaseObject<ITextPropertyImp>
		{
		protected:
			CTextProperty * const mProperty;
		public:
			ITextPropertyImp(CTextProperty * prop);
			~ITextPropertyImp();

			// Í¨¹ý ITextProperty ¼Ì³Ð
			virtual Void setFontResource(NSResourceSystem::IResource * resource) override;
			virtual NSResourceSystem::IResource * getFontResource() const override;
			virtual Void setFontSize(const CFloat2 & size) override;
			virtual const CFloat2 & getFontSize() const override;
			virtual Void setColour(const CColour & colour) override;
			virtual const CColour & getColour() const override;
			virtual Void setRowAlignMode(IEnum::ETextRowAlignMode mode) override;
			virtual IEnum::ETextRowAlignMode getRowAlignMode() const override;
			virtual Void setColumeAlignMode(IEnum::ETextColumeAlignMode mode) override;
			virtual IEnum::ETextColumeAlignMode getColumeAlignMode() const override;
		};
	}
}