#include "Precompiler.h"
using namespace NSDevilX;

NSDevilX::NSGraphicsAPI::CGLBufferImp::CGLBufferImp()
{
}

NSDevilX::NSGraphicsAPI::CGLBufferImp::~CGLBufferImp()
{
}

NSDevilX::NSGraphicsAPI::CGLBufferRangeImp::CGLBufferRangeImp()
	:mPool(nullptr)
	,mOffset(0)
	,mSize(0)
{
}

NSDevilX::NSGraphicsAPI::CGLBufferRangeImp::~CGLBufferRangeImp()
{
}
