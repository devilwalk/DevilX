#pragma once
#include "ITextureImp.h"
#include "IColourUnitStateImp.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		class IOverlayElementImp
			:public IOverlayElement
			,public TBaseObject<IOverlayElementImp>
			,public CMessageNotifier
		{
		public:
			enum EMessage
			{
				EMessage_BeginPositionChange,
				EMessage_EndPositionChange,
				EMessage_BeginSizeChange,
				EMessage_EndSizeChange,
				EMessage_BeginOrderChange,
				EMessage_EndOrderChange,
				EMessage_BeginUVTransformChange,
				EMessage_EndUVTransformChange,
				EMessage_BeginColourUnitStateCreate,
				EMessage_EndColourUnitStateCreate,
				EMessage_BeginTextureUnitStateCreate,
				EMessage_EndTextureUnitStateCreate
			};
		protected:
			const String mName;
			CFloat2 mPosition;
			CFloat2 mSize;
			Int32 mOrder;
			IColourUnitStateImp * mColourUnitState;
			ITextureUnitStateImp * mTextureUnitState;
			CFloat2 mUVOffset;
			CFloat2 mUVScale;
		public:
			IOverlayElementImp(const String & name);
			~IOverlayElementImp();
			IColourUnitStateImp * getColourUnitState() const
			{
				return mColourUnitState;
			}
			ITextureUnitStateImp * getTextureUnitState() const
			{
				return mTextureUnitState;
			}
			// Í¨¹ý IOverlayElement ¼Ì³Ð
			virtual const String & getName() const override;
			virtual Void setPosition(const CFloat2 & position) override;
			virtual const CFloat2 & getPosition() const override;
			virtual Void setSize(const CFloat2 & size) override;
			virtual const CFloat2 & getSize() const override;
			virtual Void setOrder(Int32 order) override;
			virtual Int32 getOrder() const override;
			virtual IColourUnitState * getColourUnitState() override;
			virtual ITextureUnitState * getTextureUnitState() override;
			virtual Void setUVTransform(const CFloat2 & offset,const CFloat2 & scale) override;
			virtual const CFloat2 & getUVOffset() const override;
			virtual const CFloat2 & getUVScale() const override;
		};
	}
}