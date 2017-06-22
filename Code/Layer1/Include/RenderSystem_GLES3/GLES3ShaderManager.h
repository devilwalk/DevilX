#pragma once
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		namespace NSGLES3
		{
			class CShaderManager
				:public TBaseObject<CShaderManager>
			{
			public:
				typedef TVector<std::pair<String,String> > MacroDefines;
			protected:
				TMap<const String,GLuint> mShaders;
			public:
				CShaderManager();
				~CShaderManager();
				GLuint registerVertexShader(const String & key,const String & code,const MacroDefines & macros);
				GLuint registerPixelShader(const String & key,const String & code,const MacroDefines & macros);
				GLuint getShader(const String & key)const
				{
					return mShaders.has(key)?mShaders.get(key):0;
				}
			};
		}
	}
}