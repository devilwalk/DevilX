#pragma once
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		namespace NSD3D11
		{
			class CShaderCodeManager
				:public TBaseObject<CShaderCodeManager>
			{
			public:
				typedef ConstCharPtr (getShaderCodeFunction)();
			protected:
				TMap<const String,ID3DBlob*> mCodes;
			public:
				CShaderCodeManager();
				~CShaderCodeManager();
				ID3DBlob * registerVertexShader(const String & key,const String & code,CEnum::EShaderModelType smType,const D3D_SHADER_MACRO * macros=nullptr);
				ID3DBlob * registerPixelShader(const String & key,const String & code,CEnum::EShaderModelType smType,const D3D_SHADER_MACRO * macros=nullptr);
				ID3DBlob * getCode(const String & key)const
				{
					return mCodes.has(key)?mCodes.get(key):nullptr;
				}
			};
		}
	}
}