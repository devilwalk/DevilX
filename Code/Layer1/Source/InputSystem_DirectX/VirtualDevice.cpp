#include "Precompiler.h"
#include <array>
using namespace NSDevilX;
using namespace NSInputSystem;
using namespace NSDirectX;
NSDevilX::NSInputSystem::NSDirectX::CVirtualDevice::CVirtualDevice(IVirtualDeviceImp * device)
	:mInterfaceImp(device)
{
	const DIDEVICEINSTANCE & instance=CSystem::getSingleton().getPhysicalDeviceManager()->getInstance(static_cast<IPhysicalDeviceImp*>(device->getPhysicalDevice()));
	HRESULT hr=CSystem::getSingleton().getDirectInput()->CreateDevice(instance.guidInstance,&mDevice,nullptr);
	CHECK_API_SUCCESSED;
	assert(mDevice.p);
	hr=mDevice->SetCooperativeLevel(mInterfaceImp->getWindow()?static_cast<HWND>(mInterfaceImp->getWindow()->getHandle()):GetDesktopWindow(),(mInterfaceImp->getWindow()?DISCL_FOREGROUND:DISCL_BACKGROUND)|DISCL_NONEXCLUSIVE);
	CHECK_API_SUCCESSED;
	DIPROPDWORD pw;
	pw.diph.dwHow=DIPH_DEVICE;
	pw.diph.dwHeaderSize=sizeof(pw.diph);
	pw.diph.dwSize=sizeof(pw);
	pw.diph.dwObj=0;
	switch(device->getPhysicalDevice()->getType())
	{
	case IEnum::EPhysicalDeviceType_Mouse:
		hr=mDevice->SetDataFormat(&c_dfDIMouse2);
		pw.dwData=sizeof(DIDEVICEOBJECTDATA)*11*60;
		break;
	case IEnum::EPhysicalDeviceType_Keyboard:
		hr=mDevice->SetDataFormat(&c_dfDIKeyboard);
		pw.dwData=sizeof(DIDEVICEOBJECTDATA)*(IEnum::EKeyType_Last+1)*60;
		break;
	}
	CHECK_API_SUCCESSED;
	hr=mDevice->SetProperty(DIPROP_BUFFERSIZE,&pw.diph);
	CHECK_API_SUCCESSED;
	hr=mDevice->Acquire();
	CHECK_API_SUCCESSED;
	mInterfaceImp->addListener(this,IVirtualDeviceImp::EMessage_UpdateData);
}

NSDevilX::NSInputSystem::NSDirectX::CVirtualDevice::~CVirtualDevice()
{
	mDevice->Unacquire();
}

Void NSDevilX::NSInputSystem::NSDirectX::CVirtualDevice::onMessage(IVirtualDeviceImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case IVirtualDeviceImp::EMessage_UpdateData:
	{
		_beginUpdateData();
		std::array<DIDEVICEOBJECTDATA,256*16> buffer_data;
		DWORD buffer_count=static_cast<DWORD>(buffer_data.size());
		HRESULT hr=mDevice->GetDeviceData(sizeof(DIDEVICEOBJECTDATA),&buffer_data[0],&buffer_count,0);
		if(SUCCEEDED(hr))
		{
			for(DWORD i=0;i<buffer_count;++i)
			{
				const DIDEVICEOBJECTDATA & data=buffer_data[i];
				_processData(data);
			}
		}
	}
	break;
	}
}

NSDevilX::NSInputSystem::NSDirectX::CMouse::CMouse(IVirtualDeviceImp * device)
	:CVirtualDevice(device)
{
	SecureZeroMemory(&mLastData,sizeof(mLastData));
}

NSDevilX::NSInputSystem::NSDirectX::CMouse::~CMouse()
{}

Void NSDevilX::NSInputSystem::NSDirectX::CMouse::_beginUpdateData()
{
	mFrameDatasPool.insert(mFrameDatasPool.end(),mFrameDatas.begin(),mFrameDatas.end());
	mFrameDatas.clear();
}

Void NSDevilX::NSInputSystem::NSDirectX::CMouse::_processData(const DIDEVICEOBJECTDATA & data)
{
	switch(data.dwOfs)
	{
	case DIMOFS_BUTTON0:
	case DIMOFS_BUTTON1:
	case DIMOFS_BUTTON2:
		if(data.dwData==mLastData.dwData)
			return;
		break;
	}
	auto frame_data=_allocFrameData();
	switch(data.dwOfs)
	{
	case DIMOFS_X:frame_data->mType=SMouseFrameDataImp::EType_AxisOffsetX;frame_data->mValue=data.dwData;break;
	case DIMOFS_Y:frame_data->mType=SMouseFrameDataImp::EType_AxisOffsetY;frame_data->mValue=data.dwData;break;
	case DIMOFS_Z:frame_data->mType=SMouseFrameDataImp::EType_AxisOffsetZ;frame_data->mValue=data.dwData;break;
	case DIMOFS_BUTTON0:
		frame_data->mType=SMouseFrameDataImp::EType_ButtonState_Left;
		frame_data->mValue=(data.dwData&0x80)?IEnum::EButtonState_Pressed:IEnum::EButtonState_Released;
		break;
	case DIMOFS_BUTTON1:
		frame_data->mType=SMouseFrameDataImp::EType_ButtonState_Right;
		frame_data->mValue=(data.dwData&0x80)?IEnum::EButtonState_Pressed:IEnum::EButtonState_Released;
		break;
	case DIMOFS_BUTTON2:
		frame_data->mType=SMouseFrameDataImp::EType_ButtonState_Middle;
		frame_data->mValue=(data.dwData&0x80)?IEnum::EButtonState_Pressed:IEnum::EButtonState_Released;
		break;
	case DIMOFS_BUTTON3:break;
	case DIMOFS_BUTTON4:break;
	case DIMOFS_BUTTON5:break;
	case DIMOFS_BUTTON6:break;
	case DIMOFS_BUTTON7:break;
	default:
		assert(0);
	}
	static_cast<IMouseImp*>(mInterfaceImp)->addFrameData(frame_data);
	mLastData=data;
}

NSDevilX::NSInputSystem::NSDirectX::CKeyboard::CKeyboard(IVirtualDeviceImp * device)
	:CVirtualDevice(device)
{
	SecureZeroMemory(&mLastData[0],sizeof(mLastData[0])*mLastData.size());
}

NSDevilX::NSInputSystem::NSDirectX::CKeyboard::~CKeyboard()
{}

Void NSDevilX::NSInputSystem::NSDirectX::CKeyboard::_beginUpdateData()
{
	mFrameDatasPool.insert(mFrameDatasPool.end(),mFrameDatas.begin(),mFrameDatas.end());
	mFrameDatas.clear();
}

Void NSDevilX::NSInputSystem::NSDirectX::CKeyboard::_processData(const DIDEVICEOBJECTDATA & data)
{
	if(data.dwData==mLastData[data.dwOfs].dwData)
		return;
	auto frame_data=_allocFrameData();
	frame_data->mKey=*reinterpret_cast<const IEnum::EKeyType*>(&data.dwOfs);
	frame_data->mState=(data.dwData&0x80)?IEnum::EButtonState_Pressed:IEnum::EButtonState_Released;
	static_cast<IKeyboardImp*>(mInterfaceImp)->addFrameData(frame_data);
	mLastData[data.dwOfs]=data;
}
