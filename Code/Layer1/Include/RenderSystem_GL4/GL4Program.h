#pragma once
#include "GL4VertexBufferImp.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		namespace NSGL4
		{
			class CProgram
			{
			protected:
				GLuint mHandle;
				CEnum::EVertexBufferType mInputSlots[CEnum::EVertexBufferType_Count];
				TMap<const String,UInt32> mResourceSlots;
			public:
				CProgram(GLuint vertexShader,GLuint pixelShader);
				virtual ~CProgram();
				decltype(mHandle) getInternal()const
				{
					return mHandle;
				}
				CEnum::EVertexBufferType getInputSlot(UInt32 index)const
				{
					return mInputSlots[index];
				}
				UInt32 getSlot(const String & name)const;
			};
		}
	}
}