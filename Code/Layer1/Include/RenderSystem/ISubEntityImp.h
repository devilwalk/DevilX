#pragma once
#include "IGeometryUsageImp.h"
#include "ISkyImp.h"
#include "Enum.h"
#include "IValueUnitStateImp.h"
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
				EMessage_BeginAmbientModelChange,
				EMessage_EndAmbientModelChange,
				EMessage_BeginDiffuseModelChange,
				EMessage_EndDiffuseModelChange,
				EMessage_BeginSpecularModelChange,
				EMessage_EndSpecularModelChange,
				EMessage_BeginAlphaColourCreate,
				EMessage_EndAlphaColourCreate,
				EMessage_BeginDiffuseColourCreate,
				EMessage_EndDiffuseColourCreate,
				EMessage_BeginSpecularColourCreate,
				EMessage_EndSpecularColourCreate,
				EMessage_BeginEmissiveColourCreate,
				EMessage_EndEmissiveColourCreate,
				EMessage_BeginDiffuseTextureCreate,
				EMessage_EndDiffuseTextureCreate,
				EMessage_BeginSpecularTextureCreate,
				EMessage_EndSpecularTextureCreate,
				EMessage_BeginNormalTextureCreate,
				EMessage_EndNormalTextureCreate,
				EMessage_BeginMetallicValueCreate,
				EMessage_EndMetallicValueCreate,
				EMessage_BeginRoughnessValueCreate,
				EMessage_EndRoughnessValueCreate,
				EMessage_BeginSpecularPowerValueCreate,
				EMessage_EndSpecularPowerValueCreate,
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
			IEnum::EMaterialAmbientModel mAmbientModel;
			IEnum::EMaterialDiffuseModel mDiffuseModel;
			IEnum::EMaterialSpecularModel mSpecularModel;
			DEVILX_R_CLASS_MEMBER(IColourUnitStateImp*,AlphaColour);
			DEVILX_R_CLASS_MEMBER(IColourUnitStateImp*,DiffuseColour);
			DEVILX_R_CLASS_MEMBER(IColourUnitStateImp*,SpecularColour);
			DEVILX_R_CLASS_MEMBER(IColourUnitStateImp*,EmissiveColour);
			DEVILX_R_CLASS_MEMBER(ITextureUnitStateImp*,DiffuseTexture);
			DEVILX_R_CLASS_MEMBER(ITextureUnitStateImp*,SpecularTexture);
			DEVILX_R_CLASS_MEMBER(ITextureUnitStateImp*,NormalTexture);
			DEVILX_R_CLASS_MEMBER(IFloatUnitStateImp*,MetallicValue);
			DEVILX_R_CLASS_MEMBER(IFloatUnitStateImp*,RoughnessValue);
			DEVILX_R_CLASS_MEMBER(IFloatUnitStateImp*,SpecularPowerValue);
			Bool mTransparentEnable;
			Float mAlphaTestValue;
		public:
			ISubEntityImp(const String & name,IEntityImp * object);
			Boolean isAlphaTestEnable()const
			{
				return mAlphaTestValue>0;
			}
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
			virtual Void setAmbientModel(IEnum::EMaterialAmbientModel model) override;
			virtual IEnum::EMaterialAmbientModel getAmbientModel() const override;
			virtual Void setDiffuseModel(IEnum::EMaterialDiffuseModel model) override;
			virtual IEnum::EMaterialDiffuseModel getDiffuseModel() const;
			virtual Void setSpecularModel(IEnum::EMaterialSpecularModel model) override;
			virtual IEnum::EMaterialSpecularModel getSpecularModel() const;
			virtual IColourUnitState * getAlphaColourUnitState() override;
			virtual IColourUnitState * getEmissiveColourUnitState() override;
			virtual IColourUnitState * getDiffuseColourUnitState() override;
			virtual IColourUnitState * getSpecularColourUnitState() override;
			virtual ITextureUnitState * getDiffuseTextureUnitState() override;
			virtual ITextureUnitState * getSpecularTextureUnitState() override;
			virtual ITextureUnitState * getNormalTextureUnitState() override;
			virtual IFloatUnitState * getMetallicUnitState() override;
			virtual IFloatUnitState * getRoughnessUnitState() override;
			virtual IFloatUnitState * getSpecularPowerUnitState() override;
			virtual Void setAlphaTestValue(Float alpha) override;
			virtual Float getAlphaTestValue() const override;
			virtual Void setTransparentEnable(Bool enable) override;
			virtual Bool getTransparentEnable() const override;
		protected:
			~ISubEntityImp();
		};
	}
}