#pragma once
#include "CommonDefine.h"
#include "CommonType.h"
#include "CommonMemoryAllocatorObjectTemplate.h"
#include "CommonMemoryTracker.h"
namespace NSDevilX
{
	class CAny
		:public TBaseObject<CAny>
	{
	protected:
		union
		{
			Int8Ptr mInt8Ptr;
			UInt8Ptr mUInt8Ptr;
			Int16Ptr mInt16Ptr;
			UInt16Ptr mUInt16Ptr;
			Int32Ptr mInt32Ptr;
			UInt32Ptr mUInt32Ptr;
			Int64Ptr mInt64Ptr;
			UInt64Ptr mUInt64Ptr;
			SizeTPtr mSizeTPtr;
			FloatPtr mFloatPtr;
			DoubleFloatPtr mDoubleFloatPtr;
			VoidPtr mVoidPtr;
			BooleanPtr mBooleanPtr;
			CharPtr mCharPtr;
			BytePtr mBytePtr;
			WCharPtr mWCharPtr;
			BoolPtr mBoolPtr;
		};
		SizeT mSize;
	public:
		CAny()
			:mVoidPtr(0)
			,mSize(0)
		{}
		template<typename T>
		CAny(T const & t)
			:mVoidPtr(0)
			,mSize(0)
		{
			*this=t;
		}
		CAny(const CAny & t)
		{
			*this=t;
		}
		~CAny()
		{
			DEVILX_FREE(mVoidPtr);
		}
		const CAny & operator=(const CAny & t)
		{
			if(t.mSize!=mSize)
			{
				DEVILX_FREE(mVoidPtr);
				mSize=t.mSize;
				mVoidPtr=DEVILX_ALLOC(mSize);
#ifdef DEVILX_MEMORY_TRACK_ENABLE
				getDefaultMemoryTracker()->allocate(mVoidPtr,mSize,__FILE__,__FUNCTION__,__LINE__);
#endif
			}
			memcpy(mVoidPtr,t.mVoidPtr,mSize);
			return *this;
		}
		template<typename T>
		const CAny & operator=(const T & t)
		{
			if(sizeof(T)!=mSize)
			{
				DEVILX_FREE(mVoidPtr);
				mSize=sizeof(T);
				mVoidPtr=DEVILX_ALLOC(mSize);
			}
			memcpy(mVoidPtr,&t,sizeof(T));
			return *this;
		}
		Boolean operator==(const CAny & t)const
		{
			return (mSize==t.mSize)&&memcmp(mVoidPtr,t.mVoidPtr,mSize);
		}
		template<typename T>
		Boolean operator==(const T & t)const
		{
			return (mSize==sizeof(T))&&memcmp(mVoidPtr,&t,sizeof(T));
		}
		Boolean isValidate()const
		{
			return (!mVoidPtr)||(!mSize);
		}
		template<typename T>
		const T & get()const
		{
			return *reinterpret_cast<T*>(mVoidPtr);
		}
	};
}
