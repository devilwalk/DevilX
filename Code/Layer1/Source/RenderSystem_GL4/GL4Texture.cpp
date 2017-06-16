#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;
using namespace NSGL4;

NSDevilX::NSRenderSystem::NSGL4::CTexture2D::CTexture2D(ITexture2DImp * interfaceImp)
	:TInterfaceObject<ITexture2DImp>(interfaceImp)
{
	getInterfaceImp()->addListener(static_cast<TMessageReceiver<ITexture2DImp>*>(this),ITexture2DImp::EMessage_EndArraySizeChange);
	getInterfaceImp()->addListener(static_cast<TMessageReceiver<ITexture2DImp>*>(this),ITexture2DImp::EMessage_EndFormatChange);
	getInterfaceImp()->addListener(static_cast<TMessageReceiver<ITexture2DImp>*>(this),ITexture2DImp::EMessage_EndMipmapChange);
	getInterfaceImp()->addListener(static_cast<TMessageReceiver<ITexture2DImp>*>(this),ITexture2DImp::EMessage_EndPixelsChange);
	getInterfaceImp()->addListener(static_cast<TMessageReceiver<ITexture2DImp>*>(this),ITexture2DImp::EMessage_EndSizeChange);
}

NSDevilX::NSRenderSystem::NSGL4::CTexture2D::~CTexture2D()
{
}

Void NSDevilX::NSRenderSystem::NSGL4::CTexture2D::onMessage(ITexture2DImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case ITexture2DImp::EMessage_EndArraySizeChange:
	case ITexture2DImp::EMessage_EndFormatChange:
	case ITexture2DImp::EMessage_EndMipmapChange:
	case ITexture2DImp::EMessage_EndSizeChange:
		addDirtyFlag(EDirtyFlag_Resource);
		_registerToSystemImp();
		break;
	case ITexture2DImp::EMessage_EndPixelsChange:
		addDirtyFlag(EDirtyFlag_Content);
		mDirtyContentSubTextureKeys.insert(*static_cast<UInt32*>(data));
		_registerToSystemImp();
		break;
	}
}

Void NSDevilX::NSRenderSystem::NSGL4::CTexture2D::onMessage(CSystemImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case CSystemImp::EMessage_BeginFrame:
		_update();
		break;
	}
}

Void NSDevilX::NSRenderSystem::NSGL4::CTexture2D::_update()
{
	if(hasDirtyFlag(EDirtyFlag_Resource)&&_recreateInternal())
	{
		removeDirtyFlag(EDirtyFlag_Resource);
	}
	if(hasDirtyFlag(EDirtyFlag_Content)&&_updatePixels())
	{
		removeDirtyFlag(EDirtyFlag_Content);
	}
}

Boolean NSDevilX::NSRenderSystem::NSGL4::CTexture2D::_recreateInternal()
{
	glDeleteTextures(1,&mInternal);
	CUtility::checkGLError();
	mInternal=0;
	if(getInterfaceImp()->getWidth()>0&&getInterfaceImp()->getHeight()>0)
	{
		GLint level_count=0;
		switch(getInterfaceImp()->getMipmapCount())
		{
		case 0xffffffff:
		{
			GLint row_level_count=1;
			auto width=getInterfaceImp()->getWidth();
			while(width>1)
			{
				row_level_count++;
				width/=2;
			}
			GLint col_level_count=1;
			auto height=getInterfaceImp()->getHeight();
			while(height>1)
			{
				col_level_count++;
				height/=2;
			}
			level_count=std::max<GLint>(row_level_count,col_level_count);
		}
		break;
		default:
			level_count=getInterfaceImp()->getMipmapCount()+1;
		}
		glGenTextures(1,&mInternal);
		CUtility::checkGLError();
		glTextureImage2DEXT(getInternal(),GL_TEXTURE_2D,level_count,CUtility::getInternalFormat(getInterfaceImp()->getFormat()),getInterfaceImp()->getWidth(),getInterfaceImp()->getHeight(),0,GL_RGBA,GL_UNSIGNED_BYTE,nullptr);
		CUtility::checkGLError();
		return true;
	}
	else
	{
		return false;
	}
}

Boolean NSDevilX::NSRenderSystem::NSGL4::CTexture2D::_updatePixels()
{
	if(0==getInternal())
		return false;
	Boolean ret=true;
	for(auto iter=mDirtyContentSubTextureKeys.begin();mDirtyContentSubTextureKeys.end()!=iter;)
	{
		auto sub_tex_key=*iter;
		auto sub_tex=getInterfaceImp()->getSubTextures().get(sub_tex_key);
		if(sub_tex->mRenderTargetPixels)
		{
			_updateFromRenderableSources(sub_tex);
			ret=false;
			++iter;
		}
		else
		{
			_updateFromMemorySources(sub_tex);
			iter=mDirtyContentSubTextureKeys.erase(iter);
		}
	}
	return ret;
}

Void NSDevilX::NSRenderSystem::NSGL4::CTexture2D::_updateFromMemorySources(ITexture2DImp::SSubTexture * subTexture)
{
	if(subTexture->mMemoryPixels)
	{
		GLint texture_format=0;
		glGetTextureParameteriv(getInternal(),GL_TEXTURE_IMMUTABLE_FORMAT,&texture_format);
		CUtility::checkGLError();
		switch(texture_format)
		{
		case GL_RGBA8:
			glTextureSubImage2D(getInternal(),subTexture->mMipmapLevel,0,0,subTexture->mWidth,subTexture->mHeight,GL_RGBA8,GL_UNSIGNED_INT_8_8_8_8,subTexture->mMemoryPixels);
			CUtility::checkGLError();
			break;
		case GL_COMPRESSED_RGBA_S3TC_DXT1_EXT:
		case GL_COMPRESSED_RGBA_S3TC_DXT3_EXT:
		case GL_COMPRESSED_RGBA_S3TC_DXT5_EXT:
			break;
		}
		if(getInterfaceImp()->isAutoMipmap())
		{
			glGenerateTextureMipmap(getInternal());
			CUtility::checkGLError();
		}
	}
}

Void NSDevilX::NSRenderSystem::NSGL4::CTexture2D::_updateFromRenderableSources(ITexture2DImp::SSubTexture * subTexture)
{
}