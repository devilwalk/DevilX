#pragma once
#if DEVILX_WINDOW_SYSTEM==DEVILX_WINDOW_SYSTEM_WINDOWS
namespace NSDevilX
{
	namespace NSGraphicsAPI
	{
		class CD3D11DeviceImp
			:public IDevice
		{
		protected:
			ID3D11Device* const mInternal;
		public:
			CD3D11DeviceImp(ID3D11Device* internalDevice);
			virtual ~CD3D11DeviceImp();

			ID3D11Device1* d3d11_1()const
			{
				return static_cast<ID3D11Device1*>(mInternal);
			}
			ID3D11Device2* d3d11_2()const
			{
				return static_cast<ID3D11Device2*>(mInternal);
			}
			ID3D11Device3* d3d11_3()const
			{
				return static_cast<ID3D11Device3*>(mInternal);
			}
			ID3D11Device4* d3d11_4()const
			{
				return static_cast<ID3D11Device4*>(mInternal);
			}

			virtual Bool createBufferPool(const TBufferPoolCreateInfos& createInfos,OUT IBufferPool* pool) override;
			virtual Bool createBuffer(const TBufferCreateInfos& createInfos,OUT IBuffer* buffer) override;
		};
	}
}
#endif