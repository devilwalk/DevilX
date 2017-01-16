#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;
using namespace NSD3D11;

NSDevilX::NSRenderSystem::NSD3D11::CConstantBufferDescriptionManager::CConstantBufferDescriptionManager()
{}

NSDevilX::NSRenderSystem::NSD3D11::CConstantBufferDescriptionManager::~CConstantBufferDescriptionManager()
{
}

Void NSDevilX::NSRenderSystem::NSD3D11::CConstantBufferDescriptionManager::registerDescription(ID3D11ShaderReflectionConstantBuffer * reflection)
{
	D3D11_SHADER_BUFFER_DESC shader_buffer_desc;
	reflection->GetDesc(&shader_buffer_desc);
	if(mDescriptions.has(shader_buffer_desc.Name))
	{
		CConstantBufferDescription * test_desc=mDescriptions.get(shader_buffer_desc.Name);
		assert(0==memcmp(&test_desc->getDesc().Type,&shader_buffer_desc.Type,sizeof(D3D11_SHADER_BUFFER_DESC)-sizeof(shader_buffer_desc.Name)));
		for(decltype(shader_buffer_desc.Variables) i=0;i<shader_buffer_desc.Variables;++i)
		{
			ID3D11ShaderReflectionVariable * variable_reflection=reflection->GetVariableByIndex(i);
			D3D11_SHADER_VARIABLE_DESC shader_variable_desc;
			variable_reflection->GetDesc(&shader_variable_desc);
			auto const & test_variable_desc=test_desc->getConstantDesc(shader_variable_desc.Name);
			assert(test_variable_desc.StartOffset==shader_variable_desc.StartOffset);
			assert(test_variable_desc.Size==shader_variable_desc.Size);
		}
	}
	else
	{
		mDescriptions.add(shader_buffer_desc.Name,DEVILX_NEW CConstantBufferDescription(reflection));
	}
}

CConstantBufferDescription * NSDevilX::NSRenderSystem::NSD3D11::CConstantBufferDescriptionManager::getDescription(const String & constBufferName) const
{
	return mDescriptions.has(constBufferName)?mDescriptions.get(constBufferName):nullptr;
}
