#pragma once
namespace NSDevilX
{
	namespace NSCore
	{
		class ICPPScriptEnvironment
		{
		protected:
			virtual ~ICPPScriptEnvironment(){}
		public:
			virtual Void addIncludeDirectory(const CUTF8String & directory)=0;
			virtual Void addLibraryDirectory(const CUTF8String & directory)=0;
			virtual Void addFile(const CUTF8String & file)=0;
			virtual Boolean compile()=0;
			virtual Void update()=0;
		};
	}
}