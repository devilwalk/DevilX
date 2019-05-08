#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSCore;
using namespace NSDirectX;
using namespace NSVersion11;

NSDevilX::NSCore::NSDirectX::NSVersion11::IGAShaderReflectionImp::IGAShaderReflectionImp(ID3DBlob* blob)
{
}

NSDevilX::NSCore::NSDirectX::NSVersion11::IGAShaderReflectionImp::~IGAShaderReflectionImp()
{
}

const std::array<UInt32, 5> NSDevilX::NSCore::NSDirectX::NSVersion11::IGAProgramReflectionImp::msConstantBufferSlotOffsets = { 0, static_cast<UInt16>(-1), static_cast<UInt16>(-1) * 2, static_cast<UInt16>(-1) * 3, static_cast<UInt16>(-1) * 4 };
const std::array<UInt32, 5> NSDevilX::NSCore::NSDirectX::NSVersion11::IGAProgramReflectionImp::msSamplerSlotOffsets = { 0, static_cast<UInt16>(-1), static_cast<UInt16>(-1) * 2, static_cast<UInt16>(-1) * 3, static_cast<UInt16>(-1) * 4 };
const std::array<UInt32, 5> NSDevilX::NSCore::NSDirectX::NSVersion11::IGAProgramReflectionImp::msShaderResourceSlotOffsets = { 0, static_cast<UInt16>(-1), static_cast<UInt16>(-1) * 2, static_cast<UInt16>(-1) * 3, static_cast<UInt16>(-1) * 4 };

NSDevilX::NSCore::NSDirectX::NSVersion11::IGAProgramReflectionImp::IGAProgramReflectionImp(ID3DBlob* const* blobs,UInt32 numBlobs)
{
	for(UInt32 i=0;i<numBlobs;++i)
	{
		if(blobs[i])
		{
			D3DReflect(blobs[i]->GetBufferPointer(),blobs[i]->GetBufferSize(),__uuidof(ID3D11ShaderReflection),reinterpret_cast<VoidPtr*>(&mShaderReflections[i]));
			D3D11_SHADER_DESC shader_desc;
			mShaderReflections[i]->GetDesc(&shader_desc);
			for(UInt32 j=0;j<shader_desc.ConstantBuffers;++j)
			{
				D3D11_SHADER_BUFFER_DESC buffer_desc;
				mShaderReflections[i]->GetConstantBufferByIndex(j)->GetDesc(&buffer_desc);
				assert(buffer_desc.Size);
			}
			for(UInt32 j=0;j<shader_desc.InputParameters;++j)
			{
				D3D11_SIGNATURE_PARAMETER_DESC param_desc;
				mShaderReflections[i]->GetInputParameterDesc(j,&param_desc);
				assert(param_desc.SemanticName);
			}
			for(UInt32 j=0;j<shader_desc.BoundResources;++j)
			{
				D3D11_SHADER_INPUT_BIND_DESC param_desc;
				mShaderReflections[i]->GetResourceBindingDesc(j,&param_desc);
				assert(param_desc.BindCount);
			}
		}
	}
}

NSDevilX::NSCore::NSDirectX::NSVersion11::IGAProgramReflectionImp::~IGAProgramReflectionImp()
{
}