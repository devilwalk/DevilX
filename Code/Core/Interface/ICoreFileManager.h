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
		};
	}
}