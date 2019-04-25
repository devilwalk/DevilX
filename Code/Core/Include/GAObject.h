#pragma once
namespace NSDevilX
{
	namespace NSCore
	{
		class CGAObject
		{
		protected:
		public:
			virtual ~CGAObject(){}
		};
#if DEVILX_OPERATING_SYSTEM == DEVILX_OPERATING_SYSTEM_WINDOWS
		namespace NSDirectX
		{
			template<class TD3DResource>
			class TD3DObjectContainer
			{
			protected:
				CComPtr<TD3DResource> mInternal;
			public:
				TD3DObjectContainer(TD3DResource* obj=nullptr)
					:mInternal(obj)
				{
				}
				virtual ~TD3DObjectContainer()
				{
				}

				TD3DResource* getInternal() const
				{
					return mInternal;
				}
			};
		}
#endif
		namespace NSOpenGL
		{
			template<typename TInternal=GLuint>
			class TGLObjectContainer
			{
			protected:
				TInternal mInternal;
			public:
				TGLObjectContainer(TInternal obj=0)
					:mInternal(obj)
				{
				}
				virtual ~TGLObjectContainer()
				{
					assert(mInternal==0);
				}

				TInternal getInternal() const
				{
					return mInternal;
				}
			};
		}
	}
}