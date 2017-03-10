#pragma once
namespace NSDevilX
{
	namespace NSResourceSystem
	{
		class ISystemImp
			:public TBaseObject<ISystemImp>
			,public ISystem
			,public TSingletonEx<ISystemImp>
		{
		protected:
			CThreadPool * mIOPool;
		public:
			ISystemImp();
			~ISystemImp();
		};
	}
}