#pragma once
namespace NSDevilX
{
	namespace NSCore
	{
		namespace NSDirectX
		{
			namespace NSVersion11
			{
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
					TVector(CComPtr<ID3D11ShaderReflection>) mShaderReflections;
				public:
					IGAProgramReflectionImp(ID3DBlob * const * blobs,UInt32 numBlobs);
					~IGAProgramReflectionImp();
				};
			}
		}
	}
}