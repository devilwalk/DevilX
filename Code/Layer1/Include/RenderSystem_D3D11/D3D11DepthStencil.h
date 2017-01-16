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
				Bool mLocked;
			public:
				CDepthStencil();
				~CDepthStencil();
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