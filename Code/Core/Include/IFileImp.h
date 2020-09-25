#pragma once
#include "UTFString.h"
namespace NSDevilX
{
	namespace NSCore
	{
		class IDirectoryImp;
		class IFileImp
			:public TMemoryAllocatorObject<IFileImp>
			,public IFile
		{
		protected:
			const CUTF8String mPath;
		public:
			IFileImp(const CUTF8String & path);
			~IFileImp();

			virtual IDirectory * getDirectory() const override;


			virtual NSDevilX::CUTF8String getPath() const override;


			virtual SizeT getSize() const override;


			virtual IFileProcesser * retrieveProcesser() override;


			virtual void releaseProcesser(IFileProcesser * processer) override;

		};
	}
}