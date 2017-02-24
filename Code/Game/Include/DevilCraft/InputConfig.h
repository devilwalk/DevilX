#pragma once
namespace NSDevilX
{
	namespace NSDevilCraft
	{
		class CActor;
		class CInputConfig
			:public TBaseObject<CInputConfig>
		{
		protected:
			const String mName;
			TMap<NSInputSystem::IEnum::EKeyType,UInt32> mActionKeyDownMap;
			TMap<NSInputSystem::IEnum::EKeyType,UInt32> mActionKeyUpMap;
			TMap<NSInputSystem::IEnum::EMouseButtonType,UInt32> mActionButtonDownMap;
			TMap<NSInputSystem::IEnum::EMouseButtonType,UInt32> mActionButtonUpMap;
		public:
			CInputConfig(const String & name);
			~CInputConfig();
			const String & getName()const
			{
				return mName;
			}
			Void setKeyDown(NSInputSystem::IEnum::EKeyType type,UInt32 action)
			{
				mActionKeyDownMap[type]=action;
			}
			Void setKeyUp(NSInputSystem::IEnum::EKeyType type,UInt32 action)
			{
				mActionKeyUpMap[type]=action;
			}
			Void setButtonDown(NSInputSystem::IEnum::EMouseButtonType type,UInt32 action)
			{
				mActionButtonDownMap[type]=action;
			}
			Void setButtonUp(NSInputSystem::IEnum::EMouseButtonType type,UInt32 action)
			{
				mActionButtonUpMap[type]=action;
			}
			Void update(CActor * actor);
		};
		class CInputConfigManager
			:public TBaseObject<CInputConfigManager>
		{
		protected:
			TNamedResourcePtrMap<CInputConfig> mConfigs;
		public:
			CInputConfigManager();
			~CInputConfigManager();
			CInputConfig * createConfig(const String & name);
			CInputConfig * getConfig(const String & name)const
			{
				return mConfigs.get(name);
			}
			Void destroyConfig(CInputConfig * config);
		};
	}
}