#pragma once
#include "GL4BufferImp.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		namespace NSGL4
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
				CBufferImp * getBuffer()const
				{
					return mBuffer;
				}
			protected:
				~CIndexBufferImp();
				// Inherited via TInterfaceObject
				virtual Void onMessage(IIndexBufferImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
			};
		}
	}
}