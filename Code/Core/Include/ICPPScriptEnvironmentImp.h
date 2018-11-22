#pragma once
namespace NSDevilX
{
	namespace NSCore
	{
		class ICPPScriptEnvironmentImp
			:public ICPPScriptEnvironment
			,public TBaseObject<INetworkConnectionImp>
		{
		protected:
		public:
			ICPPScriptEnvironmentImp();
			~ICPPScriptEnvironmentImp();
		};
	}
}