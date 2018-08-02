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
			virtual NSDevilX::CUTF8String getPath() const override;
			virtual IDirectory * createSubDirectory(const NSDevilX::CUTF8String & name) override;
			virtual SizeT getNumSubDirectory() const override;
			virtual IDirectory * getSubDirectory(SizeT index) const override;
			virtual IDirectory * getSubDirectory(const NSDevilX::CUTF8String & name) const override;
			virtual IFile * createFile(const NSDevilX::CUTF8String & name) override;
			virtual SizeT getNumFile() const override;
			virtual IFile * getFile(SizeT index) const override;
			virtual IFile * getFile(const NSDevilX::CUTF8String & name) const override;
		};
	}
}