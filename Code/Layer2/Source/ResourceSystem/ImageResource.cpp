#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSResourceSystem;

NSDevilX::NSResourceSystem::CImageResource::CImageResource(const String & name,const String & file)
	:CFileResource(name,file)
	,mImage(nullptr)
{
	mImage=DEVILX_NEW CImage;
}

NSDevilX::NSResourceSystem::CImageResource::~CImageResource()
{
	CFileResource::~CFileResource();
	DEVILX_DELETE(mImage);
}

IEnum::EResourceType NSDevilX::NSResourceSystem::CImageResource::getType() const
{
	return IEnum::EResourceType_Image;
}

Boolean NSDevilX::NSResourceSystem::CImageResource::_loadImpMT()
{
	mImage->load(CFileStream(getFileName()));
	return true;
}
