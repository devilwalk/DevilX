#pragma once
#include "ICoreCPPScriptEnvironment.h"
namespace NSDevilX
{
	namespace NSCore
	{
		class IScriptManager
		{
		protected:
			virtual ~IScriptManager(){}
		public:
			virtual ICPPScriptEnvironment * createCPPEnvironment()=0;
			virtual Void destroyCPPEnvironment(ICPPScriptEnvironment * environment)=0;
			virtual Void update()=0;
		};
	}
}