#pragma once
#include "D3D11Shader.h"
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
				CShader * mShader;
			public:
				CShaderImp();
				~CShaderImp();
				CShader * getShader()const
				{
					return mShader;
				}
				// 通过 IShaderImp 继承
				virtual Boolean compile(IEnum::EShaderType type,IEnum::EShaderCodeType codeType,const String & code) override;
				virtual IEnum::EShaderType getType() const override;
				virtual IEnum::EShaderCodeType getCodeType() const override;
			};
			class CProgramImp
				:public IProgramImp
				,public TBaseObject<CProgramImp>
			{
			protected:
				std::array<CShaderImp*,5> mShaders;
			public:
				CProgramImp();
				~CProgramImp();

				// 通过 IProgramImp 继承
				virtual Void setShader(IEnum::EShaderType type,IShader * shader) override;
				virtual IShader * getShader(IEnum::EShaderType type) const override;
				virtual IEnum::EProgramResourceType getResourceType(const String & name) const override;
				virtual UInt32 getResourceLocation(const String & name) const override;
				virtual IProgramBufferLayout * getBufferLayout(UInt32 resourceLocation) const override;
			};
		}
	}
}