#pragma once
#include "RenderOperation.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		class CRenderable
		{
		protected:
			UInt8 mRenderQueueID;
		public:
			CRenderable();
			virtual ~CRenderable();
			Void setRenderQueueID(UInt8 renderQueueID)
			{
				mRenderQueueID=renderQueueID;
			}
			UInt8 getRenderQueueID()const
			{
				return mRenderQueueID;
			}
			virtual Boolean createRenderOperation(OUT CRenderOperation & op);
		};
	}
}