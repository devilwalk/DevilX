#pragma once
#include "GLES3ConstantBufferDescription.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		namespace NSGLES3
		{
			class CConstantBuffer
				:public TBaseObject<CConstantBuffer>
			{
			protected:
				CConstantBufferDescription * const mDescription;
				GLuint mInternal;
				TVector<Byte> mCache;
				TSharedReadData<Bool> mNeedUpdate;
			public:
				CConstantBuffer(CConstantBufferDescription * description);
				virtual ~CConstantBuffer();
				decltype(mInternal) getInternal()const
				{
					return mInternal;
				}
				CConstantBufferDescription * getDescription()const
				{
					return mDescription;
				}
				Byte * getCache()
				{
					return &mCache[0];
				}
				Void needUpdate()
				{
					mNeedUpdate.write(True);
				}
				Void submit();
			};
		}
	}
}