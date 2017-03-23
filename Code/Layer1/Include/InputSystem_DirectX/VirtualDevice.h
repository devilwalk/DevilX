#pragma once
namespace NSDevilX
{
	namespace NSInputSystem
	{
		namespace NSDirectX
		{
			class CVirtualDevice
				:public TMessageReceiver<IVirtualDeviceImp>
			{
			protected:
				IVirtualDeviceImp * const mInterfaceImp;
				CComPtr<IDirectInputDevice8> mDevice;
			public:
				CVirtualDevice(IVirtualDeviceImp * device);
				virtual ~CVirtualDevice();
			protected:
				virtual Void _beginUpdateData(){}
				virtual Void _processData(const DIDEVICEOBJECTDATA & data)
				{}

				// Í¨¹ý TMessageReceiver ¼Ì³Ð
				virtual Void onMessage(IVirtualDeviceImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
			};
			class CMouse
				:public CVirtualDevice
				,public TBaseObject<CMouse>
			{
			protected:
				TVector<SMouseFrameDataImp*> mFrameDatas;
				TResourcePtrVector<SMouseFrameDataImp> mFrameDatasPool;
			public:
				CMouse(IVirtualDeviceImp * device);
				virtual ~CMouse();
			protected:
				SMouseFrameDataImp * _allocFrameData()
				{
					if(mFrameDatasPool.empty())
						return DEVILX_NEW SMouseFrameDataImp();
					else
					{
						auto ret=mFrameDatasPool.back();
						mFrameDatas.push_back(ret);
						mFrameDatasPool.pop_back();
						return ret;
					}
				}
				virtual Void _beginUpdateData() override;
				virtual Void _processData(const DIDEVICEOBJECTDATA & data) override;
			};
			class CKeyboard
				:public CVirtualDevice
				,public TBaseObject<CKeyboard>
			{
			protected:
				TVector<SKeyboardFrameDataImp*> mFrameDatas;
				TResourcePtrVector<SKeyboardFrameDataImp> mFrameDatasPool;
			public:
				CKeyboard(IVirtualDeviceImp * device);
				virtual ~CKeyboard();
			protected:
				SKeyboardFrameDataImp * _allocFrameData()
				{
					if(mFrameDatasPool.empty())
						return DEVILX_NEW SKeyboardFrameDataImp();
					else
					{
						auto ret=mFrameDatasPool.back();
						mFrameDatas.push_back(ret);
						mFrameDatasPool.pop_back();
						return ret;
					}
				}
				virtual Void _beginUpdateData() override;
				virtual Void _processData(const DIDEVICEOBJECTDATA & data) override;
			};
		}
	}
}