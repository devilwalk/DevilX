#pragma once
namespace NSDevilX
{
	namespace NSInputSystem
	{
		namespace NSDirectX
		{
			class CVirtualDevice
			{
			protected:
				IVirtualDeviceImp * const mInterfaceImp;
				CComPtr<IDirectInputDevice8> mDevice;
			public:
				CVirtualDevice(IVirtualDeviceImp * device);
				virtual ~CVirtualDevice();
				Void update();
			protected:
				virtual Void _processData(const DIDEVICEOBJECTDATA & data)
				{}
				virtual Void _processDataFinish()
				{}
			};
			class CMouse
				:public CVirtualDevice
				,public TBaseObject<CMouse>
			{
			public:
				CMouse(IVirtualDeviceImp * device);
				virtual ~CMouse();
			protected:
				virtual Void _processData(const DIDEVICEOBJECTDATA & data) override;
				virtual Void _processDataFinish() override;
			};
			class CKeyboard
				:public CVirtualDevice
				,public TBaseObject<CKeyboard>
			{
			public:
				CKeyboard(IVirtualDeviceImp * device);
				virtual ~CKeyboard();
			protected:
				virtual Void _processData(const DIDEVICEOBJECTDATA & data) override;
			};
		}
	}
}