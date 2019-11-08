#pragma once
#if DEVILX_WINDOW_SYSTEM==DEVILX_WINDOW_SYSTEM_WINDOWS
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
	};
}
#endif