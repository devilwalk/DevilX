#pragma once
namespace NSDevilX
{
	namespace NSCore
	{
		class CCPPScriptEnvironment
			:public TMemoryAllocatorObject<CCPPScriptEnvironment>
		{
		protected:
		public:
			CCPPScriptEnvironment();
			~CCPPScriptEnvironment();

			Void compile();
		};
	}
}