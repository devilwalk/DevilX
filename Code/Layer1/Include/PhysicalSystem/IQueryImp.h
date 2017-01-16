#pragma once
namespace NSDevilX
{
	namespace NSPhysicalSystem
	{
		class ISceneImp;
		class IQueryImp
			:public IQuery
			,public CMessageNotifier
		{
		public:
			enum EMessage
			{
				EMessage_Execute
			};
		protected:
			const String mName;
			ISceneImp * const mScene;
			UInt32 mResultMask;
			IQueryResultReceiver * mResultReceiver;
		public:
			IQueryImp(const String & name,ISceneImp * scene);
			virtual ~IQueryImp();

			// Inherited via IQuery
			virtual IRayQuery * queryInterface_IRayQuery() const override;
			virtual const String & getName() const override;
			virtual Void addResultType(IEnum::EQueryResultType type) override;
			virtual Void removeResultType(IEnum::EQueryResultType type) override;
			virtual Boolean hasResultType(IEnum::EQueryResultType type) const override;
			virtual Void setResultReceiver(IQueryResultReceiver * receiver) override;
			virtual IQueryResultReceiver * getResultReceiver() const override;
			virtual Void execute() override;
		};
		class IRayQueryImp
			:public IRayQuery
			,public IQueryImp
			,public TBaseObject<IRayQueryImp>
		{
		protected:
			CRay mRay;
		public:
			IRayQueryImp(const String & name,ISceneImp * scene);
			~IRayQueryImp();

			// Inherited via IQueryImp
			virtual IRayQuery * queryInterface_IRayQuery() const override;
			virtual IEnum::EQueryType getType() const override;

			// Inherited via IRayQuery
			virtual Void setRay(const CRay & ray) override;
			virtual const CRay & getRay() const override;
		};
	}
}