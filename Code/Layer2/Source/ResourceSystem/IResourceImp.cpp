#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSResourceSystem;

NSDevilX::NSResourceSystem::IResourceImp::IResourceImp(const String & name)
	:mName(name)
{}

NSDevilX::NSResourceSystem::IResourceImp::~IResourceImp()
{
}

const String & NSDevilX::NSResourceSystem::IResourceImp::getName() const
{
	// TODO: 在此处插入 return 语句
	return mName;
}

Void NSDevilX::NSResourceSystem::IResourceImp::load(ILoadCallback * callback,Bool sync)
{
	struct SCallbackWrapper
		:public CResource::SLoadCallback
		,public TBaseObject<SCallbackWrapper>
	{
		ILoadCallback * const mCallback;
		SCallbackWrapper(ILoadCallback * callback)
			:mCallback(callback)
		{}
		Void onLoaded(CResource * res) override final
		{
			mCallback->onLoaded(static_cast<IResourceImp*>(res));
			DEVILX_DELETE(this);
		}
	};
	CResource::load(DEVILX_NEW SCallbackWrapper(callback),sync);
}

Boolean NSDevilX::NSResourceSystem::IResourceImp::isLoaded() const
{
	return CResource::isLoaded();
}

NSDevilX::NSResourceSystem::CFileResource::CFileResource(const String & name,const String & file)
	:IResourceImp(name)
	,mFile(file)
{
}

NSDevilX::NSResourceSystem::CFileResource::~CFileResource()
{
}
