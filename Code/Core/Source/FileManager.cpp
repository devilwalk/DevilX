#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSCore;

NSDevilX::NSCore::CFileManager::CFileManager()
{
}

NSDevilX::NSCore::CFileManager::~CFileManager()
{
}

IDirectoryImp * NSDevilX::NSCore::CFileManager::createDirectory(const WString & path)
{
#if DEVILX_OPERATING_SYSTEM==DEVILX_OPERATING_SYSTEM_WINDOWS
	if(!::CreateDirectoryW(path.c_str(),nullptr))
	{
		auto error=::GetLastError();
#ifdef _MSC_VER
		TString error_msg;
		error_msg.resize(4096);
		FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM,nullptr,error,LANG_USER_DEFAULT,&error_msg[0],static_cast<DWORD>(error_msg.size()),nullptr);
		OutputDebugString(error_msg.c_str());
#endif
		return nullptr;
	}
#else
	String path_mbs;
	path_mbs.resize(path.size()*2+1);
	wcstombs(&path_mbs[0],path.c_str(),path_mbs.size());
	mkdir(path_mbs.c_str());
#endif
	auto ret=new IDirectoryImp(CUTF16String(path));
	mDirectories[path]=ret;
	return ret;
}

IDirectoryImp * NSDevilX::NSCore::CFileManager::getDirectory(const WString & path)
{
	auto ret=mDirectories.get(path);
	if(!ret)
	{
		if(_findDirectory(path))
		{
			ret=new IDirectoryImp(CUTF16String(path));
			mDirectories[path]=ret;
		}
	}
	return ret;
}

Void NSDevilX::NSCore::CFileManager::deleteDirectory(const WString & path)
{
#if DEVILX_OPERATING_SYSTEM==DEVILX_OPERATING_SYSTEM_WINDOWS
	if(!::RemoveDirectoryW(path.c_str()))
	{
		auto error=::GetLastError();
#ifdef _MSC_VER
		TString error_msg;
		error_msg.resize(4096);
		FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM,nullptr,error,LANG_USER_DEFAULT,&error_msg[0],static_cast<DWORD>(error_msg.size()),nullptr);
		OutputDebugString(error_msg.c_str());
		return;
#endif
	}
#else
	String path_mbs;
	path_mbs.resize(path.size()*2+1);
	wcstombs(&path_mbs[0],path.c_str(),path_mbs.size());
	rmdir(path_mbs.c_str());
#endif
	mDirectories.destroy(path);
}

SizeT NSDevilX::NSCore::CFileManager::getNumSubDirectory(const WString & path) const
{
	TVector<WString> sub_directories;
	_findSubDirectories(path,sub_directories);
	return sub_directories.size();
}

WString NSDevilX::NSCore::CFileManager::getSubDirectoryName(const WString & path,SizeT subIndex) const
{
	TVector<WString> sub_directories;
	_findSubDirectories(path,sub_directories);
	return sub_directories[subIndex];
}

IDirectoryImp * NSDevilX::NSCore::CFileManager::getSubDirectory(const WString & path,SizeT subIndex)
{
	auto sub_path=path+L"/"+getSubDirectoryName(path,subIndex);
	return getDirectory(sub_path);
}

NSDevilX::NSCore::IFileImp * NSDevilX::NSCore::CFileManager::createFile(const WString & path)
{
#if DEVILX_OPERATING_SYSTEM == DEVILX_OPERATING_SYSTEM_WINDOWS
	auto file_handle=::CreateFileW(path.c_str(),GENERIC_WRITE,0,nullptr,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,nullptr);
	if(INVALID_HANDLE_VALUE==file_handle)
	{
		auto error=::GetLastError();
#ifdef _MSC_VER
		TString error_msg;
		error_msg.resize(4096);
		FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM,nullptr,error,LANG_USER_DEFAULT,&error_msg[0],static_cast<DWORD>(error_msg.size()),nullptr);
		OutputDebugString(error_msg.c_str());
		return nullptr;
#endif
	}
	else
	{
		CloseHandle(file_handle);
	}
#endif
	auto ret=new IFileImp(CUTF16String(path));
	mFiles[path]=ret;
	return ret;
}

