#pragma once
#include "D3D11BaseObject.h"
#include "D3D11ConstantBufferDescription.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		namespace NSD3D11
		{
			class CConstantBuffer
				:public TBaseObject<CConstantBuffer>
				,public TCOMInternalObject<ID3D11Buffer>
			{
			protected:
				CConstantBufferDescription * const mDescription;
				TVector(Byte) mCache;
				TSharedReadData<Bool> mNeedUpdate;
			public:
				CConstantBuffer(CConstantBufferDescription * description);
				virtual ~CConstantBuffer();
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