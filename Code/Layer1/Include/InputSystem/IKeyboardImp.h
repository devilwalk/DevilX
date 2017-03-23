#pragma once
#include "IInputVirtualDeviceImp.h"
namespace NSDevilX
{
	namespace NSInputSystem
	{
		struct SKeyboardFrameDataImp
			:public IKeyboardFrameData
			,public TBaseObject<SKeyboardFrameDataImp>
		{
			IEnum::EKeyType mKey;
			IEnum::EButtonState mState;
			SKeyboardFrameDataImp();
			~SKeyboardFrameDataImp();

			// Í¨¹ý IKeyboardFrameData ¼Ì³Ð
			virtual IEnum::EKeyType getKey() const override;
			virtual IEnum::EButtonState getButtonState() const override;
		};
		class IKeyboardImp
			:public IKeyboard
			,public IVirtualDeviceImp
			,public TBaseObject<IKeyboardImp>
		{
		public:
			typedef std::array<IEnum::EButtonState,IEnum::EKeyType_Last+1> KeyStateList;
		protected:
			KeyStateList mKeyStateList;
			IKeyboardListener * mListener;
			TVector<SKeyboardFrameDataImp*> mFrameDatas;
		public:
			IKeyboardImp(const String & name,IPhysicalDeviceImp * physicalDevice,CWindow * window);
			virtual ~IKeyboardImp();
			Void addFrameData(SKeyboardFrameDataImp * data);
			virtual Void update() override;
			// Inherited via IKeyboard
			virtual IVirtualDevice * queryInterface_IVirtualDevice() const override;
			virtual IEnum::EButtonState getButtonState(IEnum::EKeyType type) const override;
			virtual UInt32 getFrameDataCount() const override;
			virtual IKeyboardFrameData * getFrameData(UInt32 index) const override;
			virtual Void setListener(IKeyboardListener * listener) override;
			virtual IKeyboardListener * getListener() const override;
		};
	}
}