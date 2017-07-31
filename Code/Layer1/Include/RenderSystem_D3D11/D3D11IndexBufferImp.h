#pragma once
#include "D3D11BufferImp.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		namespace NSD3D11
		{
			class CIndexBufferImp
				:public TInterfaceObject<IIndexBufferImp>
				,public TBaseObject<CIndexBufferImp>
				,public CReferenceObject
			{
			protected:
				CBufferImp * mBuffer;
			public:
				CIndexBufferImp(IIndexBufferImp * interfaceImp);
				ID3D11Buffer * getBuffer()const
				{
					return mBuffer->getInternal();
				}
			protected:
				~CIndexBufferImp();
				// Inherited via TInterfaceObject
				virtual Void onMessage(IIndexBufferImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
			};
		}
	}
}