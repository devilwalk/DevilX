#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSResourceSystem;

NSDevilX::NSResourceSystem::CCommonFileResource::CCommonFileResource(const String & name,const String & filename)
	:CFileResource(name,filename)
{
}

NSDevilX::NSResourceSystem::CCommonFileResource::~CCommonFileResource()
{
}

IEnum::EResourceType NSDevilX::NSResourceSystem::CCommonFileResource::getType() const
{
	return IEnum::EResourceType_CommonFile;
}

Boolean NSDevilX::NSResourceSystem::CCommonFileResource::_loadImpMT()
{
	mFileStream.load(getFileName());
	return true;
}
