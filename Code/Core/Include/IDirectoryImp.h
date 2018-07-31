#pragma once
#include "IFileImp.h"
namespace NSDevilX
{
	namespace NSCore
	{
		class IDirectoryImp
			:public TBaseObject<IDirectoryImp>
			,public IDirectory
		{
		protected:
			const CUTF8String mPath;
		public:
			IDirectoryImp(const CUTF8String & path);
			~IDirectoryImp();

			// Í¨¹ý IDirectory ¼Ì³Ð
			virtual IDirectory * getParent() const override;
			virtual std::string getPath() const override;
			virtual IDirectory * createSubDirectory(const std::string & name) override;
			virtual size_t getNumSubDirectory() const override;
			virtual IDirectory * getSubDirectory(size_t index) const override;
			virtual IDirectory * getSubDirectory(const std::string & name) const override;
			virtual IFile * createFile(const std::string & name) override;
			virtual size_t getNumFile() const override;
			virtual IFile * getFile(size_t index) const override;
			virtual IFile * getFile(const std::string & name) const override;
		};
	}
}