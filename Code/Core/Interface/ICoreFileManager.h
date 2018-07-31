#pragma once
#include "ICoreDirectory.h"
#include "ICoreFile.h"
namespace NSDevilX
{
	namespace NSCore
	{
		class DLLAPI IFileManager
		{
		protected:
			~IFileManager();
		public:
			IDirectory * getRootDirectory()const;
			IDirectory * getApplicationDirectory()const;
			IDirectory * createOrRetrieveDirectory(const std::string & path);
			IDirectory * getDirectory(const std::string & path)const;
			IFile * createOrRetrieveFile(const std::string & path);
			IFile * getFile(const std::string & path);
		};
	}
}