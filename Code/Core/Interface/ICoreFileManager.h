#pragma once
namespace NSDevilX
{
	namespace NSCore
	{
		class DLLAPI IFileManager
		{
		protected:
			~IFileManager(){}
		public:
			const char * getCurrentDirectory();
			const char * getApplicationDirectory();
			const char * getSystemFontsDirectory();
		};
	}
}