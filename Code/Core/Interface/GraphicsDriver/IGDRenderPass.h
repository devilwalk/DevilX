#pragma once
#include "IGDFramebuffer.h"
namespace NSDevilX
{
	namespace NSCore
	{
		namespace NSGraphicsDriver
		{
			class IRenderPass
			{
			public:
				struct SBeginInfo
				{
					IFramebuffer* mFramebuffer;
					VkRect2D mRenderArea;
					TVector<VkClearValue> mClearValues;
				};
			protected:
				virtual ~IRenderPass(){}
			public:
				virtual IFramebuffer* createFramebuffer(const IFramebuffer::SCreateInfo& info)=0;
				virtual Void beginFirstSubPass(const SBeginInfo& info)=0;
				virtual Void beginNextSubPass()=0;
				virtual Void end()=0;
			};
		}
	}
}