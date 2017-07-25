#pragma once
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		namespace NSD3D11
		{
			class CBufferUpdater
				:public TBaseObject<CBufferUpdater>
			{
			protected:
				ID3D11Buffer * mBuffer;
				const ConstVoidPtr * mSource;
				const CRangesI * mDirtyRanges;
			public:
				CBufferUpdater();
				~CBufferUpdater();
				Void setBuffer(ID3D11Buffer * buffer)
				{
					mBuffer=buffer;
				}
				ID3D11Buffer * getBuffer()const
				{
					return mBuffer;
				}
				Void setDataSource(const ConstVoidPtr * source)
				{
					mSource=source;
				}
				Void setDirtyRanges(const CRangesI * dirtyRanges)
				{
					mDirtyRanges=dirtyRanges;
				}
				Void update();
			};
		}
	}
}