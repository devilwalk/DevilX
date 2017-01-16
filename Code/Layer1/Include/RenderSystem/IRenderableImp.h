#pragma once
#include "IGeometryUsageImp.h"
#include "IMaterialImp.h"
#include "ISkyImp.h"
#include "Enum.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		class IRenderableObjectImp;
		class CRenderList;
		class IRenderableImp
			:public IRenderable
			,public CMessageNotifier
			,public CUserDataContainer
		{
		public:
			enum EMessage
			{
				EMessage_BeginGeometryChange,
				EMessage_EndGeometryChange,
				EMessage_BeginVisibleChange,
				EMessage_EndVisibleChange
			};
		protected:
			const String mName;
			IRenderableObjectImp * const mObject;
			IGeometryImp * mGeometry;
			IMaterialImp * mMaterial;
			IGeometryUsageImp * mGeometryUsage;
			Bool mVisible;
			mutable ISkyImp * mSky;
		public:
			IRenderableImp(const String & name,IRenderableObjectImp * object);
			virtual ~IRenderableImp();
			ISkyImp * getSky()const
			{
				return mSky;
			}
			// Inherited via IRenderable
			virtual ISky * queryInterface_ISky() const override;
			virtual const String & getName() const override;
			virtual IRenderableObject * getObject() const override;
			virtual IGeometryUsage * queryInterface_IGeometryUsage() const override;
			virtual IMaterial * queryInterface_IMaterial() const override;
			virtual Void setVisible(Bool visible) override;
			virtual Bool getVisible() const override;
			virtual Void setGeometry(IGeometry * geometry) override;
			virtual IGeometry * getGeometry() const override;
		};
	}
}