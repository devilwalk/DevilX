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
	auto && parent_path=CPathUtility::getParent(mPath);
	return CFileManager::getSingleton().getDirectory(parent_path);
}

std::string NSDevilX::NSCore::IDirectoryImp::getPath() const
{
	return mPath.toString().c_str();
}

IDirectory * NSDevilX::NSCore::IDirectoryImp::createSubDirectory(const std::string & name)
{
	auto utf8_name=CUTF8String(&name[0],name.size());
	return CFileManager::getSingleton().createDirectory(CUTF8String(mPath+"/"+utf8_name));
}

size_t NSDevilX::NSCore::IDirectoryImp::getNumSubDirectory() const
{
	return CFileManager::getSingleton().getNumSubDirectory(mPath);
}

IDirectory * NSDevilX::NSCore::IDirectoryImp::getSubDirectory(size_t index) const
{
	return CFileManager::getSingleton().getSubDirectory(mPath,index);
}

IDirectory * NSDevilX::NSCore::IDirectoryImp::getSubDirectory(const std::string & name) const
{
	auto utf8_name=CUTF8String(&name[0],name.size());
	return CFileManager::getSingleton().getDirectory(CUTF8String(mPath+"/"+utf8_name));
}

IFile * NSDevilX::NSCore::IDirectoryImp::createFile(const std::string & name)
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

IFile * NSDevilX::NSCore::IDirectoryImp::getFile(const std::string & name) const
{
	auto utf8_name=CUTF8String(&name[0],name.size());
	return CFileManager::getSingleton().getFile(CUTF8String(mPath+"/"+utf8_name));
}
