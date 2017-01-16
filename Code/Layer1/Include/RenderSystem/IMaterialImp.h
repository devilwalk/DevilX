#pragma once
#include "IColourUnitStateImp.h"
#include "ITextureUnitStateImp.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		class IRenderableImp;
		class IMaterialImp
			:public IMaterial
			,public TBaseObject<IMaterialImp>
			,public CMessageNotifier
		{
		public:
			enum EMessage
			{
				EMessage_BeginColourUnitStateCreate,
				EMessage_EndColourUnitStateCreate,
				EMessage_BeginTextureUnitStateCreate,
				EMessage_EndTextureUnitStateCreate,
				EMessage_BeginLightEnableChange,
				EMessage_EndLightEnableChange,
				EMessage_BeginAlphaTestValueChange,
				EMessage_EndAlphaTestValueChange,
				EMessage_BeginAlphaTestEnableChange,
				EMessage_EndAlphaTestEnableChange,
				EMessage_BeginTransparentEnableChange,
				EMessage_EndTransparentEnableChange
			};
		protected:
			IRenderableImp * const mRenderable;
			TVector<IColourUnitStateImp*> mColourUnitStates;
			TVector<ITextureUnitStateImp*> mTextureUnitStates;
			Bool mLightEnable,mTransparentEnable;
			Float mAlphaTestValue;
		public:
			IMaterialImp(IRenderableImp * renderable);
			~IMaterialImp();
			Boolean isAlphaTestEnable()const
			{
				return mAlphaTestValue>0;
			}
			IColourUnitStateImp * getColourUnitState(IEnum::EColourUnitStateType type) const;
			ITextureUnitStateImp * getTextureUnitState(IEnum::ETextureUnitStateType type) const;
			// Inherited via IMaterial
			virtual IColourUnitState * getColourUnitState(IEnum::EColourUnitStateType type) override;
			virtual ITextureUnitState * getTextureUnitState(IEnum::ETextureUnitStateType type) override;
			virtual Void setLightEnable(Bool enable) override;
			virtual Bool getLightEnable() const override;
			virtual Void setAlphaTestValue(Float alpha) override;
			virtual Float getAlphaTestValue() const override;
			virtual Void setTransparentEnable(Bool enable) override;
			virtual Bool getTransparentEnable() const override;
		};
	}
}