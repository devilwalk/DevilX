#pragma once
namespace NSDevilX
{
	namespace NSCore
	{
		class ICPPScriptEnvironmentImp
			:public ICPPScriptEnvironment
			,public TBaseObject<ICPPScriptEnvironmentImp>
		{
		protected:
		public:
			ICPPScriptEnvironmentImp();
			~ICPPScriptEnvironmentImp();
		};
	}
}