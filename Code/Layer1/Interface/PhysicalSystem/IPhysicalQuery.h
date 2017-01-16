#pragma once
#include "IPhysicalEnum.h"
#include "IPhysicalQueryResultReceiver.h"
namespace NSDevilX
{
	namespace NSPhysicalSystem
	{
		class IRayQuery
		{
		protected:
			virtual ~IRayQuery(){}
		public:
			virtual Void setRay(const CRay & ray)=0;
			virtual const CRay & getRay()const=0;
		};
		class IQuery
		{
		protected:
			virtual ~IQuery(){}
		public:
			virtual IRayQuery * queryInterface_IRayQuery()const=0;
			virtual const String & getName()const=0;
			virtual IEnum::EQueryType getType()const=0;
			virtual Void addResultType(IEnum::EQueryResultType type)=0;
			virtual Void removeResultType(IEnum::EQueryResultType type)=0;
			virtual Boolean hasResultType(IEnum::EQueryResultType type)const=0;
			virtual Void setResultReceiver(IQueryResultReceiver * receiver)=0;
			virtual IQueryResultReceiver * getResultReceiver()const=0;
			virtual Void execute()=0;
		};
	}
}