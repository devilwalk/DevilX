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
