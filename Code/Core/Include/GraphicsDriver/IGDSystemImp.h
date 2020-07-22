#pragma once
namespace NSDevilX
{
	namespace NSCore
	{
		namespace NSGraphicsDriver
		{
			class ISystemImp
				:public ISystem
				,public TBaseObject<ISystemImp>
				,public TSingleton<ISystemImp>
			{
			protected:
			public:
				ISystemImp();
				virtual ~ISystemImp();
				// Í¨¹ý ISystem ¼Ì³Ð
				virtual IInstance* createInstance(IEnum::EInstanceMajorType majorType,Int32 minorType) override;
			};
		}
	}
}