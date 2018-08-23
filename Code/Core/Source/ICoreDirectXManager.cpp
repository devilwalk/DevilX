#include "Precompiler.h"
#if DEVILX_OPERATING_SYSTEM==DEVILX_OPERATING_SYSTEM_WINDOWS
using namespace NSDevilX;
using namespace NSCore;

NSDevilX::NSCore::IDirectXManager::~IDirectXManager()
{
}

IDXGIFactory * NSDevilX::NSCore::IDirectXManager::getDXGIFactory() const
{
	return CDirectXManager::getSingleton().getDXGIFactory();
}

#endif
