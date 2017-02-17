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
				ID3DBlob * registerShader(const String & key,const String & code,CEnum::EShaderType type,CEnum::EShaderModelType modeType,const D3D_SHADER_MACRO * macros=nullptr);
				ID3DBlob * getCode(const String & key)const
				{
					return mCodes.has(key)?mCodes.get(key):nullptr;
				}
			};
		}
	}
}