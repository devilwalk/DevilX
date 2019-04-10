#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSCore;
using namespace NSDirectX;

NSDevilX::NSCore::NSDirectX::IGASwapChainImp::IGASwapChainImp(IUnknown * dev,DXGI_SWAP_CHAIN_DESC && desc)
{
	CGAManager::getSingleton().getFactory()->CreateSwapChain(dev,&desc,&mInternal);
}

NSDevilX::NSCore::NSDirectX::IGASwapChainImp::~IGASwapChainImp()
{
}

Void NSDevilX::NSCore::NSDirectX::IGASwapChainImp::present()
{
	mInternal->Present(0,0);
}
