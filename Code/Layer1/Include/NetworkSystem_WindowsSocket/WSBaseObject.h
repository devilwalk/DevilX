#pragma once
namespace NSDevilX
{
	namespace NSNetworkSystem
	{
		namespace NSWindowsSocket
		{
			class CSystemImp;
			template<class InterfaceImpT>
			class TInterfaceObject
				:public TMessageReceiver<InterfaceImpT>
			{
			public:
				TInterfaceObject(InterfaceImpT * interfaceImp)
				{
					setInterfaceImp(interfaceImp);
				}
				~TInterfaceObject()
				{
					setInterfaceImp(nullptr);
				}
				Void setInterfaceImp(InterfaceImpT * interfaceImp)
				{
					if(interfaceImp!=mInterfaceImp)
					{
						if(mInterfaceImp)
							CSystemImp::getSingleton().removeInstanceByInterfaceImp(mInterfaceImp);
						mInterfaceImp=interfaceImp;
						if(mInterfaceImp)
							CSystemImp::getSingleton().addInstanceByInterfaceImp(interfaceImp,this);
					}
				}
				InterfaceImpT * getInterfaceImp()const
				{
					return mInterfaceImp;
				}
			private:
				InterfaceImpT * mInterfaceImp;
			};

			template<class InternalT>
			class TInternalObject
			{
			public:
				TInternalObject()
					:mInternal(nullptr)
				{}
				~TInternalObject()
				{
					setInternal(nullptr);
				}
				Void setInternal(InternalT * i)
				{
					if(i!=mInternal)
					{
						if(mInternal)
							CSystemImp::getSingleton().removeInstanceByInternal(mInternal);
						mInternal=i;
						if(mInternal)
							CSystemImp::getSingleton().addInstanceByInternal(i,this);
					}
				}
				InternalT * getInternal()const
				{
					return mInternal;
				}
			private:
				InternalT * mInternal;
			};

			template<class InternalT>
			class TCOMInternalObject
			{
			public:
				TCOMInternalObject()
					:mInternal(nullptr)
				{}
				~TCOMInternalObject()
				{
					setInternal(nullptr);
				}
				Void setInternal(InternalT * i)
				{
					if(i!=mInternal)
					{
						if(mInternal)
						{
							CSystemImp::getSingleton().removeInstanceByCOMInternal(mInternal);
							mInternal->Release();
						}
						mInternal=i;
						if(mInternal)
							CSystemImp::getSingleton().addInstanceByCOMInternal(i,this);
					}
				}
				InternalT * getInternal()const
				{
					return mInternal;
				}
			private:
				InternalT * mInternal;
			};
		}
	}
}