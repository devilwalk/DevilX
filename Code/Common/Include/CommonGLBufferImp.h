#pragma once
namespace NSDevilX
{
	namespace NSGraphicsAPI
	{
		class CGLBufferImp
			:public IBufferPool
			,public IBuffer
			,public CGLObject
		{
		protected:
		public:
			CGLBufferImp();
			virtual ~CGLBufferImp();
		};

		class CGLBufferRangeImp
			:public IBuffer
		{
			friend class CGLDeviceImp;
		protected:
			CGLBufferImp* mPool;
			GLintptr mOffset;
			GLsizeiptr mSize;
		public:
			CGLBufferRangeImp();
			virtual ~CGLBufferRangeImp();
		};
	}
}