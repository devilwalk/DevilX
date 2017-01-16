#pragma once
#include "D3D11BaseObject.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		namespace NSD3D11
		{
			class CTexture
				:public TCOMInternalObject<ID3D11ShaderResourceView>
			{
			protected:
				CTexture(){}
				virtual ~CTexture(){}
			};
			class CTexture2D
				:public TInterfaceObject<ITexture2DImp>
				,public TCOMInternalObject<ID3D11Texture2D>
				,public TBaseObject<CTexture2D>
				,public TMessageReceiver<CSystemImp>
				,public CTexture
			{
			public:
				CTexture2D(ITexture2DImp * interfaceImp);
				~CTexture2D();
				// Inherited via TInterfaceObject
				virtual Void onMessage(ITexture2DImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
				virtual Void onMessage(CSystemImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
			protected:
				Void _update();
				Boolean _recreateInternal();
				Boolean _updatePixels();
			};
		}
	}
}