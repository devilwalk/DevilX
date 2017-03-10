#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSResourceSystem;

NSDevilX::NSResourceSystem::IResourceImp::IResourceImp(const String & name,const String & file)
	:mName(name)
	,mFile(file)
{}

NSDevilX::NSResourceSystem::IResourceImp::~IResourceImp()
{}

const String & NSDevilX::NSResourceSystem::IResourceImp::getName() const
{
	// TODO: 在此处插入 return 语句
	return mName;
}

const String & NSDevilX::NSResourceSystem::IResourceImp::getFileName() const
{
	// TODO: 在此处插入 return 语句
	return mFile;
}