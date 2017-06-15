#pragma once
#include "GL4Resource.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		namespace NSGL4
		{
			class CTexture
				:public CResource
				,public CDirtyFlagContainer
			{
			public:
				enum EDirtyFlag
				{
					EDirtyFlag_Resource,
					EDirtyFlag_Content
				};
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
				,public CTexture
			{
			protected:
				TSet<UInt32> mDirtyContentSubTextureKeys;
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
				Void _updateFromMemorySources(ITexture2DImp::SSubTexture * subTexture);
				Void _updateFromRenderableSources(ITexture2DImp::SSubTexture * subTexture);
			};
		}
	}
}