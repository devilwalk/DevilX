#pragma once
#include "ISceneElementImp.h"
#include "IGeometryImp.h"
#include "IColourUnitStateImp.h"
#include "ITextureUnitStateImp.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		class ISkyImp
			:public ISky
			,public TBaseObject<ISkyImp>
			,public CMessageNotifier
		{
			enum EMessage
			{
				EMessage_BeginGeometryChange,
				EMessage_EndGeometryChange,
				EMessage_BeginVisibleChange,
				EMessage_EndVisibleChange,
				EMessage_BeginColourUnitStateCreate,
				EMessage_EndColourUnitStateCreate,
				EMessage_BeginTextureUnitStateCreate,
				EMessage_EndTextureUnitStateCreate
			};
		protected:
			ISceneElementImp * mSceneElement;
			IGeometryImp * mGeometry;
			Bool mVisible;
			Int32 mOrder;
			IColourUnitStateImp * mColourUnitState;
			ITextureUnitStateImp * mTextureUnitState;
		public:
			ISkyImp(const String & name,ISceneImp * scene);
			~ISkyImp();

			// Inherited via ISky
			virtual ISceneElement * queryInterface_ISceneElement() const override;
			virtual Void setVisible(Bool visible) override;
			virtual Bool getVisible() const override;
			virtual Void setGeometry(IGeometry * geometry) override;
			virtual IGeometry * getGeometry() const override;
			virtual Void setOrder(Int32 order) override;
			virtual Int32 getOrder() const override;
			virtual IColourUnitState * getColourUnitState() override;
			virtual ITextureUnitState * getTextureUnitState() override;
		};
	}
}