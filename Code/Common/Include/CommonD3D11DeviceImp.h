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

			// Í¨¹ý IDevice ¼Ì³Ð
			virtual Bool createVertexBuffer(UINT Length,DWORD Usage,DWORD FVF,D3DPOOL Pool,OUT IBuffer* Buffer) override;
			virtual Bool createIndexBuffer(UINT Length,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,OUT IBuffer* Buffer) override;
			virtual Bool createBuffer(const D3D10_BUFFER_DESC& desc,const D3D10_SUBRESOURCE_DATA* initializeData,OUT IBuffer* buffer) override;
			virtual Bool createBuffer(const D3D11_BUFFER_DESC& desc,const D3D11_SUBRESOURCE_DATA* initializeData,OUT IBuffer* buffer) override;
		};
	}
}
#endif