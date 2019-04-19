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

				// Í¨¹ý IGADevice ¼Ì³Ð
				virtual IGADeviceContext * getImmediateContext() const override;
				virtual IGADeviceContext * createDeferredContext() override;
			};
		}
	}
}