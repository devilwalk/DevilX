#pragma once
namespace NSDevilX
{
	namespace NSPhysicalSystem
	{
		class IQueryMark
		{
		protected:
			virtual ~IQueryMark(){}
		public:
			virtual IUserDataContainer * queryInterface_IUserDataContainer()const=0;
		};
	}
}