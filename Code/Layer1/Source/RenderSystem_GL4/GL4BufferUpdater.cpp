#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;
using namespace NSGL4;

NSDevilX::NSRenderSystem::NSGL4::CBufferUpdater::CBufferUpdater()
	:mBuffer(0)
	,mSource(nullptr)
	,mDirtyRanges(nullptr)
{}

NSDevilX::NSRenderSystem::NSGL4::CBufferUpdater::~CBufferUpdater()
{}

Void NSDevilX::NSRenderSystem::NSGL4::CBufferUpdater::update()
{
	if(mDirtyRanges&&mSource&&(*mSource))
	{
		for(auto const & dirty:*mDirtyRanges)
		{
			ConstVoidPtr src_ptr=reinterpret_cast<ConstVoidPtr>(reinterpret_cast<SizeT>(*mSource)+dirty.getMin());
			glNamedBufferSubData(getBuffer(),dirty.getMin(),dirty.getMax()+1-dirty.getMin(),src_ptr);
			CUtility::checkGLError();
		}
	}
}
