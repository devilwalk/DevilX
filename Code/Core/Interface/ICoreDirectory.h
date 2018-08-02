#pragma once
#include "ICoreFile.h"
namespace NSDevilX
{
	namespace NSCore
	{
		class IDirectory
		{
		protected:
			virtual ~IDirectory(){}
		public:
			virtual IDirectory * getParent()const=0;
			virtual CUTF8String getPath()const=0;
			virtual IDirectory * createSubDirectory(const CUTF8String & name)=0;
			virtual size_t getNumSubDirectory()const=0;
			virtual IDirectory * getSubDirectory(size_t index)const=0;
			virtual IDirectory * getSubDirectory(const CUTF8String & name)const=0;
			virtual IFile * createFile(const CUTF8String & name)=0;
			virtual size_t getNumFile()const=0;
			virtual IFile * getFile(SizeT index)const=0;
			virtual IFile * getFile(const CUTF8String & name)const=0;
		};
	}
}