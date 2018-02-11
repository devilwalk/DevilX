#pragma once
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		namespace NSGL4
		{
			class CBufferUpdater
				:public TBaseObject<CBufferUpdater>
			{
			protected:
				GLuint mBuffer;
				const ConstVoidPtr * mSource;
				const COrderedRangesI * mDirtyRanges;
			public:
				CBufferUpdater();
				~CBufferUpdater();
				Void setBuffer(GLuint buffer)
				{
					mBuffer=buffer;
				}
				GLuint getBuffer()const
				{
					return mBuffer;
				}
				Void setDataSource(const ConstVoidPtr * source)
				{
					mSource=source;
				}
				Void setDirtyRanges(const COrderedRangesI * dirtyRanges)
				{
					mDirtyRanges=dirtyRanges;
				}
				Void update();
			};
		}
	}
}