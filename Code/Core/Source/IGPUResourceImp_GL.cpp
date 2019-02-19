#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSCore;
using namespace NSGL;

NSDevilX::NSCore::NSGL::IGPUResourceImp::IGPUResourceImp()
	:mInternal(0)
{

}

NSDevilX::NSCore::NSGL::IGPUResourceImp::~IGPUResourceImp()
{
	mInternal=0;
}

NSDevilX::NSCore::NSGL::IGPUBufferImp::IGPUBufferImp()
{
	glCreateBuffers(1,&mInternal);
}

NSDevilX::NSCore::NSGL::IGPUBufferImp::~IGPUBufferImp()
{
	glDeleteBuffers(1,&mInternal);
}
