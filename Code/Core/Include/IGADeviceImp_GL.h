#pragma once
namespace NSDevilX
{
	namespace NSCore
	{
		namespace NSOpenGL
		{
			class IGADeviceImp
				:public TBaseObject<IGADeviceImp>
				,public IGADevice
				,public IGADeviceContext
			{
			protected:
				HGLRC mContext;
			public:
				IGADeviceImp();
				~IGADeviceImp();

				// ͨ�� IGADevice �̳�
				virtual IGADeviceContext * getImmediateContext() const override;
				virtual IGADeviceContext * createDeferredContext() override;
			};
		}
	}
}