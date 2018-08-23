#pragma once
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		namespace NSD3D11
		{
			class CConstantBufferDescription
				:public TBaseObject<CConstantBufferDescription>
			{
			protected:
				String mNameInShader;
				D3D11_SHADER_BUFFER_DESC mDescription;
				TMap(const String,const D3D11_SHADER_VARIABLE_DESC) mConstantDescriptions;
			public:
				CConstantBufferDescription(ID3D11ShaderReflectionConstantBuffer * reflection);
				~CConstantBufferDescription();
				const String & getNameInShader()const
				{
					return mNameInShader;
				}
				const D3D11_SHADER_BUFFER_DESC & getDesc()const
				{
					return mDescription;
				}
				const D3D11_SHADER_VARIABLE_DESC & getConstantDesc(const String & name)const
				{
					return mConstantDescriptions.get(name);
				}
			};
		}
	}
}