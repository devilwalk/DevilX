#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSCore;
using namespace NSOpenGL;

IGADeviceImp::IGADeviceImp()
{
}

IGADeviceImp::~IGADeviceImp()
{

}

IGADeviceContext * NSDevilX::NSCore::NSOpenGL::IGADeviceImp::getImmediateContext() const
{
	return const_cast<IGADeviceImp*>(this);
}

IGADeviceContext * NSDevilX::NSCore::NSOpenGL::IGADeviceImp::createDeferredContext()
{
	return nullptr;
}