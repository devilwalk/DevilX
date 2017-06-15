#pragma once
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		namespace NSGL4
		{
			class CSystemImp;
			class CResource
				:public TMessageReceiver<CSystemImp>
			{
			protected:
				UInt32 mRegisterCounter;
			public:
				CResource();
				virtual ~CResource();
			protected:
				Void _registerToSystemImp();
				Void _unregisterToSystemImp();
			};
		}
	}
}