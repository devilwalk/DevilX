#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;
using namespace NSD3D11;

NSDevilX::NSRenderSystem::NSD3D11::CConstantBufferDescription::CConstantBufferDescription(ID3D11ShaderReflectionConstantBuffer * reflection)
{
	reflection->GetDesc(&mDescription);
	mNameInShader=mDescription.Name;
	for(decltype(mDescription.Variables) i=0;i<mDescription.Variables;++i)
	{
		ID3D11ShaderReflectionVariable * variable_reflection=reflection->GetVariableByIndex(i);
		D3D11_SHADER_VARIABLE_DESC shader_variable_desc;
		variable_reflection->GetDesc(&shader_variable_desc);
		mConstantDescriptions.add(shader_variable_desc.Name,shader_variable_desc);
	}
}

NSDevilX::NSRenderSystem::NSD3D11::CConstantBufferDescription::~CConstantBufferDescription()
{}
