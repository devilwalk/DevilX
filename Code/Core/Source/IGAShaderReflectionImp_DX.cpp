#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSCore;
using namespace NSDirectX;

NSDevilX::NSCore::NSDirectX::NSVersion11::IGAShaderReflectionImp::IGAShaderReflectionImp(ID3DBlob * blob)
{
	D3DReflect(blob->GetBufferPointer(),blob->GetBufferSize(),__uuidof(ID3D11ShaderReflection),reinterpret_cast<VoidPtr*>(&mReflection));
}

NSDevilX::NSCore::NSDirectX::NSVersion11::IGAShaderReflectionImp::~IGAShaderReflectionImp()
{}

IGAStruct::SShaderDesc NSDevilX::NSCore::NSDirectX::NSVersion11::IGAShaderReflectionImp::getDesc()
{
	D3D11_SHADER_DESC desc;
	mReflection->GetDesc(&desc);
	IGAStruct::SShaderDesc ret;
	ret.BoundResources=desc.BoundResources;
	ret.ConstantBuffers=desc.ConstantBuffers;
	ret.InputParameters=desc.InputParameters;
	ret.OutputParameters=desc.OutputParameters;
	return ret;
}

IGAStruct::SShaderSignatureParameterDesc NSDevilX::NSCore::NSDirectX::NSVersion11::IGAShaderReflectionImp::getInputParameterDesc(UInt32 parameterIndex)
{
	D3D11_SIGNATURE_PARAMETER_DESC desc;
	mReflection->GetInputParameterDesc(parameterIndex,&desc);
	IGAStruct::SShaderSignatureParameterDesc ret;
	ret.ComponentType=CUtility::mapping(desc.ComponentType);
	ret.Register=desc.Register;
	ret.SemanticIndex=desc.SemanticIndex;
	ret.SemanticName=desc.SemanticName;
	ret.Stream=desc.Stream;
	return ret;
}

IGAStruct::SShaderBufferDesc NSDevilX::NSCore::NSDirectX::NSVersion11::IGAShaderReflectionImp::getBufferDesc(UInt32 index)
{
	D3D11_SHADER_BUFFER_DESC desc;
	mReflection->GetConstantBufferByIndex(index)->GetDesc(&desc);
	IGAStruct::SShaderBufferDesc ret;
	ret.Name=desc.Name;
	ret.Size=desc.Size;
	ret.Type=CUtility::mapping(desc.Type);
	ret.Variables=desc.Variables;
	return ret;
}

IGAStruct::SShaderVariableDesc NSDevilX::NSCore::NSDirectX::NSVersion11::IGAShaderReflectionImp::getVariableDesc(UInt32 bufferIndex,UInt32 variableIndex)
{
	D3D11_SHADER_VARIABLE_DESC desc;
	mReflection->GetConstantBufferByIndex(bufferIndex)->GetVariableByIndex(variableIndex)->GetDesc(&desc);
	D3D11_SHADER_TYPE_DESC type_desc;
	mReflection->GetConstantBufferByIndex(bufferIndex)->GetVariableByIndex(variableIndex)->GetType()->GetDesc(&type_desc);
	IGAStruct::SShaderVariableDesc ret;
	ret.Class=CUtility::mapping(type_desc.Class);
	ret.Name=desc.Name;
	ret.SamplerSize=desc.SamplerSize;
	ret.Size=desc.Size;
	ret.StartOffset=desc.StartOffset;
	ret.StartSampler=desc.StartSampler;
	ret.StartTexture=desc.StartTexture;
	ret.TextureSize=desc.TextureSize;
	ret.Type=CUtility::mapping(type_desc.Type);
	return ret;
}
