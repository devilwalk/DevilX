#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSCore;
using namespace NSDirectX;
using namespace NSVersion11;

const std::array<UInt32, 5> NSDevilX::NSCore::NSDirectX::NSVersion11::IGAProgramReflectionImp::msConstantBufferSlotOffsets = { 0, static_cast<UInt16>(-1), static_cast<UInt16>(-1) * 2, static_cast<UInt16>(-1) * 3, static_cast<UInt16>(-1) * 4 };
const std::array<UInt32, 5> NSDevilX::NSCore::NSDirectX::NSVersion11::IGAProgramReflectionImp::msSamplerSlotOffsets = { 0, static_cast<UInt16>(-1), static_cast<UInt16>(-1) * 2, static_cast<UInt16>(-1) * 3, static_cast<UInt16>(-1) * 4 };
const std::array<UInt32, 5> NSDevilX::NSCore::NSDirectX::NSVersion11::IGAProgramReflectionImp::msShaderResourceSlotOffsets = { 0, static_cast<UInt16>(-1), static_cast<UInt16>(-1) * 2, static_cast<UInt16>(-1) * 3, static_cast<UInt16>(-1) * 4 };

NSDevilX::NSCore::NSDirectX::NSVersion11::IGAProgramReflectionImp::IGAProgramReflectionImp(ID3DBlob* const* blobs,UInt32 numBlobs)
{
	mShaderReflections.resize(numBlobs);
	for(UInt32 i=0;i<numBlobs;++i)
	{
		if(blobs[i])
		{
			D3DReflect(blobs[i]->GetBufferPointer(),blobs[i]->GetBufferSize(),__uuidof(ID3D11ShaderReflection),reinterpret_cast<VoidPtr*>(&mShaderReflections[i]));
			D3D11_SHADER_DESC shader_desc;
			mShaderReflections[i]->GetDesc(&shader_desc);
			for(UInt32 i=0;i<shader_desc.ConstantBuffers;++i)
			{
				D3D11_SHADER_BUFFER_DESC buffer_desc;
				mShaderReflections[i]->GetConstantBufferByIndex(i)->GetDesc(&buffer_desc);
			}
			for(UInt32 i=0;i<shader_desc.InputParameters;++i)
			{
				D3D11_SIGNATURE_PARAMETER_DESC param_desc;
				mShaderReflections[i]->GetInputParameterDesc(i,&param_desc);
			}
			for(UInt32 i=0;i<shader_desc.BoundResources;++i)
			{
				D3D11_SHADER_INPUT_BIND_DESC param_desc;
				mShaderReflections[i]->GetResourceBindingDesc(i,&param_desc);
			}
		}
	}
}

NSDevilX::NSCore::NSDirectX::NSVersion11::IGAProgramReflectionImp::~IGAProgramReflectionImp()
{
}
