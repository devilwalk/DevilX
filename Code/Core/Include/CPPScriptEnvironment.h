#pragma once
namespace NSDevilX
{
	namespace NSCore
	{
		class CCPPScriptEnvironment
			:public TBaseObject<CCPPScriptEnvironment>
		{
		protected:
		public:
			CCPPScriptEnvironment();
			~CCPPScriptEnvironment();

			Void compile();
		};
	}
}