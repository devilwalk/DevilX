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
					if(getInterfaceImp())
						getInterfaceImp()->release();
				}
				Void setInterfaceImp(InterfaceImpT * interfaceImp)
				{
					if(getInterfaceImp())
						getInterfaceImp()->release();
					mInterfaceImp=interfaceImp;
					if(getInterfaceImp())
						getInterfaceImp()->addRef();
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
				typedef InternalT* InternalType;
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
				typedef InternalT* InternalType;
			public:
				TCOMInternalObject()
					:mInternal(nullptr)
				{}
				virtual ~TCOMInternalObject()
				{
					if(!ISystemImp::getSingleton().isExit())
					{
						setInternal(nullptr);
					}
					else
					{
						if(getInternal())
							getInternal()->Release();
					}
				}
				Void setInternal(InternalT * i)
				{
					if(i!=getInternal())
					{
						if(getInternal())
						{
							CSystemImp::getSingleton().removeInstanceByCOMInternal(getInternal());
							getInternal()->Release();
						}
						mInternal=i;
						if(getInternal())
							CSystemImp::getSingleton().addInstanceByCOMInternal(getInternal(),this);
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