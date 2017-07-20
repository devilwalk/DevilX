#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;
using namespace NSD3D11;

NSDevilX::NSRenderSystem::NSD3D11::CBufferUpdater::CBufferUpdater(UInt32 stride)
	:mStride(stride)
	,mSource(nullptr)
	,mDirtyRanges(nullptr)
{
}

NSDevilX::NSRenderSystem::NSD3D11::CBufferUpdater::~CBufferUpdater()
{}

Void NSDevilX::NSRenderSystem::NSD3D11::CBufferUpdater::update()
{
	if(mDirtyRanges&&mSource&&(*mSource))
	{
		for(auto const & dirty:*mDirtyRanges)
		{
			D3D11_BOX dst_box={0};
			dst_box.left=dirty.getMin()*mStride;
			dst_box.right=(dirty.getMax()+1)*mStride;
			dst_box.bottom=1;
			dst_box.back=1;
			ConstVoidPtr src_ptr=reinterpret_cast<ConstVoidPtr>(reinterpret_cast<SizeT>(*mSource)+dst_box.left);
			CSystemImp::getSingleton().getImmediateContext()->UpdateSubresource(mBuffer,0,&dst_box,src_ptr,dst_box.right-dst_box.left+1,dst_box.right-dst_box.left+1);
		}
	}
}
