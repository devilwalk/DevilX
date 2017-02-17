#pragma once
#include "IGeometryUsageImp.h"
#include "ISkyImp.h"
#include "Enum.h"
#include "IColourUnitStateImp.h"
#include "ITextureUnitStateImp.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		class IEntityImp;
		class CRenderList;
		class IEntityRenderableImp
			:public IEntityRenderable
			,public CMessageNotifier
			,public CUserDataContainer
		{
		public:
			enum EMessage
			{
				EMessage_BeginGeometryChange,
				EMessage_EndGeometryChange,
				EMessage_BeginVisibleChange,
				EMessage_EndVisibleChange,
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
			const String mName;
			IEntityImp * const mObject;
			IGeometryImp * mGeometry;
			IGeometryUsageImp * mGeometryUsage;
			Bool mVisible;
			TVector<IColourUnitStateImp*> mColourUnitStates;
			TVector<ITextureUnitStateImp*> mTextureUnitStates;
			Bool mLightEnable,mTransparentEnable;
			Float mAlphaTestValue;
		public:
			IEntityRenderableImp(const String & name,IEntityImp * object);
			virtual ~IEntityRenderableImp();
			Boolean isAlphaTestEnable()const
			{
				return mAlphaTestValue>0;
			}
			IColourUnitStateImp * getColourUnitState(IEnum::EEntityColourUnitStateType type) const;
			ITextureUnitStateImp * getTextureUnitState(IEnum::EEntityTextureUnitStateType type) const;
			// Inherited via IRenderable
			virtual const String & getName() const override;
			virtual IEntity * getEntity() const override;
			virtual IGeometryUsage * queryInterface_IGeometryUsage() const override;
			virtual Void setVisible(Bool visible) override;
			virtual Bool getVisible() const override;
			virtual Void setGeometry(IGeometry * geometry) override;
			virtual IGeometry * getGeometry() const override;
			virtual IColourUnitState * getColourUnitState(IEnum::EEntityColourUnitStateType type) override;
			virtual ITextureUnitState * getTextureUnitState(IEnum::EEntityTextureUnitStateType type) override;
			virtual Void setLightEnable(Bool enable) override;
			virtual Bool getLightEnable() const override;
			virtual Void setAlphaTestValue(Float alpha) override;
			virtual Float getAlphaTestValue() const override;
			virtual Void setTransparentEnable(Bool enable) override;
			virtual Bool getTransparentEnable() const override;
		};
	}
}