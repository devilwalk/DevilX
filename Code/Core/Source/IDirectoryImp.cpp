#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSCore;

NSDevilX::NSCore::IDirectoryImp::IDirectoryImp(const CUTF8String & path)
	:mPath(path)
{
}

NSDevilX::NSCore::IDirectoryImp::~IDirectoryImp()
{
}

IDirectory * NSDevilX::NSCore::IDirectoryImp::getParent() const
{
	return CFileManager::getSingleton().getDirectory(CUTF8String(CPathUtility::getParent(mPath)));
}

NSDevilX::CUTF8String NSDevilX::NSCore::IDirectoryImp::getPath() const
{
	return mPath;
}

IDirectory * NSDevilX::NSCore::IDirectoryImp::createSubDirectory(const NSDevilX::CUTF8String & name)
{
	return CFileManager::getSingleton().createDirectory(CUTF8String(mPath+"/"+name));
}

size_t NSDevilX::NSCore::IDirectoryImp::getNumSubDirectory() const
{
	return CFileManager::getSingleton().getNumSubDirectory(mPath);
}

IDirectory * NSDevilX::NSCore::IDirectoryImp::getSubDirectory(size_t index) const
{
	return CFileManager::getSingleton().getSubDirectory(mPath,index);
}

IDirectory * NSDevilX::NSCore::IDirectoryImp::getSubDirectory(const NSDevilX::CUTF8String & name) const
{
	auto utf8_name=CUTF8String(&name[0],name.size());
	return CFileManager::getSingleton().getDirectory(CUTF8String(mPath+"/"+utf8_name));
}

IFile * NSDevilX::NSCore::IDirectoryImp::createFile(const NSDevilX::CUTF8String & name)
{
	auto utf8_name=CUTF8String(&name[0],name.size());
	return CFileManager::getSingleton().createFile(CUTF8String(mPath+"/"+utf8_name));
}

size_t NSDevilX::NSCore::IDirectoryImp::getNumFile() const
{
	return CFileManager::getSingleton().getNumFile(mPath);
}

IFile * NSDevilX::NSCore::IDirectoryImp::getFile(size_t index) const
{
	return CFileManager::getSingleton().getFile(mPath,index);
}

IFile * NSDevilX::NSCore::IDirectoryImp::getFile(const NSDevilX::CUTF8String & name) const
{
	auto utf8_name=CUTF8String(&name[0],name.size());
	return CFileManager::getSingleton().getFile(CUTF8String(mPath+"/"+utf8_name));
}
