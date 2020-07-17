#pragma once
namespace NSDevilX
{
	struct SMemoryBlock
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