#pragma once
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		namespace NSGL4
		{
			class CTexture
			{
			protected:
				GLuint mInternal;
			protected:
				CTexture(){}
				virtual ~CTexture(){}
				decltype(mInternal) getInternal()const
				{
					return mInternal;
				}
			};
			class CTexture2D
				:public TInterfaceObject<ITexture2DImp>
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