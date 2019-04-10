#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSCore;
using namespace NSDirectX;
using namespace NSVersion11;

NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceImp::IGADeviceImp()
	:mInternal(nullptr)
	,mImmediateContext(nullptr)
{
	UINT flags=0;
#if DEVILX_DEBUG
	flags|=D3D11_CREATE_DEVICE_DEBUG;
#endif
	D3D_FEATURE_LEVEL levels[]={D3D_FEATURE_LEVEL_11_1};
	D3D11CreateDevice(NULL,D3D_DRIVER_TYPE_HARDWARE,NULL,flags,levels,_countof(levels),D3D11_SDK_VERSION,&mInternal,levels,&mImmediateContext);
}

NSDevilX::NSCore::NSDirectX::NSVersion11::IGADeviceImp::~IGADeviceImp()
{
	DEVILX_COM_SAFE_RELEASE(mImmediateContext);
	DEVILX_COM_SAFE_RELEASE(mInternal);
}