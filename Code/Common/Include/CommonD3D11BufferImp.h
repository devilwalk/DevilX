#pragma once
namespace NSDevilX
{
	namespace NSGraphicsAPI
	{
		class CD3D11BufferImp
			:public IBuffer
			,public IBufferPool
		{
			friend class CD3D11DeviceImp;
		protected:
			ID3D11Buffer* mInternal;
		public:
		};

		class CD3D11BufferRangeImp
			:public IBuffer
		{
			friend class CGLDeviceImp;
		protected:
			CD3D11BufferImp* mPool;
			GLintptr mOffset;
			GLsizeiptr mSize;
		public:
			CD3D11BufferRangeImp();
			virtual ~CD3D11BufferRangeImp();
		};
	}
}