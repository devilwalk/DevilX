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
				:public TGAViewImp<IGARenderTargetView>
				,public TBaseObject<IGARenderTargetViewImp>
			{
			protected:
				GLuint mTexture;
				GLuint mMipLevel;
				GLuint mArrayIndex;
			public:
				IGARenderTargetViewImp(GLuint texture,GLint mipLevel,GLint arrayIndex);
				~IGARenderTargetViewImp();

				auto getTexture()const
				{
					return mTexture;
				}
				auto getMipLevel()const
				{
					return mMipLevel;
				}
				auto getArrayIndex()const
				{
					return mArrayIndex;
				}
			};
			class IGADepthStencilViewImp
				:public TGAViewImp<IGADepthStencilView>
				,public TBaseObject<IGADepthStencilViewImp>
			{
			protected:
				GLuint mTexture;
				GLuint mMipLevel;
				GLuint mArrayIndex;
			public:
				IGADepthStencilViewImp(GLuint texture,GLint mipLevel,GLint arrayIndex);
				~IGADepthStencilViewImp();

				auto getTexture()const
				{
					return mTexture;
				}
				auto getMipLevel()const
				{
					return mMipLevel;
				}
				auto getArrayIndex()const
				{
					return mArrayIndex;
				}
			};
			class IGATextureViewImp
				:public TGAGLViewImp<IGATextureView>
				,public TBaseObject<IGATextureViewImp>
			{
			public:
				IGATextureViewImp(
					GLenum target,
					GLuint origtexture,
					GLenum internalformat,
					GLuint minlevel,
					GLuint numlevels,
					GLuint minlayer,
					GLuint numlayers);
				~IGATextureViewImp();
			};
			class IGATextureBufferViewImp
				:public TGAGLViewImp<IGATextureBufferView>
				,public TBaseObject<IGATextureBufferViewImp>
			{
			public:
				IGATextureBufferViewImp(GLuint texture,GLint mipLevel,GLint arrayIndex,GLenum access);
				~IGATextureBufferViewImp();
			};
			class IGAUnorderedAccessViewImp
				:public TGAGLViewImp<IGAUnorderedAccessView>
				,public TBaseObject<IGAUnorderedAccessViewImp>
			{

			};
		}
	}
}