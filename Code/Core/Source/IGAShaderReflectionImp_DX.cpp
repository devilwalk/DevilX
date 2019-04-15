#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSCore;
using namespace NSDirectX;

NSDevilX::NSCore::NSDirectX::NSVersion11::IGAShaderReflectionImp::IGAShaderReflectionImp(ID3DBlob * const * blobs,UInt32 numBlobs)
{
	mReflections.resize(numBlobs);
	for(UInt32 i=0;i<numBlobs;++i)
	{
		ID3D11ShaderReflection * reflection=nullptr;
		D3DReflect(blobs[i]->GetBufferPointer(),blobs[i]->GetBufferSize(),__uuidof(ID3D11ShaderReflection),reinterpret_cast<VoidPtr*>(&reflection));
		mReflections[i]=reflection;
	}
}

NSDevilX::NSCore::NSDirectX::NSVersion11::IGAShaderReflectionImp::~IGAShaderReflectionImp()
{}

IGAStruct::SShaderDesc NSDevilX::NSCore::NSDirectX::NSVersion11::IGAShaderReflectionImp::getDesc()
{
	return IGAStruct::SShaderDesc();
}

IGAStruct::SShaderSignatureParameterDesc NSDevilX::NSCore::NSDirectX::NSVersion11::IGAShaderReflectionImp::getInputParameterDesc(UInt32 parameterIndex)
{
	return IGAStruct::SShaderSignatureParameterDesc();
}

IGAStruct::SShaderBufferDesc NSDevilX::NSCore::NSDirectX::NSVersion11::IGAShaderReflectionImp::getBufferDesc(UInt32 index)
{
	return IGAStruct::SShaderBufferDesc();
}

IGAStruct::SShaderVariableDesc NSDevilX::NSCore::NSDirectX::NSVersion11::IGAShaderReflectionImp::getVariableDesc(UInt32 bufferIndex,UInt32 variableIndex)
{
	return IGAStruct::SShaderVariableDesc();
}
