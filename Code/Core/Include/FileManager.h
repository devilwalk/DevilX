#pragma once
#include "IFileImp.h"
#include "IDirectoryImp.h"
namespace NSDevilX
{
	namespace NSCore
	{
		class CFileManager
			:public TSingletonEx<CFileManager>
			,public TMemoryAllocatorObject<CFileManager>
		{
		protected:
			TResourcePtrMap<WString,IDirectoryImp> mDirectories;
			TResourcePtrMap<WString,IFileImp> mFiles;
		public:
			CFileManager();
			~CFileManager();

			IDirectoryImp * createDirectory(const WString & path);
			IDirectoryImp * getDirectory(const WString & path);
			Void deleteDirectory(const WString & path);
			SizeT getNumSubDirectory(const WString & path)const;
			WString getSubDirectoryName(const WString & path,SizeT subIndex)const;
			IDirectoryImp * getSubDirectory(const WString & path,SizeT subIndex);
			IFileImp * createFile(const WString & path);
			IFileImp * getFile(const WString & path);
			Void deleteFile(const WString & path);
			SizeT getNumFile(const WString & path)const;
			WString getFileName(const WString & path,SizeT index)const;
			IFileImp * getFile(const WString & path,SizeT index);
		protected:
			Boolean _findDirectory(const WString & path)const;
			Void _findSubDirectories(const WString & path,OUT TVector<WString> & outSubDirectorys)const;
			Boolean _findFile(const WString & path)const;
			Void _findFiles(const WString & path,OUT TVector<WString> & outFiles)const;
		};
	}
}