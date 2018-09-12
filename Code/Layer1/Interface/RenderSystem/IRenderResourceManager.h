#pragma once
#include "IRenderGeometry.h"
#include "IRenderTexture.h"
#include "IRenderBuffer.h"
#include "IRenderProgram.h"
#include "IRenderShader.h"
#include "IRenderPipelineState.h"
#include "IRenderMaterial.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		class IResourceManager
		{
		protected:
			virtual ~IResourceManager(){}
		public:
			virtual IGeometry * createGeometry(const String & name)=0;
			virtual Void destroyGeometry(IGeometry * geo)=0;
			virtual IGeometry * getGeometry(const String & name)const=0;
			virtual ITexture * createTexture(const String & name,IEnum::ETextureType type)=0;
			virtual ITexture * getTexture(const String & name)const=0;
			virtual Void destroyTexture(ITexture * texture)=0;
			virtual IBuffer * createBuffer(const String & name)=0;
			virtual IBuffer * getBuffer(const String & name)const=0;
			virtual Void destroyBuffer(IBuffer * buffer)=0;
			virtual IShader * createShader(const String & name,IEnum::EShaderType type,IEnum::EShaderCodeType codeType,const String & code)=0;
			virtual IShader * getShader(const String & name)const=0;
			virtual Void destroyShader(IShader * shader)=0;
			virtual IProgram * createProgram(const String & name)=0;
			virtual IProgram * getProgram(const String & name)const=0;
			virtual Void destroyProgram(IProgram * program)=0;
			virtual IPipelineState * createPipelineState(const String & name)=0;
			virtual IPipelineState * getPipelineState(const String & name)const=0;
			virtual Void destroyPipelineState(IPipelineState * state)=0;
			virtual IMaterial * createMaterial(const String & name)=0;
			virtual IMaterial * getMaterial()const=0;
			virtual Void destroyMaterial(IMaterial * material)=0;
		};
	}
}