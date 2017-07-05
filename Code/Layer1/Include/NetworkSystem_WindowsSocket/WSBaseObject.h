#pragma once
namespace NSDevilX
{
	namespace NSNetworkSystem
	{
		namespace NSWindowsSocket
		{
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
						mInterfaceImp=interfaceImp;
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
						mInternal=i;
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
							mInternal->Release();
						}
						mInternal=i;
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