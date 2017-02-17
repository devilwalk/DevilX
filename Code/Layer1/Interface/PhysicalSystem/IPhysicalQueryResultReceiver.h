#pragma once
#include "IPhysicalEnum.h"
#include "IPhysicalSubEntitiy.h"
namespace NSDevilX
{
	namespace NSPhysicalSystem
	{
		class IQueryResultReceiver
		{
		protected:
			virtual ~IQueryResultReceiver(){}
		public:
			virtual Void addHitSubEntity(ISubEntity * subEntity)=0;
			virtual Void addHitPoint(const CFloat3 & position,const CFloat3 & normal)=0;
		};
	}
}