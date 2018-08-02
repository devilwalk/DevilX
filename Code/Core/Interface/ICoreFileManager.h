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
			IDirectory * createOrRetrieveDirectory(const CUTF8String & path);
			IDirectory * getDirectory(const CUTF8String & path)const;
			IFile * createOrRetrieveFile(const CUTF8String & path);
			IFile * getFile(const CUTF8String & path);
		};
	}
}