#pragma once
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		namespace NSD3D11
		{
			class CTexture1DImp
				:public CTexture1D
				,public TCOMInternalObject<ID3D11Texture1D>
				,public TBaseObject<CTexture1DImp>
				,public CTexture
			{
			protected:
			public:
				CTexture1DImp();
				~CTexture1DImp();

				virtual Void initialize(UInt32 width,UInt32 mipLevels,IEnum::ETexture1DFormat fmt,UInt32 flag=IEnum::EAccessFlag_GPURead,UInt32 arraySize=1) override;
			};
			class CTexture2DImp
				:public CTexture2D
				,public TCOMInternalObject<ID3D11Texture2D>
				,public TBaseObject<CTexture2DImp>
				,public CTexture
			{
			protected:
			public:
				CTexture2DImp();
				~CTexture2DImp();

				virtual Void initialize(UInt32 width,UInt32 height,UInt32 mipLevels,IEnum::ETexture2DFormat fmt,UInt32 flag=IEnum::EAccessFlag_GPURead,UInt32 arraySize=1) override;
			};
			class CTexture3DImp
				:public CTexture3D
				,public TCOMInternalObject<ID3D11Texture3D>
				,public TBaseObject<CTexture3DImp>
				,public CTexture
			{
			protected:
			public:
				CTexture3DImp();
				~CTexture3DImp();

				virtual Void initialize(UInt32 width,UInt32 height,UInt32 depth,UInt32 mipLevels,IEnum::ETexture3DFormat fmt,UInt32 flag=IEnum::EAccessFlag_GPURead) override;
			};
		};
	}
}