IFileImp * NSDevilX::NSCore::CFileManager::getFile(const WString & path)
{
	auto ret=mFiles.get(path);
	if(!ret)
	{
		if(_findFile(path))
		{
			ret=new IFileImp(CUTF16String(path));
			mFiles[path]=ret;
		}
	}
	return ret;
}

NSDevilX::Void NSDevilX::NSCore::CFileManager::deleteFile(const WString & path)
{
#if DEVILX_OPERATING_SYSTEM == DEVILX_OPERATING_SYSTEM_WINDOWS
	if(!DeleteFileW(path.c_str()))
	{
		auto error=::GetLastError();
#ifdef _MSC_VER
		TString error_msg;
		error_msg.resize(4096);
		FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM,nullptr,error,LANG_USER_DEFAULT,&error_msg[0],static_cast<DWORD>(error_msg.size()),nullptr);
		OutputDebugString(error_msg.c_str());
		return;
#endif
	}
#endif
	mFiles.destroy(path);
}

NSDevilX::SizeT NSDevilX::NSCore::CFileManager::getNumFile(const WString & path) const
{
	TVector<WString> files;
	_findFiles(path,files);
	return files.size();
}

NSDevilX::NSCore::WString NSDevilX::NSCore::CFileManager::getFileName(const WString & path,SizeT index) const
{
	TVector<WString> files;
	_findFiles(path,files);
	return files[index];
}

NSDevilX::NSCore::IFileImp * NSDevilX::NSCore::CFileManager::getFile(const WString & path,SizeT index)
{
	auto sub_path=path+L"/"+getFileName(path,index);
	return getFile(sub_path);
}

Boolean NSDevilX::NSCore::CFileManager::_findDirectory(const WString & path) const
{
	Boolean ret=false;
#if DEVILX_OPERATING_SYSTEM==DEVILX_OPERATING_SYSTEM_WINDOWS
	::WIN32_FIND_DATAW find_data;
	auto handle=::FindFirstFileW(path.c_str(),&find_data);
	ret=(INVALID_HANDLE_VALUE!=handle)&&(find_data.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY);
#endif
	return ret;
}

Void NSDevilX::NSCore::CFileManager::_findSubDirectories(const WString & path,OUT TVector<WString>& outSubDirectorys) const
{
#if DEVILX_OPERATING_SYSTEM==DEVILX_OPERATING_SYSTEM_WINDOWS
	::WIN32_FIND_DATAW find_data;
	auto handle=::FindFirstFileW((path+L"/*").c_str(),&find_data);
	if(INVALID_HANDLE_VALUE!=handle)
	{
		if(find_data.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY)
		{
			outSubDirectorys.push_back(find_data.cFileName);
		}
		while(::FindNextFileW(handle,&find_data))
		{
			if(find_data.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY)
			{
				outSubDirectorys.push_back(find_data.cFileName);
			}
		}
	}
#endif
}

NSDevilX::Boolean NSDevilX::NSCore::CFileManager::_findFile(const WString & path) const
{
	Boolean ret=false;
#if DEVILX_OPERATING_SYSTEM==DEVILX_OPERATING_SYSTEM_WINDOWS
	::WIN32_FIND_DATAW find_data;
	auto handle=::FindFirstFileW(path.c_str(),&find_data);
	ret=(INVALID_HANDLE_VALUE!=handle)&&(!(find_data.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY));
#endif
	return ret;
}

NSDevilX::Void NSDevilX::NSCore::CFileManager::_findFiles(const WString & path,OUT TVector<WString> & outFiles) const
{
#if DEVILX_OPERATING_SYSTEM==DEVILX_OPERATING_SYSTEM_WINDOWS
	::WIN32_FIND_DATAW find_data;
	auto handle=::FindFirstFileW((path+L"/*").c_str(),&find_data);
	if(INVALID_HANDLE_VALUE!=handle)
	{
		if(!(find_data.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY))
		{
			outFiles.push_back(find_data.cFileName);
		}
		while(::FindNextFileW(handle,&find_data))
		{
			if(!(find_data.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY))
			{
				outFiles.push_back(find_data.cFileName);
			}
		}
	}
#endif
}
