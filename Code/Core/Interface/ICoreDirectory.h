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
			virtual std::string getPath(const std::string & relativePath)const=0;
			virtual IDirectory * createSubDirectory(const std::string & name)=0;
			virtual size_t getNumSubDirectory()const=0;
			virtual IDirectory * getSubDirectory(size_t index)const=0;
			virtual IDirectory * getSubDirectory(const std::string & name)const=0;
			virtual IFile * createFile(const std::string & name)=0;
			virtual size_t getNumFile()const=0;
			virtual IFile * getFile(size_t index)const=0;
			virtual IFile * getFile(const std::string & name)const=0;
		};
	}
}