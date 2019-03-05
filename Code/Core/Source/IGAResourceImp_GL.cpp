#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSCore;
using namespace NSGL;

NSDevilX::NSCore::NSGL::IGAResourceImp::IGAResourceImp()
	:mInternal(0)
{

}

NSDevilX::NSCore::NSGL::IGAResourceImp::~IGAResourceImp()
{
	mInternal=0;
}

NSDevilX::NSCore::NSGL::IGABufferImp::IGABufferImp()
{
	glCreateBuffers(1,&mInternal);
}

NSDevilX::NSCore::NSGL::IGABufferImp::~IGABufferImp()
{
	glDeleteBuffers(1,&mInternal);
}
