#pragma once
namespace NSDevilX
{
	namespace NSGUISystem
	{
		class CTextProperty
			:public TBaseObject<CTextProperty>
			,public CDirtyFlagContainer
			,public CMessageNotifier
		{
		public:
			enum EMessage
			{
				EMessage_AddDirtyFlag
			};
			enum EDirtyFlag
			{
				EDirtyFlag_Font,
				EDirtyFlag_Colour
			};
		protected:
			NSResourceSystem::IResource * mFontResource;
			CFloat2 mFontSize;
			CFloatRGBA mColour;
			IEnum::ETextRowAlignMode mRowAlignMode;
			IEnum::ETextColumeAlignMode mColumeAlignMode;
		public:
			CTextProperty();
			~CTextProperty();
			Void copyFrom(const CTextProperty * prop);
			Void setFontResource(NSResourceSystem::IResource * resource);
			NSResourceSystem::IResource * getFontResource() const
			{
				return mFontResource;
			}
			Void setFontSize(const CFloat2 & size);
			const CFloat2 & getFontSize()const
			{
				return mFontSize;
			}
			Void setColour(const CColour & colour);
			const CColour & getColour() const
			{
				return mColour;
			}
			Void setRowAlignMode(IEnum::ETextRowAlignMode mode);
			IEnum::ETextRowAlignMode getRowAlignMode()const
			{
				return mRowAlignMode;
			}
			Void setColumeAlignMode(IEnum::ETextColumeAlignMode mode);
			IEnum::ETextColumeAlignMode getColumeAlignMode()const
			{
				return mColumeAlignMode;
			}

			virtual Void _postProcessDirtyFlagAdd(UInt32 flagIndex) override;
		};
	}
}