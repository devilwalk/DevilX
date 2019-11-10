#pragma once
#if DEVILX_WINDOW_SYSTEM==DEVILX_WINDOW_SYSTEM_WINDOWS
namespace NSDevilX
{
	namespace NSGraphicsAPI
	{
		class CD3D9DeviceImp
			:public IDevice
		{
		protected:
			IDirect3DDevice9* const mInternal;
		public:
			CD3D9DeviceImp(IDirect3DDevice9* internalDevice);
			virtual ~CD3D9DeviceImp();

			IDirect3DDevice9Ex* d3d9Ex()const
			{
				return static_cast<IDirect3DDevice9Ex*>(mInternal);
			}
		};
	}
}
#endif