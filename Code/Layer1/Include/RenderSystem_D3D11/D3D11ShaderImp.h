#pragma once
#include "D3D11Shader.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		namespace NSD3D11
		{
			class CProgramBufferLayoutImp
				:public IProgramBufferLayout
				,public TCOMInternalObject<ID3D11ShaderReflectionConstantBuffer>
				,public TBaseObject<CProgramBufferLayoutImp>
			{
			public:
				CProgramBufferLayoutImp(ID3D11ShaderReflectionConstantBuffer * internalObj);
				~CProgramBufferLayoutImp();

				// 通过 IProgramBufferLayout 继承
				virtual UInt32 getOffset(const String & name) const override;
				virtual UInt32 getSize(const String & name) const override;
			};
			class CShaderImp
				:public IShaderImp
				,public TBaseObject<CShaderImp>
			{
			protected:
				IEnum::EShaderType mType;
				IEnum::EShaderCodeType mCodeType;
				CShader * mShader;
				TNamedResourcePtrMap(CProgramBufferLayoutImp) mBufferLayout;
			public:
				CShaderImp();
				~CShaderImp();
				CShader * getShader()const
				{
					return mShader;
				}
				CProgramBufferLayoutImp * getBufferLayout(const String & name);
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
				TVector(const String) mResourceNames;
			public:
				CProgramImp();
				~CProgramImp();

				// 通过 IProgramImp 继承
				virtual Void setShader(IEnum::EShaderType type,IShader * shader) override;
				virtual IShader * getShader(IEnum::EShaderType type) const override;
				virtual IEnum::EProgramResourceType getResourceType(const String & name) const override;
				virtual UInt32 getResourceLocation(const String & name) const override;
				virtual IProgramBufferLayout * getBufferLayout(UInt32 resourceLocation) const override;

			protected:
				Void _rebuildResourceNames();
			};
		}
	}
}