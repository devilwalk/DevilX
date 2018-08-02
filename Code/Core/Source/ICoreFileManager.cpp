#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSCore;

NSDevilX::NSCore::IFileManager::~IFileManager()
{
}

IDirectory * NSDevilX::NSCore::IFileManager::getRootDirectory() const
{
	return nullptr;
}

IDirectory * NSDevilX::NSCore::IFileManager::getApplicationDirectory() const
{
	return nullptr;
}

NSDevilX::NSCore::IDirectory * NSDevilX::NSCore::IFileManager::createOrRetrieveDirectory(const NSDevilX::CUTF8String & path)
{
	auto utf_path=CUTF8String(&path[0],path.size());
	auto ret=CFileManager::getSingleton().getDirectory(utf_path);
	if(!ret)
	{
		ret=CFileManager::getSingleton().createDirectory(utf_path);
	}
	return ret;
}

NSDevilX::NSCore::IDirectory * NSDevilX::NSCore::IFileManager::getDirectory(const NSDevilX::CUTF8String & path) const
{
	auto utf_path=CUTF8String(&path[0],path.size());
	return CFileManager::getSingleton().getDirectory(utf_path);
}

NSDevilX::NSCore::IFile * NSDevilX::NSCore::IFileManager::createOrRetrieveFile(const NSDevilX::CUTF8String & path)
{
	auto utf_path=CUTF8String(&path[0],path.size());
	auto ret=CFileManager::getSingleton().getFile(utf_path);
	if(!ret)
	{
		ret=CFileManager::getSingleton().createFile(utf_path);
	}
	return ret;
}

NSDevilX::NSCore::IFile * NSDevilX::NSCore::IFileManager::getFile(const NSDevilX::CUTF8String & path)
{
	auto utf_path=CUTF8String(&path[0],path.size());
	return CFileManager::getSingleton().getFile(utf_path);
}
