#pragma once
#include "IInputVirtualDeviceImp.h"
namespace NSDevilX
{
	namespace NSInputSystem
	{
		struct SMouseFrameDataImp
			:public IMouseFrameData
			,public TBaseObject<SMouseFrameDataImp>
		{
			enum EType
			{
				EType_Unknown,
				EType_AxisOffsetX,
				EType_AxisOffsetY,
				EType_AxisOffsetZ,
				EType_ButtonState_Left,
				EType_ButtonState_Right,
				EType_ButtonState_Middle
			};
			EType mType;
			Int32 mValue;
			SMouseFrameDataImp();
			~SMouseFrameDataImp();
			// Í¨¹ý IMouseFrameData ¼Ì³Ð
			virtual Int32 getAxisXOffset() const override;
			virtual Int32 getAxisYOffset() const override;
			virtual Int32 getWheelOffset() const override;
			virtual IEnum::EButtonState getButtonState(IEnum::EMouseButtonType type) const override;
		};
		class IMouseImp
			:public IMouse
			,public IVirtualDeviceImp
			,public TBaseObject<IMouseImp>
		{
		public:
			typedef std::array<IEnum::EButtonState,IEnum::EMouseButtonType_Last+1> ButtonStateList;
		protected:
			CInt3 mOffset;
			CInt3 mPosition;
			ButtonStateList mButtonStateList;
			IMouseListener * mListener;
			TVector<SMouseFrameDataImp*> mFrameDatas;
		public:
			IMouseImp(const String & name,IPhysicalDeviceImp * physicalDevice,CWindow * window);
			virtual ~IMouseImp();
			Void addFrameData(SMouseFrameDataImp * data);
			virtual Void update() override;
			// Inherited via IMouse
			virtual IVirtualDevice * queryInterface_IVirtualDevice() const override;
			virtual const CInt2 & getOffset() const override;
			virtual const CInt2 & getPosition() const override;
			virtual Int32 getWheelOffset() const override;
			virtual Int32 getWheelPosition() const override;
			virtual IEnum::EButtonState getButtonState(IEnum::EMouseButtonType type) const override;
			virtual UInt32 getFrameDataCount() const override;
			virtual IMouseFrameData * getFrameData(UInt32 index) const override;
			virtual Void setListener(IMouseListener * listener) override;
			virtual IMouseListener * getListener() const override;
		};
	}
}