#pragma once
#include "RenderCommandList.h"
#include "Resource.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		class CRenderOperation
		{
		public:
			CBuffer * mIndexBuffer;
			UInt32 mIndexBufferOffset;
			UInt32 mIndexCount;
			UInt32 mVertexBufferOffset;
			UInt32 mVertexCount;
			IEnum::EOperationType mPrimitiveTopology;
			CProgram * mProgram;
			TVector(CBuffer*) mVertexBuffers;
			TVector(UInt32) mVertexStrides;
			TVector(CBuffer*) mConstantBuffers;
			TVector(CRect) mScissorRects;
			CRenderOperation();
			~CRenderOperation();
		};
	}
}