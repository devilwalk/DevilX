#pragma once
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		class IQueryObjectImp
			:public IQueryObject
			,public TBaseObject<IQueryObjectImp>
			,public CMessageNotifier
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
			ISceneElementImp * mSceneElement;
			IGeometryUsageImp * mGeometryUsage;
			IGeometryImp * mGeometry;
			Bool mVisible;
		public:
			IQueryObjectImp(const String & name,ISceneImp * scene);
			~IQueryObjectImp();

			// Í¨¹ý IQueryObject ¼Ì³Ð
			virtual ISceneElement * queryInterface_ISceneElement() const override;
			virtual IGeometryUsage * queryInterface_IGeometryUsage() const override;
			virtual Void setGeometry(IGeometry * geometry) override;
			virtual IGeometry * getGeometry() const override;
			virtual Void setVisible(Bool visible) override;
			virtual Bool getVisible() const override;
		};
	}
}