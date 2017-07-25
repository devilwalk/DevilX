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
		class ISubEntityImp
			:public ISubEntity
			,public CMessageNotifier
			,public CUserDataContainer
			,public CReferenceObject
		{
		public:
			enum EMessage
			{
				EMessage_BeginRenderableChange,
				EMessage_EndRenderableChange,
				EMessage_BeginQueriableChange,
				EMessage_EndQueriableChange,
				EMessage_BeginGeometryChange,
				EMessage_EndGeometryChange,
				EMessage_BeginQueryBufferChange,
				EMessage_EndQueryBufferChange,
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
			Bool mIsRenderable;
			Bool mIsQueriable;
			IGeometryImp * mGeometry;
			IGeometryUsageImp * mGeometryUsage;
			IBufferImp * mQueryBuffer;
			IBufferUsageImp * mQueryBufferUsage;
			Bool mVisible;
			TVector<IColourUnitStateImp*> mColourUnitStates;
			TVector<ITextureUnitStateImp*> mTextureUnitStates;
			Bool mLightEnable,mTransparentEnable;
			Float mAlphaTestValue;
		public:
			ISubEntityImp(const String & name,IEntityImp * object);
			Boolean isAlphaTestEnable()const
			{
				return mAlphaTestValue>0;
			}
			IColourUnitStateImp * getColourUnitState(IEnum::EEntityColourUnitStateType type) const;
			ITextureUnitStateImp * getTextureUnitState(IEnum::EEntityTextureUnitStateType type) const;
			// Inherited via IRenderable
			virtual IGeometryUsage * queryInterface_IGeometryUsage() const override;
			virtual const String & getName() const override;
			virtual IEntity * getEntity() const override;
			virtual Void setRenderable(Bool renderable) override;
			virtual Bool isRenderable() const override;
			virtual Void setQueriable(Bool queriable) override;
			virtual Bool isQueriable() const override;
			virtual Void setQueryBuffer(IBuffer * buffer) override;
			virtual IBuffer * getQueryBuffer() const override;
			virtual IBufferUsage * getQueryBufferUsage() const override;
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
		protected:
			~ISubEntityImp();
		};
	}
}