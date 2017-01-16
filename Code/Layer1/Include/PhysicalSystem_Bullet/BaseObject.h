#pragma once
namespace NSDevilX
{
	namespace NSPhysicalSystem
	{
		namespace NSBullet
		{
			class CSystem;
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
					if(ISystemImp::getSingleton().isExit())
						return;
					setInterfaceImp(nullptr);
				}
				Void setInterfaceImp(InterfaceImpT * interfaceImp)
				{
					if(interfaceImp!=mInterfaceImp)
					{
						if(mInterfaceImp)
							CSystem::getSingleton().removeInstanceByInterfaceImp(mInterfaceImp);
						mInterfaceImp=interfaceImp;
						if(mInterfaceImp)
							CSystem::getSingleton().addInstanceByInterfaceImp(interfaceImp,this);
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
					if(ISystemImp::getSingleton().isExit())
						return;
					setInternal(nullptr);
				}
				Void setInternal(InternalT * i)
				{
					if(i!=mInternal)
					{
						if(mInternal)
							CSystem::getSingleton().removeInstanceByInternal(mInternal);
						mInternal=i;
						if(mInternal)
							CSystem::getSingleton().addInstanceByInternal(i,this);
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