#pragma once
#include "ICoreFileProcesser.h"
namespace NSDevilX
{
	namespace NSCore
	{
		class IDirectory;
		class IFile
		{
		protected:
			virtual ~IFile(){}
		public:
			virtual IDirectory * getDirectory()const=0;
			virtual CUTF8String getPath()const=0;
			virtual SizeT getSize()const=0;
			virtual IFileProcesser * retrieveProcesser()=0;
			virtual void releaseProcesser(IFileProcesser * processer)=0;
		};
	}
}