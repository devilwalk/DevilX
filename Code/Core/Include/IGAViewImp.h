#pragma once
namespace NSDevilX
{
	namespace NSCore
	{
		class IGAViewImp
			:public IGAView
			,virtual public CGAObject
		{
		public:
			IGAViewImp();
			virtual ~IGAViewImp();
		};
		template<class TInterface>
		class TGAViewImp
			:public TInterface
			,virtual public IGAViewImp
		{
		public:
			TGAViewImp()
			{
			}
			virtual ~TGAViewImp()
			{
			}

			virtual IGAView* queryInterface_IGAView()override
			{
				return this;
			}
		};
	}
}