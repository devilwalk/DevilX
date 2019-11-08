#pragma once
namespace NSDevilX
{
	class CD3D11GraphicsBufferImp
		:public IGraphicsBuffer
	{
		friend class CD3D11GraphicsDeviceImp;
	protected:
		ID3D11Buffer* mInternal;
	public:
	};
}