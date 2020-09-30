#pragma once
#include "IGDResource.h"
namespace NSDevilX
{
	namespace NSCore
	{
		namespace NSGraphicsDriver
		{
			class IFramebuffer
			{
			public:
				struct SCreateInfo
				{
					TVector<IImageView*> mAttachments;
					UInt32 mWidth;
					UInt32 mHeight;
					UInt32 mLayers;
				};
			protected:
				virtual ~IFramebuffer(){}
			public:
			};
		}
	}
}