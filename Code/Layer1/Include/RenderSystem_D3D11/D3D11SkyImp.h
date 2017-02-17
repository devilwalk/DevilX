#pragma once
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		namespace NSD3D11
		{
			class CSkyImp
				:public TBaseObject<CSkyImp>
				,public TInterfaceObject<ISkyImp>
			{
			protected:
			public:
				CSkyImp(ISkyImp * interfaceImp);
				~CSkyImp();

				// ͨ�� TInterfaceObject �̳�
				virtual Void onMessage(ISkyImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
			};
		}
	}
}