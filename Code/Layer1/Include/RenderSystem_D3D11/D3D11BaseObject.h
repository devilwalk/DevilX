#pragma once
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		namespace NSD3D11
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
				virtual ~TInterfaceObject()
				{
				}
				Void setInterfaceImp(InterfaceImpT * interfaceImp)
				{
					mInterfaceImp=interfaceImp;
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
				virtual ~TInternalObject()
				{
					if(ISystemImp::getSingleton().isExit())
						return;
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
				virtual ~TCOMInternalObject()
				{
					if(ISystemImp::getSingleton().isExit())
					{
						if(getInternal())
							getInternal()->Release();
					}
					else
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