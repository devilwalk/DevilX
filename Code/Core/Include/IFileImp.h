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
		};
	}
}