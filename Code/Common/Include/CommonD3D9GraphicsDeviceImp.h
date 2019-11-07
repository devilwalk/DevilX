#pragma once
namespace NSDevilX
{
	class CD3D9GraphicsDeviceImp
		:public IGraphicsDevice
	{
	protected:
		IDirect3DDevice9* const mInternal;
	public:
		CD3D9GraphicsDeviceImp(IDirect3DDevice9* internalDevice);
		virtual ~CD3D9GraphicsDeviceImp();

		IDirect3DDevice9Ex* d3d9Ex()const{ return static_cast<IDirect3DDevice9Ex*>(mInternal); }

		// Í¨¹ý IGraphicsDevice ¼Ì³Ð
		virtual IGraphicsVertexBuffer* CreateVertexBuffer(UINT Length,DWORD Usage,DWORD FVF,D3DPOOL Pool) override;
		virtual IGraphicsIndexBuffer* CreateIndexBuffer(UINT Length,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool) override;
		virtual IGraphicsBuffer* createBuffer(const D3D10_BUFFER_DESC* desc) override;
		virtual IGraphicsBuffer* createBuffer(const D3D11_BUFFER_DESC* desc) override;
	};
}