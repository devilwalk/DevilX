#include "Precompiler.h"
#if DEVILX_OPERATING_SYSTEM==DEVILX_OPERATING_SYSTEM_WINDOWS
using namespace NSDevilX;
using namespace NSCore;

NSDevilX::NSCore::CDirectXManager::CDirectXManager()
	:mDXGIFactory(nullptr)
{
	VoidPtr factory=nullptr;
	if(FAILED(CreateDXGIFactory1(__uuidof(IDXGIFactory1),&factory)))
	{
		if(FAILED(CreateDXGIFactory(__uuidof(IDXGIFactory),&factory)))
		{
		}
		else
			mDXGIFactory=static_cast<IDXGIFactory*>(factory);
	}
	else
		mDXGIFactory=static_cast<IDXGIFactory1*>(factory);
}

NSDevilX::NSCore::CDirectXManager::~CDirectXManager()
{
	mDXGIFactory->Release();
}
#endif