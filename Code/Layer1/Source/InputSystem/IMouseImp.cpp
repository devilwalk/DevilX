#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSInputSystem;

NSDevilX::NSInputSystem::SMouseFrameDataImp::SMouseFrameDataImp()
	:mType(EType_Unknown)
	,mValue(0)
{
}

NSDevilX::NSInputSystem::SMouseFrameDataImp::~SMouseFrameDataImp()
{}

Int32 NSDevilX::NSInputSystem::SMouseFrameDataImp::getAxisXOffset() const
{
	// TODO: 在此处插入 return 语句
	return (EType_AxisOffsetX==mType)?mValue:0;
}

Int32 NSDevilX::NSInputSystem::SMouseFrameDataImp::getAxisYOffset() const
{
	// TODO: 在此处插入 return 语句
	return (EType_AxisOffsetY==mType)?mValue:0;
}

Int32 NSDevilX::NSInputSystem::SMouseFrameDataImp::getWheelOffset() const
{
	return (EType_AxisOffsetZ==mType)?mValue:0;
}

IEnum::EButtonState NSDevilX::NSInputSystem::SMouseFrameDataImp::getButtonState(IEnum::EMouseButtonType type) const
{
	return (type==mType-EType_ButtonState_Left)?*reinterpret_cast<const IEnum::EButtonState*>(&mValue):IEnum::EButtonState_Released;
}

NSDevilX::NSInputSystem::IMouseImp::IMouseImp(const String & name,IPhysicalDeviceImp * physicalDevice,CWindow * window)
	:IVirtualDeviceImp(name,physicalDevice,window)
	,mListener(nullptr)
{
	memset(&mButtonStateList[0],0,mButtonStateList.size()*sizeof(IEnum::EButtonState));
}

NSDevilX::NSInputSystem::IMouseImp::~IMouseImp()
{}

Void NSDevilX::NSInputSystem::IMouseImp::addFrameData(SMouseFrameDataImp * data)
{
	mFrameDatas.push_back(data);
	if(data->mType>=SMouseFrameDataImp::EType_ButtonState_Left)
		mButtonStateList[data->mType-SMouseFrameDataImp::EType_ButtonState_Left]=*reinterpret_cast<const IEnum::EButtonState*>(&data->mValue);
	else
	{
		mOffset[data->mType]+=data->mValue;
		mPosition[data->mType]+=data->mValue;
	}
}

Void NSDevilX::NSInputSystem::IMouseImp::update()
{
	mFrameDatas.clear();
	IVirtualDeviceImp::update();
	if(getListener())
	{
		for(auto data:mFrameDatas)
		{
			getListener()->addFrameData(data);
		}
	}
}

IVirtualDevice * NSDevilX::NSInputSystem::IMouseImp::queryInterface_IVirtualDevice() const
{
	return const_cast<IMouseImp*>(this);
}

const CInt2 & NSDevilX::NSInputSystem::IMouseImp::getOffset() const
{
	// TODO: insert return statement here
	return mOffset.xy();
}

const CInt2 & NSDevilX::NSInputSystem::IMouseImp::getPosition() const
{
	// TODO: insert return statement here
	return mPosition.xy();
}

Int32 NSDevilX::NSInputSystem::IMouseImp::getWheelOffset() const
{
	return mOffset.z;
}

Int32 NSDevilX::NSInputSystem::IMouseImp::getWheelPosition() const
{
	return mPosition.z;
}

IEnum::EButtonState NSDevilX::NSInputSystem::IMouseImp::getButtonState(IEnum::EMouseButtonType type) const
{
	return mButtonStateList[type];
}

UInt32 NSDevilX::NSInputSystem::IMouseImp::getFrameDataCount() const
{
	return static_cast<UInt32>(mFrameDatas.size());
}

IMouseFrameData * NSDevilX::NSInputSystem::IMouseImp::getFrameData(UInt32 index) const
{
	return mFrameDatas[index];
}

Void NSDevilX::NSInputSystem::IMouseImp::setListener(IMouseListener * listener)
{
	mListener=listener;
}

IMouseListener * NSDevilX::NSInputSystem::IMouseImp::getListener() const
{
	return mListener;
}
