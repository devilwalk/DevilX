#pragma once
#include "IGAViewImp.h"
namespace NSDevilX
{
	namespace NSCore
	{
		namespace NSOpenGL
		{
			template<class TInterface,typename TInternal=GLuint>
			class TGAGLViewImp
				:public TGAViewImp<TInterface>
				,public TGLObjectContainer<TInternal>
			{
			public:
				TGAGLViewImp(TInternal obj=0)
					:TGLObjectContainer<TInternal>(obj)
				{
				}
				virtual ~TGAGLViewImp()
				{
				}
			};
			class IGARenderTargetViewImp
				:public TGAGLViewImp<IGARenderTargetView>
				,public TBaseObject<IGARenderTargetViewImp>
			{
			protected:
				union
				{
					struct
					{
						GLuint mTexture;
						GLuint mMipLevel;
						GLuint mArrayIndex;
					};
				};
			public:
				IGARenderTargetViewImp(GLuint texture,GLint mipLevel,GLint arrayIndex);
				~IGARenderTargetViewImp();
			};
			class IGADepthStencilViewImp
				:public TGAGLViewImp<IGADepthStencilView>
				,public TBaseObject<IGADepthStencilViewImp>
			{
			protected:
				union
				{
					struct
					{
						GLuint mTexture;
						GLuint mMipLevel;
						GLuint mArrayIndex;
					};
				};
			public:
				IGADepthStencilViewImp(GLuint texture,GLint mipLevel,GLint arrayIndex);
				~IGADepthStencilViewImp();
			};
		}
	}
}