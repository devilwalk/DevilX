#pragma once
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		namespace NSGL4
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
			class CGLInternalObject
			{
			public:
				typedef GLvoid (GLAPIENTRY*glDeleteFunctionPtr)(GLsizei,GLuint*);
			protected:
				glDeleteFunctionPtr mDeleteFunctionPtr;
			public:
				CGLInternalObject(VoidPtr funcPtr)
					:mInternal(0)
					,mDeleteFunctionPtr(static_cast<glDeleteFunctionPtr>(funcPtr))
				{}
				virtual ~CGLInternalObject()
				{
					(*mDeleteFunctionPtr)(1,&mInternal);
				}
				GLuint getInternal()const
				{
					return mInternal;
				}
				Void setInternal(GLuint res)
				{
					mInternal=res;
				}
			private:
				GLuint mInternal;
			};
		}
	}
}