#pragma once
namespace NSDevilX
{
	namespace NSCore
	{
		namespace NSDirectX
		{
			namespace NSVersion11
			{
				class IGAShaderReflectionImp
					:public IGAShaderReflection
					,public CGAObject
					,public TD3DObjectContainer<ID3D11ShaderReflection>
					,public TBaseObject<IGAShaderReflectionImp>
				{
				public:
					IGAShaderReflectionImp(ID3DBlob* blob);
					~IGAShaderReflectionImp();
				};
				class IGAProgramReflectionImp
					:public IGAProgramReflection
					,public TBaseObject<IGAProgramReflectionImp>
					,public CGAObject
				{
				public:
					static const std::array<UInt32, 5> msConstantBufferSlotOffsets;
					static const std::array<UInt32, 5> msSamplerSlotOffsets;
					static const std::array<UInt32, 5> msShaderResourceSlotOffsets;
				protected:
					std::array<CComPtr<ID3D11ShaderReflection>,5> mShaderReflections;
				public:
					IGAProgramReflectionImp(ID3DBlob * const * blobs,UInt32 numBlobs);
					~IGAProgramReflectionImp();
				};
			}
		}
	}
}