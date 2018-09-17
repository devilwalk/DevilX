#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;
NSDevilX::NSRenderSystem::IResourceManagerImp::IResourceManagerImp()
	:mInternalBufferNameGenerator("Internal/Buffer")
{}

NSDevilX::NSRenderSystem::IResourceManagerImp::~IResourceManagerImp()
{
}

IGeometry * NSDevilX::NSRenderSystem::IResourceManagerImp::createGeometry(const String & name)
{
	if(mGeometrys.has(name))
		return nullptr;
	notify(EMessage_BeginGeometryCreate);
	IGeometryImp * ret=DEVILX_NEW IGeometryImp(name);
	mGeometrys[name]=ret;
	notify(EMessage_EndGeometryCreate,ret);
	return ret;
}

Void NSDevilX::NSRenderSystem::IResourceManagerImp::destroyGeometry(IGeometry * geo)
{
	if(!mGeometrys.has(geo->getName()))
		return;
	notify(EMessage_BeginGeometryDestroy,static_cast<IGeometryImp*>(geo));
	mGeometrys.destroy(geo->getName());
	notify(EMessage_EndGeometryDestroy);
}

IGeometry * NSDevilX::NSRenderSystem::IResourceManagerImp::getGeometry(const String & name) const
{
	return mGeometrys.get(name);
}

ITexture * NSDevilX::NSRenderSystem::IResourceManagerImp::createTexture(const String & name,IEnum::ETextureType type)
{
	if(mTextures.has(name))
		return nullptr;
	notify(EMessage_BeginTextureCreate);
	ITextureImp * ret=nullptr;
	switch(type)
	{
	case IEnum::ETextureType_2D:
		ret=DEVILX_NEW ITexture2DImp(name);
		break;
	case IEnum::ETextureType_Cube:
		break;
	}
	mTextures[name]=ret;
	notify(EMessage_EndTextureCreate,ret);
	return ret;
}

Void NSDevilX::NSRenderSystem::IResourceManagerImp::destroyTexture(ITexture * texture)
{
	if(!mTextures.has(texture->getName()))
		return;
	notify(EMessage_BeginTextureDestroy,static_cast<ITextureImp*>(texture));
	mTextures.destroy(texture->getName());
	notify(EMessage_EndTextureDestroy);
}

ITexture * NSDevilX::NSRenderSystem::IResourceManagerImp::getTexture(const String & name) const
{
	return mTextures.get(name);
}

IBuffer * NSDevilX::NSRenderSystem::IResourceManagerImp::createBuffer(const String & name)
{
	if(mBuffers.has(name))
		return nullptr;
	notify(EMessage_BeginBufferCreate);
	IBufferImp * ret=DEVILX_NEW IBufferImp(name);
	mBuffers[name]=ret;
	notify(EMessage_EndBufferCreate,ret);
	return ret;
}

IBuffer * NSDevilX::NSRenderSystem::IResourceManagerImp::getBuffer(const String & name) const
{
	return mBuffers.get(name);
}

Void NSDevilX::NSRenderSystem::IResourceManagerImp::destroyBuffer(IBuffer * buffer)
{
	if(!mBuffers.has(buffer->getName()))
		return;
	notify(EMessage_BeginBufferDestroy,static_cast<IBufferImp*>(buffer));
	mBuffers.destroy(buffer->getName());
	notify(EMessage_EndBufferDestroy);
}

IShader * NSDevilX::NSRenderSystem::IResourceManagerImp::createShader(const String & name)
{
	IShaderImp * ret=nullptr;
	notify(EMessage_CreateShader,&ret);
	if(ret)
	{
		ret->setName(name);
		mShaders.add(name,ret);
	}
	return ret;
}

IShader * NSDevilX::NSRenderSystem::IResourceManagerImp::getShader(const String & name) const
{
	return mShaders.get(name);
}

Void NSDevilX::NSRenderSystem::IResourceManagerImp::destroyShader(IShader * shader)
{
	mShaders.destroy(shader->getName());
}

IProgram * NSDevilX::NSRenderSystem::IResourceManagerImp::createProgram(const String & name)
{
	IProgramImp * ret=nullptr;
	notify(EMessage_CreateProgram,&ret);
	if(ret)
	{
		ret->setName(name);
		mPrograms.add(name,ret);
	}
	return ret;
}

IProgram * NSDevilX::NSRenderSystem::IResourceManagerImp::getProgram(const String & name) const
{
	return mPrograms.get(name);
}

Void NSDevilX::NSRenderSystem::IResourceManagerImp::destroyProgram(IProgram * program)
{
	mPrograms.destroy(program->getName());
}

IMaterial * NSDevilX::NSRenderSystem::IResourceManagerImp::createMaterial(const String & name)
{
	return nullptr;
}

IMaterial * NSDevilX::NSRenderSystem::IResourceManagerImp::getMaterial() const
{
	return nullptr;
}

Void NSDevilX::NSRenderSystem::IResourceManagerImp::destroyMaterial(IMaterial * material)
{
	return Void();
}

ISamplerState * NSDevilX::NSRenderSystem::IResourceManagerImp::createSamplerState(const String & name)
{
	ISamplerStateImp * ret=nullptr;
	notify(EMessage_CreateSamplerState,&ret);
	if(ret)
	{
		ret->setName(name);
		mSamplerStates.add(name,ret);
	}
	return ret;
}

ISamplerState * NSDevilX::NSRenderSystem::IResourceManagerImp::getSamplerState(const String & name) const
{
	return mSamplerStates.get(name);
}

Void NSDevilX::NSRenderSystem::IResourceManagerImp::destroySamplerState(const String & name)
{
	return mSamplerStates.destroy(name);
}
