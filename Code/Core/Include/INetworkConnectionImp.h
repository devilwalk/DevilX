#pragma once
namespace NSDevilX
{
	namespace NSCore
	{
		class INetworkConnectionImp
			:public INetworkConnection
			,public TBaseObject<INetworkConnectionImp>
		{
		protected:
		public:
			INetworkConnectionImp();
			~INetworkConnectionImp();
		};
	}
}