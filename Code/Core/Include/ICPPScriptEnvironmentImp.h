#pragma once
namespace NSDevilX
{
	namespace NSCore
	{
		class ICPPScriptEnvironmentImp
			:public ICPPScriptEnvironment
			,public TMemoryAllocatorObject<ICPPScriptEnvironmentImp>
		{
		protected:
		public:
			ICPPScriptEnvironmentImp();
			~ICPPScriptEnvironmentImp();
		};
	}
}