#pragma once
namespace NSDevilX
{
	namespace NSCore
	{
		namespace NSOpenGL
		{
			class IGADeviceImp
				:public TBaseObject<IGADeviceImp>
			{
			protected:
				HGLRC mContext;
			public:
				IGADeviceImp();
				~IGADeviceImp();
			};
		}
	}
}