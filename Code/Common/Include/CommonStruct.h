#pragma once
#include "CommonMemoryAllocator.h"
namespace NSDevilX
{
	struct SMemoryBlock
		:public TMemoryAllocatorObject<SMemoryBlock>
	{
		BytePtr mData;
		SizeT mSizeInByte;

		SMemoryBlock(SizeT sizeInByte=0)
			:mData(nullptr)
			,mSizeInByte(sizeInByte)
		{
			if(sizeInByte)
				mData=new Byte[mSizeInByte];
		}
		~SMemoryBlock()
		{
			delete[]mData;
		}
		SMemoryBlock & clone(SMemoryBlock & dst)
		{
			dst.mData=new Byte[mSizeInByte];
			dst.mSizeInByte=mSizeInByte;
			return dst;
		}
		SMemoryBlock clone()
		{
			SMemoryBlock ret;
			return clone(ret);
		}
	};
}