#pragma once
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		namespace NSGLES3
		{
			class CDepthStencil
				:public TBaseObject<CDepthStencil>
			{
			protected:
				GLuint mInternal;
				Bool mLocked;
			public:
				CDepthStencil();
				~CDepthStencil();
				decltype(mInternal) getInternal()const
				{
					return mInternal;
				}
				Void reserve(UInt32 width,UInt32 height);
				Void lock()
				{
					mLocked=True;
				}
				Void unlock()
				{
					mLocked=False;
				}
				Bool getLocked()const
				{
					return mLocked;
				}
			};
		}
	}
}