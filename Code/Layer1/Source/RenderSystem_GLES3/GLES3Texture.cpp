#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;
using namespace NSGLES3;

NSDevilX::NSRenderSystem::NSGLES3::CTexture2D::CTexture2D(ITexture2DImp * interfaceImp)
	:TInterfaceObject<ITexture2DImp>(interfaceImp)
{
	getInterfaceImp()->addListener(static_cast<TMessageReceiver<ITexture2DImp>*>(this),ITexture2DImp::EMessage_EndArraySizeChange);
	getInterfaceImp()->addListener(static_cast<TMessageReceiver<ITexture2DImp>*>(this),ITexture2DImp::EMessage_EndFormatChange);
	getInterfaceImp()->addListener(static_cast<TMessageReceiver<ITexture2DImp>*>(this),ITexture2DImp::EMessage_EndMipmapChange);
	getInterfaceImp()->addListener(static_cast<TMessageReceiver<ITexture2DImp>*>(this),ITexture2DImp::EMessage_EndPixelsChange);
	getInterfaceImp()->addListener(static_cast<TMessageReceiver<ITexture2DImp>*>(this),ITexture2DImp::EMessage_EndSizeChange);
}

NSDevilX::NSRenderSystem::NSGLES3::CTexture2D::~CTexture2D()
{
}

Void NSDevilX::NSRenderSystem::NSGLES3::CTexture2D::onMessage(ITexture2DImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
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

Void NSDevilX::NSRenderSystem::NSGLES3::CTexture2D::onMessage(CSystemImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case CSystemImp::EMessage_BeginFrame:
		_update();
		break;
	}
}

Void NSDevilX::NSRenderSystem::NSGLES3::CTexture2D::_update()
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

Boolean NSDevilX::NSRenderSystem::NSGLES3::CTexture2D::_recreateInternal()
{
	if(getInternal())
	{
		glDeleteTextures(1,&mInternal);
		CUtility::checkGLError();
		mInternal=0;
	}
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
		glBindTexture(GL_TEXTURE_2D,getInternal());
		CUtility::checkGLError();
		glTexStorage2D(GL_TEXTURE_2D,level_count,CUtility::getInternalFormat(getInterfaceImp()->getFormat()),getInterfaceImp()->getWidth(),getInterfaceImp()->getHeight());
		CUtility::checkGLError();
		glBindTexture(GL_TEXTURE_2D,0);
		CUtility::checkGLError();
		return true;
	}
	else
	{
		return false;
	}
}

Boolean NSDevilX::NSRenderSystem::NSGLES3::CTexture2D::_updatePixels()
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

Void NSDevilX::NSRenderSystem::NSGLES3::CTexture2D::_updateFromMemorySources(ITexture2DImp::SSubTexture * subTexture)
{
	if(subTexture->mMemoryPixels)
	{
		glBindTexture(GL_TEXTURE_2D,getInternal());
		CUtility::checkGLError();
		GLint texture_format=0;
		glGetTexLevelParameteriv(GL_TEXTURE_2D,0,GL_TEXTURE_INTERNAL_FORMAT,&texture_format);
		CUtility::checkGLError();
		switch(texture_format)
		{
		case GL_R8:
			glTexSubImage2D(GL_TEXTURE_2D,subTexture->mMipmapLevel,0,0,subTexture->mWidth,subTexture->mHeight,GL_RED,GL_UNSIGNED_BYTE,subTexture->mMemoryPixels);
			CUtility::checkGLError();
			break;
		case GL_RGBA8:
			glTexSubImage2D(GL_TEXTURE_2D,subTexture->mMipmapLevel,0,0,subTexture->mWidth,subTexture->mHeight,GL_RGBA,GL_UNSIGNED_INT,subTexture->mMemoryPixels);
			CUtility::checkGLError();
			break;
		default:
			assert(0);
		}
		if(getInterfaceImp()->isAutoMipmap())
		{
			glGenerateMipmap(GL_TEXTURE_2D);
			CUtility::checkGLError();
		}
		glBindTexture(GL_TEXTURE_2D,0);
		CUtility::checkGLError();
	}
}

Void NSDevilX::NSRenderSystem::NSGLES3::CTexture2D::_updateFromRenderableSources(ITexture2DImp::SSubTexture * subTexture)
{
}