#pragma once
namespace NSDevilX
{
	namespace NSCore
	{
		namespace NSGraphicsDriver
		{
			class ISystemImp: public ISystem
			{
			protected:
			public:
				ISystemImp();
				virtual ~ISystemImp();
				// ͨ�� ISystem �̳�
				virtual IInstance* createInstance(IEnum::EInstance* types) override;
			};
		}
	}
}