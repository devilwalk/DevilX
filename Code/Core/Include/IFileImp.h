#pragma once
namespace NSDevilX
{
	namespace NSCore
	{
		class IDirectoryImp;
		class IFileImp
			:public TBaseObject<IFileImp>
			,public IFile
		{
		protected:
			const CUTF8String mPath;
		public:
			IFileImp(const CUTF8String & path);
			~IFileImp();

			virtual IDirectory * getDirectory() const override;


			virtual std::string getPath() const override;


			virtual size_t getSize() const override;


			virtual IFileProcesser * retrieveProcesser() override;


			virtual void releaseProcesser(IFileProcesser * processer) override;

		};
	}
}