#pragma once
namespace NSDevilX
{
	typedef char Int8;
	typedef unsigned char UInt8;
	typedef short Int16;
	typedef unsigned short UInt16;
	typedef int Int32;
	typedef int Int;
	typedef unsigned int UInt32;
	typedef unsigned int UInt;
	typedef long long Int64;
	typedef unsigned long long UInt64;
	typedef std::size_t SizeT;
	typedef float Float;
	typedef double DoubleFloat;
	typedef void Void;
	typedef bool Boolean;
	typedef Int8 Char;
	typedef UInt8 Byte;
	typedef wchar_t WChar;
	typedef UInt32 Bool;
	typedef Int32 RGBA;

	typedef Int8 * Int8Ptr;
	typedef UInt8 * UInt8Ptr;
	typedef Int16 * Int16Ptr;
	typedef UInt16 * UInt16Ptr;
	typedef Int32 * Int32Ptr;
	typedef UInt32 * UInt32Ptr;
	typedef Int64 * Int64Ptr;
	typedef UInt64 * UInt64Ptr;
	typedef SizeT * SizeTPtr;
	typedef Float * FloatPtr;
	typedef DoubleFloat * DoubleFloatPtr;
	typedef Void * VoidPtr;
	typedef Boolean * BooleanPtr;
	typedef Char * CharPtr;
	typedef Byte * BytePtr;
	typedef WChar * WCharPtr;
	typedef Bool * BoolPtr;

	typedef const Int8 * ConstInt8Ptr;
	typedef const UInt8 * ConstUInt8Ptr;
	typedef const Int16 * ConstInt16Ptr;
	typedef const UInt16 * ConstUInt16Ptr;
	typedef const Int32 * ConstInt32Ptr;
	typedef const UInt32 * ConstUInt32Ptr;
	typedef const Int64 * ConstInt64Ptr;
	typedef const UInt64 * ConstUInt64Ptr;
	typedef const SizeT * ConstSizeTPtr;
	typedef const Float * ConstFloatPtr;
	typedef const DoubleFloat * ConstDoubleFloatPtr;
	typedef const Void * ConstVoidPtr;
	typedef const Boolean * ConstBooleanPtr;
	typedef const Char * ConstCharPtr;
	typedef const Byte * ConstBytePtr;
	typedef const WChar * ConstWCharPtr;
	typedef const Bool * ConstBoolPtr;

	typedef Int8 & Int8Ref;
	typedef UInt8 & UInt8Ref;
	typedef Int16 & Int16Ref;
	typedef UInt16 & UInt16Ref;
	typedef Int32 & Int32Ref;
	typedef UInt32 & UInt32Ref;
	typedef Int64 & Int64Ref;
	typedef UInt64 & UInt64Ref;
	typedef SizeT & SizeTRef;
	typedef Float & FloatRef;
	typedef DoubleFloat & DoubleFloatRef;
	typedef Boolean & BooleanRef;
	typedef Char & CharRef;
	typedef Byte & ByteRef;
	typedef WChar & WCharRef;
	typedef Bool & BoolRef;

	union UDataPtr
	{
		const Int8Ptr mInt8Ptr;
		const UInt8Ptr mUInt8Ptr;
		const Int16Ptr mInt16Ptr;
		const UInt16Ptr mUInt16Ptr;
		const Int32Ptr mInt32Ptr;
		const UInt32Ptr mUInt32Ptr;
		const Int64Ptr mInt64Ptr;
		const UInt64Ptr mUInt64Ptr;
		const SizeTPtr mSizeTPtr;
		const FloatPtr mFloatPtr;
		const DoubleFloatPtr mDoubleFloatPtr;
		const VoidPtr mVoidPtr;
		const BooleanPtr mBooleanPtr;
		const CharPtr mCharPtr;
		const BytePtr mBytePtr;
		const WCharPtr mWCharPtr;
		const BoolPtr mBoolPtr;
	};

#ifdef VOID
#undef VOID
	typedef Void VOID;
#define VOID void
#else
	typedef Void VOID;
#endif
	typedef Byte BYTE;
	typedef Char CHAR;
	typedef UInt8 UINT8;
	typedef Int16 SHORT;
	typedef UInt16 USHORT;
	typedef UInt32 UINT;
	typedef Int32 INT;
	typedef UInt32 DWORD;
	typedef long LONG;
	typedef unsigned long ULONG;
	typedef long long LONGLONG;
	typedef Float FLOAT;
	typedef SizeT SIZE_T;
	typedef ConstCharPtr LPCSTR;
	typedef ConstWCharPtr LPCWSTR;
}