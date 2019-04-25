#pragma once
#include "GAObject.h"
namespace NSDevilX
{
	namespace NSCore
	{
		class IGAResourceImp
			:public IGAResource
			,virtual public CGAObject
		{
		public:
			IGAResourceImp();
			virtual ~IGAResourceImp();
		};
		template<class TInterface>
		class TGAResourceImp
			:public TInterface
			,virtual public IGAResourceImp
		{
		public:
			TGAResourceImp()
			{
			}
			virtual ~TGAResourceImp()
			{
			}

			virtual IGAResource* queryInterface_IGAResource()override
			{
				return this;
			}
		};
	}
}