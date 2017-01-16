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
	hr=mDevice->SetCooperativeLevel(GetDesktopWindow(),DISCL_BACKGROUND|DISCL_NONEXCLUSIVE);
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
}

NSDevilX::NSInputSystem::NSDirectX::CVirtualDevice::~CVirtualDevice()
{
}

Void NSDevilX::NSInputSystem::NSDirectX::CVirtualDevice::update()
{
	static std::array<DIDEVICEOBJECTDATA,256*16> buffer_data;
	DWORD buffer_count=static_cast<DWORD>(buffer_data.size());
	HRESULT hr=mDevice->GetDeviceData(sizeof(DIDEVICEOBJECTDATA),&buffer_data[0],&buffer_count,0);
	if(SUCCEEDED(hr))
	{
		for(DWORD i=0;i<buffer_count;++i)
		{
			const DIDEVICEOBJECTDATA & data=buffer_data[i];
			_processData(data);
		}
		_processDataFinish();
	}
}
static DWORD gMouseX=0;
static DWORD gMouseY=0;
static DWORD gMouseZ=0;
NSDevilX::NSInputSystem::NSDirectX::CMouse::CMouse(IVirtualDeviceImp * device)
	:CVirtualDevice(device)
{}

NSDevilX::NSInputSystem::NSDirectX::CMouse::~CMouse()
{}

Void NSDevilX::NSInputSystem::NSDirectX::CMouse::_processData(const DIDEVICEOBJECTDATA & data)
{
	switch(data.dwOfs)
	{
	case DIMOFS_X:gMouseX+=data.dwData;break;
	case DIMOFS_Y:gMouseY+=data.dwData;break;
	case DIMOFS_Z:gMouseZ+=data.dwData;break;
	case DIMOFS_BUTTON0:static_cast<IMouseImp*>(mInterfaceImp->queryInterface_IMouse())->changeButtonState(IEnum::EMouseButtonType_Left,(data.dwData&0x80)?IEnum::EButtonState_Pressed:IEnum::EButtonState_Released);break;
	case DIMOFS_BUTTON1:static_cast<IMouseImp*>(mInterfaceImp->queryInterface_IMouse())->changeButtonState(IEnum::EMouseButtonType_Right,(data.dwData&0x80)?IEnum::EButtonState_Pressed:IEnum::EButtonState_Released);break;
	case DIMOFS_BUTTON2:static_cast<IMouseImp*>(mInterfaceImp->queryInterface_IMouse())->changeButtonState(IEnum::EMouseButtonType_Middle,(data.dwData&0x80)?IEnum::EButtonState_Pressed:IEnum::EButtonState_Released);break;
	case DIMOFS_BUTTON3:break;
	case DIMOFS_BUTTON4:break;
	case DIMOFS_BUTTON5:break;
	case DIMOFS_BUTTON6:break;
	case DIMOFS_BUTTON7:break;
	}
}

Void NSDevilX::NSInputSystem::NSDirectX::CMouse::_processDataFinish()
{
	static_cast<IMouseImp*>(mInterfaceImp->queryInterface_IMouse())->setOffset(gMouseX,gMouseY);
	static_cast<IMouseImp*>(mInterfaceImp->queryInterface_IMouse())->setWheelOffset(gMouseZ);
	POINT pt;
	GetCursorPos(&pt);
	static_cast<IMouseImp*>(mInterfaceImp->queryInterface_IMouse())->setPosition(pt.x,pt.y);
	gMouseX=0;
	gMouseY=0;
	gMouseZ=0;
}

NSDevilX::NSInputSystem::NSDirectX::CKeyboard::CKeyboard(IVirtualDeviceImp * device)
	:CVirtualDevice(device)
{}

NSDevilX::NSInputSystem::NSDirectX::CKeyboard::~CKeyboard()
{}

Void NSDevilX::NSInputSystem::NSDirectX::CKeyboard::_processData(const DIDEVICEOBJECTDATA & data)
{
	const IEnum::EButtonState state=(data.dwData&0x80)?IEnum::EButtonState_Pressed:IEnum::EButtonState_Released;
	static_cast<IKeyboardImp*>(mInterfaceImp->queryInterface_IKeyboard())->changeButtonState(*reinterpret_cast<const IEnum::EKeyType*>(&data.dwOfs),state);
}
