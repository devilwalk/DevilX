#pragma once
namespace NSDevilX
{
	namespace NSGraphicsAPI
	{
		class CD3D11BufferImp
			:public IBuffer
		{
			friend class CD3D11DeviceImp;
		protected:
			ID3D11Buffer* mInternal;
		public:
		};
	}
}