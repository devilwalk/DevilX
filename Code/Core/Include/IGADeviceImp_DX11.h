#pragma once
namespace NSDevilX
{
	namespace NSCore
	{
		namespace NSDirectX
		{
			namespace NSVersion11
			{
				class IGADeviceImp
					:public TBaseObject<IGADeviceImp>
					,public IGADevice
				{
				protected:
					ID3D11Device * mInternal;
					ID3D11DeviceContext * mImmediateContext;
				public:
					IGADeviceImp();
					~IGADeviceImp();

					ID3D11Device * getInternal()const
					{
						return mInternal;
					}
					ID3D11DeviceContext * getImmediateContext()const
					{
						return mImmediateContext;
					}
				};
			}
		}
	}
}