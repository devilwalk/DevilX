#pragma once
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		namespace NSGLES3
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
			class CGLResourceObject
			{
			public:
				CGLResourceObject()
					:mResource(0)
				{}
				virtual ~CGLResourceObject()
				{
				}
				GLuint getResource()const
				{
					return mResource;
				}
			protected:
				Void _setResource(GLuint res)
				{
					mResource=res;
				}
			private:
				GLuint mResource;
			};
		}
	}
}