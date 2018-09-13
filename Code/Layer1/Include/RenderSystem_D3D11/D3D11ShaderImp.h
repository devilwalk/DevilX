#pragma once
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		namespace NSD3D11
		{
			class CShaderImp
				:public IShaderImp
				,public TBaseObject<CShaderImp>
			{
			protected:
				IEnum::EShaderType mType;
				IEnum::EShaderCodeType mCodeType;
				ID3DBlob * mBlob;
			public:
				CShaderImp();
				~CShaderImp();

				// Í¨¹ý IShaderImp ¼Ì³Ð
				virtual Boolean compile(IEnum::EShaderType type,IEnum::EShaderCodeType codeType,const String & code) override;
				virtual IEnum::EShaderType getType() const override;
				virtual IEnum::EShaderCodeType getCodeType() const override;
			};
		}
	}
}