#pragma once
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		class IShaderImp
			:public IShader
			,public TBaseObject<IShaderImp>
		{
		protected:
			const IEnum::EShaderType mType;
		public:
			IShaderImp(IEnum::EShaderType type,const String & code);
			~IShaderImp();
		};
	}
}