#pragma once
#include "D3D11BaseObject.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		namespace NSD3D11
		{
			class CDepthStencil
				:public TBaseObject<CDepthStencil>
				,public TCOMInternalObject<ID3D11DepthStencilView>
			{
			protected:
				ID3D11Texture2D * mTextureResource;
				UInt32 mLocked;
			public:
				CDepthStencil(UInt32 width,UInt32 height);
				~CDepthStencil();
				Void lock()
				{
					++mLocked;
				}
				Void unlock()
				{
					--mLocked;
				}
				Bool getLocked()const
				{
					return mLocked>0;
				}
			};
		}
	}
}