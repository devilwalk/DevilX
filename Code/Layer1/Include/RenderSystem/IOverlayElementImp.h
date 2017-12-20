#pragma once
#include "ITextureImp.h"
#include "IValueUnitStateImp.h"
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
				EMessage_BeginEnableChange,
				EMessage_EndEnableChange,
				EMessage_BeginPositionChange,
				EMessage_EndPositionChange,
				EMessage_BeginSizeChange,
				EMessage_EndSizeChange,
				EMessage_BeginOrderChange,
				EMessage_EndOrderChange,
				EMessage_BeginUVChange,
				EMessage_EndUVChange,
				EMessage_BeginScissorRectChange,
				EMessage_EndScissorRectChange,
				EMessage_BeginColourUnitStateCreate,
				EMessage_EndColourUnitStateCreate,
				EMessage_BeginTextureUnitStateCreate,
				EMessage_EndTextureUnitStateCreate
			};
		protected:
			const String mName;
			Bool mEnable;
			CFloat2 mPosition;
			CFloat2 mSize;
			CFloat2 mUVs[4];
			CFloat2 mScissorRectPosition;
			CFloat2 mScissorRectSize;
			Int32 mOrder;
			IColourUnitStateImp * mColourUnitState;
			ITextureUnitStateImp * mTextureUnitState;
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
			virtual Void setEnable(Bool enable) override;
			virtual Bool getEnable() const override;
			virtual const String & getName() const override;
			virtual Void setPosition(const CFloat2 & position) override;
			virtual const CFloat2 & getPosition() const override;
			virtual Void setSize(const CFloat2 & size) override;
			virtual const CFloat2 & getSize() const override;
			virtual Void setUVs(const CFloat2 & uv0,const CFloat2 & uv1,const CFloat2 & uv2,const CFloat2 & uv3) override;
			virtual const CFloat2 * getUVs() const override;
			virtual Void setOrder(Int32 order) override;
			virtual Int32 getOrder() const override;
			virtual Void SetScissorRect(const CFloat2 & position,const CFloat2 & size) override;
			virtual const CFloat2 & getScissorRectPosition() const override;
			virtual const CFloat2 & getScissorRectSize() const override;
			virtual IColourUnitState * getColourUnitState() override;
			virtual ITextureUnitState * getTextureUnitState() override;
		};
	}
}